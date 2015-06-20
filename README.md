# N-Body: a Lightweight N-Body Simulator

This is n-body simulator I'm currently writing in C. It solves the n-body system
numerically using the midpoint formula and Newton's law of universal 
gravitation.

# How to Use

## Cloning

You can clone the repository with 
`git clone https://github.com/davidretler/N-Body.git`.

## Building
To build, type `gcc main.c -lm -g -std=gnu99`

## Running

To run, `./a.out > data.csv`

## Output

The program will write to a `.csv' file that contains on each row the following data:

    Planet_1_ID, pos_1, pos_2, pos_3, Planet_2_ID, pos_1, pos_2, pos_3,...
    
with successive rows representing different points in time. Currently I have not
written a script to plot the data. I suggest viewing the data in either
LibreOffice Calc or Microsoft Excel.

# Features to Add

I will be attempting to add the following features:

* Allow for custom lists of bodies
* Script to plot output


  
