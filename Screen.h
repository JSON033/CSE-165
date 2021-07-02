//#pragma once
#ifndef Screen_h
#define Screen_h

enum Size { small, big };
enum Color { red, blue, black, white };

struct Screen {

	float x;
	float y;
	Size w;
	Color h;






	Screen();

	Screen(float x, float y, Size w, Color h);

	float Screen::getX();
	float Screen::getY();
	Size Screen::getSize();
	Color Screen::getColor();
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
};



#endif /* Screen_h */