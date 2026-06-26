#!/bin/bash
## Author: { TuringProblem } : @15:34 20260626
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
CXX_FLAGS=(-pthread -std=c++20 -Wall -Wextra)

border() {
  local number="$1" # width
  local isTop="$2"   # true=top, else bottom
  local l r
  case $isTop in
    true) l="╔"; r="╗" ;;
    *)    l="╚"; r="╝" ;;
  esac
  for ((i = 0; i <= number; i++)); do
    case $i in
      0)       echo -n "$l" ;;
      $number) echo -n "$r" ;;
      *)       echo -n "═" ;;
    esac
  done
  [[ $isTop == true ]] && echo || echo
}

listPrograms() {
  border 75 true
  echo -e "\n Available programs (./run.sh <tag>):\n"
  local week last=""
  while IFS= read -r src; do
    week="$(sed -E 's#.*/(wk[0-9]+)/code/.*#\1#' <<<"$src")"
    if [[ $week != "$last" ]]; then
      echo "  [$week]"
      last="$week"
    fi
    echo "    - $(basename "$src" .cpp)"
  done < <(find "$ROOT" -path '*/code/*.cpp' -not -path '*/out/*' | sort)
  echo
  border 75 false
}

displayHelp() {
  border 75 true
  echo -e "\n ./run.sh <tag>          compile & run wk*/code/<tag>.cpp"
  echo -e " ./run.sh <wk> <tag>     disambiguate when <tag> exists in many weeks"
  echo -e " ./run.sh --make <wk>    scaffold wk<N>/{code/out,notes} + notes.typ"
  echo -e " ./run.sh --list         list all programs"
  echo -e " ./run.sh --h            this help"
  border 75 false
}

makeModule() {
  local week="$1"
  if [[ ! $week =~ ^wk[0-9]+$ ]]; then
    echo "Bad week '$week'. Format: wk<number> (e.g. wk2)" >&2
    exit 1
  fi
  local dir="$ROOT/$week"
  if [[ -d $dir ]]; then
    echo "$week already exists at $dir — refusing to clobber." >&2
    exit 1
  fi
  local notes="$dir/notes/$week-notes.typ"
  mkdir -p "$dir/code/out" "$dir/notes"
  cat >"$notes" <<EOF
#import "../../typst-lib/lib.typ": colorCode, reflectionCard;

#let data = (
  reflectionTitle: "What I learned this week",
  reflectionSubContent: [
    TODO
  ],
);

= $week Notes

#reflectionCard("$week", data: data, 1)
EOF
  echo "✔ created $week:"
  echo "    $week/code/out/"
  echo "    $notes"
}

buildAndRun() {
  local src="$1"
  local name outdir bin
  name="$(basename "$src" .cpp)"
  outdir="$(dirname "$src")/out"
  bin="$outdir/$name"
  mkdir -p "$outdir"
  echo "▶ compiling $src"
  g++ "${CXX_FLAGS[@]}" -o "$bin" "$src"
  echo "▶ running $bin"
  echo "──────────────────────────────────────"
  "$bin"
}

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

main() {
  case "${1:-}" in
    "--h" | "-h" | "--help" | "")
      displayHelp; exit 0 ;;
    "--list" | "--ls")
      listPrograms; exit 0 ;;
    "--make" | "--mk")
      makeModule "${2:-}"; exit 0 ;;
  esac

  local week="" tag
  # Two-arg form: ./run.sh wk2 random
  if [[ $# -ge 2 && $1 =~ ^wk[0-9]+$ ]]; then
    week="$1"; tag="$2"
  else
    tag="$1"
  fi

  local matches
  matches="$(resolve "$week" "$tag")"

  if [[ -z $matches ]]; then
    echo "No program '$tag'${week:+ in $week}. Use ./run.sh --list" >&2
    exit 1
  fi

  if [[ $(wc -l <<<"$matches") -gt 1 ]]; then
    echo "Ambiguous tag '$tag' — found in multiple weeks:" >&2
    while IFS= read -r m; do
      echo "  $(sed -E 's#.*/(wk[0-9]+)/.*#\1#' <<<"$m")" >&2
    done <<<"$matches"
    echo "Disambiguate: ./run.sh <wk> $tag" >&2
    exit 1
  fi

  buildAndRun "$matches"
}

main "$@"
