#include "planet.h"
#include <stdlib.h>
#include <string.h>

int curr_planet_id = 0;
const double G = 6.67384e-11;     //gravitational constant
#ifdef _DT
const double dt = _DT;            //time step (lower for more accuracy)
#else
const double dt = 60;
#endif

planet* new_planet(char* name, double pos[static 3], double vel[static 3], double mass)
{
    planet* ptr = malloc(sizeof(planet));

    //ptr->id = curr_planet_id++; //increment id each time

    //set name, mass, position, and velocity
    ptr->name = malloc((strlen(name) + 1) * sizeof(char));

    for (int i = 0; i < strlen(name); i++)
    {
        //ptr->name[i] = ' '; //I have no clue why this needs to be here but it fixes a bug
        ptr->name[i] = name[i];
    }
    ptr->name[strlen(name)] = '\0';

    ptr->pos = malloc(3 * sizeof(double));
    ptr->vel = malloc(3 * sizeof(double));

    for (int i = 0; i < 3; i++)
    {
        ptr->pos[i] = pos[i];
        ptr->vel[i] = vel[i];
    }

    ptr->mass = mass;

    return ptr;
}

/*
 * Magnitude-squared of a vector (faster than magnitude)
 */
double magnitude2(double vec[3])
{
    double mag = 0.0;
    for (int i = 0; i < 3; i++)
    {
        mag += vec[i] * vec[i];
    }
    return mag;
}

/*
 * Magnitude of a vector
 */
double magnitude(double vec[3])
{
    double mag = 0.0;
    for (int i = 0; i < 3; i++)
    {
        mag += vec[i] * vec[i];
    }
    return sqrt(mag);
}

/**
 * Calculates the force on planet1 due to planet2
 *
 * By Newton's law of gravitation:
 *
 * F_{1,2} = G*m1*m2/|r|^2 * unit_r = G*m1*m2/|r|^3 * unit_r
 *
 * with r = pos2 - pos1 and |r| is magnitude of r
 *
 * Results are stored in force (since C cannot safely return arrays)
 *
 *
 *
 */
void add_force_vector(planet* planet1, planet* planet2, double force[3])
{
    double r[3] = { 0.0, 0.0, 0.0 };
    //double F = {0.0, 0.0, 0.0};

    //calculate r
    for (int i = 0; i < 3; i++)
    {
        r[i] = planet2->pos[i] - planet1->pos[i];
    }

    //find |r|^2
    double mag_r = magnitude(r);
    double r3 = mag_r * mag_r * mag_r;

    //find F given Newton's equation
    double Gm1m2r2 = G * planet1->mass * planet2->mass / r3;

    for (int i = 0; i < 3; i++)
    {
        //add the force to the vector passed
        force[i] += Gm1m2r2 * r[i];
    }
}

/*
 * Uses Euler's method to update the planet given a net force, overriding dt
 */
void update_planet_dt(planet* planet, double net_force[3], double dt)
{
    for (int i = 0; i < 3; i++)
    {
        //calculations
        double curr_vel = planet->vel[i];
        double new_vel = curr_vel + dt * (net_force[i] / planet->mass);
        double avg_vel = (curr_vel + new_vel) / 2.0; //the average velocity over the time step

        planet->pos[i] += dt * avg_vel;
        planet->vel[i] = new_vel;
    }
}

/*
 * Uses Euler's method to update the planet given a net force, defualt dt
 */
void update_planet(planet* planet, double net_force[3])
{
    update_planet_dt(planet, net_force, dt);
}

void free_planet(planet* planet)
{
    free(planet->name);
    free(planet->pos);
    free(planet->vel);
    free(planet);
}
