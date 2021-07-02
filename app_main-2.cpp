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
using namespace std;

// Store the width and height of the window
int width = 640, height = 640;
int board[3][3];
bool gameover = false;
bool lonely = true;
bool playernum= true;





vector<Rect> grid;

bool winX(vector<Rect> grid);
bool winO(vector<Rect> grid);


void checkGameState(vector<Rect> grid) {
	if (winX(grid)) {
		cout << "X wins" << endl;
		
		gameover = true;
	}
	if (winO(grid)) {
		cout << "O wins" << endl;
		gameover = true;
	}

	if (!gameover) {
		bool flag = true;
		for (int i = 0; i < grid.size(); i++) {
			if (!grid[i].occupied) {
				flag = false;
				break;
			}
		}
		if (flag) {
			gameover = true;
			cout << "Nobody wins" << endl;
		}
	}
}



bool winX(vector<Rect> grid) {
	Shape temp = exe;
	if (grid[0].shape == temp && grid[1].shape == temp && grid[2].shape == temp) {
		return true;
	}
	if (grid[3].shape == temp && grid[4].shape == temp && grid[5].shape == temp) {
		return true;
	}
	if (grid[6].shape == temp && grid[7].shape == temp && grid[8].shape == temp) {
		return true;
	}
	if (grid[0].shape == temp && grid[3].shape == temp && grid[6].shape == temp) {
		return true;
	}
	if (grid[1].shape == temp && grid[4].shape == temp && grid[7].shape == temp) {
		return true;
	}
	if (grid[2].shape == temp && grid[5].shape == temp && grid[8].shape == temp) {
		return true;
	}
	if (grid[0].shape == temp && grid[4].shape == temp && grid[8].shape == temp) {
		return true;
	}
	if (grid[2].shape == temp && grid[4].shape == temp && grid[6].shape == temp) {
		return true;
	}
	else {
		return false;
	}
}

bool winO(vector<Rect> grid) {
	Shape temp = circle;
	if (grid[0].shape == temp && grid[1].shape == temp && grid[2].shape == temp) {
		return true;
	}
	if (grid[3].shape == temp && grid[4].shape == temp && grid[5].shape == temp) {
		return true;
	}
	if (grid[6].shape == temp && grid[7].shape == temp && grid[8].shape == temp) {
		return true;
	}
	if (grid[0].shape == temp && grid[3].shape == temp && grid[6].shape == temp) {
		return true;
	}
	if (grid[1].shape == temp && grid[4].shape == temp && grid[7].shape == temp) {
		return true;
	}
	if (grid[2].shape == temp && grid[5].shape == temp && grid[8].shape == temp) {
		return true;
	}
	if (grid[0].shape == temp && grid[4].shape == temp && grid[8].shape == temp) {
		return true;
	}
	if (grid[2].shape == temp && grid[4].shape == temp && grid[6].shape == temp) {
		return true;
	}
	else {
		return false;
	}
}


//-------------------------------------------------------
// A function to draw the scene
//-------------------------------------------------------
void appDrawScene() {
	// Clear the screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Set background color to black
	glClearColor(0.0, 0.0, 0.0, 1.0);

	// Set up the transformations stack
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
    

    // Draw stuff here
	for (int i = 0; i < grid.size(); i++) {
		grid[i].draw();
	}
    
	 glColor3f(1.0, 1.0, 1.0);
	
	glBegin(GL_POLYGON);
		glVertex2f(-0.8, 0.4);
		glVertex2f(0.8, 0.4);
		glVertex2f(0.8, 0.2);
		glVertex2f(-0.8, 0.2);
		glEnd();
		
	
		glBegin(GL_POLYGON);
		glVertex2f(-0.8, -0.20);
		glVertex2f(0.8, -0.20);
		glVertex2f(0.8, -0.4);
		glVertex2f(-0.8, -0.4);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex2f(-0.4, 0.8);
		glVertex2f(-0.2, 0.8);
		glVertex2f(-0.2, -0.8);
		glVertex2f(-0.4, -0.8);
		glEnd();
		
    
		glBegin(GL_POLYGON);
		glVertex2f(0.2, 0.8);
		glVertex2f(0.4, 0.8);
		glVertex2f(0.4, -0.8);
		glVertex2f(0.2, -0.8);
		glEnd();

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

	if (b == 0) {
		if (s == 0) {
			// I clicked the left button
			for (int i = 0; i < grid.size(); i++) {
				if (!gameover) {
					if (grid[i].contains(mx, my)) {
						if (!grid[i].occupied) {
							if (playernum) {
								grid[i].shape = exe;
							}
							else {
								grid[i].shape = circle;
							}
							grid[i].occupied = true;
							playernum = !playernum;
						}
						checkGameState(grid);
						if (lonely && !gameover) {
							for (int i = 0; i < grid.size(); i++) {
								if (!grid[i].occupied) {
									grid[i].shape = circle;
									grid[i].occupied = true;
									playernum = !playernum;
									break;
								}
							}
							checkGameState(grid);
						}
						break;
					}
				}
			}
		}
	}


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
	case 'e':
		if (!gameover) {
			gameover = true;
			cout << "Everyone is a winner when you start over" << endl;
			for (int i = 0; i < grid.size(); i++) {
				grid[i].shape = blank;
				grid[i].occupied = false;
				gameover = false;
				playernum = true;
			}
		}
		
		break;
	case 'a':
		if (gameover) {
			for (int i = 0; i < grid.size(); i++) {
				grid[i].shape = blank;
				grid[i].occupied = false;
				gameover = false;
				playernum = true;
			}
			lonely = true;
		}
		break;
	case 'p':
		if (gameover) {
			for (int i = 0; i < grid.size(); i++) {
				grid[i].shape = blank;
				grid[i].occupied = false;
				gameover = false;
				playernum = true;
			}
			lonely = false;
		}
		break;
	case ' ':
		if (gameover) {
			for (int i = 0; i < grid.size(); i++) {
				grid[i].shape = blank;
				grid[i].occupied = false;
				gameover = false;
				playernum = true;
			}
		}
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

	cout << "finish a game and then press p for pvp" << endl;
	cout << "a for ai, space when finished" << endl;
	cout << "press e to restart midgame" << endl;

	grid.push_back(Rect(-0.8, 0.8, 0.4, 0.4));
	grid.push_back(Rect(-0.2, 0.8, 0.4, 0.4));
	grid.push_back(Rect(0.4, 0.8, 0.4, 0.4));

	grid.push_back(Rect(-0.8, 0.2, 0.4, 0.4));
	grid.push_back(Rect(-0.2, 0.2, 0.4, 0.4));
	grid.push_back(Rect(0.4, 0.2, 0.4, 0.4));

	grid.push_back(Rect(-0.8, -0.4, 0.4, 0.4));
	grid.push_back(Rect(-0.2, -0.4, 0.4, 0.4));
	grid.push_back(Rect(0.4, -0.4, 0.4, 0.4));

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

	// Start the main loop
	glutMainLoop();
}
