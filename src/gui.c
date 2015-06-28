#include "gui.h"

static int frame_time = (int)((1.0/(double)FPS) * 1000);
static float circ_pos_y = 0.0f;
universe* my_universe;
extern const double AU;
extern const double G;
extern const double dt;

#define NUM_STEPS (int)(SPEEDUP/dt/FPS) /*Number of steps to update each frame to achieve desired speedup*/

void Draw() {
    glClear(GL_COLOR_BUFFER_BIT);

    //DrawCircle(0.5, circ_pos_y, 0.2, 100);
    //
    for(int p = 0; p < my_universe->planet_list->length; p++)
    {
        DrawCircle(my_universe->planet_list->list_address[p]->pos[0]/AU, my_universe->planet_list->list_address[p]->pos[1]/AU, PLANET_RADIUS, NUM_SIDES);
        //printf("Rendering planet %u (pos=%f)\n", p, my_universe->planet_list->list_address[p]->pos[0]/AU);
    }
    glutSwapBuffers();
}

void DrawCircle(float cx, float cy, float r, int num_segments)
{
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_TRIANGLE_FAN);
    for(int ii = 0; ii < num_segments; ii++)
    {
        float theta = 2.0f * 3.1415926f * (float)(ii) / (float)(num_segments);//get the current angle

        float x = r * cosf(theta);//calculate the x component
        float y = r * sinf(theta);//calculate the y component

        glVertex2f(x + cx, y + cy);//output vertex
    }
    glEnd();
}

void inialize_gui(universe* universe)
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-SCALE, SCALE, -SCALE, SCALE, -1.0, 1.0);
    my_universe = universe;
}

void loop()
{
    /*
     * Get the start time
     */
    struct timeval tv;
    gettimeofday(&tv, 0);
    int start_time = (tv.tv_sec) * 1000 + (tv.tv_usec) / 1000;

    /*
     * Render things
     */
    glClear(GL_COLOR_BUFFER_BIT);
    Draw();

    /*
     * Update the universe
     */
    for(int n = 0; n < NUM_STEPS; n++)
    {
        universe_update_midpoint(my_universe);
    }
    //printf("Ran n=%u steps\n", NUM_STEPS);


    /*
     * Get end time, and sleep required length
     */
    gettimeofday(&tv, 0);
    int end_time = (tv.tv_sec) * 1000 + (tv.tv_usec) / 1000;

    int time_diff = end_time - start_time;

    //printf("Frame took %u ms to render.\n", time_diff);

    if(time_diff < frame_time)
    {
        usleep(frame_time - time_diff);
    }

    circ_pos_y += 0.002f;

    glutPostRedisplay();
}
