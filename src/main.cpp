#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

using namespace cv;

int main(int argc, char *argv[])
{
    std::cout << "parametro 1: " << argv[1] << std::endl;
    std::cout << "parametro 2: " << argv[2] << std::endl;
    std::string image_path = samples::findFile(argv[1]);
    if(image_path.empty())
    {
        std::cout << "Could not read the image" << std::endl;
        return 1;
    }
    else
    {
        Mat img_gris = imread(image_path, IMREAD_GRAYSCALE);
        Mat vacio = Mat::zeros(img_gris.size(), CV_8UC1);
        std::vector<Mat> canales;
        canales.push_back(vacio);
        canales.push_back(vacio);
        canales.push_back(img_gris);

        Mat img_color;
        merge(canales, img_color);

        imwrite(argv[2], img_color);
    }
}