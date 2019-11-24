#include <iostream>
#include "opencv2/videoio.hpp"
#include "camerastream.h"

using namespace std;
using namespace cv;


CameraStream::CameraStream(int camera) {
	this->video = cv::VideoCapture(camera);
	this->isRunning = false;
	this->_isOpened = this->video.isOpened();

	if (!this->_isOpened) {
		cout << "[CameraStream] Cannot open video stream" << endl;
	}
	else {
		cout << "[CameraStream] Opened" << endl;

		// IMPORTANT: read the first frame from camera
		this->isGrabbed = this->video.read(this->frame);

		if (start())
			cout << "[CameraStream] Streaming thread created" << endl;
		else
			cout << "[CameraStream] Cannot create streaming thread" << endl;
	}
}


CameraStream::~CameraStream() {
	if (this->isRunning)
		this->release();
}


bool CameraStream::isOpened() {
	return this->_isOpened;
}


int CameraStream::start() {
	this->isRunning = true;

	if (pthread_create(&this->thread, NULL, stream, this) == 0) {
		return 1;
	}
	
	return 0;
}


void CameraStream::release() {
	this->isRunning = false;
}


bool CameraStream::read(Mat& frame) {
	frame = this->frame;
	return this->isGrabbed;
}


void CameraStream::operator>>(Mat& frame) {
	frame = this->frame;
}


void* stream(void *video) {
	CameraStream* vs = static_cast<CameraStream*>(video);

	while (vs->isRunning) {
		vs->isGrabbed = vs->video.read(vs->frame);
	}

	vs->video.release();
	cout << "[CameraStream] Stopped" << endl;

	return 0;
}