#ifndef __VIDEOSTREAM__
#define __VIDEOSTREAM__

#include <pthread.h>
#include <string>


class VideoStream {
public:
	VideoStream(int);
	VideoStream(std::string);
	~VideoStream();

	void start();
	void stop();
	void operator>>(cv::Mat&);
	cv::Mat& read();
	bool isOpened();

private:
	cv::VideoCapture video;
	cv::Mat frame;
	
	bool isGrabbed;
	bool _isOpened;
	bool isRunning;
	pthread_t thread;

	friend void* stream(void*);
};

void* stream(void*);

#endif