#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include "opencv2/imgproc.hpp"
#include <iostream>

using namespace cv;

int main(int argc, char *argv[])
{
    // std::cout << "parametro 1: " << argv[1] << std::endl;
    // std::cout << "parametro 2: " << argv[2] << std::endl;
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
        Mat img_gris = imread(image_path);
        Mat img_thres; //guardar imagen por threshold
        Mat aux;
        int opt = -1;
        float R1=1,G1=1,B1=1,R2=1,G2=1,B2=1;

        std::cout << "*-------------------------------------------------*" << std::endl;
        std::cout << "| Selecciona un set de colores preeajustados (1-4)|" << std::endl;
        std::cout << "| o crea uno manualmente (0) (default = 1)        |" << std::endl;
        std::cout << "*-------------------------------------------------*" << std::endl;
        std::cout << "Opcion: ";
        std::cin >> opt;

        switch(opt){
            case 0:
                std::cout << "Manual" << std::endl;
                std::cout << "Selecciona la intensidad(%) de cada canal de RGB (Color 1)" << std::endl;
                std::cout << "Red: ";
                std::cin >> R1;
                std::cout << "Green: ";
                std::cin >> G1;
                std::cout << "Blue: ";
                std::cin >> B1;
                std::cout << "Selecciona la intensidad(%) de cada canal de RGB (Color 2)" << std::endl;
                std::cout << "Red: ";
                std::cin >> R2;
                std::cout << "Green: ";
                std::cin >> G2;
                std::cout << "Blue: ";
                std::cin >> B2;
                break;
            case 2:
                std::cout << "Preset 2" << std::endl;
                R1 = 1;
                G1 = 1;
                B1 = 1;
                R2 = 1;
                G2 = 0;
                B2 = 0;
                break;
            case 3:
                std::cout << "Preset 3" << std::endl;
                R1 = 1;
                G1 = 1;
                B1 = 1;
                R2 = 0;
                G2 = 1;
                B2 = 0;
                break;
            case 4:
                std::cout << "Preset 4" << std::endl;
                R1 = 1;
                G1 = 1;
                B1 = 1;
                R2 = 0;
                G2 = 0;
                B2 = 1;
                break;
            default:
                std::cout << "Preset 1" << std::endl;
                R1 = 1;
                G1 = 1;
                B1 = 1;
                R2 = 1;
                G2 = 0.753;
                B2 = 0.796;
                break;
        }

        threshold(img_gris, aux, 180, 255, THRESH_BINARY); //guarda threshold blanco y negro
        aux.convertTo(img_thres, CV_8UC3);

        int i,j;
        #pragma omp parallel for private(i,j)
        for(int i = 0; i < img_thres.rows; i++){
            for(int j = 0; j < img_thres.cols; j++){ //itera por cada pixel de la imagen ingresada en el 1er parametro
                if (img_thres.at<Vec3b>(i, j) == Vec3b(255, 255, 255)){ //busca pixeles blancos en threshold
                    // std::cout << "flag" << std::endl;
                    img_gris.at<Vec3b>(i, j)[0] = B1 * img_gris.at<Vec3b>(i, j)[0]; //Blue
                    img_gris.at<Vec3b>(i, j)[1] = G1 * img_gris.at<Vec3b>(i, j)[1]; //Green
                    img_gris.at<Vec3b>(i, j)[2] = R1 * img_gris.at<Vec3b>(i, j)[2]; //Red
                }
                if (img_thres.at<Vec3b>(i, j) == Vec3b(0, 0, 0)){ //busca pixeles negros en threshold
                    // std::cout << "flag" << std::endl;
                    img_gris.at<Vec3b>(i, j)[0] = B2 * img_gris.at<Vec3b>(i, j)[0]; //Blue
                    img_gris.at<Vec3b>(i, j)[1] = G2 * img_gris.at<Vec3b>(i, j)[1]; //Green
                    img_gris.at<Vec3b>(i, j)[2] = R2 * img_gris.at<Vec3b>(i, j)[2]; //Red
                }
            }
        }
        #pragma omp critical

        imwrite(argv[2], img_gris);
        // imwrite("threshold.jpg", img_thres); //guardar buffer threshold opcional
        std::cout << "Finish" << std::endl;

    }
}