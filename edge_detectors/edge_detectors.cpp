#include <iostream>
#include <string>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

int main(int argc, char** argv)
{
	// Different Mat objects for various sources and results
	cv::Mat src, src_gblur, src_gray;
	cv::Mat grad, grad_x, grad_y, abs_grad_x, abs_grad_y;
	cv::Mat laplacian, abs_laplacian;
	cv::Mat canny;
	// Output image depth
	int ddepth = CV_16S;
	// Scale factor multiplied to values computed by the filter
	int scale = 1;
	// Delta value added to the results from the filter
	int delta = 0;
	// Read the input file and return an error if it has no data
	src = cv::imread(argv[1]);
	if(!src.data)
	{
		std::cout << "Invalid File\n";
		return -1;
	}

	// Different windows to display various results 
	std::string win0 = "Original Image";
	std::string win0gb = "Gaussian Blur";
	std::string win0g = "Grayscale Image";
	std::string win1 = "Sobel Total Gradient";
	std::string win2 = "Sobel Gx";
	std::string win3 = "Sobel Gy";
	std::string win4 = "LoG";
	std::string win5 = "Canny";
	cv::namedWindow(win0, cv::WindowFlags::WINDOW_AUTOSIZE);
	cv::namedWindow(win0gb, cv::WindowFlags::WINDOW_AUTOSIZE);
	cv::namedWindow(win0g, cv::WindowFlags::WINDOW_AUTOSIZE);
	cv::namedWindow(win1, cv::WindowFlags::WINDOW_AUTOSIZE);
	cv::namedWindow(win2, cv::WindowFlags::WINDOW_AUTOSIZE);
	cv::namedWindow(win3, cv::WindowFlags::WINDOW_AUTOSIZE);
	cv::namedWindow(win4, cv::WindowFlags::WINDOW_AUTOSIZE);
	cv::namedWindow(win5, cv::WindowFlags::WINDOW_AUTOSIZE);

	// Smoothing with Gaussian and conversion to Grayscale image
	cv::GaussianBlur(src, src_gblur, cv::Size(3, 3), 0, 0, cv::BORDER_DEFAULT);
	cv::cvtColor(src_gblur, src_gray, cv::COLOR_BGR2GRAY);
	
	// Sobel Edge Detector
	cv::Sobel(src_gray, grad_x, ddepth, 1, 0, 3, scale, delta, cv::BORDER_DEFAULT);
	cv::convertScaleAbs(grad_x, abs_grad_x);
	cv::Sobel(src_gray, grad_y, ddepth, 0, 1, 3, scale, delta, cv::BORDER_DEFAULT);
	cv::convertScaleAbs(grad_y, abs_grad_y);
	cv::addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, grad);

	// Laplacian Edge Detector
	cv::Laplacian(src_gray, laplacian, ddepth, 3, scale, delta, cv::BORDER_DEFAULT);
	cv::convertScaleAbs(laplacian, abs_laplacian);

	// Canny Edge Detector
	cv::Canny(src_gray, canny, 30, 150, 3);

	// Display various sources and results
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
