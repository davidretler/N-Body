/*
 * planent.h
 * Header file for planet structures
 *
 *  Created on: Jun 16, 2015
 *      Author: David Etler
 */

#ifndef PLANENT_H_
#define PLANENT_H_

static const double G = 6.67384e-11;     //gravitational constant
#ifdef _DT
static const double dt = _DT;            //time step (lower for more accuracy)
#else
static const double dt = 60;
#endif

#include <math.h>

typedef struct planet
{
    double* pos;           //position vector
    double* vel;           //velocity vector
    double mass;           //planets mass
    int id;                //id number
    char* name;            //planent's name
} planet;

planet* new_planet(char* name, double pos[static 3], double vel[static 3], double mass);
double magnitude2(double vec[3]);
double magnitude2(double vec[3]);
double magnitude(double vec[3]);
void add_force_vector(planet* planet1, planet* planet2, double force[3]);
void update_planet_dt(planet* planet, double net_force[3], double dt);
void update_planet(planet* planet, double net_force[3]);
void free_planet(planet* planet);

#endif /* PLANENT_H_ */
