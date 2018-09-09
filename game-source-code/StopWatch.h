#ifndef STOPWATCH_H
#define STOPWATCH_H

class StopWatch{

public:
	// Constructor:
	StopWatch(): startTime_(0.0), pauseTime_( 0.0),
	resumeTime_(0.0), stopTime_(0.0), runTime_(0.0), lapTime_(0.0), mode_(Mode::STOPPED){};

	// Strongly typed enum containing stopwatch operations:
	enum class Mode{ RUNNING, PAUSED, STOPPED};

	//starts the timer
	void start ();

	// Pauses the stopwatch:
	void pause();

	// Resumes the stopwatch:
	void resume();

	// Stops the timer and resets:
	void stop();

	// returns the amount of time in seconds that has passed in the piece of code.
	double getLapTime();

	// returns the amount of time in seconds that has passed in the piece of code.
	double getRunTime();

	// returns the amount of time in seconds that has passed since the process (i.e. your program) started executing
	double getProcessTime();

private:
	// Private members:
	double startTime_;
	double pauseTime_;
	double resumeTime_;
	double stopTime_;
	double runTime_;
	double lapTime_;

	// Stores current operation of stop watch:
	Mode mode_;
};
#endif
