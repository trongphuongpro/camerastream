#include <iostream>
#include <stdio.h>
#include "opencv2/highgui.hpp"
#include "opencv2/videoio.hpp"
#include "camerastream.h"
#include <time.h>


using namespace std;

int main(int argc, const char** argv) {
	CameraStream vs(0);
	
	cv::Mat frame;
	unsigned int count = 0;
	unsigned int frameNum = 500;
	time_t begin = time(NULL);
	int delay = 15;
	
	while (vs.isOpened()) {
		vs.read(frame);

		if (frame.empty()) {
			//cout << "no frame" << endl;
			continue;
		}
		
		if (delay != 0) {
			cv::imshow("frame", frame);
			int key = cv::waitKey(delay) & 0xFF;
			if (key == 27)
				break;
		}

		count++;
		if (count == frameNum) {
			break;
		}
	}

	time_t end = time(NULL);
	printf("FPS: %.2f\n", (float)frameNum/(end-begin));

	vs.release();
	cv::destroyAllWindows();
}