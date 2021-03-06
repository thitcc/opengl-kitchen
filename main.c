#include <stdlib.h>
#include <GL/gl.h>
#include <GL/freeglut.h>
#include <math.h>
#include <ctype.h>
#include "libs/colors.h"
#include "libs/vectors.h"
#include "libs/texture.h"
#include "libs/build.h"
#include "libs/animation.h"

// Points of Interest
#define ORIGIN 0.0f, 0.0f, 0.0f
#define RIGHT 1.0f, 0.0f, 0.0f
#define UP 0.0f, 1.0f, 0.0f
#define FORWARD 0.0f, 0.0f, -1.0f
#define FPS 120

typedef struct Transform {
	Vec3D position;
	Vec3D rotation;
	Vec3D scale;
} Transform;

// Global variables

const float DEG2RAD = M_PI / 180.0f;
const float RAD2DEG = 180.0f / M_PI;

Vec2D WINDOW_SIZE = {1920, 1080};
Vec2D WINDOW_CENTER = {960, 540};

float FOVY = 75.0f;
float ZNEAR = 10e-3;
float ZFAR = 10e3;

Transform CAM;

int KEYBOARD[128] = {0};

GLfloat light0_ambient[] = { 0.1, 0.1, 0.1, 1.0 };
GLfloat light0_diffuse[] = { 1.0, 1.0, 0.9, 1.0 };
GLfloat light0_specular[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat light0_position[] = { 10.0f, 5.0f, 10.0f, 1.0f };

void init_gl();

// Callbacks

void display();

void idle();

void motion(int x, int y);

void keyboard(unsigned char key, int x, int y);

void keyboard_up(unsigned char key, int x, int y);

void reshape(int width, int height);

void draw_axis(int x, int y, int z);

void draw_grid(int n);

void init_light();

void setup_light();

// Math utils

Vec3D forward(Transform* t);

Vec3D right(Transform* t);

Vec3D up(Transform* t);


int main(int argc, char** argv) {
	glutInit(&argc, argv);

	glutInitWindowSize(WINDOW_SIZE.x, WINDOW_SIZE.y);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow("Kitchen");
	glutWarpPointer(WINDOW_CENTER.x, WINDOW_CENTER.y);	

	glutDisplayFunc(display);
	glutPassiveMotionFunc(motion);
	glutKeyboardFunc(keyboard);
	glutKeyboardUpFunc(keyboard_up);
	glutReshapeFunc(reshape);
	glutTimerFunc(1000 / FPS, idle, 0);

	init_gl();

	init_textures();

	CAM.position = (Vec3D) {0.0f, 3.0f, 0.0f};
	CAM.rotation = (Vec3D) {-90.0f, 0.0f, 0.0f};
	
	init_light();

	glEnable(GL_COLOR_MATERIAL);
  glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	glutMainLoop();

	return 0;
}

void init_gl() {
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
}

void init_light() {
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);

	// Anti aliasing
	glEnable(GL_LINE_SMOOTH);   
	glEnable(GL_POINT_SMOOTH);   
	glEnable(GL_BLEND);    

	// Lighting and Shade
	glEnable(GL_DEPTH_TEST);   
	glDepthFunc(GL_LEQUAL);   
	glShadeModel(GL_SMOOTH);     
	glEnable(GL_LIGHT0);
}

void setup_light() {
	glPushMatrix();
    glEnable(GL_LIGHTING);

    glPushMatrix();
      glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);
      glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
      glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular);
      glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
    glPopMatrix();
  glPopMatrix();
}

// Callbacks
void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// View matrix
	Vec3D fwd = forward(&CAM);
	Vec3D u = up(&CAM);
	Vec3D eye = CAM.position;
	Vec3D center = {eye.x + fwd.x, eye.y + fwd.y, eye.z + fwd.z};

	gluLookAt(eye.x, eye.y, eye.z, center.x, center.y, center.z, u.x, u.y, u.z); 

	setup_light();

	changeCeilingFanAngle();

	buildFrontWall(&wall_texture);
	buildBackWall(&wall_texture);
	buildWindow(window.angle, &window_texture);
	buildLeftWall(&wall_texture);
	buildRightWall(&wall_texture);
	buildDoor(door.angle, &door_texture);
	buildFloor(&tile_texture);
	buildCeiling(&ceiling_texture);
	buildSink(&cabinet_door_texture, &metal_texture, &metal_matte_texture);
	buildSinkUpperCabinet(&wood_texture, &cabinet_door_texture);
	buildFridge(&metal_texture, &fridge_texture);
	buildStove(&metal_texture, &stove_front_texture, &stove_up_texture);
	buildCabinet(&wood_texture, &cabinet_door_texture);
	buildTable();
	buildLighting();
	buildCeilingFan(ceiling_fan_angle, &metal_texture);
	buildPainting(&confuso_texture);

	doorAnimation();
	windowAnimation();
	
	glutSwapBuffers();
}

