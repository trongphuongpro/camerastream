#ifndef __CAMERASTREAM__
#define __CAMERASTREAM__

#include <pthread.h>
#include <string>


class CameraStream {
public:
	CameraStream(int);
	CameraStream(std::string);
	~CameraStream();

	void release();
	void operator>>(cv::Mat&);
	bool read(cv::Mat&);
	bool isOpened();

private:
	cv::VideoCapture video;
	cv::Mat frame;
	
	bool _isOpened;
	bool isRunning;
	bool isNewFrame;
	pthread_t thread;

	int start();
	void setup();
	friend void* stream(void*);
};

void* stream(void*);

#endif