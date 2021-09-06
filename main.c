#include <GL/gl.h>
#include <GL/freeglut.h>
#include <math.h>
#include <ctype.h>
#include "libs/colors.h"
#include "libs/vectors.h"
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

	CAM.position = (Vec3D) {0.0f, 3.0f, 0.0f};
	CAM.rotation = (Vec3D) {-90.0f, 0.0f, 0.0f};
	
	glutMainLoop();

	return 0;
}

void init_gl() {
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
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

	draw_grid(50);
	draw_axis(1, 1, 1);

	buildFrontWall();
	buildBackWall();
	buildWindow(window.angle);
	buildLeftWall();
	buildRightWall();
	buildDoor(door.angle);
	buildFloor();
	buildCeiling();
	buildSink();
	buildSinkUpperCabinet();
	buildFridge();
	buildStove();
	buildCabinet();

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
	} else if (key == 112) { // p
		changeDoorState();
	} else if (key == 106) { // j
		changeWindowState();
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

// Grid

void draw_axis(int x, int y, int z) {
	glLineWidth(3.0f);
	glBegin(GL_LINES);
	if(x) {
		glColor3f(RED);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(ZFAR, 0.0f, 0.0f);
	}
	if(y) {
		glColor3f(GREEN);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, ZFAR, 0.0f);
	}
	if(z) {
		glColor3f(BLUE);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, 0.0f, ZFAR);
	}
	glEnd();
	glLineWidth(1.0f);
}

void draw_grid(int n) {
	int i;

	glBegin(GL_LINES);
	glColor3f(WHITE);
	for(i = -n;i < n;i++){
		float d = (float) i;
		// Parallel to x-axis 
		glVertex3f(-n, 0.0f, d);
		glVertex3f(n, 0.0f, d);
		// Parallel to z-axis
		glVertex3f(d, 0.0f, -n);
		glVertex3f(d, 0.0f, n);
	}
	glEnd();
}