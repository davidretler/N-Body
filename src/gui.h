#ifndef GUI_H_
#define GUI_H_

#include <GL/glut.h>
#include <math.h>
#include <unistd.h>
#include <stdio.h>
#include "universe.h"

#define WINDOW_HEIGHT 800      /*Window Dimensions*/
#define WINDOW_WIDTH 800
#define FPS 60                 /*Frames per second*/
#define PLANET_RADIUS 0.001    /*Scale factor for radii (actual radii varies with log(planet->mass))*/
#define NUM_SIDES 100          /*Number of sides to draw polygon with to approximate circle*/

extern double SCALE;    /*How many AU to include in the rendering the universe*/
extern int SPEEDUP;  /*How man times faster the simulation is than realtime*/
extern const double AU;
extern const double G;
extern double dt;

void Draw(void);
void DrawCircle(float cx, float cy, float r, int num_segments, unsigned char color[static 3]);
void DrawPlanet(planet* my_planet);
void inialize_gui(universe* universe);
void loop(void);

#endif /* GUI_H_ */
