#include "StopWatch.h"
#include <ctime>
using namespace std;


//starts the count
void StopWatch::start(){
	// If stopwatch is not already running, start it:
	if (mode_ != Mode::RUNNING)
		mode_ = Mode::RUNNING;
		startTime_ = getProcessTime(); 
	return;
}

void StopWatch::pause(){
	// If stopwatch is not already paused, pause it:
	if (mode_ != Mode::PAUSED)
		mode_ = Mode::PAUSED;
		pauseTime_ = getProcessTime(); 
	
	return;	
}

void StopWatch::resume(){
	// If stopwatch is paused:
	if (mode_ == Mode::PAUSED){
		// Set it to running:
		mode_ = Mode::RUNNING;
		resumeTime_ = getProcessTime(); 
		runTime_ -= (resumeTime_ - pauseTime_);
		lapTime_ += (resumeTime_ - pauseTime_);
	}//if
	return;	
}

void StopWatch::stop(){
	// If stopwatch is not already stopped, stop it:
	if (mode_!=Mode::STOPPED)
		mode_ = Mode::STOPPED;
		stopTime_ = getProcessTime(); 
	return;	
}

double StopWatch::getLapTime(){
	if (mode_!=Mode::STOPPED || mode_ == Mode::PAUSED)
		lapTime_ = getProcessTime() - lapTime_;
	return lapTime_;
}

// returns the amount of time in seconds that has passed in the piece of code.
double StopWatch::getRunTime(){
	runTime_ += (stopTime_ - startTime_);
	return runTime_;
}

// returns the amount of time in seconds that has passed since the process (i.e. your program) started executing 
double StopWatch::getProcessTime()
{
	clock_t time = clock();
	return static_cast<double>(time)/CLOCKS_PER_SEC;
}
