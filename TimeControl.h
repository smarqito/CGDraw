#pragma once
#include <gl/glut.h>

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