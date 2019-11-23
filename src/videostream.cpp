#include <iostream>
#include "videostream.h"

using namespace std;
using namespace cv;

VideoStream::VideoStream(int camera) {
	this->video = cv::VideoCapture(camera);
	this->isRunning = false;
	this->isOpened = this->video.isOpened();

	if (!this->isOpened)
		cout << "Cannot open video stream" << endl;
}


VideoStream::VideoStream(string filename) {
	this->video = cv::VideoCapture(filename);
	this->isRunning = false;
	this->isOpened = this->video.isOpened();

	if (!this->isOpened)
		cout << "Cannot open video stream" << endl;
}


VideoStream::~VideoStream() {

}

void VideoStream::start() {
	if (this->isOpened) {
		this->isRunning = true;
		pthread_create(&this->thread, NULL, stream, this);
		cout << "New thread created" << endl;
	}
}


void VideoStream::stop() {
	this->isRunning = false;
}


Mat& VideoStream::read() {
	return this->frame;
}


void VideoStream::operator>>(Mat& frame) {
	if (this->grab)
		frame = this->frame;
}


void* stream(void *video) {
	VideoStream* vs = static_cast<VideoStream*>(video);

	while (vs->isRunning) {
		vs->grab = vs->video.read(vs->frame);
	}

	vs->video.release();

	return 0;
}