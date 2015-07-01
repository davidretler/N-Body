#ifndef GUI_H_
#define GUI_H_

#include <GL/glut.h>
#include <math.h>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>
#include "universe.h"

#define WINDOW_HEIGHT 800      /*Window Dimensions*/
#define WINDOW_WIDTH 800
#define FPS 60                 /*Frames per second*/
#define SCALE 2.0              /*How many AU to include in the rendering the universe*/
#define PLANET_RADIUS 0.000002    /*Scale factor for radii (actual radii varies with log(planet->mass))*/
#define NUM_SIDES 100          /*Number of sides to draw polygon with to approximate circle*/
#define SPEEDUP 500000         /*How man times faster the simulation is than realtime*/

void Draw(void);
void DrawCircle(float cx, float cy, float r, int num_segments, unsigned char color[static 3]);
void DrawPlanet(planet* my_planet);
void inialize_gui(universe* universe);
void loop(void);

#endif /* GUI_H_ */
