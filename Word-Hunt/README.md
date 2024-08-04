
# Word Hunt Solver
If you find that you can't win at Word Hunt, no matter how hard you try, take this out for a spin. Just open up the GUI, type in the letters in the grid, and click "Generate Answers". 



## ⚠️IMPORTANT⚠️

If you don't have all your words in your wordList.txt file as ALL CAPS, you WILL GET A SEGMENT FAULT. I should probably change this, but it would effect the time it takes to run and I really don't want to sit down and code anymore. I spent too long on this project...


## Compiling
Inorder to compile the program succesfully, I would reccommend using the cross-compiler on Linux to build for windows.
```console
~$ x86_64-w64-mingw32-gcc -o WordHunt.exe wordHuntSolver3.c
```