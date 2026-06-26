# `run.sh` — How It Works (a Bash learning guide)

This walks through every piece of `run.sh` so you can understand *why* each line
is there, not just *what* it does. Read it top to bottom alongside the script.

---

## 1. The header

```bash
#!/bin/bash
set -euo pipefail
```

- `#!/bin/bash` — the **shebang**. Tells the OS "run this file with `/bin/bash`".
  It only matters when you execute the file directly (`./run.sh`), not when you
  do `bash run.sh`.
- `set -euo pipefail` — turns on strict mode. This is the single most useful
  habit in Bash. It is three flags at once:
  - `-e` — **exit on error.** If any command returns non-zero (fails), the
    script stops instead of blindly marching on.
  - `-u` — **error on undefined variable.** Using `$foo` when `foo` was never
    set is now a hard error instead of silently expanding to an empty string.
  - `-o pipefail` — in a pipe like `a | b`, the pipeline's exit code is the
    *first failing* command's, not just the last one's. Without this, `false |
    true` would look like success.

Why care? Without strict mode, a typo'd variable or a failed `mkdir` keeps
going and you debug a mystery later. With it, the script fails loudly at the
real cause.

---

## 2. Finding the repo root

```bash
ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
CXX_FLAGS=(-pthread -std=c++20 -Wall -Wextra)
```

- `${BASH_SOURCE[0]}` — the path to *this script file* (works better than `$0`).
- `dirname ...` — strips the filename, leaving the directory.
- `cd ... && pwd` — go into that directory and print its **absolute** path.
- The whole thing in `$( ... )` is **command substitution**: run the command,
  capture its stdout as a string.

Result: `ROOT` is the absolute path to the folder holding `run.sh`, *no matter
where you call the script from*. That is why `./run.sh output` works from any
directory — every path below is built from `$ROOT`.

- `CXX_FLAGS=(...)` — a Bash **array**. Arrays keep each flag as a separate
  element so spaces never get mangled. Later we expand it with
  `"${CXX_FLAGS[@]}"` (more on the quoting in §7).

---

## 3. `border` — drawing the box

```bash
border() {
  local number="$1"
  local isTop="$2"
  ...
}
```

- `border() { ... }` — defines a **function**.
- `local number="$1"` — `$1` is the first argument passed to the function.
  `local` keeps the variable scoped to this function so it does not leak into
  the rest of the script. **Always use `local` inside functions.**

```bash
  for ((i = 0; i <= number; i++)); do
    case $i in
      0)       echo -n "$l" ;;
      $number) echo -n "$r" ;;
      *)       echo -n "═" ;;
    esac
  done
```

- `for (( ... ))` — C-style arithmetic loop (Bash specific).
- `case $i in ... esac` — like a `switch`. Patterns end with `)`, each branch
  ends with `;;`, and `*)` is the default (catch-all).
- `echo -n` — print **without** a trailing newline, so the characters sit on
  one line to form the bar.
- `$l` / `$r` are the left/right corner characters chosen by the top/bottom
  `case` above.

---

## 4. `listPrograms` — auto-discovering every program

```bash
  while IFS= read -r src; do
    ...
  done < <(find "$ROOT" -path '*/code/*.cpp' -not -path '*/out/*' | sort)
```

This is the most important idiom in the script. Read it inside-out:

- `find "$ROOT" -path '*/code/*.cpp' -not -path '*/out/*'` — search the tree for
  any file matching `.../code/*.cpp`, **excluding** the compiled binaries under
  `out/`. This is what makes the script "deterministic structure" aware: drop a
  new `.cpp` in any `wk*/code/`, and it shows up automatically — no editing.
- `| sort` — alphabetize.
- `< <( ... )` — **process substitution**. The `<( ... )` part turns a
  command's output into something that looks like a file; the outer `<` feeds
  that "file" into the `while` loop as its input.
  - Why not `find ... | while ...`? Because a pipe runs the `while` in a
    **subshell**, so any variable you set inside (like `last`) would be lost
    when the loop ends. Process substitution keeps the loop in the main shell.
- `while IFS= read -r src` — the canonical safe way to read lines:
  - `IFS=` — don't trim leading/trailing whitespace.
  - `-r` — don't treat backslashes as escapes.
  - `src` — each line (a file path) lands in this variable.

```bash
    week="$(sed -E 's#.*/(wk[0-9]+)/code/.*#\1#' <<<"$src")"
```

- `sed -E '...'` — stream editor with extended regex. The pattern captures the
  `wk<number>` piece of the path and replaces the whole line with just it
  (`\1` = first captured group). We use `#` as the delimiter instead of `/` so
  the slashes in the path don't clash.
- `<<<"$src"` — a **here-string**: feed the string `$src` to `sed` as stdin.

The `if [[ $week != "$last" ]]` block just prints the `[wk1]` header once per
week, then lists each program with `basename "$src" .cpp` (strips the directory
and the `.cpp` extension).

---

## 5. `build_and_run` — compile then execute

```bash
build_and_run() {
  local src="$1"
  local name outdir bin
  name="$(basename "$src" .cpp)"
  outdir="$(dirname "$src")/out"
  bin="$outdir/$name"
  mkdir -p "$outdir"
  g++ "${CXX_FLAGS[@]}" -o "$bin" "$src"
  "$bin"
}
```

- `basename "$src" .cpp` → `random.cpp` becomes `random`.
- `dirname "$src"` → the folder the source lives in; we append `/out`.
- `mkdir -p "$outdir"` — `-p` means "create parents as needed, and don't error
  if it already exists." Safe to run every time.
