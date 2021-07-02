#include "Screen.h"

#if defined WIN32
#include <freeglut.h>
#elif defined __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif








	Screen::Screen() {

		x = 0.0;
		y = 0.0;


		w = small;
		h = black;

	}

	Screen::Screen(float x, float y, Size w, Color h) {

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
	*/


