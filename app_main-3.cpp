#include <iostream>
#include <cmath>
#include <vector>
#if defined WIN32
#include <freeglut.h>
#elif defined __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>

#endif

#include "Rect.h"
#include "Screen.h"
using namespace std;
float brush = 0.1;
//enum Size {small, big};
//enum Color { red, blue, black, white };

bool dragging = false;
float xOffset = 0.3;

float yOffset = 0.2;
float xD = 0;
float yD = 0;


Color c;
Size m;


// Store the width and height of the window
int width = 640, height = 640;

/*
struct Screen {

	float x;
	float y;
	Size w;
	Color h;

	
	
		
	

	Screen() {

		x = -0.5;
		y = 0.5;
		

		w = small;
		h = black;

	}
	
	Screen(float x, float y, Size w, Color h) {

		this->x = x;
		this->y = y;
		this->w = w;
		this->h = h;

		

	}

	float Screen::getX() {
		return x;
	}
	float Screen::getY() {
		return y;
	}
	Size Screen::getSize() {
		return w;
	}
	Color Screen::getColor() {
		return h;
	}
	/*
	void draw() {
		if (w == small) {
			if (h == white) {
				glColor3f(1, 1, 1);
			}
			if (h == blue) {
				glColor3f(1, 0, 0);
			}
			if (h == red) {
				glColor3f(0, 0, 1);
			}
			if (c == black) {
				glColor3f(0.0f, 0.0f, 0.0f);
			}
			
			
			glBegin(GL_POLYGON);
			glVertex2f(x, y);
			glVertex2f(x + w, y - w);

			glVertex2f(x, y - w);
			glVertex2f(x + w, y);
			glEnd();

		}
		if (w == big) {
			if (h== white) {
				glColor3f(1, 1, 1);
			}
			if (h== blue) {
				glColor3f(1, 0, 0);
			}
			if (h == red) {
				glColor3f(0, 0, 1);
			}
			if (c == black) {
				glColor3f(0.0f, 0.0f, 0.0f);
			}
				
			glBegin(GL_POLYGON);
			glVertex2f(x, y);
			glVertex2f(x + w, y - w);

			glVertex2f(x, y - w);
			glVertex2f(x + w, y);
			glEnd();
		}
	}
	
};

*/

vector <Screen> screen;
//-------------------------------------------------------
// A function to draw the scene
//-------------------------------------------------------
void appDrawScene() {
	// Clear the screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



	// Set background color to black
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	// Set up the transformations stack
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();




	for (int i = screen.size()-1; i > 0; i--) {
	float	x = screen[i].getX();
	float	y = screen[i].getY();
	Size w = screen[i].getSize();
	Color h = screen[i].getColor();
	float brush;
	if (h == 3) {
		glColor3f(1, 1, 1);
	}
	if (h == 0) {
		glColor3f(1, 0, 0);
	}
	if (h == 1) {
		glColor3f(0, 0, 1);
	}
	if (h == 2) {
		glColor3f(0.0f, 0.0f, 0.0f);
	}
	if (w == 0) {
		brush = 0.1;
	}
	if (w == 1) {
		brush = 0.2;
	}
	glBegin(GL_POLYGON);
	glVertex2f(x, y);
	glVertex2f(x + brush, y );

	glVertex2f(x + brush, y - brush);
	glVertex2f(x, y - brush);
	glEnd();
	/*
	cout << "x " << x << endl;
	cout << "y " << y << endl;
	cout << "size " << w << endl;
	cout << "color " << h << endl;
	cout << "brush" << brush << endl;

	*/
	}

	/*
	glColor3f(0, 1, 1);
	glBegin(GL_POLYGON);
	glVertex2f(0.1, 0.1);
	glVertex2f(0.1 + 0.1, 0.1);

	glVertex2f(0.1 + 0.1, 0.1 - 0.1);
	glVertex2f(0.1, 0.1 - 0.1);
	glEnd();
	*/

	
	
	
    // Draw stuff here
	
	




		//Blocks::makeblock();
		
		
	

		
    
	// We have been drawing everything to the back buffer
	// Swap the buffers to see the result of what we drew
	glFlush();
	glutSwapBuffers();
	

}


//-------------------------------------------------------
// A function to convert window coordinates to scene
// We use it when a mouse event is handled
// Arguments: 	
//	x, y - the coordinates to be updated
//-------------------------------------------------------
void windowToScene(float& x, float& y) {
	x = (2.0f*(x / float(width))) - 1.0f;
	y = 1.0f - (2.0f*(y / float(height)));
}

