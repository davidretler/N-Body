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
extern double dt;                        //time step (lower for more accuracy)

#include <math.h>
#include <stdlib.h>
#include <string.h>

typedef struct planet
{
    double* pos;              //position vector
    double* vel;              //velocity vector
    double mass;              //planets mass
    int id;                   //id number
    char* name;               //planent's name
    unsigned char color[3];   //planet's color
    double mass_log10;        //log10 of mass, for scaling the radius when drawing
                                //(extra memory for a double is far better than the wasting cycles calculating this every frame)
} planet;

planet* new_planet(char* name, double pos[static 3], double vel[static 3], double mass);
planet* new_planet_color(char* name, double pos[static 3], double vel[static 3], double mass, unsigned char the_color[static 3]);
double magnitude2(double vec[3]);
double magnitude2(double vec[3]);
double magnitude(double vec[3]);
void add_force_vector(planet* planet1, planet* planet2, double force[3]);
void update_planet_dt(planet* planet, double net_force[3], double dt);
void update_planet(planet* planet, double net_force[3]);
void free_planet(planet* planet);

#endif /* PLANENT_H_ */
