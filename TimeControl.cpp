#include <math.h>
#include "TimeControl.h"

TimeControl::TimeControl() : TimeControl(0.0f)
{
}

TimeControl::TimeControl(float total_time)
{
	_last_refresh = _refresh_rate = 0;
	_total_time = total_time;
}

void TimeControl::setTime(float total_time)
{
	_total_time = total_time;
}

void TimeControl::updateRate()
{
	
	float time = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
	_refresh_rate += (time - _last_refresh) / _total_time; //calculte the new translate_rate
	_refresh_rate -= floor(_refresh_rate);
	_last_refresh = time;
}

float TimeControl::getRate()
{
	return _refresh_rate;
}
