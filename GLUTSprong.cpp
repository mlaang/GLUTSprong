#include <cstdlib>
#include <gl/glut.h>
#include <gl/gl.h>
#include "vec2.h"
#include "SimpleBall.h"
#include "CenteredSquareViewport.h"
#include "LineSegment.h"
#include "Paddle.h"
#include <algorithm>
#include <limits>
#include <time.h>

SimpleBall ball1(0.0f, 0.0f, 1.0f, 1.0f, 0.1f); //initial velocity (1.0,f 1.0f), initial diameter 0.1f.
SimpleBall ball2(0.0f, 0.5f, 1.0f, 1.0f, 0.1f);
SimpleBall ball3(0.0f, -0.5f, 1.0f, 0.0f, 0.1f);
//SpringBall ball(0.0f, 0.0f, 1.0f, 1.0f, 0.2f, 0.05f, 4); //Initial position is (0.0f, 0.0f), 
Paddle paddle(-0.85f); //Set x-plane height for the paddle.
LineSegment top(-1.0f, 1.0f, 1.0f, 1.0f), left(-1.0f, -1.0f, -1.0f, 1.0f), right(1.0f, -1.0f, 1.0f, 1.0f);
CollissionObject2D* collission_objects[] = {&paddle, &top, &left, &right, &ball1, &ball2, &ball3};
const int N_collission_objects = 7;
CenteredSquareViewport viewport(800, 600, 0, 0, 100);

void display() {
    glClearColor(0.5f, 0.2f, 0.2f, 0.0f); 
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(1.0f, 1.0f);
    glVertex2f(1.0f, -1.0f);
    glVertex2f(-1.0f, -1.0f);
    glVertex2f(-1.0f, 1.0f);
    glEnd();

    ball1.display();
    ball2.display();
    ball3.display();
    paddle.display();

    //Draws a square when the game is over.
    if (ball1.is_fully_outside(-1.0f, 1.0f, -1.0f, 1.0f) ||
        ball2.is_fully_outside(-1.0f, 1.0f, -1.0f, 1.0f) ||
        ball3.is_fully_outside(-1.0f, 1.0f, -1.0f, 1.0f)) {
        glBegin(GL_TRIANGLES);
        glColor3f(0.7f, 0.15f, 0.15f);
        glVertex2f(0.5f, 0.5f);

        glColor3f(0.75f, 0.075f, 0.075f);
        glVertex2f(-0.5f, 0.5f);
        glVertex2f(0.5f, -0.5f);
        glVertex2f(-0.5f, 0.5f);
        glVertex2f(0.5f, -0.5f);

        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex2f(-0.5f, -0.5f);
        glEnd();
    }

    glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y) {
    if (key == (char)27)
        exit(EXIT_SUCCESS);
}

void mouse(int button, int state, int x, int y) {
    //Restart when button press is released and at least one ball has left the screen, thus we wait for a left button state change to the up state.
    if (button == GLUT_LEFT && state == GLUT_UP) {
        if (ball1.is_fully_outside(-1.0f, 1.0f, -1.0f, 1.0f) ||
            ball2.is_fully_outside(-1.0f, 1.0f, -1.0f, 1.0f) ||
            ball3.is_fully_outside(-1.0f, 1.0f, -1.0f, 1.0f)) {
            ball1 = SimpleBall(0.0f, 0.0f, 1.0f, 1.0f, 0.1f);
            ball2 = SimpleBall(0.0f, 0.5f, 1.0f, 1.0f, 0.1f);
            ball3 = SimpleBall(0.0f, -0.5f, 1.0f, 1.0f, 0.1f);
        }
    }
}

void reshape(int w, int h) {
    viewport.update(w, h);
}

void passive_motion(int x, int y) {
    paddle.update(viewport.get_mouse_position(x, y).x);
    glutPostRedisplay();
}

void timer(int t) {
    const int substeps = 10,
              collission_substeps = 100;
    for (int i = 0; i != substeps; ++i) {
        float elapsed_time = t / (1000.0f * (float)substeps);
        ball1.apply_free_motion(elapsed_time);
        ball2.apply_free_motion(elapsed_time);
        ball3.apply_free_motion(elapsed_time);
        ball1.preupdate(elapsed_time, collission_objects, N_collission_objects);
        ball2.preupdate(elapsed_time, collission_objects, N_collission_objects);
        ball3.preupdate(elapsed_time, collission_objects, N_collission_objects);
        ball1.update();
        ball2.update();
        ball3.update();
        while(!ball1.collissions_resolved(collission_objects) ||
              !ball2.collissions_resolved(collission_objects) ||
              !ball3.collissions_resolved(collission_objects)) {
            float collission_substep_elapsed_time = elapsed_time / (float)collission_substeps;
            ball1.resolve_collissions(collission_substep_elapsed_time, collission_objects, N_collission_objects);
            ball2.resolve_collissions(collission_substep_elapsed_time, collission_objects, N_collission_objects);
            ball3.resolve_collissions(collission_substep_elapsed_time, collission_objects, N_collission_objects);
        }
    }
    glutTimerFunc(t, timer, t);
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Sprong");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutPassiveMotionFunc(passive_motion);
    glutTimerFunc(10, timer, 10);
    glutMainLoop();
    return EXIT_SUCCESS;
}