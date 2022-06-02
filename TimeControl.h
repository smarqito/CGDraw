#pragma once
#ifndef _GL_INCLUDE
#define _GL_INCLUDE
#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/gl.h>
#endif // !_GL_INCLUDE
class TimeControl
{
protected:
	float _last_refresh;
	float _refresh_rate;
	float _total_time;
public:
	TimeControl();
	TimeControl(float _total_time);
	void setTime(float total_time);
	void updateRate();
	float getRate();
};