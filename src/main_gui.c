/*
 * main_gui.c
 *
 *
 * Main code for GUI for N-Body
 *
 *  Created on: Jun 16, 2015
 *      Author: David Etler
 */

#define _DT 60  /*Defualt timestep*/

#include <stdint.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "planet.h"
#include "universe.h"
#include "gui.h"
#include "parse.h"


static universe* my_universe;                                   //pointer to the universe
static int error = 0;                                           //remains 0 if no error
double SCALE = 2.0;                                             //scale to draw universe at (number of AU)
int SPEEDUP = 500000;                                           //how many times faster than realtime to run the simulation
char* universe_fname;                                           //name of the universe file (null for no file)
double dt = 1;                                                  //timestep
void (*update_function)(universe*) = &universe_update_midpoint; //pointer to the universe's update function


/*
 * Cleans up
 */
void cleanup(void);


int main(int argc, char* argv[])
{
    my_universe = new_universe();
    atexit(cleanup);

    if (argc == 1)
    {
        //default system

        planet* my_planet;

        my_planet = new_planet("Earth", (double[3]) { 1.52e11, 0.0, 0.0 }, (double[3]) { 0.0, 29316, 0.0 }, 5.972e24);
        add_planet(my_universe, my_planet);

        my_planet = new_planet("Sun", (double[3]) { 0.0, 0.0, 0.0 }, (double[3]) { 0.0, 0.0, 0.0 }, 1.988435e30);
        add_planet(my_universe, my_planet);
    }
    else
    {
        //parse the args passed on the command line

        parse_args(argc, argv);

        printf("Opening file: %s\n", universe_fname);
        int p = parse_universe(my_universe, universe_fname);
        error = 1;
        if(p != 0)
        {
            //catch errors
            free_universe(my_universe);
            if(p == -1)
            {
                printf("Error: planet file (%s) malformed, aborting.\n", universe_fname);
                return 1;
            }
            if(p == -2)
            {
                printf("Error: planet file (%s) not found, aborting.\n", universe_fname);
                return 1;
            }
        }
    }

    //gui stuff
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(WINDOW_HEIGHT, WINDOW_WIDTH);
    glutInitWindowPosition(200, 200);
    glutCreateWindow("N-Body Simulator");
    inialize_gui(my_universe);
    glutDisplayFunc(loop);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);
    glutMainLoop();

    return 0;
}


void cleanup(void)
{
    if(error == 0)
    {
        free_universe(my_universe);
    }
}
