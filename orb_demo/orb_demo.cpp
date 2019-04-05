#include <iostream>
#include <limits>
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/features2d.hpp"

// Specify image files. The input1 is being searched inside input2. 
const char* keys = 
	"{help h | | Print help message.}"
	"{input1 | box.png| Path to input image 1.}"
	"{input2 | box_in_scene.png| Path to input image 2.}";

// Parameter for finding good matches
constexpr double good_param = 30.0;

int main(int argc, char* argv[])
{
	// Read input images as grayscale images.
	cv::CommandLineParser parser( argc, argv, keys);
	cv::Mat img1 = cv::imread(parser.get<std::string>("input1"), cv::IMREAD_GRAYSCALE);
	cv::Mat img2 = cv::imread(parser.get<std::string>("input2"), cv::IMREAD_GRAYSCALE);
	if(img1.empty() || img2.empty())
	{
		std::cout << "Could not open or find the image!\n";
		parser.printMessage();
		return -1;
	}
	
	// Create ORB detector, detect keypoints and generate descriptors on both the images.
	cv::Ptr<cv::ORB> detector = cv::ORB::create();
	std::vector<cv::KeyPoint> keypoints1, keypoints2;
	cv::Mat descriptors1, descriptors2;
	detector->detectAndCompute(img1, cv::noArray(), keypoints1, descriptors1);
	detector->detectAndCompute(img2, cv::noArray(), keypoints2, descriptors2);
	
	// Create a Brute force matcher that uses Hamming distance and find all the matches.
	cv::Ptr<cv::DescriptorMatcher> matcher = cv::DescriptorMatcher::create("BruteForce-Hamming");
	std::vector<cv::DMatch> matches;
	matcher->match(descriptors1, descriptors2, matches);
	
	// Find good matches based on minimum distance. 
	double min_dist = std::numeric_limits<double>::max(), max_dist = 0;
	for(int i = 0; i < matches.size(); i++)
	{
		double dist = matches[i].distance;
		if(dist < min_dist)
		{
			min_dist = dist;
		}
		if(dist > max_dist)
		{
			max_dist = dist;
		}
	}	
	
	std::vector<cv::DMatch> good_matches;
	
	for(int i = 0; i < matches.size(); i++)
	{
		if(matches[i].distance <= std::max(2 * min_dist, good_param))
		{
			good_matches.push_back(matches[i]);
		}
	}

	// Draw and display matches in the images
	cv::Mat img_res;
	cv::drawMatches(img1, keypoints1, img2, keypoints2, good_matches, img_res);
	cv::imshow("ORB:Result", img_res);

	cv::waitKey(0);
	return(0);	
	
}

