#include "gui.h"

static int frame_time = (int)((1.0/(double)FPS) * 1000); //time frame should take, ms
universe* my_universe;

#define NUM_STEPS (int)ceil(SPEEDUP/dt/FPS) /*Number of steps to update each frame to achieve desired speedup*/

void Draw() {
    glClear(GL_COLOR_BUFFER_BIT);

    //DrawCircle(0.5, circ_pos_y, 0.2, 100);
    //
    for(int p = 0; p < my_universe->planet_list->length; p++)
    {
        DrawPlanet(my_universe->planet_list->list_address[p]);
        //printf("Rendering planet %u (pos=%f)\n", p, my_universe->planet_list->list_address[p]->pos[0]/AU);
    }
    glutSwapBuffers();
}

void DrawPlanet(planet* my_planet)
{
    DrawCircle(my_planet->pos[0]/AU, my_planet->pos[1]/AU, PLANET_RADIUS * my_planet->mass_log10 , NUM_SIDES, my_planet->color);
}

void DrawCircle(float cx, float cy, float r, int num_segments, unsigned char color[static 3])
{
    //set color to color passed
    glColor3ub(color[0], color[1], color[2]);
    glBegin(GL_TRIANGLE_FAN);
    for(int ii = 0; ii < num_segments; ii++)
    {
        float theta = 2.0f * 3.1415926f * (float)(ii) / (float)(num_segments);//get the current angle

        float x = r * cosf(theta);//calculate the x component
        float y = r * sinf(theta);//calculate the y component

        glVertex2f(x + cx, y + cy);//output vertex
    }
    glEnd();

    //set the color white to the defualt
    glColor3f(1.0f, 1.0f, 1.0f);
}

void inialize_gui(universe* universe)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);   //sets the background color
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
    int start_time = glutGet(GLUT_ELAPSED_TIME);

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
        update_function(my_universe);
    }
    //printf("Ran n=%u steps\n", NUM_STEPS);


    /*
     * Get end time, and sleep required length
     */
    int end_time = glutGet(GLUT_ELAPSED_TIME);

    int time_diff = end_time - start_time;

    printf("Frame took %u ms to render. Time left %u ms. Ran universe for %f seconds (dt = %f).\n", time_diff, frame_time > time_diff ? frame_time - time_diff : 0, NUM_STEPS*dt, dt);

    if(time_diff < frame_time)
    {
        usleep(frame_time - time_diff);
        glutPostRedisplay();
    }
    else
    {
        glutPostRedisplay();
    }


}
