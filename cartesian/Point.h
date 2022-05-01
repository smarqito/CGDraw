#pragma once
class Point {
public:
	float x, y, z;
	Point();
	Point(float x, float y, float z);
	void setPoint(Point p);
	void setPoint(float x, float y, float z);
};
