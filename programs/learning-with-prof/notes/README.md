# What I learned:

> I Learned how to use `cmake` with `cmake ..` command and also for optimized `cmake .. -DCMAKE_BUILD_TYPE=Release`
>
> Then using `objdump -d -Mintel main > <filename>` allows me to see the assembly code for the program.

# How to build your own, and test with assembly:
> go inside of the `/build` directory and run `cmake ..` then you will be able to run `objdump -d -Mintel main > <filename>` to see the asm dump that you wish. 



stack adds all variables to the stack, and requires 8mb on the stack

`virtualAlloc function` -> for windows based virtual memory [see]()
`mmap function` -> for unix based virtual memory [see]()
