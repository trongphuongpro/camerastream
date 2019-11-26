#include <iostream>
#include "opencv2/videoio.hpp"
#include "camerastream.h"

using namespace std;
using namespace cv;


CameraStream::CameraStream(int camera) {
	this->video = cv::VideoCapture(camera);
	this->isRunning = false;
	this->isNewFrame = false;
	this->_isOpened = this->video.isOpened();

	if (!this->_isOpened) {
		cout << "[CameraStream] Cannot open video stream" << endl;
	}
	else {
		cout << "[CameraStream] Opened" << endl;

		// IMPORTANT: warm up the camera by reading the first frame
		bool isGrabbed = this->video.read(this->frame);

		if (isGrabbed)
			this->isNewFrame = true;

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
	if (this->isNewFrame) {
		frame = this->frame;
		this->isNewFrame = false;

		return true;
	}
	else {
		frame = Mat();

		return false;
	}
}


void CameraStream::operator>>(Mat& frame) {
	if (this->isNewFrame) {
		frame = this->frame;
		this->isNewFrame = false;
	}
	else {
		frame = Mat();
	}
}


void* stream(void *video) {
	CameraStream* vs = static_cast<CameraStream*>(video);
	bool isGrabbed = false;

	while (vs->isRunning) {
		isGrabbed = vs->video.read(vs->frame);
		if (isGrabbed)
			vs->isNewFrame = true;
	}

	vs->video.release();
	cout << "[CameraStream] Stopped" << endl;

	return 0;
}