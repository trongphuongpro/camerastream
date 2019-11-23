#include <iostream>
#include "opencv2/videoio.hpp"
#include "videostream.h"

using namespace std;
using namespace cv;

VideoStream::VideoStream(int camera) {
	this->video = cv::VideoCapture(camera);
	this->isRunning = false;
	this->isGrabbed = false;
	this->_isOpened = this->video.isOpened();

	if (!this->_isOpened)
		cout << "Cannot open video stream" << endl;
	else
		cout << "Video stream opened" << endl;
}


VideoStream::VideoStream(string filename) {
	this->video = cv::VideoCapture(filename);
	this->isRunning = false;
	this->_isOpened = this->video.isOpened();

	if (!this->_isOpened)
		cout << "Cannot open video stream" << endl;
	else
		cout << "Video stream opened" << endl;
}


VideoStream::~VideoStream() {

}


bool VideoStream::isOpened() {
	return this->_isOpened;
}


void VideoStream::start() {
	if (this->_isOpened) {
		this->isRunning = true;
		pthread_create(&this->thread, NULL, stream, this);
		cout << "New thread created" << endl;
	}
}


void VideoStream::stop() {
	this->isRunning = false;
}


Mat& VideoStream::read() {
	if (this->isGrabbed)
		return this->frame;
	
	return ???
}


void VideoStream::operator>>(Mat& frame) {
	if (this->isGrabbed)
		frame = this->frame;
	else
		frame = ???
}


void* stream(void *video) {
	VideoStream* vs = static_cast<VideoStream*>(video);

	while (vs->isRunning) {
		vs->isGrabbed = vs->video.read(vs->frame);
	}

	vs->video.release();

	return 0;
}