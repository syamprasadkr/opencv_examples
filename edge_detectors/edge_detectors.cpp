#include <iostream>
#include <string>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

int main(int argc, char** argv)
{
	cv::Mat src, src_gblur, src_gray;
	cv::Mat grad, grad_x, grad_y, abs_grad_x, abs_grad_y;
	cv::Mat laplacian, abs_laplacian;
	cv::Mat canny;
	std::string win0 = "Original Image";
	std::string win0gb = "Gaussian Blur";
	std::string win0g = "Grayscale Image";
	std::string win1 = "Sobel Total Gradient";
	std::string win2 = "Sobel Gx";
	std::string win3 = "Sobel Gy";
	std::string win4 = "LoG";
	std::string win5 = "Canny";
	int ddepth = CV_16S;
	int scale = 1;
	int delta = 0;
	src = cv::imread(argv[1]);
	if(!src.data)
	{
		std::cout << "Invalid File\n";
		return -1;
	}
	
	cv::namedWindow(win0, CV_WINDOW_AUTOSIZE);
	cv::namedWindow(win0gb, CV_WINDOW_AUTOSIZE);
	cv::namedWindow(win0g, CV_WINDOW_AUTOSIZE);
	cv::namedWindow(win1, CV_WINDOW_AUTOSIZE);
	cv::namedWindow(win2, CV_WINDOW_AUTOSIZE);
	cv::namedWindow(win3, CV_WINDOW_AUTOSIZE);
	cv::namedWindow(win4, CV_WINDOW_AUTOSIZE);
	cv::namedWindow(win5, CV_WINDOW_AUTOSIZE);
	cv::GaussianBlur(src, src_gblur, cv::Size(3, 3), 0, 0, cv::BORDER_DEFAULT);
	cv::cvtColor(src_gblur, src_gray, CV_BGR2GRAY);
	
	
	cv::Sobel(src_gray, grad_x, ddepth, 1, 0, 3, scale, delta, cv::BORDER_DEFAULT);
	cv::convertScaleAbs(grad_x, abs_grad_x);
	cv::Sobel(src_gray, grad_y, ddepth, 0, 1, 3, scale, delta, cv::BORDER_DEFAULT);
	cv::convertScaleAbs(grad_y, abs_grad_y);
	cv::addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, grad);

	cv::Laplacian(src_gray, laplacian, ddepth, 3, scale, delta, cv::BORDER_DEFAULT);
	cv::convertScaleAbs(laplacian, abs_laplacian);

	cv::Canny(src_gray, canny, 30, 150, 3);

	cv::imshow(win0, src);
	cv::imshow(win0gb, src_gblur);
	cv::imshow(win0g, src_gray);
	cv::imshow(win1, grad);
	cv::imshow(win2, abs_grad_x);
	cv::imshow(win3, abs_grad_y);
	cv::imshow(win4, abs_laplacian);
	cv::imshow(win5, canny);

	cv::waitKey(0);
	return 0;
}
