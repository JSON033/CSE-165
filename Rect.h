#ifndef Rect_h
#define Rect_h
enum Shape { blank, circle, exe };
struct Rect {
	float x;
	float y;
	float w;
	float h;

	bool occupied;
	Shape shape;

	Rect();

	Rect(float x, float y, float w, float h);

	bool contains(float mx, float my);

	void draw();
};



#endif /* Rect_h */