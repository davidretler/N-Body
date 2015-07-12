#include "universe.h"

/*
 * Initialize a new universe
 */
universe* new_universe()
{
    universe* universe = malloc(sizeof(universe));

    //create an empty list to store the planets
    universe->planet_list = malloc(sizeof(array_list));
    init_list(universe->planet_list);

    return universe;
}

/*
 * Adds a planet to the universe
 */
void add_planet(universe* universe, planet* planet)
{
    list_add(universe->planet_list, planet);
}

/*
 * Updates the universe, one planet at a time, using Euler's method
 */
void universe_update_euler(universe* universe)
{
    //array to store net forces
    double net_forces[universe->planet_list->length][3];

    //for each planet in universe
    for (int curr_planet = 0; curr_planet < universe->planet_list->length; curr_planet++)
    {
        double net_force[3];

        //for every other planet, add to net force
        for (int other_planet = 0; other_planet < universe->planet_list->length; other_planet++)
        {
            if (curr_planet != other_planet)
            {
                add_force_vector(universe->planet_list->list_address[curr_planet], universe->planet_list->list_address[other_planet], net_force);
            }
        }
        //save net force
        for (int i = 0; i < 3; i++)
        {
            net_forces[curr_planet][i] = net_force[i];
        }
    }

    for (int i = 0; i < universe->planet_list->length; i++)
    {
        update_planet(universe->planet_list->list_address[i], net_forces[i]);
    }

}

/*
 * Updates the universe using the midpoint method.
 *
 * First update the universe by dt/2 using Euler's method
 * Then this universe to find the net force after dt/2
 * Revert to the back to it's orignal state, and then update the universe
 *     over the time interval dt using the net force from dt/2
 */
void universe_update_midpoint(universe* universe)
{
    //allocate memory to store initial net force and initial pos/vel
    double net_forces[universe->planet_list->length][3];
    double old_pos[universe->planet_list->length][3];
    double old_vel[universe->planet_list->length][3];

    //calculate initial net force
    for (int curr_planet = 0; curr_planet < universe->planet_list->length; curr_planet++)
    {
        double net_force[3];
        for (int i = 0; i < 3; i++)
        {
            net_force[i] = 0;
        }
        //for every other planet, add to net force
        for (int other_planet = 0; other_planet < universe->planet_list->length; other_planet++)
        {
            if (curr_planet != other_planet)
            {
                add_force_vector(universe->planet_list->list_address[curr_planet], universe->planet_list->list_address[other_planet], net_force);
            }
        }
        for (int i = 0; i < 3; i++)
        {
            //save the net force and current state
            net_forces[curr_planet][i] = net_force[i];
            old_pos[curr_planet][i] = universe->planet_list->list_address[curr_planet]->pos[i];
            old_vel[curr_planet][i] = universe->planet_list->list_address[curr_planet]->vel[i];

        }
    }
    //use net force to update planets by dt/2
    for (int curr_planet = 0; curr_planet < universe->planet_list->length; curr_planet++)
    {
        update_planet_dt(universe->planet_list->list_address[curr_planet], net_forces[curr_planet], dt / 2.0);
    }

    //allocate memory for midpoint forces
    double mid_net_forces[universe->planet_list->length][3];

    //find midpoint forces
    for (int curr_planet = 0; curr_planet < universe->planet_list->length; curr_planet++)
    {
        double net_force[3];
        for (int i = 0; i < 3; i++)
        {
            net_force[i] = 0;
        }
        //for every other planet, add to net force
        for (int other_planet = 0; other_planet < universe->planet_list->length; other_planet++)
        {
            if (curr_planet != other_planet)
            {
                add_force_vector(universe->planet_list->list_address[curr_planet], universe->planet_list->list_address[other_planet], net_force);
            }
        }
        for (int i = 0; i < 3; i++)
        {
            //save the net force
            mid_net_forces[curr_planet][i] = net_force[i];
        }
    }

    //revert the planets and then update based on midpoint net force
    for (int curr_planet = 0; curr_planet < universe->planet_list->length; curr_planet++)
    {
        //revert
        for (int i = 0; i < 3; i++)
        {
            universe->planet_list->list_address[curr_planet]->pos[i] = old_pos[curr_planet][i];
            universe->planet_list->list_address[curr_planet]->vel[i] = old_vel[curr_planet][i];
        }

        //update
        update_planet(universe->planet_list->list_address[curr_planet], mid_net_forces[curr_planet]);

    }
}

/*
 * Frees all memory allocated for universe
 */
void free_universe(universe* universe)
{
    //free the planets
    for (int i = 0; i < universe->planet_list->length; i++)
    {
        free_planet(universe->planet_list->list_address[i]);
    }

    //free the list itself, and finally the universe
    free_list(universe->planet_list);
    free(universe);

}
