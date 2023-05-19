/*

1. Group Number: 14
2. Group Members:-
        Gourang Pathak (2004213)
        Rohith G (2004232)
        Kanishk chugh (2004215)
3. Course: Computer Graphics using Opengl (CS440)
4. Submitted to: Dr.Venkatesh Kamat

*/

/*Including header files*/
#define GL_SILENCE_DEPRECATION
#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

GLfloat angle = 0;

void Spin()
{
    angle = angle + 0.5;
    if (angle > 360)
        angle = 0;
    glutPostRedisplay();
}

GLboolean amb1 = true;
GLboolean diff1 = true;
GLboolean spec1 = true;
GLboolean amb2 = true;
GLboolean diff2 = true;
GLboolean spec2 = true;
GLboolean amb3 = true;
GLboolean diff3 = true;
GLboolean spec3 = true;
GLboolean FlaggerRed = true;
GLboolean FirstSwitch = false;
GLboolean SecondSwitch = false;
GLboolean SwitchLamp = false;

double windowHeight = 1200;
double windowWidth = 3000;
double eyeX = 7.0;
double eyeY = 2.0;
double eyeZ = 15.0;
double refX = 0;
double refY = 0;
double refZ = 0;
double Theta = 180.0;
double y = 1.36;
double z = 7.97888;

static GLubyte QuadIndices[6][4] =
    {
        {0, 1, 2, 3}, // bottom
        {4, 5, 6, 7}, // top
        {5, 1, 2, 6}, // front
        {0, 4, 7, 3}, // back is clockwise
        {2, 3, 7, 6}, // right
        {1, 5, 4, 0}  // left is clockwise
};

static GLfloat VCube[8][3] =
    {
        {0.0, 0.0, 0.0}, // 0
        {0.0, 0.0, 3.0}, // 1
        {3.0, 0.0, 3.0}, // 2
        {3.0, 0.0, 0.0}, // 3
        {0.0, 3.0, 0.0}, // 4
        {0.0, 3.0, 3.0}, // 5
        {3.0, 3.0, 3.0}, // 6
        {3.0, 3.0, 0.0}  // 7
};

static void GetNormal(GLfloat x1, GLfloat y1, GLfloat z1, GLfloat x2, GLfloat y2, GLfloat z2, GLfloat x3, GLfloat y3, GLfloat z3)
{
    GLfloat Ux, Uy, Uz, Vx, Vy, Vz, Nx, Ny, Nz;

    Ux = x2 - x1;
    Uy = y2 - y1;
    Uz = z2 - z1;

    Vx = x3 - x1;
    Vy = y3 - y1;
    Vz = z3 - z1;

    Nx = Uy * Vz - Uz * Vy;
    Ny = Uz * Vx - Ux * Vz;
    Nz = Ux * Vy - Uy * Vx;

    glNormal3f(Nx, Ny, Nz);
}

void DrawCube()
{
    glBegin(GL_QUADS);
    for (GLint i = 0; i < 6; i++)
    {
        GetNormal(VCube[QuadIndices[i][0]][0], VCube[QuadIndices[i][0]][1], VCube[QuadIndices[i][0]][2],
                  VCube[QuadIndices[i][1]][0], VCube[QuadIndices[i][1]][1], VCube[QuadIndices[i][1]][2],
                  VCube[QuadIndices[i][2]][0], VCube[QuadIndices[i][2]][1], VCube[QuadIndices[i][2]][2]);
        glVertex3fv(&VCube[QuadIndices[i][0]][0]);
        glVertex3fv(&VCube[QuadIndices[i][1]][0]);
        glVertex3fv(&VCube[QuadIndices[i][2]][0]);
        glVertex3fv(&VCube[QuadIndices[i][3]][0]);
    }
    glEnd();
}

void DrawCube1(GLfloat difX, GLfloat difY, GLfloat difZ, GLfloat ambX = 0, GLfloat ambY = 0, GLfloat ambZ = 0, GLfloat shine = 50)
{
    GLfloat no_mat[] = {0.0, 0.0, 0.0, 1.0};
    GLfloat mat_ambient[] = {ambX, ambY, ambZ, 1.0};
    GLfloat mat_diffuse[] = {difX, difY, difZ, 1.0};
    GLfloat mat_specular[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat mat_shininess[] = {shine};

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);

    glBegin(GL_QUADS);

    for (GLint i = 0; i < 6; i++)
    {
        GetNormal(VCube[QuadIndices[i][0]][0], VCube[QuadIndices[i][0]][1], VCube[QuadIndices[i][0]][2],
                  VCube[QuadIndices[i][1]][0], VCube[QuadIndices[i][1]][1], VCube[QuadIndices[i][1]][2],
                  VCube[QuadIndices[i][2]][0], VCube[QuadIndices[i][2]][1], VCube[QuadIndices[i][2]][2]);
        glVertex3fv(&VCube[QuadIndices[i][0]][0]);
        glVertex3fv(&VCube[QuadIndices[i][1]][0]);
        glVertex3fv(&VCube[QuadIndices[i][2]][0]);
        glVertex3fv(&VCube[QuadIndices[i][3]][0]);
    }
    glEnd();
}

static GLfloat VTrapezoid[8][3] =
    {
        {0.0, 0.0, 0.0}, // 0
        {0.0, 0.0, 3.0}, // 1
        {3.0, 0.0, 3.0}, // 2
        {3.0, 0.0, 0.0}, // 3
        {0.5, 3.0, 0.5}, // 4
        {0.5, 3.0, 2.5}, // 5
        {2.5, 3.0, 2.5}, // 6
        {2.5, 3.0, 0.5}  // 7
};

static GLubyte TquadIndices[6][4] =
    {
        {0, 1, 2, 3}, // bottom
        {4, 5, 6, 7}, // top
        {5, 1, 2, 6}, // front
        {0, 4, 7, 3}, // back is clockwise
        {2, 3, 7, 6}, // right
        {1, 5, 4, 0}  // left is clockwise
};

