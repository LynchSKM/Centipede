#ifndef STOPWATCH_H
#define STOPWATCH_H

class StopWatch{

public:
	// Constructor:
	/**< \brief Default Constructor. Creates a Stopwatch object. */
	StopWatch(): startTime_(0.0), pauseTime_( 0.0),
	resumeTime_(0.0), stopTime_(0.0), runTime_(0.0), lapTime_(0.0), mode_(Mode::STOPPED){};

	/**< \brief Strongly typed enum containing stopwatch operations. */
	enum class Mode{ RUNNING, PAUSED, STOPPED};

	/**< \brief Starts the timer. */
	void start ();

	/**< \brief Pauses the stopwatch. */
	void pause();

	/**< \brief Resumes the stopwatch. */
	void resume();

	/**< \brief Stops the timer and resets. */
	void stop();

	/** \brief Returns the amount of time in seconds that has passed in the piece of code.
	 *  \return double
	 */
	double getLapTime();

	/** \brief Returns the amount time in seconds between start() and pause().
	 *  \return double
	 */
    double getPauseTime() {return pauseTime_;};

    /** \brief Returns the amount time in seconds when stop is called.
	 *  \return double
	 */
    double getStopTime();

	/** \brief Returns the amount of time in seconds that has passed in the piece of code.
	 *  \return double
	 */
	double getRunTime();

	/** \brief Returns the amount of time in seconds that has passed since the process (i.e. your program) started executing.
	 *  \return double
	 */
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
