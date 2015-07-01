/*
 * main.c
 *
 *  Created on: Jun 16, 2015
 *      Author: David Etler
 */


#define _N_STEPS 365*5
#define _DT 60*60*24
#define _DELIMITER ','

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "planet.h"
#include "universe.h"
#include "parse.h"


int main(int argc, char* argv[])
{
    universe* my_universe = new_universe();

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

    for (int n = 0; n < _N_STEPS; n++)
    {
        //don't clutter the output with 1000s of lines of information
        //make number smaller for more verbose output
        if (n % 1 == 0)
        {
            //print info for all planets (csv)
            for (int i = 0; i < my_universe->planet_list->length; i++)
            {
                if (i != 0)
                {
                    printf("%c", _DELIMITER);
                }
                printf("%s", my_universe->planet_list->list_address[i]->name);
                for (int j = 0; j < 3; j++)
                {
                    printf("%c%f", _DELIMITER, my_universe->planet_list->list_address[i]->pos[j] / AU);
                }
            }
            printf("\n");
        }
        universe_update_midpoint(my_universe);
    }

    free_universe(my_universe);

    return 0;
}
