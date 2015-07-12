/*
 * universe.h
 *
 *    The Universe
 *
 *  Created on: Jun 16, 2015
 *      Author: david
 */

#ifndef UNIVERSE_H_
#define UNIVERSE_H_

#include <stdlib.h>
#include "planet.h"
#include "list.h"

static const double AU = 1.496e11; //one astronomical unit (in meters)
extern double dt;

typedef struct universe
{
    array_list* planet_list;

} universe;

universe* new_universe();
void add_planet(universe* universe, planet* planet);
void universe_update_euler(universe* universe);
void universe_update_midpoint(universe* universe);
void free_universe(universe* universe);

#endif /* UNIVERSE_H_ */
