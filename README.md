# Convex Hull
Member Names: Matthew Tibbitts, Beckett Maestas, Jacob Ly. 

1: Implement the graham's scan algorithm
2: Read a set of points from a file
3: Find a way to save a visualization
    a: can generate a DOT file
    
Summary:

This project is about the C++ implementation of Convex Hull by using Graham's Scan Algorithm to find the convex hull of a given set of points. 
Then display if onto SFML application.
![image](https://user-images.githubusercontent.com/98777321/205776188-b49cb789-a2cf-42a3-9314-154c0dd65038.png)



Features:
- get Visual Studio or any other C++ IDLE downloaded (compatible with SFML)
- SFML application https://www.sfml-dev.org/download.php 


Inputs:

- text file

Outputs:

- Screen shott
- SFML display


How to compile:

First the user must install SFML

Installing SFML:

Step1: Install Git (if not already done so)

If git had not been installed add to path

C:\Program Files\Git\cmd\

C:\Program Files\Git\bin\		

Step2: Use command:

git clone https://github.com/Microsoft/vcpkg.git

Step3: once installed run:

.\vcpkg\bootstrap-vcpkg.bat

Step4: Add vcpkg to path with the file destination

Step5: download sfml:

Vcpkg install sfml:x86-windows

Step6: lastly use:

vcpkg integrate install

And SFML will be fully usable!

Now to run the program do:

g++ -c main.cpp

g++ main.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio 

./sfml-app

When in the interface itself, you will begin in drawmode. This mode allows you to draw points and greate your own convex hull. If this becomes uninteresting,
you can hit the backspace key (may take a couple tries). Then just type the filename of one of the .txt files in this folder WITHOUT the .txt, and the dislplay will begin drawing the convex hull of the selected data set.
