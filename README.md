# N-Body: a Lightweight N-Body Simulator

This is n-body simulator I'm currently writing in C. It solves the n-body system
numerically using the midpoint formula and Newton's law of universal 
gravitation.

# How to Use

## Cloning

You can clone the repository with 
`git clone https://github.com/davidretler/N-Body.git`.

## Building
To build the cli version use

    make cli
    ./nbody > data.csv
    
TO build the GUI version use

    make gui
    ./nbody-gui

## Running

You can run the program using a custom list of bodies by typing `./nbody planets` where `planets` is a properly-formatted file containg planet data.

Note that the gui version is likely only to run on Unix systems. GLUT is is required to build and run the gui version.

## Output

The program will write to a `.csv` file that contains on each row the following data:

    Planet_1_ID, pos_1, pos_2, pos_3, Planet_2_ID, pos_1, pos_2, pos_3,...
    
with successive rows representing different points in time. Currently I have not
written a script to plot the data. I suggest viewing the data in either
LibreOffice Calc or Microsoft Excel.

## Planet list

If you make a file called `planets` which contains initial planetary data, run the program with `./a.out /path/to/planets` and the program will initialize the universe with that data. Each body should have a it's own line formatted as:

    NAME,POS_1,POS_2,POS_3,VEL_1,VEL_2,VEL_3,MASS
    
For example, to add the Earth and the Sun:

    Earth,1.52e11,0,0,0,29316,0,5.972e24
    Sun,0,0,0,0,0,0.0,1.988435e30

Note that the numerical value of every quantity is given in SI (MKS) units.

# Features to Add

I will be attempting to add the following features:

* Allow for custom lists of bodies [✓]
* Script to plot output
* 

# Current Issues

* The sun appears to be slowing drifting from the center, but only when using the midpoint algorithm (which *should* be more accurate)


  
