#include <iostream>
#include <unistd.h>
#include "opencv2/videoio.hpp"
#include "videostream.h"

using namespace std;
using namespace cv;


VideoStream::VideoStream(int camera) {
	this->video = cv::VideoCapture(camera);
	setup();
}


VideoStream::VideoStream(string filename) {
	this->video = cv::VideoCapture(filename);
	setup();
}


void VideoStream::setup() {
	this->isRunning = false;
	this->isGrabbed = false;
	this->_isOpened = this->video.isOpened();

	if (!this->_isOpened)
		cout << "[VideoStream] Cannot open video stream" << endl;
	else {
		cout << "[VideoStream] Opened" << endl;

		if (start())
			cout << "[VideoStream] Streaming thread created" << endl;
		else
			cout << "[VideoStream] Cannot create streaming thread" << endl;
	}
}


VideoStream::~VideoStream() {
	if (this->isRunning)
		this->release();
}


bool VideoStream::isOpened() {
	return this->_isOpened;
}


int VideoStream::start() {
	this->isRunning = true;
	if (pthread_create(&this->thread, NULL, stream, this) == 0) {
		sleep(2);
		return 1;
	}
	
	return 0;
}


void VideoStream::release() {
	this->isRunning = false;
}


bool VideoStream::read(Mat& frame) {
	frame = this->frame;
	return this->isGrabbed;
}


void VideoStream::operator>>(Mat& frame) {
	frame = this->frame;
}


void* stream(void *video) {
	VideoStream* vs = static_cast<VideoStream*>(video);

	while (vs->isRunning) {
		vs->isGrabbed = vs->video.read(vs->frame);
	}

	vs->video.release();
	cout << "[VideoStream] Stopped" << endl;

	return 0;
}