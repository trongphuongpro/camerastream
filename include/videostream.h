#ifndef __VIDEOSTREAM__
#define __VIDEOSTREAM__

#include <pthread.h>
#include <string>
#include "opencv2/videoio.hpp"

class VideoStream {
public:
	VideoStream(int);
	VideoStream(std::string);
	~VideoStream();

	void start();
	void stop();
	void operator>>(cv::Mat&);
	cv::Mat& read();

	bool grab;
	bool isOpened;

private:
	cv::VideoCapture video;
	cv::Mat frame;
	
	bool isRunning;
	

	pthread_t thread;

	friend void* stream(void*);
};

void* stream(void*);

#endif