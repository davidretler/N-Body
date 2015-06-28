#include "gui.h"

static int frame_time = (int)((1.0/(double)FPS) * 1000000);
static float circ_pos_y = 0.0f;

void Draw() {
    glClear(GL_COLOR_BUFFER_BIT);

    DrawCircle(0.5, circ_pos_y, 0.2, 100);

    glFlush();
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

void inialize_gui()
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
}

void loop()
{
    /*
     * Get the start time
     */
    struct timeval tv;
    gettimeofday(&tv, 0);
    int start_time = tv.tv_usec; //microsecond time

    /*
     * Render things
     */
    glClear(GL_COLOR_BUFFER_BIT);
    Draw();
    //printf("The time is %ld.\n", (long)time(0));


    /*
     * Get end time, and sleep required length
     */
    gettimeofday(&tv, 0);
    int end_time = tv.tv_usec;
    //free(tv);
    int time_diff = end_time - start_time;
    if(time_diff < frame_time)
    {
        usleep(frame_time - time_diff);
    }

    circ_pos_y += 0.002f;

    glutPostRedisplay();
}
