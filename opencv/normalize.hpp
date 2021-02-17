#include <opencv2/opencv.hpp>

void normalize() {
	cv::Mat input(10, 10, CV_8UC1);

	for (int y = 0; y < input.rows; y++) {
		for (int x = 0; x < input.cols; x++) {
			input.at<unsigned char>(y, x) = x * y + 1;
		}
	}

	cv::Mat input_64f;
	
	input.convertTo(input_64f, CV_64F);

	cv::normalize(input_64f, input_64f, 0.0, 1.0, cv::NORM_MINMAX);

	for (int y = 0; y < input.rows; y++) {
		for (int x = 0; x < input.cols; x++) {
			std::cout
				<< std::setprecision(2)
				<< input_64f.at<double>(y, x)
				<< std::setw(8);
		}
		std::cout << std::endl;
	}
}