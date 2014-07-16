//High Resolution timer found on: http://cplus.about.com/od/howtodothingsi2/a/timing.htm

#ifndef __HR_TIME_H
#define __HR_TIME_H

#include <windows.h>

typedef struct {
    LARGE_INTEGER start;
    LARGE_INTEGER stop;
} stopWatch;

class CStopWatch {

private:
	stopWatch timer;
	LARGE_INTEGER frequency;
	double LIToSecs( LARGE_INTEGER & L);
public:
	CStopWatch();
	void startTimer( );
	void stopTimer( );
	double getElapsedTime();
};

#endif


