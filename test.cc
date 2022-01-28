#include "input.h"
#include <iostream>
#include <atomic>
#include <thread>
#include <vector>

std::atomic_flag mFlag{};
std::atomic_flag EndFlag{};


int INT_X{};
int INT_Y{};
bool RC {true};
bool CLICK{false};
char KEY {};
//Enter char '13'


inputManipulation ioMani;

void Instructor(int x = 0,int y = 0,bool clickonly = false,char key) {

    if(clickonly)
    {
        CLICK = true;

    }else if (key)
    {
        KEY = key;       
    }else
    {
        INT_X = x ;
        INT_Y = y;
    };
    /std::cout << "Sender: Data prepared."  << std::endl;
    mFlag.test_and_set();                             // (1)
    mFlag.notify_all();   

}

void Manipulator() 
{
    while(!EndFlag.test())
    {
        std::cout << "Worker: Waiting for data." << std::endl;
        mFlag.wait(false); 
        mFlag.clear();                               // (2)
        if (CLICK)
        {
            CLICK = false;
            ioMani.Left_click();
        }else if (KEY)
        {
            auto tmpkey = KEY;
            KEY = {};
            ioMani.Ctrl(tmpkey);
        }
        else
        {
            auto tmp_x = INT_X;
            auto tmp_y = INT_Y;
            INT_X = 0;
            INT_Y = 0:
            ioMani.Move_To(tmp_x,tmp_y);
        }
    }
}





void End() {

    std::cout << "Sender: EndFlg."  << std::endl;
    EndFlag.test_and_set();                             // (1)
    EndFlag.notify_all();   

}



int main() {

    std::cout << std::endl;


    std::thread t1(Worker);

    for (int i=1;i<10;i++)
    {
        Sender();
    }
    End();
    t1.join();

    std::cout << std::endl;
  
}



#include <iostream>
#include <fstream>

#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/dnn/dnn.hpp>

using namespace cv;
using namespace cv::dnn;


std::string DnnOCR(cv::Mat& srcimg)
{

    String modelPath = set["modelPath"];  //May bug
    String vocPath = set["vocabularyPath"]; //May bug

    // Load the network
    CV_Assert(!modelPath.empty());
    TextRecognitionModel recognizer(modelPath);

    // Load vocabulary
    CV_Assert(!vocPath.empty());
    std::ifstream vocFile;
    vocFile.open(samples::findFile(vocPath));
    CV_Assert(vocFile.is_open());
    String vocLine;
    std::vector<String> vocabulary;
    while (std::getline(vocFile, vocLine)) {
        vocabulary.push_back(vocLine);
    }
    recognizer.setVocabulary(vocabulary);
    recognizer.setDecodeType("CTC-greedy");

    // Set parameters
    double scale = 1.0 / 127.5;
    Scalar mean = Scalar(127.5, 127.5, 127.5);
    Size inputSize = Size(100, 32);
    recognizer.setInputParams(scale, inputSize, mean);

        // Create a window
    　　 //  static const std::string winName = "Input Cropped Image";

    // Recognition
    std::string recognitionResult = recognizer.recognize(srcimg);
    std::cout << "Predition: '" << recognitionResult << "'" << std::endl;
    return recognitionResult;
}





#include <regex>

std::string str = "3.14";
std::regex rx("\\+([0-9]+)\\([0-9]))");





int    i = std::stoi(str); // 3










/*cv::Rect crop_region(int a,int b, int c, int d);


a,b : Coordinates of the top-left corner.

c,d : Rectangle width and height.


To crop the image we have to specify the Region of Interest in the form of Rectangle.

 */







cv::Mat source = getYourSource();

// Setup a rectangle to define your region of interest
cv::Rect myROI(10, 10, 100, 100);

// Crop the full image to that image contained by the rectangle myROI
// Note that this doesn't copy the data
cv::Mat croppedRef(source, myROI);

cv::Mat cropped;
// Copy the data into new matrix
croppedRef.copyTo(cropped);



#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>

using namespace cv;
using namespace std;


int countPixels(const cv::Mat &image, cv::Scalar color) {

    // Setup a rectangle to define your region of interest
    cv::Rect myROI(10, 10, 100, 100);//To change
    // Crop the full image to that image contained by the rectangle myROI
    // Note that this doesn't copy the data
    cv::Mat croppedRef(image, myROI);
    cv::Mat cropped;
    // Copy the data into new matrix
    croppedRef.copyTo(cropped);
    Scalar color = Scalar(255,0,0);/Change to res
    Mat binary_image;
    cv::inRange(cropped, color, color, binary_image);
        return cv::countNonZero(binary_image)/500.0;
}




int countPixels(const cv::Mat &image, cv::Scalar color) {

    Mat binary_image;
    cv::inRange(image, color, color, binary_image);
        return cv::countNonZero(binary_image);
}

int main(int argc, char* argv[])
{
    Mat input;

    cv::VideoCapture capture;
    capture.open(0);

    while (true){

        capture.read(input);
        imshow("test", input);
        waitKey(30);
        Scalar color = Scalar(10, 10, 10);

        double t = (double)getTickCount();
        cout << "pixel count : " << countPixels(input, color);
        t = ((double)getTickCount() - t) / getTickFrequency();
        cout << "  times passed in seconds: " << t << endl;

    }
    return 0;
}
