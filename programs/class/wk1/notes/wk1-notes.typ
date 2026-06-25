#import "../../typst-lib/lib.typ": colorCode, reflectionCard;

#let textColors = (
  background: rgb(245, 245, 245),
  text: rgb(0, 0, 0),
)

#let data = ((
  reflectionTitle: "What I learned about random numbers",
  reflectionSubContent: [

  ```cpp
  #include <iostream>
  #include <cstdlib>


  int main() {
    int n = rand(); // why is this the same number every re-compile?

    std::cout << "Your random number: " << n << std::endl;
    std::cout << "Random Max: " << RAND_MAX << std::endl;
    std::cout << "Real Random generated: [1] " << (rand() % 10) << std::endl;
    std::cout << "Real Random generated: [2] " << (rand() % 10) << std::endl;
    std::cout << "Real Random generated: [3] " << (rand() % 10) << std::endl;
    return 0;
  }
  ```

  #align(left)[
    what I've learned is that, `rand()` is not so random when assigned to a variable.

    lol... what I mean is doing: `int n = rand();` - whatever that value for `n` is that shit is going to stay that value #emph[***every***] re-compile.

    however, an interesing thing is when we look at: 
  ]

  ```cpp
  std::cout << (rand() % 10) << std::endl;
  // hell even when we just do...
  std::cout << (rand()) << std::endl // it will be a random number
  ```

  #align(left)[ So what I'm implying is rand() is not so weird, but it's not truly a random number generator?]

  ]),
  (
    reflectionTitle: "Another Example",
    reflectionSubContent: [
      shiver me timbers
    ]
  )
);

= Random Numbers Notes



#let firstData = data.at(0);
#let secondData = data.at(1);



// okay so waht I'm noticing... this is goign to be a repetative process so I'm going to make a implementation for this to just be in one place.

#reflectionCard("Random Numbers", data: firstData, 1)
#reflectionCard("", data: secondData, 2)



//#reflectionCard("Random", data: secondData, 2)





// use for later :)
#let realData = data.flatten();
#let titles = realData.map(data => data.reflectionTitle)

