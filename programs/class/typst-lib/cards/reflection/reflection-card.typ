#let reflectionCard(title, data: (:), count) = {

let myContent = [Reflection Note: #count]
  box(fill: rgb(245, 245, 245), inset: 16pt, radius: 8pt, width: 100%)[
    #text(size: 16pt, weight: "bold", fill: rgb(0, 0, 0), [#align(left, emph[#text(size: 6pt, weight: "bold", fill: rgb(0, 0, 0), myContent) #h(1fr) #title])])
    #align(center, emph[#text(size: 8pt, weight: "bold", fill: rgb(0, 0, 0), data.reflectionTitle)])
    #align(center)[
      #v(1em)
      #align(center, text(size: 10pt, fill: rgb(0, 0, 0), data.reflectionSubContent))
    ]
  ]
}
