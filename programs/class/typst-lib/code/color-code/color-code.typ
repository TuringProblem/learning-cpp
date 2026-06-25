#let colorCode(codeBlock, color: (:)) = {
  box(fill: color.background, outset: 2pt, radius: 2pt, text(color: color.text, codeBlock))
}
