#include <opencv2/opencv.hpp>

void phase_correlation() {
	std::string input1_path = "C:\\workspace\\data\\3.png";
	std::string input2_path = "C:\\workspace\\data\\3-1.png";
	std::string save_path = "C:\\workspace\\data\\save.png";

	cv::Mat input1 = cv::imread(input1_path, cv::IMREAD_GRAYSCALE);
	//cv::Mat _input2 = cv::imread(input2_path, cv::IMREAD_GRAYSCALE);

	cv::Rect roi(100, 100, 2000, 2000);
	cv::Mat input2 = input1(roi);

	cv::GaussianBlur(input2, input2, cv::Size(9,9), 2.0);

	cv::Mat input1_64f, input2_64f;
	input1.convertTo(input1_64f, CV_64F);
	input2.convertTo(input2_64f, CV_64F);

	int _width = cv::max(input1_64f.cols, input2_64f.cols);
	int _height = cv::max(input1_64f.rows, input2_64f.rows);

	int fft_width = cv::getOptimalDFTSize(_width);
	int fft_height = cv::getOptimalDFTSize(_height);

	cv::Mat expand1, expand2;
	cv::copyMakeBorder(
		input1_64f, expand1,
		0, fft_height - input1_64f.rows, 
		0, fft_width - input1_64f.cols, 
		cv::BORDER_CONSTANT, 0);

	cv::copyMakeBorder(
		input2_64f, expand2,
		0, fft_height - input2_64f.rows,
		0, fft_width - input2_64f.cols,
		cv::BORDER_CONSTANT, 0);

	cv::Mat fft1, fft2;
	cv::dft(expand1, fft1, cv::DFT_COMPLEX_OUTPUT);
	cv::dft(expand2, fft2, cv::DFT_COMPLEX_OUTPUT);

	cv::Mat fft_mul;
	cv::mulSpectrums(fft1, fft2, fft_mul, 0, true);

	cv::Mat fft_complex[2];
	cv::split(fft_mul, fft_complex);

	cv::Mat output;
	cv::magnitude(fft_complex[0], fft_complex[1], output);
	cv::divide(fft_complex[0], output, fft_complex[0]);
	cv::divide(fft_complex[1], output, fft_complex[1]);

	cv::merge(fft_complex, 2, fft_mul);
	cv::dft(fft_mul, output, cv::DFT_INVERSE | cv::DFT_SCALE | cv::DFT_REAL_OUTPUT);

	cv::Point min_loc, max_loc;
	double min_val, max_val;
	cv::minMaxLoc(output, &min_val, &max_val, &min_loc, &max_loc);

	std::cout << "min_loc : " << min_loc.x << ", " << min_loc.y <<std::endl;
	std::cout << "max_loc : " << max_loc.x << ", " << max_loc.y << std::endl;
	std::cout << "min_val : " << min_val << std::endl;
	std::cout << "max_val : " << max_val << std::endl;

	cv::imwrite(save_path, input2);
}