void idle(int value) {
	// Forward movement
	int move_forward = KEYBOARD['w'] - KEYBOARD['s'];
	Vec3D fwd = forward(&CAM);
	
	fwd.x *= move_forward;
	fwd.y = 0.0f; // Projects fwd in the xz plane
	fwd.z *= move_forward;

	// Lateral movement
	int move_right = KEYBOARD['d'] - KEYBOARD['a'];
	Vec3D rgt = right(&CAM);

	rgt.x *= move_right;
	rgt.z *= move_right;

	int move_up = KEYBOARD[' '] - KEYBOARD['c'];
	Vec3D upw = up(&CAM);

	upw.y *= move_up;
	
	CAM.position.x += 0.1f * (fwd.x + rgt.x);
	CAM.position.y += 0.1f * upw.y;
	CAM.position.z += 0.1f * (fwd.z + rgt.z);

	glutPostRedisplay();
	glutTimerFunc(1000 / FPS, idle, 0);
}

void motion(int x, int y) { 
	static int wrap = 0;
	Vec2D delta;
	
	if (!wrap) {
		delta.x = x - WINDOW_CENTER.x;
		delta.y = y - WINDOW_CENTER.y;
		
		CAM.rotation.x += delta.y > 0 ? -1.0f : (delta.y < 0 ? 1.0f : 0.0f);
		CAM.rotation.y -= delta.x > 0 ? 1.0f : (delta.x < 0 ? -1.0f : 0.0f);

		wrap = 1;
		glutWarpPointer(WINDOW_CENTER.x, WINDOW_CENTER.y);
	} else {
		wrap = 0;
	}
}

void keyboard(unsigned char key, int x, int y){
	key = tolower(key);

	if (key == 27) { // ESC
		glutLeaveMainLoop();
	} else if (key == 'p') {
		changeDoorState();
	} else if (key == 'j') {
		changeWindowState();
	} else if (key == 'l') {
		glEnable(GL_LIGHT0);
	} else if (key == 'k') {
		glDisable(GL_LIGHT0);
	}
		
	KEYBOARD[tolower(key)] = 1;
}

void keyboard_up(unsigned char key, int x, int y){
	KEYBOARD[tolower(key)] = 0;
}

void reshape(int width, int height) {
	float aspect = (float) width / (float) height;
	WINDOW_SIZE.x = width;
	WINDOW_SIZE.y = height;
	WINDOW_CENTER.x = width / 2;
	WINDOW_CENTER.y = height / 2;

	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(FOVY, aspect, ZNEAR, ZFAR);
}

Vec3D forward(Transform* t) {
	Vec3D v;
	float a = t->rotation.x * DEG2RAD;
	float b = t->rotation.y * DEG2RAD;
	float c = t->rotation.z * DEG2RAD;

	v.x = -(sin(c) * sin(a) + cos(c) * sin(b) * cos(a));
	v.y = -(-cos(c) * sin(a) + sin(c) * sin(b) * cos(a));
	v.z = -(cos(b) * cos(a));

	return v;
}

Vec3D up(Transform* t) {
	Vec3D v;
	float a = t->rotation.x * DEG2RAD;
	float b = t->rotation.y * DEG2RAD;
	float c = t->rotation.z * DEG2RAD;

	v.x = -sin(c) * cos(a) + cos(c) * sin(b) * sin(a);
	v.y = cos(c) * cos(a) + sin(c) * sin(b) * sin(a);
	v.z = cos(b) * sin(a);
	
	return v;
}

Vec3D right(Transform* t) {
	Vec3D v;
	float a = t->rotation.x * DEG2RAD;
	float b = t->rotation.y * DEG2RAD;
	float c = t->rotation.z * DEG2RAD;

	v.x = cos(c) * cos(b);
	v.y = sin(c) * cos(b);
	v.z = -sin(b);

	return v;
}