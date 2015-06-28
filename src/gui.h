#ifndef GUI_H_
#define GUI_H_

#include <GL/glut.h>
#include <math.h>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>


#define WINDOW_HEIGHT 800
#define WINDOW_WIDTH 800
#define FPS 60

void Draw(void);
void DrawCircle(float cx, float cy, float r, int num_segments);
void inialize_gui(void);
void loop(void);

#endif /* GUI_H_ */