- `g++ "${CXX_FLAGS[@]}" -o "$bin" "$src"` — compile. The flags array expands
  into separate words here.
- `"$bin"` — run the compiled binary. Quoted in case the path has spaces.

This is generic: it works for *any* `.cpp` path you hand it, which is what let
us delete the old per-program `case` statement.

---

## 6. `resolve` — turn a tag into a file path

```bash
resolve() {
  local week_filter="$1" tag="$2"
  local pattern
  if [[ -n $week_filter ]]; then
    pattern="*/$week_filter/code/$tag.cpp"
  else
    pattern="*/code/$tag.cpp"
  fi
  find "$ROOT" -path "$pattern" -not -path '*/out/*'
}
```

- `[[ -n $week_filter ]]` — `-n` tests "string is non-empty". So: if a week was
  given, narrow the search to that week; otherwise search all weeks.
- Returns (prints) the matching path(s). The caller captures them.

`[[ ... ]]` is Bash's test command. Prefer it over the older `[ ... ]` — it is
safer with empty variables and supports `&&`, `||`, and pattern matching.

---

## 7. `make_module` — scaffolding a new week

```bash
  if [[ ! $week =~ ^wk[0-9]+$ ]]; then
    echo "Bad week ..." >&2
    exit 1
  fi
```

- `=~` — **regex match** inside `[[ ]]`. `^wk[0-9]+$` means "starts with `wk`,
  then one or more digits, then end." This rejects `make foo` or `make week2`.
- `>&2` — redirect this `echo` to **stderr** (file descriptor 2) instead of
  stdout. Error messages belong on stderr so they don't pollute piped output.
- `exit 1` — non-zero exit = failure (so callers/CI know it broke).

```bash
  if [[ -d $dir ]]; then
    echo "... refusing to clobber." >&2
    exit 1
  fi
```

- `-d $dir` — "is this a directory that exists?" If yes, bail out instead of
  overwriting your work. Defensive scripting: never destroy without checking.

```bash
  mkdir -p "$dir/code/out" "$dir/notes"
  cat >"$notes" <<EOF
#import "../../typst-lib/lib.typ": colorCode, reflectionCard;
...
EOF
```

- `cat >"$notes" <<EOF ... EOF` — a **heredoc**. Everything between `<<EOF` and
  the closing `EOF` is written to the file (`>` truncates/creates it). Variables
  like `$week` are expanded inside, which is how `wk2 Notes` gets filled in.
  - Tip: if you ever want the text *verbatim* with no `$` expansion, quote the
    marker: `<<'EOF'`.

---

## 8. `main` — the dispatcher

```bash
  case "${1:-}" in
    "--h" | "-h" | "--help" | "")
      displayHelp; exit 0 ;;
    "--list" | "--ls")
      listPrograms; exit 0 ;;
    "--make" | "--mk")
      make_module "${2:-}"; exit 0 ;;
  esac
```

- `"${1:-}"` — **parameter expansion with a default.** `${1:-}` means "the value
  of `$1`, or empty string if it is unset." Needed because `set -u` would
  otherwise crash on a missing `$1`. The empty-string pattern `""` is how
  `./run.sh` with no args lands on help.
- `|` inside a `case` pattern means "or" — multiple aliases share one branch.

```bash
  if [[ $# -ge 2 && $1 =~ ^wk[0-9]+$ ]]; then
    week="$1"; tag="$2"
  else
    tag="$1"
  fi
```

- `$#` — the **number of arguments**. `-ge 2` = "two or more". So `./run.sh wk2
  random` is parsed as (week=wk2, tag=random), while `./run.sh random` is just
  (tag=random).

```bash
  if [[ $(wc -l <<<"$matches") -gt 1 ]]; then
    ... ambiguous: list weeks, tell user to disambiguate ...
  fi
  build_and_run "$matches"
```

- `wc -l <<<"$matches"` — count lines. More than one line means the same tag
  exists in multiple weeks, so we refuse and explain rather than guess wrong.

```bash
main "$@"
```

- The last line **actually runs** `main`, passing along every argument.
- `"$@"` — expands to all arguments, each properly quoted as a separate word.
  This is different from `$*` (which joins them into one string). **Use `"$@"`
  to forward arguments** — it is almost always what you want.

---

## Cheat sheet of the idioms used

| Idiom | Meaning |
|---|---|
| `set -euo pipefail` | strict mode: fail fast, no silent bugs |
| `local x` | function-scoped variable |
| `$( cmd )` | command substitution (capture output) |
| `<( cmd )` | process substitution (output as a fake file) |
| `<<<"str"` | here-string (feed a string as stdin) |
| `<<EOF ... EOF` | heredoc (multi-line text into a file/command) |
| `"$@"` | all args, each quoted separately |
| `${1:-}` | `$1` or default if unset |
| `[[ -n s ]]` / `[[ -d p ]]` / `[[ -z s ]]` | non-empty / dir-exists / empty tests |
| `[[ s =~ re ]]` | regex match |
| `>&2` | write to stderr |
| `arr=(a b)` / `"${arr[@]}"` | array / expand each element safely |
| `$#` | argument count |

---

## Golden rule: **quote your variables**

You'll notice almost every `$var` is written `"$var"`. Unquoted variables get
**word-split** (broken on spaces) and **glob-expanded** (a `*` turns into
filenames). Quoting prevents both. When in doubt, quote.
