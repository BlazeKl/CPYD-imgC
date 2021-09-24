#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include "opencv2/imgproc.hpp"
#include <iostream>

using namespace cv;

int main(int argc, char *argv[])
{
    std::cout << "parametro 1: " << argv[1] << std::endl;
    std::cout << "parametro 2: " << argv[2] << std::endl;
    std::cout << "Integrantes de grupo: " << std::endl;
    std::cout << "  *Felipe Perez Cares" << std::endl;
    std::cout << "  *Javier Cisternas Cristi " << std::endl;
    std::string image_path = samples::findFile(argv[1]); //buscar archivo a base de 1er parametro
    if(image_path.empty())
    {
        std::cout << "Could not read the image" << std::endl;
        return 1;
    }
    else
    {
        Mat img_gris = imread(image_path, IMREAD_GRAYSCALE);

        Mat img_thres; //guardar imagen por threshold
        threshold(img_gris, img_thres, 180, 255, THRESH_BINARY); //guarda threshold blanco y negro

        imwrite("threshold.jpg", img_thres);

        for(int i=0; i<img_gris.rows; i++){
            for(int j=0; j<img_gris.cols; j++){
                std::cout << int(img_thres.at<uchar>(i,j)) << std::endl; //print valor de cada pixel de 0 a 255
            }
        }

    }
}