//-------------------------------------------------------
// A function to handle window resizing
// Called every time the window is resized
// Arguments: 	
//	b    - mouse button that was clicked, left or right
//	s 	 - state, either mouse-up or mouse-down
//	x, y - coordinates of the mouse when click occured
//-------------------------------------------------------
void appReshapeFunc(int w, int h) {
	// Window size has changed
	width = w;
	height = h;

	double scale, center;
	double winXmin, winXmax, winYmin, winYmax;

	// Define x-axis and y-axis range
	const double appXmin = -1.0;
	const double appXmax = 1.0;
	const double appYmin = -1.0;
	const double appYmax = 1.0;

	// Define that OpenGL should use the whole window for rendering
	glViewport(0, 0, w, h);

	// Set up the projection matrix using a orthographic projection that will
	// maintain the aspect ratio of the scene no matter the aspect ratio of
	// the window, and also set the min/max coordinates to be the disered ones
	w = (w == 0) ? 1 : w;
	h = (h == 0) ? 1 : h;

	if ((appXmax - appXmin) / w < (appYmax - appYmin) / h) {
		scale = ((appYmax - appYmin) / h) / ((appXmax - appXmin) / w);
		center = (appXmax + appXmin) / 2;
		winXmin = center - (center - appXmin)*scale;
		winXmax = center + (appXmax - center)*scale;
		winYmin = appYmin;
		winYmax = appYmax;
	}
	else {
		scale = ((appXmax - appXmin) / w) / ((appYmax - appYmin) / h);
		center = (appYmax + appYmin) / 2;
		winYmin = center - (center - appYmin)*scale;
		winYmax = center + (appYmax - center)*scale;
		winXmin = appXmin;
		winXmax = appXmax;
	}

	// Now we use glOrtho to set up our viewing frustum
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(winXmin, winXmax, winYmin, winYmax, -1, 1);
}


//-------------------------------------------------------
// A function to handle mouse clicks
// Called every time the mouse button goes up or down
// Arguments: 	
//	b    - mouse button that was clicked, left or right
//	s 	 - state, either mouse-up or mouse-down
//	x, y - coordinates of the mouse when click occured
//-------------------------------------------------------
void appMouseFunc(int b, int s, int x, int y) {
	// Convert from Window to Scene coordinates
	// here we can use this as the version of click i get it now

	float mx = (float)x;
	float my = (float)y;

	windowToScene(mx, my);
	
	
	


	// Redraw the scene by calling appDrawScene above
	// so that the point we added above will get painted
	glutPostRedisplay();
}

//-------------------------------------------------------
// A function to handle mouse dragging
// Called every time mouse moves while button held down
// Arguments: 	
//	x, y - current coordinates of the mouse
//-------------------------------------------------------
void appMotionFunc(int x, int y) {
	//cout << "hi " << endl;
	float mx = (float)x;
	float my = (float)y;

	windowToScene(mx, my);
	
		xOffset = mx - xD;
		yOffset = my - yD;
	
	/*
	if (c == white) {
		glColor3f(1, 1, 1);
	}
	if (c == red) {
		glColor3f(1, 0, 0);
	}
	if (c == blue) {
		glColor3f(0, 0, 1);
	}
	if (c == black) {
		glColor3f(0.0f, 0.0f, 0.0f);
	}
	if (m == small) {
		brush = 0.1;
	}
	if (m == big) {
		brush = 0.2;
	}
	GLint x = mx;
	GLint y = my;
	*/
//	cout << xOffset << "x Offest" << endl;
	Screen nscreen(xOffset, yOffset, m, c);
	screen.push_back(nscreen);
	glFlush();
	
	// Again, we redraw the scene
	glutPostRedisplay();
}

//-------------------------------------------------------
// A function to handle keyboard events
// Called every time a key is pressed on the keyboard
// Arguments: 	
//	key  - the key that was pressed
//	x, y - coordinates of the mouse when key is pressed
//-------------------------------------------------------
void appKeyboardFunc(unsigned char key, int x, int y) {
	
	switch (key) {
	case 27:
		exit(0);
		break;
	case 'q' :
		c = blue;
		break;
	case 'w':
		c = white;
		break;
	case 'e':
		c = black;
		break;

	case 'r':
		c = red;
		break;
	case 'b':
		m = big;
		cout << "big" << big << endl;
		break;
	case 's':
		m = small;
		
		break;
	default:
		break;
	}

	// After all the state changes, redraw the scene
	glutPostRedisplay();
}


void idle() {
	glutDisplayFunc(appDrawScene);
}


int main(int argc, char** argv) {
	// Initialize GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);

	// Setup window position, size, and title
	glutInitWindowPosition(20, 60);
	glutInitWindowSize(width, height);
	glutCreateWindow("CSE165 OpenGL Demo");

	// Setup some OpenGL options
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_LINE_SMOOTH);

	// Set callback for drawing the scene
	glutDisplayFunc(appDrawScene);

	// Set callback for resizing th window
    glutReshapeFunc(appReshapeFunc);

	// Set callback to handle mouse clicks
	glutMouseFunc(appMouseFunc);

	// Set callback to handle mouse dragging
	glutMotionFunc(appMotionFunc);

	// Set callback to handle keyboad events
	glutKeyboardFunc(appKeyboardFunc);
    
    glutIdleFunc(idle);
	cout << "q for blue, w for erase, e for black, r for red " << endl;
	cout << "s for small, b for big" << endl;
	// Start the main loop
	glutMainLoop();
}
