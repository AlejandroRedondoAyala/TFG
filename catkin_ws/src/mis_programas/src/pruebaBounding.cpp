#include <opencv2/core/mat.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
//#include <opencv2/core/types_c.h>
#include <iostream>
#include <fstream>


int main (int argc, char ** argv){
    /*Escritura del cout en un fichero*/
    std::ofstream out("Bounding_test.txt");
    std::streambuf *coutbuf = std::cout.rdbuf(); //save old buf
    std::cout.rdbuf(out.rdbuf());
    /*Escritura del cout en un fichero*/


    /*prueba apertura de imagen*/
    cv::Mat imagen;
    imagen = cv::imread("/home/alejandro/catkin_ws/src/mis_programas/bagfiles/experimento5_64_vacio/depth_map/313.png",CV_LOAD_IMAGE_GRAYSCALE);
    std::cout << imagen;
    std::cerr << "tamaño de la imagen: " << std::endl;
    std::cerr << "columnas [width]: " << imagen.cols << std::endl;
    std::cerr << "filas [height]: " << imagen.rows << std::endl;
    std::cerr << imagen.at<float> (0,0) << std::endl;
    /*Necesario convertir para operar con los datos como float*/
    cv::Mat modificada (64,1024,CV_32FC1);
    imagen.convertTo(modificada,CV_32FC1);
    /*Necesario convertir para operar con los datos como float*/
    
    cv::namedWindow( "original", cv::WINDOW_AUTOSIZE );
    cv::imshow("original", imagen);
    for (int row = 0; row < modificada.rows; row++){
        for(int col = 0; col < modificada.cols; col++){
            if(modificada.at<float>(row,col)<255){
                modificada.at<float>(row,col) = 255;
            }
            else{
                modificada.at<float>(row,col) = 0;
            }
        }
    }
    std::cout << modificada;
    double min;
    double max;
    /*lineas necesarias para que al mostrar salgan los valores de los píxeles aunque si no lo pongo la imagen está*/
    //cv::cvtColor(modificada,modificada,CV_32FC1);
    cv::minMaxIdx(modificada, &min, &max);        
    cv::convertScaleAbs(modificada, modificada, 255.0 / max);
    /*lineas necesarias para que al mostrar salgan los valores de los píxeles*/
    cv::namedWindow("modificada",cv::WINDOW_AUTOSIZE);
    cv::imshow("modificada", modificada);

    /*Prueba de rodear el dron*/
    cv::Rect boundingBox;
    boundingBox = cv::boundingRect(modificada);
    std::cerr << "height: "<< boundingBox.height << std::endl;
    std::cerr << "width: " << boundingBox.width << std::endl;
    std::cerr << "x: " << boundingBox.x << std::endl;
    std::cerr << "y: " << boundingBox.y << std::endl;
    cv::Mat final;
    final = cv::imread("/home/alejandro/catkin_ws/src/mis_programas/bagfiles/experimento5_64_vacio/depth_map/313.png");
    //cv::cvtColor(modificada,final);
    cv::rectangle(final,boundingBox.tl(),boundingBox.br(), cv::Scalar(0, 255, 0),1,8,0);
   
    cv::namedWindow("final",cv::WINDOW_AUTOSIZE);
    cv::imshow("final", final);
    /*Prueba de rodear el dron*/

    cv::waitKey(0);
    /*prueba apertura de imagen*/

    std::cout.rdbuf(coutbuf); //reset to standard output again

    return 0;
}