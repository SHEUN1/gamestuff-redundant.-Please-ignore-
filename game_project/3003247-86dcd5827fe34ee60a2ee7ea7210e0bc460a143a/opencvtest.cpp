#include<iostream>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/gpu/gpu.hpp>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

int load(string filename)
{
	Mat imgBeforeGpu = imread(filename,CV_LOAD_IMAGE_GRAYSCALE);
	/// Convert to grayscale
 	//cvtColor( img, img, CV_BGR2GRAY );
	gpu::GpuMat img, img2, BW1, BW2, blur, blur2;
	img.upload(imgBeforeGpu);
	gpu::equalizeHist( img, img2);
	gpu::GaussianBlur(img, blur, Size(5, 5), 0, 0);
	gpu::GaussianBlur(img2, blur2, Size(5, 5), 0, 0);
	gpu::threshold(blur, BW1, 0, 255, CV_THRESH_BINARY /**| CV_THRESH_OTSU*/);
    	gpu::threshold(blur2, BW2, 0, 255, CV_THRESH_BINARY /**| CV_THRESH_OTSU*/);
	Mat resultImg;
	BW1.download(resultImg);	
	imshow("opencvtest",resultImg);
	waitKey(0);
	return 1;

   /** try
    {
        cv::Mat src_host = cv::imread(filename, CV_LOAD_IMAGE_GRAYSCALE);
        cv::gpu::GpuMat dst, src;
        src.upload(src_host);

        cv::gpu::threshold(src, dst, 128.0, 255.0, CV_THRESH_BINARY|CV_THRESH_OTSU);

        cv::Mat result_host;
        dst.download(result_host);

        cv::imshow("Result", result_host);
        cv::waitKey();
    }
    catch(const cv::Exception& ex)
    {
        std::cout << "Error: " << ex.what() << std::endl;
    }
    return 0;*/
}

int load2 (string filename)
{
VideoCapture cap("/home/sheun/Pictures/transistorVideo1.mp4"); // open the default camera
    if(!cap.isOpened())  // check if we succeeded
        return -1;

    
    gpu::GpuMat img2, BW1, BW2, blur, blur2;
    
    for(;;)
    {
	Mat imgBeforeGpu;
	cap >> imgBeforeGpu;
        gpu::GpuMat img;
	cvtColor( imgBeforeGpu, imgBeforeGpu, CV_BGR2GRAY );
        img.upload(imgBeforeGpu);
	/// Convert to grayscale
	//Mat img2, BW1, BW2, blur, blur2;
	gpu:: equalizeHist( img, img2);
	gpu:: GaussianBlur(img, blur, Size(5, 5), 0, 0);
	gpu:: GaussianBlur(img2, blur2, Size(5, 5), 0, 0);
	gpu:: threshold(blur, BW1, 100, 255,  CV_THRESH_BINARY);
    	gpu:: threshold(blur2, BW2, 100, 255,  CV_THRESH_BINARY);
	//gpu::adaptiveThreshold(blur, BW1, 255,  ADAPTIVE_THRESH_GAUSSIAN_C, 5, 11);//;(InputArray src, OutputArray dst, double maxValue, int adaptiveMethod, int thresholdType, int blockSize, double C)
	//gpu::adaptiveThreshold(blur2, BW2, 255,  ADAPTIVE_THRESH_GAUSSIAN_C, 5, 11);

	Mat imageAfterGpu;
	BW1.download(imageAfterGpu);
	if(waitKey(30) >= 0) break;
	imshow("opencvtest",imageAfterGpu);
    }
    // the camera will be deinitialized automatically in VideoCapture destructor
    return 1;
}

int load3 (string filename)
{
VideoCapture cap("/home/sheun/Pictures/transistorVideo1.mp4"); // open the default camera
    if(!cap.isOpened())  // check if we succeeded
        return -1;

    
    Mat img2, BW1, BW2, blur, blur2;
    
    for(;;)
    {
	Mat img;
	cap >> img;
  
	cvtColor( img, img, CV_BGR2GRAY );
        
	/// Convert to grayscale
	//Mat img2, BW1, BW2, blur, blur2;
	//equalizeHist( img, img2);
	GaussianBlur(img, blur, Size(5, 5), 0, 0);
	//GaussianBlur(img2, blur2, Size(5, 5), 0, 0);
	threshold(blur, BW1, 0, 255,  CV_THRESH_BINARY | CV_THRESH_OTSU);
    	//threshold(blur2, BW2, 0, 255,  CV_THRESH_BINARY| CV_THRESH_OTSU);

	//gpu::adaptiveThreshold(blur, BW1, 255,  ADAPTIVE_THRESH_GAUSSIAN_C, 5, 11);//;(InputArray src, OutputArray dst, double maxValue, int adaptiveMethod, int thresholdType, int blockSize, double C)
	//gpu::adaptiveThreshold(blur2, BW2, 255,  ADAPTIVE_THRESH_GAUSSIAN_C, 5, 11);

	if(waitKey(30) >= 0) break;
	imshow("opencvtest",BW1);
    }
    // the camera will be deinitialized automatically in VideoCapture destructor
    return 1;
}


//#include<boost/python/detail/wrap_python.hpp>
#include<boost/python.hpp>
using namespace boost::python;
BOOST_PYTHON_MODULE(opencvtest)
{
    //def("load",load);
    //def("load2",load2);
    def("load3",load3);
}
