#ifndef __VIDEOSTREAM__
#define __VIDEOSTREAM__

#include <pthread.h>
#include <string>


class VideoStream {
public:
	VideoStream(int);
	VideoStream(std::string);
	~VideoStream();

	int start();
	void release();
	void operator>>(cv::Mat&);
	bool read(cv::Mat&);
	bool isOpened();

private:
	cv::VideoCapture video;
	cv::Mat frame;
	
	bool isGrabbed;
	bool _isOpened;
	bool isRunning;
	pthread_t thread;

	void setup();
	friend void* stream(void*);
};

void* stream(void*);

#endif