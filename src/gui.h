void Draw();
void DrawCircle(float cx, float cy, float r, int num_segments);
void inialize_gui();

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
