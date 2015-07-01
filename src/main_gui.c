/*
 * main_gui.c
 *
 *
 * Main code for GUI for N-Body
 *
 *  Created on: Jun 16, 2015
 *      Author: David Etler
 */

#define _N_STEPS 365*5
#define _DT 60
#define _DELIMITER ','

#include <stdint.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "planet.h"
#include "universe.h"
#include "gui.h"
#include "parse.h"

static universe* my_universe;
static int error = 0; //remains 0 if no error

/**
 * Cleans up
 */
void cleanup(void);


int main(int argc, char* argv[])
{
    my_universe = new_universe();
    atexit(cleanup);

    //load either the default system or the system stored in the file, depending on the argument
    if (argc == 1)
    {
        //default system

        planet* my_planet;

        my_planet = new_planet("Earth", (double[3] ) { 1.52e11, 0.0, 0.0 }, (double[3] ) { 0.0, 29316, 0.0 }, 5.972e24);
        add_planet(my_universe, my_planet);

        my_planet = new_planet("Sun", (double[3] ) { 0.0, 0.0, 0.0 }, (double[3] ) { 0.0, 0.0, 0.0 }, 1.988435e30);
        add_planet(my_universe, my_planet);
    }
    else
    {
        //load saved system
        int p = parse_universe(my_universe, argv[1]);
        error = 1;
        if(p != 0)
        {
            //catch errors
            free_universe(my_universe);
            if(p == -1)
            {
                printf("Error: planet file malformed, aborting.\n");
                return 1;
            }
            if(p == -2)
            {
                printf("Error: planet file not found, aborting.\n");
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
