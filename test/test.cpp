#include <iostream>
#include "opencv2/highgui.hpp"
#include "videostream.h"

using namespace std;

int main(int argc, const char** argv) {
	VideoStream vs(2);
	cv::Mat frame;

	vs.start();

	while (vs.isOpened) {
		frame = vs.read();

		if (!vs.grab)
			continue;

		cv::imshow("frame", frame);
		int key = cv::waitKey(30) & 0xFF;
		if (key == 27)
			break;
	}

	vs.stop();
}