void DrawTrapezoid(GLfloat difX, GLfloat difY, GLfloat difZ, GLfloat ambX, GLfloat ambY, GLfloat ambZ, GLfloat shine = 50)
{
    GLfloat no_mat[] = {0.0, 0.0, 0.0, 1.0};
    GLfloat mat_ambient[] = {ambX, ambY, ambZ, 1.0};
    GLfloat mat_diffuse[] = {difX, difY, difZ, 1.0};
    GLfloat mat_specular[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat mat_emission[] = {difX, difY, difZ, 0.0};
    GLfloat mat_shininess[] = {shine};

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

    if (SwitchLamp == true)
    {
        glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
    }
    else
    {
        glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
    }

    glBegin(GL_QUADS);
    for (GLint i = 0; i < 6; i++)
    {
        GetNormal(VTrapezoid[TquadIndices[i][0]][0], VTrapezoid[TquadIndices[i][0]][1], VTrapezoid[TquadIndices[i][0]][2],
                  VTrapezoid[TquadIndices[i][1]][0], VTrapezoid[TquadIndices[i][1]][1], VTrapezoid[TquadIndices[i][1]][2],
                  VTrapezoid[TquadIndices[i][2]][0], VTrapezoid[TquadIndices[i][2]][1], VTrapezoid[TquadIndices[i][2]][2]);

        glVertex3fv(&VTrapezoid[TquadIndices[i][0]][0]);
        glVertex3fv(&VTrapezoid[TquadIndices[i][1]][0]);
        glVertex3fv(&VTrapezoid[TquadIndices[i][2]][0]);
        glVertex3fv(&VTrapezoid[TquadIndices[i][3]][0]);
    }
    glEnd();
}

// Drawing pyramid
static GLfloat v_pyramid[5][3] =
    {
        {0.0, 0.0, 0.0},
        {0.0, 0.0, 2.0},
        {2.0, 0.0, 2.0},
        {2.0, 0.0, 0.0},
        {1.0, 4.0, 1.0}};

static GLubyte p_Indices[4][3] =
    {
        {4, 1, 2},
        {4, 2, 3},
        {4, 3, 0},
        {4, 0, 1}};

static GLubyte PquadIndices[1][4] =
    {
        {0, 3, 2, 1}};

void DrawPyramid(GLfloat difX, GLfloat difY, GLfloat difZ, GLfloat ambX, GLfloat ambY, GLfloat ambZ, GLfloat shine)
{
    GLfloat no_mat[] = {0.0, 0.0, 0.0, 1.0};
    GLfloat mat_ambient[] = {ambX, ambY, ambZ, 1.0};
    GLfloat mat_diffuse[] = {difX, difY, difZ, 1.0};
    GLfloat mat_specular[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat mat_shininess[] = {shine};

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

    glBegin(GL_TRIANGLES);
    for (GLint i = 0; i < 4; i++)
    {
        GetNormal(v_pyramid[p_Indices[i][0]][0], v_pyramid[p_Indices[i][0]][1], v_pyramid[p_Indices[i][0]][2],
                  v_pyramid[p_Indices[i][1]][0], v_pyramid[p_Indices[i][1]][1], v_pyramid[p_Indices[i][1]][2],
                  v_pyramid[p_Indices[i][2]][0], v_pyramid[p_Indices[i][2]][1], v_pyramid[p_Indices[i][2]][2]);
        glVertex3fv(&v_pyramid[p_Indices[i][0]][0]);
        glVertex3fv(&v_pyramid[p_Indices[i][1]][0]);
        glVertex3fv(&v_pyramid[p_Indices[i][2]][0]);
    }
    glEnd();

    glBegin(GL_QUADS);
    for (GLint i = 0; i < 1; i++)
    {
        GetNormal(v_pyramid[PquadIndices[i][0]][0], v_pyramid[PquadIndices[i][0]][1], v_pyramid[PquadIndices[i][0]][2],
                  v_pyramid[PquadIndices[i][1]][0], v_pyramid[PquadIndices[i][1]][1], v_pyramid[PquadIndices[i][1]][2],
                  v_pyramid[PquadIndices[i][2]][0], v_pyramid[PquadIndices[i][2]][1], v_pyramid[PquadIndices[i][2]][2]);
        glVertex3fv(&v_pyramid[PquadIndices[i][0]][0]);
        glVertex3fv(&v_pyramid[PquadIndices[i][1]][0]);
        glVertex3fv(&v_pyramid[PquadIndices[i][2]][0]);
        glVertex3fv(&v_pyramid[PquadIndices[i][3]][0]);
    }
    glEnd();
}

void Polygon(GLfloat difX, GLfloat difY, GLfloat difZ, GLfloat ambX, GLfloat ambY, GLfloat ambZ, GLfloat shine)
{
    GLfloat no_mat[] = {0.0, 0.0, 0.0, 1.0};
    GLfloat mat_ambient[] = {ambX, ambY, ambZ, 1.0};
    GLfloat mat_diffuse[] = {difX, difY, difZ, 1.0};
    GLfloat mat_specular[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat mat_shininess[] = {shine};

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

    glBegin(GL_POLYGON);
    glVertex2f(0, 0);
    glVertex2f(6, 0);
    glVertex2f(5.8, 1);
    glVertex2f(5.2, 2);
    glVertex2f(5, 2.2);
    glVertex2f(4, 2.8);
    glVertex2f(3, 3);
    glVertex2f(2, 2.8);
    glVertex2f(1, 2.2);
    glVertex2f(0.8, 2);
    glVertex2f(0.2, 1);

    glEnd();
}

void PolygonLine(GLfloat difX, GLfloat difY, GLfloat difZ, GLfloat ambX, GLfloat ambY, GLfloat ambZ, GLfloat shine)
{
    GLfloat no_mat[] = {0.0, 0.0, 0.0, 1.0};
    GLfloat mat_ambient[] = {ambX, ambY, ambZ, 1.0};
    GLfloat mat_diffuse[] = {difX, difY, difZ, 1.0};
    GLfloat mat_specular[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat mat_shininess[] = {shine};

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    glBegin(GL_LINE_STRIP);
    glVertex2f(6, 0);
    glVertex2f(5.8, 1);
    glVertex2f(5.2, 2);
    glVertex2f(5, 2.2);
    glVertex2f(4, 2.8);
    glVertex2f(3, 3);
    glVertex2f(2, 2.8);
    glVertex2f(1, 2.2);
    glVertex2f(0.8, 2);
    glVertex2f(0.2, 1);
    glVertex2f(0, 0);

    glEnd();
}

void DrawSphere(GLfloat difX, GLfloat difY, GLfloat difZ, GLfloat ambX, GLfloat ambY, GLfloat ambZ, GLfloat shine = 90)
{
    GLfloat no_mat[] = {0.0, 0.0, 0.0, 1.0};
    GLfloat mat_ambient[] = {ambX, ambY, ambZ, 1.0};
    GLfloat mat_diffuse[] = {difX, difY, difZ, 1.0};
    GLfloat mat_specular[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat mat_shininess[] = {shine};

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

    glutSolidSphere(3.0, 20, 16);
}

void Cupboard()
{
    // cupboard
    glPushMatrix();
    glTranslatef(4, 0, 4.4);
    glScalef(0.5, 1, 0.5);
    DrawCube1(0.5, 0.6, 0.6, 0.25, 0.1, 0.1);
    glPopMatrix();

    // cupboard's first vertical stripline
    glPushMatrix();
    glTranslatef(4, 1, 5.9);
    glScalef(0.5, 0.01, 0.0001);
    DrawCube1(0.2, 0.1, 0.1, 0.1, 0.05, 0.05);
    glPopMatrix();

    // cupboard's second vertical stripline
    glPushMatrix();
    glTranslatef(4, 0.5, 5.9);
    glScalef(0.5, 0.01, 0.0001);
    DrawCube1(0.2, 0.1, 0.1, 0.1, 0.05, 0.05);
    glPopMatrix();

    // cupboard's last stripline
    glPushMatrix();
    glTranslatef(4, 0, 5.9);
    glScalef(0.5, 0.01, 0.0001);
    DrawCube1(0.2, 0.1, 0.1, 0.1, 0.05, 0.05);
    glPopMatrix();

    // cupboard's lst horizontal stripline
    glPushMatrix();
    glTranslatef(5.5, 0, 5.9);
    glScalef(0.01, 1, 0.0001);
    DrawCube1(0.2, 0.1, 0.1, 0.1, 0.05, 0.05);
    glPopMatrix();

    // cupboard's right side horizontal stripline
    glPushMatrix();
    glTranslatef(4.75, 1, 5.9);
    glScalef(0.01, 0.67, 0.0001);
    DrawCube1(0.2, 0.1, 0.1, 0.1, 0.05, 0.05);
    glPopMatrix();

    // cupboard's left side horizontal stripline
    glPushMatrix();
    glTranslatef(4, 0, 5.9);
    glScalef(0.01, 1, 0.0001);
    DrawCube1(0.2, 0.1, 0.1, 0.1, 0.05, 0.05);
    glPopMatrix();

    // cupboard's handle right
    glPushMatrix();
    glTranslatef(5, 1.4, 5.9);
    glScalef(0.02, 0.18, 0.01);
    DrawCube1(0.2, 0.1, 0.1, 0.1, 0.05, 0.05);
    glPopMatrix();

    // cupboard's handle right sphere
    glPushMatrix();
    glTranslatef(5.02, 1.9, 5.91);
    glScalef(0.02, 0.02, 0.01);
    DrawSphere(0.2, 0.1, 0.1, 0.1, 0.05, 0.05, 10);
    glPopMatrix();

    // cupboard's handle left
    glPushMatrix();
    glTranslatef(4.5, 1.4, 5.9);
    glScalef(0.02, 0.18, 0.01);
    DrawCube1(0.2, 0.1, 0.1, 0.1, 0.05, 0.05);
    glPopMatrix();

    // cupboard's handle left sphere
    glPushMatrix();
    glTranslatef(4.52, 1.9, 5.91);
    glScalef(0.02, 0.02, 0.01);
    DrawSphere(0.2, 0.1, 0.1, 0.1, 0.05, 0.05, 10);
    glPopMatrix();

    // cupboard's drawer's first handle
    glPushMatrix();
    glTranslatef(4.5, 0.7, 5.9);
    glScalef(0.16, 0.02, 0.01);
    DrawCube1(0.2, 0.1, 0.1, 0.1, 0.05, 0.05);
    glPopMatrix();

    // cupboard's drawer's second handle
    glPushMatrix();
    glTranslatef(4.5, 0.25, 5.9);
    glScalef(0.16, 0.02, 0.01);
    DrawCube1(0.2, 0.1, 0.1, 0.1, 0.05, 0.05);
    glPopMatrix();
}

void Room()
{
    // code for carpet
    glPushMatrix();
    glTranslatef(3, -0.2, 7);
    glScalef(1.3, 0.01, 1.7);
    DrawCube1(0.75, 0.75, 0.4, 0.20, 0.05, 0.0);
    glPopMatrix();

    // code for right wall
    glPushMatrix();
    glTranslatef(-1.5, -1, .5);
    glScalef(5, 2, 0.1);
    DrawCube1(0.9, 0.2, 0.2, 0.5, 0.4, 0.35);
    glPopMatrix();

    // code for left wall
    glColor3f(0, 0, 0);
    glPushMatrix();
    glTranslatef(-4.5, -1, 0);
    glScalef(1, 2, 5);
    DrawCube1(0.9, 0.2, 0.2, 0.5, 0.4, 0.35);
    glPopMatrix();

    // code for wall besides the right wall
    glPushMatrix();
    glTranslatef(8, -1, 0);
    glScalef(0.2, 2, 5);
    DrawCube1(0.9, 0.2, 0.2, 0.5, 0.4, 0.35);
    glPopMatrix();

    // code for ceiling
    glPushMatrix();
    glTranslatef(-2, 5.1, 0);
    glScalef(5, 0.1, 7);
    DrawCube1(1, 0.9, 0.8, 0.5, 0.45, 0.4);
    glPopMatrix();

    // code floor
    glPushMatrix();
    glScalef(5, 0.1, 7);
    glTranslatef(-1, -5, 0);
    DrawCube1(0.5, 0.1, 0.0, 0.25, 0.05, 0);
    glPopMatrix();
}

/*Function to make the bed*/
void Bed()
{
    // bed headboard
    glPushMatrix();
    glScalef(0.1, 0.5, 0.9);
    glTranslatef(-2, -0.5, 6.2);
    DrawCube1(0.5, 0.2, 0.2, 0.25, 0.1, 0.1);
    glPopMatrix();

    // bed body
    glPushMatrix();
    glScalef(1, 0.2, 0.9);
    glTranslatef(0, -0.5, 6.2);
    DrawCube1(0.4, 0.7, 0.3, 0.412, 0.353, 0.2745);
    glPopMatrix();

    // pillow right away from front view
    glPushMatrix();
    glTranslatef(0.5, 0.5, 6);
    glRotatef(20, 0, 0, 1);
    glScalef(0.1, 0.15, 0.28);
    DrawCube1(0.3, 0.7, 0.7, 0.3135, 0.161, 0.088);
    glPopMatrix();

    // pillow left near
    glPushMatrix();
    glTranslatef(0.5, 0.5, 7.2);
    glRotatef(22, 0, 0, 1);
    glScalef(0.1, 0.15, 0.28);
    DrawCube1(0.3, 0.7, 0.7, 0.3135, 0.161, 0.088);
    glPopMatrix();

    // blanket
    glPushMatrix();
    glTranslatef(1.4, 0.45, 5.5);
    glScalef(0.5, 0.05, 0.95);
    DrawCube1(00.3, 0.7, 0.7, 0.3135, 0.161, 0.088);
    glPopMatrix();

    // blanket side left part for front view
    glPushMatrix();
    glTranslatef(1.4, -0.3, 8.16);
    glScalef(0.5, 0.25, 0.05);
    DrawCube1(0.3, 0.7, 0.7, 0.3135, 0.161, 0.088);
    glPopMatrix();
}

void BedSideDrawer()
{
    // side drawer
    glPushMatrix();
    glTranslatef(0.5, -0.1, 8.7);
    glScalef(0.12, 0.2, 0.23);
    DrawCube1(0.9, 0.3, 0.1, 0.1, 0.05, 0.05);
    glPopMatrix();

    // side drawer's drawer
    glPushMatrix();
    glTranslatef(0.88, 0, 8.8);
    glScalef(0.0001, 0.11, 0.18);
    DrawCube1(0.9, 0.7, 0.1, 0.15, 0.1, 0.1);
    glPopMatrix();

    // side drawer's knob
    glPushMatrix();
    glTranslatef(0.9, 0.15, 9.05);
    glScalef(0.01, 0.02, 0.02);
    DrawSphere(0.9, 0.3, 0.1, 0.15, 0.05, 0.0);
    glPopMatrix();
}

/*Function to draw the lamp*/
void DrawLamp()
{
    // Lamp Base
    glPushMatrix();
    glTranslatef(.6, 0.5, 8.95);
    glScalef(0.07, 0.02, 0.07);
    DrawCube1(1.1, 0.5, 0.8, 0, 0, 0.5);
    glPopMatrix();

    // Lamp Stand
    glColor3f(1, 0, 0);
    glPushMatrix();
    glTranslatef(.7, 0.35, 9.05);
    glScalef(0.01, 0.2, 0.01);
    DrawCube1(1.1, 0.5, 0.8, 0.5, 0.0, 0.0);
    glPopMatrix();

    // Lamp Shade
    glColor3f(0.000, 0.000, 0.545);
    glPushMatrix();
    glTranslatef(.6, 0.9, 8.9);
    glScalef(0.08, 0.09, 0.08);
    DrawTrapezoid(1.1, 0.5, 0.8, 0, 0, 0.2725);
    glPopMatrix();
}

/*Function to make the poster of Lighting */
void Poster()
{
    // Poster black
    glColor3f(0.0, 1.0, 0.0);
    glPushMatrix();
    glTranslatef(-1, 1.4, 4.6);
    glScalef(0.0001, .65, .8);
    DrawCube1(0.1, 0.7, 0.7, 0, 0, 0, 10);
    glPopMatrix();

    // Poster logo
    glColor3f(1.0, 1.0, 1.0);
    glPushMatrix();
    glTranslatef(-0.9, 2.1, 5.5);
    glScalef(0.0, .02, .25);
    DrawCube1(1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 10);
    glPopMatrix();

    // Poster logo
    glColor3f(1.0, 1.0, 1.0);
    glPushMatrix();
    glTranslatef(-0.9, 2.1, 6.2);
    glRotatef(-14, 1, 0, 0);
    glScalef(0.1, .28, .02);
    DrawCube1(1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 10);
    glPopMatrix();

    // Poster logo
    glColor3f(1.0, 1.0, 1.0);
    glPushMatrix();
    glTranslatef(-0.9, 1.8, 6);
    glRotatef(-14, 1, 0, 0);
    glScalef(0.1, .29, .02);
    DrawCube1(1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 10);
    glPopMatrix();

    // Poster logo
    glColor3f(1.0, 1.0, 1.0);
    glPushMatrix();
    glTranslatef(-0.9, 2.1, 5.5);
    glRotatef(23, 1, 0, 0);
    glScalef(0.0, .25, .02);
    DrawCube1(1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 10);
    glPopMatrix();
}

/*Function to draw the wardrobe*/

void Wardrobe()
{
    // Wardrobe
    glPushMatrix();
    glTranslatef(0, 0, 4);
    glScalef(0.12, 0.6, 0.4);
    DrawCube1(0.5, 0.6, 0.6, 0.15, 0.05, 0);
    glPopMatrix();

    // Wardrobe's 1st drawer
    glPushMatrix();
    glTranslatef(0.36, 1.4, 4.05);
    glScalef(0.0001, 0.11, 0.38);
    DrawCube1(0.5, 0.6, 0.6, 0.25, 0.1, 0.1);
    glPopMatrix();

    // Wardrobe's 2nd drawer
    glPushMatrix();
    glTranslatef(0.36, 1, 4.05);
    glScalef(0.0001, 0.11, 0.38);
    DrawCube1(0.5, 0.6, 0.6, 0.25, 0.1, 0.1);
    glPopMatrix();

    // Wardrobe's 3rd drawer
    glPushMatrix();
    glTranslatef(0.36, 0.6, 4.05);
    glScalef(0.0001, 0.11, 0.38);
    DrawCube1(0.5, 0.6, 0.6, 0.25, 0.1, 0.1);
    glPopMatrix();

    // Wardrobe's 4th drawer
    glPushMatrix();
    glTranslatef(0.36, 0.2, 4.05);
    glScalef(0.0001, 0.11, 0.38);
    DrawCube1(0.5, 0.6, 0.6, 0.25, 0.1, 0.1);
    glPopMatrix();

    // Wardrobe's 1st drawer handle
    glColor3f(0.3, 0.1, 0);
    glPushMatrix();
    glTranslatef(0.37, 1.5, 4.3);
    glScalef(0.01, 0.03, 0.2);
    DrawCube1(0.3, 0.1, 0, 0.15, 0.05, 0.0);
    glPopMatrix();

    // Wardrobe's 2nd drawer handle
    glColor3f(0.3, 0.1, 0);
    glPushMatrix();
    glTranslatef(0.37, 1.1, 4.3);
    glScalef(0.01, 0.03, 0.2);
    DrawCube1(0.3, 0.1, 0, 0.15, 0.05, 0.0);
    glPopMatrix();

    // Wardrobe's 3rd drawer handle
    glColor3f(0.3, 0.1, 0);
    glPushMatrix();
    glTranslatef(0.37, 0.7, 4.3);
    glScalef(0.01, 0.03, 0.2);
    DrawCube1(0.3, 0.1, 0, 0.15, 0.05, 0.0);
    glPopMatrix();

    // Wardrobe's 4th drawer handle
    glColor3f(0.3, 0.1, 0);
    glPushMatrix();
    glTranslatef(0.37, 0.3, 4.3);
    glScalef(0.01, 0.03, 0.2);
    DrawCube1(0.3, 0.1, 0, 0.15, 0.05, 0.0);
    glPopMatrix();
}

/*Function to draw the dressing table*/
void DressingTable()
{
    // Dressing table

    // Dressing table left body
    glPushMatrix();
    glTranslatef(5.9, 0, 4.6);
    glScalef(0.2, 0.2, 0.2);
    DrawCube1(0.5, 0.6, 0.6, 0.2725, 0.1355, 0.0375);
    glPopMatrix();

    // Dressing table right body
    glPushMatrix();
    glTranslatef(7, 0, 4.6);
    glScalef(0.2, 0.2, 0.2);
    DrawCube1(0.5, 0.6, 0.6, 0.2725, 0.1355, 0.0375);
    glPopMatrix();

    // Dressing table upper body
    glPushMatrix();
    glTranslatef(5.9, 0.6, 4.6);
    glScalef(0.57, 0.1, 0.2);
    DrawCube1(0.5, 0.6, 0.6, 0.2725, 0.1355, 0.0375);
    glPopMatrix();

    // Dressing table upper body bottom stripe
    glPushMatrix();
    glTranslatef(5.9, 0.6, 5.2);
    glScalef(0.57, 0.01, 0.0001);
    DrawCube1(0.2, 0.1, 0.1, 0.1, 0.05, 0.05);
    glPopMatrix();

    // Dressing table upper body upper stripe
    glPushMatrix();
    glTranslatef(5.9, 0.9, 5.2);
    glScalef(0.57, 0.01, 0.0001);
    DrawCube1(0.2, 0.1, 0.1, 0.1, 0.05, 0.05);
    glPopMatrix();

    // dressing table upper body handle
    glColor3f(0.2, 0.1, 0.1);
    glPushMatrix();
    glTranslatef(6.5, 0.75, 5.2);
    glScalef(0.16, 0.02, 0.0001);
    DrawCube1(0.2, 0.1, 0.1, 0.1, 0.05, 0.05);
    glPopMatrix();

    // dressing table left body handle
    glColor3f(0.2, 0.1, 0.1);
    glPushMatrix();
    glTranslatef(6.4, 0.1, 5.2);
    glScalef(0.02, 0.13, 0.0001);
    DrawCube1(0.2, 0.1, 0.1, 0.1, 0.05, 0.05);
    glPopMatrix();

    // dressing table right body handle
    glColor3f(0.2, 0.1, 0.1);
    glPushMatrix();
    glTranslatef(7.1, 0.1, 5.2);
    glScalef(0.02, 0.13, 0.0001);
    DrawCube1(0.2, 0.1, 0.1, 0.1, 0.05, 0.05);
    glPopMatrix();

    // dressing table main mirror
    glPushMatrix();
    glTranslatef(6.2, 0.9, 4.7);
    glScalef(0.36, 0.5, 0.0001);
    DrawCube1(0.690, 0.878, 0.902, 0.345, 0.439, 0.451, 10);
    glPopMatrix();

    // dressing table left mirror
    glPushMatrix();
    glTranslatef(5.92, 0.9, 4.7);
    glScalef(0.1, 0.48, 0.0001);
    DrawCube1(0.690, 0.878, 0.902, 0.345, 0.439, 0.451, 10);
    glPopMatrix();

    // dressing table left mirror left stripe
    glColor3f(0.2, 0.1, 0.1);
    glPushMatrix();
    glTranslatef(5.92, 0.9, 4.71);
    glScalef(0.019, 0.48, 0.0001);
    DrawCube1(0.2, 0.1, 0.1, 0.1, 0.05, 0.05);
    glPopMatrix();

    // dressing table left mirror left stripe
    glColor3f(0.2, 0.1, 0.1);
    glPushMatrix();
    glTranslatef(6.17, 0.9, 4.71);
    glScalef(0.019, 0.48, 0.0001);
    DrawCube1(0.2, 0.1, 0.1, 0.1, 0.05, 0.05);
    glPopMatrix();

    // dressing table mirror  stripe
    glColor3f(0.2, 0.1, 0.1);
    glPushMatrix();
    glTranslatef(5.92, 0.9, 4.71);
    glScalef(0.55, 0.019, 0.0001);
    DrawCube1(0.2, 0.1, 0.1, 0.1, 0.05, 0.05);
    glPopMatrix();

    // dressing table left mirror upper stripe
    glColor3f(0.2, 0.1, 0.1);
    glPushMatrix();
    glTranslatef(5.92, 2.3, 4.71);
    glScalef(0.1, 0.019, 0.0001);
    DrawCube1(0.2, 0.1, 0.1, 0.1, 0.05, 0.05);
    glPopMatrix();

    // dressing table right mirror
    glPushMatrix();
    glTranslatef(7.25, 0.9, 4.7);
    glScalef(0.1, 0.48, 0.0001);
    DrawCube1(0.690, 0.878, 0.902, 0.345, 0.439, 0.451, 10);
    glPopMatrix();

    // dressing table left mirror upper stripe
    glColor3f(0.2, 0.1, 0.1);
    glPushMatrix();
    glTranslatef(7.25, 2.3, 4.71);
    glScalef(0.1, 0.019, 0.0001);
    DrawCube1(0.2, 0.1, 0.1, 0.1, 0.05, 0.05);
    glPopMatrix();

    // dressing table right mirror left stripe
    glColor3f(0.2, 0.1, 0.1);
    glPushMatrix();
    glTranslatef(7.25, 0.9, 4.71);
    glScalef(0.019, 0.48, 0.0001);
    DrawCube1(0.2, 0.1, 0.1, 0.1, 0.05, 0.05);
    glPopMatrix();

    // dressing table right mirror right stripe
    glColor3f(0.2, 0.1, 0.1);
    glPushMatrix();
    glTranslatef(7.5, 0.9, 4.71);
    glScalef(0.019, 0.48, 0.0001);
    DrawCube1(0.2, 0.1, 0.1, 0.1, 0.05, 0.05);
    glPopMatrix();

    // dressing table main mirror polygon part
    glColor3f(0.690, 0.878, 0.902);
    glPushMatrix();
    glTranslatef(6.2, 2.4, 4.7);
    glScalef(0.18, 0.18, 2);
    Polygon(0.690, 0.878, 0.902, 0.345, 0.439, 0.451, 10);
    glPopMatrix();

    // dressing table upper round srtipe
    glColor3f(0.2, 0.1, 0.1);
    glPushMatrix();
    glTranslatef(6.2, 2.4, 4.71);
    glScalef(.18, .18, 1);
    PolygonLine(0.2, 0.1, 0.1, 0.1, 0.05, 0.05, 50);
    glPopMatrix();
}

/*Function to draw the shelf wall*/
void Shelf_Wall()
{
    // first wall shelf
    glPushMatrix();
    glTranslatef(1.5, 2.7, 3);
    glScalef(0.4, 0.03, 0.2);
    DrawCube1(0.4, 0.3, 0.3, 0.1, 0.05, 0.05);
    glPopMatrix();

    // second wall shelf
    glPushMatrix();
    glTranslatef(1, 2.3, 3);
    glScalef(0.4, 0.03, 0.2);
    DrawCube1(0.4, 0.3, 0.3, 0.1, 0.05, 0.05);
    glPopMatrix();

    // third wall shelf
    glPushMatrix();
    glTranslatef(0.5, 1.9, 3);
    glScalef(0.4, 0.03, 0.2);
    DrawCube1(0.4, 0.3, 0.3, 0.1, 0.05, 0.05);
    glPopMatrix();

    // fourth wall shelf
    glPushMatrix();
    glTranslatef(1, 1.5, 3);
    glScalef(0.4, 0.03, 0.2);
    DrawCube1(0.4, 0.3, 0.3, 0.1, 0.05, 0.05);
    glPopMatrix();

    // fifth wall shelf
    glPushMatrix();
    glTranslatef(1.5, 1.1, 3);
    glScalef(0.4, 0.03, 0.2);
    DrawCube1(0.4, 0.3, 0.3, 0.1, 0.05, 0.05);
    glPopMatrix();

    // showpiece on the bottom shelf from left 1
    glPushMatrix();
    glTranslatef(1.5, 1.2, 3);
    glScalef(0.04, 0.06, 0.2);
    DrawCube1(0.698, 0.133, 0.133, 0.349, 0.0665, 0.0665);
    glPopMatrix();

    // showpiece on the bottom shelf from left 2
    glPushMatrix();
    glTranslatef(2, 1.2, 3);
    glScalef(0.04, 0.06, 0.2);
    DrawCube1(0.729, 0.333, 0.827, 0.3645, 0.1665, 0.4135);
    glPopMatrix();

    // showpiece on the bottom shelf from left 3 lower portion
    glPushMatrix();
    glTranslatef(2.5, 1.2, 3);
    glScalef(0.04, 0.06, 0.2);
    DrawCube1(0.098, 0.098, 0.439, 0.049, 0.049, 0.2195);
    glPopMatrix();

    // showpiece on the bottom shelf from left 3 upper portion
    glPushMatrix();
    glTranslatef(2.51, 1.35, 3);
    glScalef(0.01, 0.05, 0.2);
    DrawCube1(0.529, 0.808, 0.980, 0.2645, 0.404, 0.490);
    glPopMatrix();

    // showpiece on the top shelf  left 2
    glColor3f(0.502, 0.502, 0.000);
    glPushMatrix();
    glTranslatef(2.5, 2.71, 3);
    glScalef(0.05, 0.16, 0.01);
    DrawCube1(0.502, 0.502, 0.000, 0.251, 0.251, 0);
    glPopMatrix();

    // showpiece on the top shelf left 1
    glPushMatrix();
    glTranslatef(1.8, 2.71, 3);
    glScalef(0.16, 0.1, 0.01);
    DrawCube1(0, 0, 0.9, 0, 0, 0.45);
    glPopMatrix();

    // showpiece on 2nd shelf
    glColor3f(.416, 0.353, 0.804);
    glPushMatrix();
    glTranslatef(1.3, 2.4, 3);
    glScalef(0.16, 0.08, 0.01);
    DrawCube1(.416, 0.353, 0.804, 0.208, 0.1765, 0.402);
    glPopMatrix();

    // showpiece on 3rd shelf left 1
    glPushMatrix();
    glTranslatef(0.4, 1.9, 3);
    glScalef(0.05, 0.16, 0.01);
    DrawCube1(0.863, 0.078, 0.235, 0.4315, 0.039, 0.1175);
    glPopMatrix();

    // showpiece on 3rd shelf left 2
    glPushMatrix();
    glTranslatef(0.7, 1.9, 3);
    glScalef(0.05, 0.12, 0.01);
    DrawCube1(0.780, 0.082, 0.522, 0.39, 0.041, 0.261);
    glPopMatrix();

    // showpiece on 3rd shelf left 3
    glColor3f(0.600, 0.196, 0.800);
    glPushMatrix();
    glTranslatef(1, 1.9, 3);
    glScalef(0.05, 0.09, 0.01);
    DrawCube1(0.6, 0.196, 0.8, 0.3, 0.098, 0.4);
    glPopMatrix();

    // showpiece on 4th shelf
    glPushMatrix();
    glTranslatef(1.8, 1.5, 3);
    glScalef(0.2, 0.1, 0.2);
    DrawPyramid(0.282, 0.239, 0.545, 0.141, 0.1195, 0.2725, 50);
    glPopMatrix();

    // showpiece on 4th shelf
    glPushMatrix();
    glTranslatef(1.4, 1.5, 3);
    glScalef(0.15, 0.1, 0.2);
    DrawPyramid(0.251, 0.878, 0.816, 0.1255, 0.439, 0.408, 50);
    glPopMatrix();
}

/*Function to draw the clock*/
void DrawClock()
{
    // clock body
    glColor3f(1, 0, 0);
    glPushMatrix();
    glTranslatef(-0.9, 1.8, 7.87);
    glScalef(0.08, 0.25, 0.1);
    DrawCube1(0.5, 0.1, 0.6, 0.271, 0.1335, 0.0375, 50);
    glPopMatrix();

    // clock body white
    glPushMatrix();
    glTranslatef(-0.83, 1.9, 7.9);
    glScalef(0.06, 0.2, 0.08);
    DrawCube1(1.000, 0.894, 0.710, 1.000, 0.894, 0.710);
    glPopMatrix();

    // clock hour handle
    glPushMatrix();
    glTranslatef(-0.65, 2.18, 8.01);
    glRotatef(45, 1, 0, 0);
    glScalef(0.0001, 0.01, 0.04);
    DrawCube1(0, 0, 0, 0, 0, 0);
    glPopMatrix();

    // clock minute handle
    glPushMatrix();
    glTranslatef(-0.65, 2.18, 8.01);
    glRotatef(90, 1, 0, 0);
    glScalef(0.0001, 0.012, 0.08);
    DrawCube1(0, 0, 0, 0, 0, 0);
    glPopMatrix();

    // clock pendulum stick
    glColor3f(0.2, 0.1, 0.1);
    glPushMatrix();
    glTranslatef(-0.7, 2, 8.1);
    glRotatef(Theta, 1, 0, 0);
    glScalef(0.0001, 0.2, 0.03);
    DrawCube1(0.2, 0.1, 0.1, 0.1, 0.05, 0.05);
    glPopMatrix();

    // clock pendulum ball
    glColor3f(0.2, 0.1, 0.1);
    glPushMatrix();
    glTranslatef(-0.72, 1.42, z);
    glScalef(0.035, 0.035, 0.035);
    DrawSphere(0.2, 0.1, 0.1, 0.1, 0.05, 0.05, 10);
    glPopMatrix();

    // clock top pyramid
    glPushMatrix();
    glTranslatef(-0.9, 2.5, 7.81);
    glScalef(0.16, 0.1, 0.2);
    DrawPyramid(0.5, 0.2, 0, 0.25, 0.1, 0, 50);
    glPopMatrix();
}

/*Function to make the window in the room*/
void Window()
{
    // window white open
    glPushMatrix();
    glTranslatef(-0.9, 1, 8.9);
    glScalef(0.0001, .6, .3);
    DrawCube1(1.0, 1.0, 1.0, 0.05, 0.05, 0.05);
    glPopMatrix();

    // window right side corner
    glPushMatrix();
    glTranslatef(-0.9, 1, 8.9);
    glScalef(0.04, 0.6, 0.0001);
    DrawCube1(0.8, 0.6, 0.4, 0.4, 0.3, 0.2);
    glPopMatrix();

    // window left side corner
    glPushMatrix();
    glTranslatef(-0.9, 1, 9.8);
    glScalef(0.04, 0.6, 0.0001);
    DrawCube1(0.8, 0.6, 0.4, 0.4, 0.3, 0.2);
    glPopMatrix();

    // window upper side corner
    glPushMatrix();
    glTranslatef(-0.7, 2.7, 8.9);
    glScalef(0.0001, 0.05, 0.4);
    DrawCube1(0.7, 0.6, 0.5, 0.35, 0.3, 0.25);
    glPopMatrix();

    // window lower side corner
    glPushMatrix();
    glTranslatef(-0.8, 1.02, 8.9);
    glScalef(0.0001, 0.02, 0.34);
    DrawCube1(0.7, 0.6, 0.5, 0.35, 0.3, 0.25);
    glPopMatrix();

    // window vertical bar 1
    glPushMatrix();
    glTranslatef(-0.87, 2.1, 8.9);
    glScalef(0.0001, 0.02, 0.3);
    DrawCube1(0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 5);
    glPopMatrix();

    // window vertical bar 2
    glPushMatrix();
    glTranslatef(-0.87, 1.6, 8.9);
    glScalef(0.0001, 0.02, 0.3);
    DrawCube1(0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 5);
    glPopMatrix();

    // window horizontal bar
    glPushMatrix();
    glTranslatef(-0.87, 1, 9.3);
    glScalef(0.0001, 0.6, 0.02);
    DrawCube1(0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 5);
    glPopMatrix();
}

/*Function to make the LightBulb first*/
void LightBulb1()
{
    GLfloat no_mat[] = {0.0, 0.0, 0.0, 1.0};
    GLfloat mat_ambient[] = {0.7, 0.7, 0.7, 1.0};
    GLfloat mat_ambient_color[] = {0.8, 0.8, 0.2, 1.0};
    GLfloat mat_diffuse[] = {1.000, 0.843, 0.000, 1.0};
    GLfloat mat_specular[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat high_shininess[] = {100.0};
    GLfloat mat_emission[] = {1.000, 1, 1, 0.0};

    glPushMatrix();
    glTranslatef(5, 5, 8);
    glScalef(0.2, 0.2, 0.2);
    glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);

    if (FirstSwitch == true)
    {
        glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
    }
    else
    {
        glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
    }

    glutSolidSphere(1.0, 16, 16);
    glPopMatrix();
}

/*Function to make the LightBulb second*/

void LightBulb2()
{
    GLfloat no_mat[] = {0.0, 0.0, 0.0, 1.0};
    GLfloat mat_ambient[] = {0.7, 0.7, 0.7, 1.0};
    GLfloat mat_ambient_color[] = {0.8, 0.8, 0.2, 1.0};
    GLfloat mat_diffuse[] = {1.000, 0.843, 0.000, 1.0};
    GLfloat high_shininess[] = {100.0};
    GLfloat mat_emission[] = {1, 1, 1, 1.0};

    glPushMatrix();
    glTranslatef(0, 5, 8);
    glScalef(0.2, 0.2, 0.2);
    glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
    if (SecondSwitch == true)
    {
        glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
    }
    else
    {
        glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
    }
    glutSolidSphere(1.0, 16, 16);
    glPopMatrix();
}

/*Function to draw the first light*/
void FirstLight()
{
    glPushMatrix();
    GLfloat Light_None[] = {0.0, 0.0, 0.0, 1.0};
    GLfloat AmbientLight[] = {0.5, 0.5, 0.5, 1.0};
    GLfloat DiffuseLight[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat SpecularLight[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat PositionLight[] = {5.0, 5.0, 8.0, 1.0};

    if (amb1 == true)
    {
        glLightfv(GL_LIGHT0, GL_AMBIENT, AmbientLight);
    }
    else
    {
        glLightfv(GL_LIGHT0, GL_AMBIENT, Light_None);
    }

    if (diff1 == true)
    {
        glLightfv(GL_LIGHT0, GL_DIFFUSE, DiffuseLight);
    }
    else
    {
        glLightfv(GL_LIGHT0, GL_DIFFUSE, Light_None);
    }

    if (spec1 == true)
    {
        glLightfv(GL_LIGHT0, GL_SPECULAR, SpecularLight);
    }
    else
    {
        glLightfv(GL_LIGHT0, GL_SPECULAR, Light_None);
    }

    glLightfv(GL_LIGHT0, GL_POSITION, PositionLight);
    glPopMatrix();
}

/*function to draw the second light*/

void SecondLight()
{
    glPushMatrix();
    GLfloat Light_None[] = {229.0, 53.0, 115.0, 1.0};
    GLfloat AmbientLight[] = {0.5, 0.5, 0.5, 1.0};
    GLfloat DiffuseLight[] = {1.0, 1.0, 0.9, 1.0};
    GLfloat SpecularLight[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat PositionLight[] = {0.0, 5.0, 8.0, 1.0};

    if (amb2 == true)
    {
        glLightfv(GL_LIGHT1, GL_AMBIENT, AmbientLight);
    }
    else
    {
        glLightfv(GL_LIGHT1, GL_AMBIENT, Light_None);
    }

    if (diff2 == true)
    {
        glLightfv(GL_LIGHT1, GL_DIFFUSE, DiffuseLight);
    }
    else
    {
        glLightfv(GL_LIGHT1, GL_DIFFUSE, Light_None);
    }

    if (spec2 == true)
    {
        glLightfv(GL_LIGHT1, GL_SPECULAR, SpecularLight);
    }
    else
    {
        glLightfv(GL_LIGHT1, GL_SPECULAR, Light_None);
    }

    glLightfv(GL_LIGHT1, GL_POSITION, PositionLight);
    glPopMatrix();
}

/*Function to make the lamp light*/

void LampLight()
{
    glPushMatrix();
    GLfloat Light_None[] = {0.0, 0.0, 0.0, 1.0};
    GLfloat AmbientLight[] = {0.5, 0.5, 0.5, 1.0};
    GLfloat DiffuseLight[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat SpecularLight[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat PositionLight[] = {0.7, 1.5, 9.0, 1.0};

    if (amb3 == true)
    {
        glLightfv(GL_LIGHT2, GL_AMBIENT, AmbientLight);
    }
    else
    {
        glLightfv(GL_LIGHT2, GL_AMBIENT, Light_None);
    }

    if (diff3 == true)
    {
        glLightfv(GL_LIGHT2, GL_DIFFUSE, DiffuseLight);
    }
    else
    {
        glLightfv(GL_LIGHT2, GL_DIFFUSE, Light_None);
    }

    if (spec3 == true)
    {
        glLightfv(GL_LIGHT2, GL_SPECULAR, SpecularLight);
    }
    else
    {
        glLightfv(GL_LIGHT2, GL_SPECULAR, Light_None);
    }

    glLightfv(GL_LIGHT2, GL_POSITION, PositionLight);
    GLfloat DirectionSpot[] = {0.3, -1, -0.8};
    glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, DirectionSpot);
    glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 35.0);
    glPopMatrix();
}

/*Function to display all the scene at once*/

void Display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, 1, 1, 100);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(eyeX, eyeY, eyeZ, refX, refY, refZ, 0, 1, 0);

    /*Enabling the lighting effect*/
    glEnable(GL_LIGHTING);

    /*calling all the function to assemble our scene*/
    FirstLight();
    SecondLight();
    LampLight();
    Room();
    Bed();
    BedSideDrawer();
    DrawLamp();
    Poster();
    Shelf_Wall();
    Wardrobe();
    Cupboard();
    DressingTable();
    DrawClock();
    Window();
    LightBulb1();
    LightBulb2();
    glDisable(GL_LIGHTING);
    glFlush();
    glutSwapBuffers();
}

/*Function for using our special keys for different features*/
void KeyboardInputFunction(unsigned char key, int x, int y)
{
    switch (key)
    {

    // move eye point upwards along Y axis
    case 'w':
        eyeY += 1.0;
        break;
    // move eye point downwards along Y axis
    case 's':
        eyeY -= 1.0;
        break;
    // move eye point left along X axis
    case 'a':
        eyeX -= 1.0;
        break;
    // move eye point right along X axis
    case 'd':
        eyeX += 1.0;
        break;
    // zoom out
    case 'o':
        eyeZ += 1;
        break;
    case 'i': // zoom in
        eyeZ -= 1;
        break;
    // back to default eye point and ref point
    case 'q':
        eyeX = 7.0;
        eyeY = 2.0;
        eyeZ = 15.0;
        refX = 0.0;
        refY = 0.0;
        refZ = 0.0;
        break;
    // move ref point upwards along Y axis
    case 'j':
        refY += 1.0;
        break;
    // move ref point downwards along Y axis
    case 'n':
        refY -= 1.0;
        break;
    // move ref point left along X axis
    case 'b':
        refX -= 1.0;
        break;
    // move eye point right along X axis
    case 'm':
        refX += 1.0;
        break;
    // move ref point away from screen/ along z axis
    case 'k':
        refZ += 1;
        break;
    // move ref point towards screen/ along z axis
    case 'l':
        refZ -= 1;
        break;
    // to turn on and off light one
    case '1':
        if (FirstSwitch == false)
        {
            FirstSwitch = true;
            amb1 = true;
            diff1 = true;
            spec1 = true;
            glEnable(GL_LIGHT0);
            break;
        }
        else if (FirstSwitch == true)
        {
            FirstSwitch = false;
            amb1 = false;
            diff1 = false;
            spec1 = false;
            glDisable(GL_LIGHT0);
            break;
        }

    // to turn on and off light two
    case '2':
        if (SecondSwitch == false)
        {
            SecondSwitch = true;
            amb2 = true;
            diff2 = true;
            spec2 = true;
            glEnable(GL_LIGHT1);
            break;
        }
        else if (SecondSwitch == true)
        {
            SecondSwitch = false;
            amb2 = false;
            diff2 = false;
            spec2 = false;
            glDisable(GL_LIGHT1);
            break;
        }
    // to turn on and off light one
    case '3':
        if (SwitchLamp == false)
        {
            SwitchLamp = true;
            amb3 = true;
            diff3 = true;
            spec3 = true;
            glEnable(GL_LIGHT2);
            break;
        }
        else if (SwitchLamp == true)
        {
            SwitchLamp = false;
            amb3 = false;
            diff3 = false;
            spec3 = false;
            glDisable(GL_LIGHT2);
            break;
        }

    // turn on/off ambient light 1
    case '4':
        if (amb1 == false)
        {
            amb1 = true;
            break;
        }
        else
        {
            amb1 = false;
            break;
        }
    case '5':
        if (diff1 == false)
        {
            diff1 = true;
            break;
        }
        else
        {
            diff1 = false;
            break;
        }
    case '6':
        if (spec1 == false)
        {
            spec1 = true;
            break;
        }
        else
        {
            spec1 = false;
            break;
        }
    case 'e': // turn on/off ambient lamp light
        if (amb3 == false)
        {
            amb3 = true;
            break;
        }
        else
        {
            amb3 = false;
            break;
        }
    case 'r':
        if (diff3 == false)
        {
            diff3 = true;
            break;
        }
        else
        {
            diff3 = false;
            break;
        }
    case 't':
        if (spec3 == false)
        {
            spec3 = true;
            break;
        }
        else
        {
            spec3 = false;
            break;
        }

    // Escape key
    case 27:
        exit(1);
    }

    glutPostRedisplay();
}

/*Function for the animation*/
void Animate()
{
    if (FlaggerRed == true)
    {
        Theta += 2;
        z -= 0.02;
        if (Theta >= 196 && Theta <= 210)
        {
            y = 1.44;
        }
        else if (Theta >= 180 && Theta <= 194)
        {
            y = 1.42;
        }
        else if (Theta >= 180 && Theta <= 194)
        {
            y = 1.4;
        }
        else if (Theta >= 164 && Theta <= 178)
        {
            y = 1.42;
        }

        if (Theta == 210)
        {
            FlaggerRed = false;
        }
    }
    else if (FlaggerRed == false)
    {
        Theta -= 2;
        z += 0.02;

        if (Theta >= 196 && Theta <= 210)
        {
            y = 1.44;
        }
        else if (Theta >= 180 && Theta <= 194)
        {
            y = 1.42;
        }
        else if (Theta >= 180 && Theta <= 194)
        {
            y = 1.4;
        }
        else if (Theta >= 164 && Theta <= 178)
        {
            y = 1.42;
        }

        if (Theta == 150)
        {
            FlaggerRed = true;
        }
    }

    glutPostRedisplay();
}

void MakeFullScreen(int w, int h)
{
    // Prevent a divide by zero, when window is too short;you cant make a window of zero width.
    if (h == 0)
        h = 1;
    float Ratio = (GLfloat)w / (GLfloat)h; // Calculate aspect ratio of the window

    // Set the perspective coordinate system
    glMatrixMode(GL_PROJECTION); // Use the Projection Matrix
    glLoadIdentity();            // Reset Matrix

    glViewport(0, 0, w, h);            // Set the viewport to be the entire window
    gluPerspective(60, Ratio, 1, 500); // Set the correct perspective.
    // glFrustum(-2.5,2.5,-2.5,2.5, ratio, 200);
    glMatrixMode(GL_MODELVIEW); // Get Back to the Modelview
}

/*Main Routine Begins*/

int main(int argc, char **argv)
{
    glutInit(&argc, argv);

    /*Here we are printing the interaction for easy use for the user to run the various features of our project model */
    std::cout << "     ============================= PRINT INTERACTION ===========================      \n\n\n"
              << std::endl;
    std::cout << "To move Eye point:" << std::endl;
    std::cout << "w: up" << std::endl;
    std::cout << "s: down" << std::endl;
    std::cout << "a: left" << std::endl;
    std::cout << "d: right" << std::endl;
    std::cout << "i: zoom in" << std::endl;
    std::cout << "o: zoom out" << std::endl;
    std::cout << "      " << std::endl;
    std::cout << "To move Camera point:" << std::endl;
    std::cout << "j: up" << std::endl;
    std::cout << "n: down" << std::endl;
    std::cout << "b: left" << std::endl;
    std::cout << "m: right" << std::endl;
    std::cout << "l: move nearer" << std::endl;
    std::cout << "k: move far" << std::endl;
    std::cout << "      " << std::endl;
    std::cout << "Press q to move to default position" << std::endl;
    std::cout << "      " << std::endl;
    std::cout << "For lighting:      " << std::endl;
    std::cout << "Light source 1 [the light on the right on the screen      " << std::endl;
    std::cout << "1: to turn on/off light one     " << std::endl;
    std::cout << "4: to turn on/off ambient light one     " << std::endl;
    std::cout << "5: to turn on/off diffusion light one     " << std::endl;
    std::cout << "6: to turn on/off specular light one      " << std::endl;
    std::cout << "      " << std::endl;
    std::cout << "Light source 2 [the light on the left on the screen " << std::endl;
    std::cout << "2: to turn on/off light two     " << std::endl;
    std::cout << "      " << std::endl;
    std::cout << "Lamp light (spot light)" << std::endl;
    std::cout << "3: to turn on/off lamp     " << std::endl;
    std::cout << "e: to turn on/off ambient lamp light    " << std::endl;
    std::cout << "r: to turn on/off diffusion lamp light      " << std::endl;
    std::cout << "t: to turn on/off specular lamp light      " << std::endl;
    std::cout << "      " << std::endl;
    std::cout << "____________________" << std::endl;
    std::cout << "      " << std::endl;
    std::cout << "      " << std::endl;

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    // Intitializing the window position
    glutInitWindowPosition(150, 0);
    // Initializing the window size
    glutInitWindowSize(windowHeight, windowWidth);
    // Naming of the model screen
    glutCreateWindow("Mini Project: Team 14");

    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);

    glutReshapeFunc(MakeFullScreen);
    glutDisplayFunc(Display);
    glutKeyboardFunc(KeyboardInputFunction);
    glutIdleFunc(Spin);
    glutIdleFunc(Animate); // Calling our animate function
    glutMainLoop();
    return 0;
}
