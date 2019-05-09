#include <opencv2/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <string>

int main(int argc, char** argv)
{
	// The im2 will be corrected to look like im1.
	// The images can be provided from command line input.
	// Else default images can be used.
	// Name is used to save the result based on the input image name.
	cv::Mat im1, im2;
	std::string name;
	if(argc < 3)
	{
		// Default input set
		im1 = cv::imread("lena1.jpg");
		im2 = cv::imread("lena2.png");
		name = "lena2.jpg";

	}
	else
	{
		im1 = cv::imread(argv[1]);
		im2 = cv::imread(argv[2]);
		name = argv[2];
	}

	// Check image type and note down no. of channels.
	if(im1.type() != im2.type())
	{
		std::cout << "Please provide images of same type.\n Exiting.....";
		return 0;
	}
	std::cout << "Image type: " << im1.type() << "\t" << im2.type() << "\n";
	int nChannels = im1.channels();

	// Display the original images
	cv::imshow("Original Im1: ", im1);
	cv::imshow("Original Im2: ", im2);

	// Calculate mean and std. deviation for the two images. 
	// Based on these values calculate alpha and beta to correct brightness and contrast.
	cv::Scalar mean1, mean2, stdDev1, stdDev2, alpha, beta;
	cv::meanStdDev(im1, mean1, stdDev1);
	cv::meanStdDev(im2, mean2, stdDev2);
	std::cout << "Mean 1 and 2: " << mean1 << "\t" << mean2 << "\n";
	std::cout << "stdDev 1 and 2: " << stdDev1 << "\t" << stdDev2 << "\n";

	for(int i = 0; i < nChannels; i++)
	{
		alpha[i] = stdDev1[i] / stdDev2[i];
		beta[i] = mean1[i] - alpha[i] * mean2[i];
		std::cout << "Ch: " << i << "\tAlpha: " << alpha[i] << "\tBeta: " << beta[i] << "\n";  
	}
	
	// Apply correction and generate a result image.
	cv::Mat im2Res(im2);
	
	for(int k = 0; k < nChannels; k++)
	{
		for(int j = 0; j < im2.rows; j++)
		{
			for(int i = 0; i < im2.cols; i++)
			{
				im2Res.at<cv::Vec3b>(j, i)[k] = cv::saturate_cast<uchar> (alpha[k] * im2.at<cv::Vec3b>(j, i)[k] + beta[k]);
			}
		}
	}
	
	// Display result image.
	cv::imshow("Processed Im2: ", im2Res);
	cv::waitKey(0);

	// Save the result image.
	cv::imwrite("corrected_" + name, im2Res);

	return 0;
}
