## Project-Leaf
A project carried out as the semester project for the fulfillment of university curriculum.  

## Language: 
C++, Compiler: MinGW 

## Library: 
graphics.h and other default c++ libraries 
### graphics.h Setup:
* download the graphics.h, libbgi.a and winbgim.h
* inside MinGW>>include>> add graphics.h and winbgim.h
* inside MinGW>>lib>> add libbgi.a
* Add the linker: -lbgi -lgdi32 -lcomdlg32 -luuid -loleaut32 -lole32
* In codeblocks: Settings>> Compiler>> Linker Settings>> other link options: add the linker

## File hierarchy:
* Place the folder User_Data in C Drive. 
* **generalfunction.h** and **AllProjectModules.h** should be in the same directory with **leaf.cpp**
