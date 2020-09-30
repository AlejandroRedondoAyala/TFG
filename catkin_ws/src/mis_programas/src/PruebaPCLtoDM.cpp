#include <iostream>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <math.h>
#include <opencv2/core/mat.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <ros/ros.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <boost/filesystem.hpp>
#include <vector>
#include <string>


int main (int argc, char** argv)
{
    float _x, _y, _z, _r, _phi, _theta;
    long unsigned int _u, _v;
    int IMAGE_WIDTH = 1024;
    int IMAGE_HEIGHT = 64;
    float MIN_PHI = -1*M_PI;
    float MAX_PHI = M_PI;
    float MIN_THETA = (3*M_PI)/8;
    float MAX_THETA = (5*M_PI)/8;
    /*Prueba paso de argumentos al ejecutar*/
    std::cout << "Has pasado " << argc << " argumentos" << std::endl;
    for (int i = 0; i < argc; i++){
        std::cout << argv[i] << std::endl;
    }
    std::string argumento = argv[1];
    /*Prueba paso de argumentos al ejecutar*/
    

    /*Prueba comprobación existencia directorio*/
    std::string rutita = "/home/alejandro/catkin_ws/merienda/";
    std::string a = "/nocilla";
    boost::filesystem::path LA_ruta = (rutita + argumento + a );
    if(!(boost::filesystem::exists(LA_ruta))){
        std::cout << "NO EXISTE LA RUTA" << std::endl;  
        std::cout << "creando ruta" << std::endl;
        if(boost::filesystem::create_directories(LA_ruta)){
            std::cout << "Ruta " << LA_ruta << " creada correctamente. "<< std::endl;
        }
        else{
            std::cout <<"ERROR: no se pudo crear " << LA_ruta << std::endl;
        }

        /*Importante create_directory crea un directorio en la ruta especificada, pero tiene que existir previamente
          los directorios que cuelgan de ella, por ejemplo, si se desea crear el directorio nocilla en la siguiente ruta
          /home/alejandro/catkin_ws/merienda/nocilla, al hacer create_directory debe existir previamente el directorio merienda.
          Por otro lado, create_directories crea un directorio en la ruta especificada pero si en la ruta se especifica algún
          directorio que no exista, se crea. En el caso de /home/alejandro/catkin_ws/merienda/nocilla, si queremos crear el directorio
          nocilla, si el directorio merienda no existe al hacer create_directories se va a crear también el directorio merienda
        */
    }
    else{
        std::cout << "Ya existe " << LA_ruta << std::endl;
    }

    /*Prueba comprobación existencia directorio*/


    /*Prueba lectura de varios ficheros en un directorio*/
    //namespace fs = boost::filesystem;
    std::string directorio_imagenes = "/home/alejandro/catkin_ws";
    std::vector<boost::filesystem::path> ficheros;
    for (const auto &entry : boost::filesystem::directory_iterator(directorio_imagenes)){
        std::cout << entry.path() << std::endl;
        std::cout << entry.path().extension() << std::endl;
        if ((entry.path().extension()==".png")){
            std::cout << "Formato correcto" << std::endl;
            ficheros.push_back(entry.path());
        }

    }
    std::cout << "Numero de ficheros .png =  "<< ficheros.size() << std::endl;
    std::cout << "La ruta de dichos ficheros es: " << std::endl;
    for (const auto &vectorcillo : ficheros){
        std::cout << vectorcillo <<std::endl;
    }

    std::string ruta_depth_map = "/home/alejandro/catkin_ws/" ;
    for (unsigned int i = 0; i < ficheros.size(); i++){
        std::cout << ruta_depth_map << i << +".png" <<std::endl;
    }

    /*Prueba lectura de varios ficheros en un directorio*/
    
    std::ofstream out("out.txt");
    std::streambuf *coutbuf = std::cout.rdbuf(); //save old buf
    std::cout.rdbuf(out.rdbuf());

  pcl::PointCloud<pcl::PointXYZ>::Ptr cloud (new pcl::PointCloud<pcl::PointXYZ>);
    
  cv::Mat depth_float(IMAGE_HEIGHT,IMAGE_WIDTH,CV_32FC1,cv::Scalar::all(75.0));
  //cv::Mat depth_float(IMAGE_HEIGHT,IMAGE_WIDTH,CV_32FC1);
  cv::Mat depth_float_gray(IMAGE_HEIGHT,IMAGE_WIDTH,CV_32FC1);

  if (pcl::io::loadPCDFile<pcl::PointXYZ> ("/home/alejandro/catkin_ws/src/mis_programas/src/test2.pcd", *cloud) == -1) //* load the file
  {
    PCL_ERROR ("Couldn't read file test_pcd.pcd \n");
    return (-1);
  }
  std::cout << "Loaded "
            << cloud->width * cloud->height
            << " data points from test_pcd.pcd with the following fields: "
            << std::endl;
  for (size_t i = 0; i < cloud->points.size (); ++i){
    std::cout << "X:  " << cloud->points[i].x
              << "  Y:  "    << cloud->points[i].y
              << "  Z:  "    << cloud->points[i].z << std::endl;

        
        _x = cloud->points[i].x;
        _y = cloud->points[i].y;
        _z = cloud->points[i].z;

        _r=sqrt(_x*_x+_y*_y+_z*_z);
        if(_z>0){
            _theta=atan(sqrt(_x*_x+_y*_y)/_z);
            }
        else if(_z==0){
            _theta=M_PI/2.0;
            }
        else{
            _theta=M_PI + atan(sqrt(_x*_x+_y*_y)/_z);
        }

        /*
        if(_x>0 && _y>0){
            _phi=atan(_y/_x);
        }
        else if (_x>0 && _y<0){
            _phi=2.0*M_PI + atan(_y/_x);
        }
        else if (_x==0){
            if(_y>0){
                _phi=M_PI/2.0;
            }
            else{
                _phi=(3*M_PI)/2.0;
            }
            /*_phi=sgn(_y)*M_PI/2.0;*/
        /*    
        }
        else{
            _phi=M_PI + atan(_y/_x);
        }
        */

       _phi=-atan2(_y,_x);
       

        _u=(IMAGE_WIDTH-1)*(_phi-MIN_PHI)/(MAX_PHI-MIN_PHI) + 0.5;
        _v=(IMAGE_HEIGHT-1)*(_theta-MIN_THETA)/(MAX_THETA-MIN_THETA) + 0.5;
         std::cout << "_phi: " <<_phi;
         std::cout << "_theta: " <<_theta << std::endl;
         std::cout << "r: " <<_r;
         std::cout << " r: " <<_r;
         std::cout << " u: " <<_u;
         std::cout << " v: " <<_v << std::endl;
         depth_float.at<float>(_v,_u)= abs(_x);
         //depth_float.at<float>(_v,_u)= _r;

    }  
        //Para pasar a escala de grises
        double min;
        double max;
        cv::minMaxIdx(depth_float, &min, &max);
        
        cv::convertScaleAbs(depth_float, depth_float_gray, 255.0 / max);
        
        
        std::cout <<"La matriz es" << std::endl << depth_float << std::endl;
        std::cout <<"La matriz es" << std::endl << depth_float_gray << std::endl;
        cv::namedWindow( "window", cv::WINDOW_AUTOSIZE );
        cv::imshow("window", depth_float);


        
        cv::namedWindow("Gray scale", CV_WINDOW_AUTOSIZE);
        cv::imshow("Gray scale", depth_float_gray);
        cv::imwrite("/home/alejandro/catkin_ws/imagen/gris.png",depth_float_gray);
        cv::waitKey(0);
        

    std::cout.rdbuf(coutbuf); //reset to standard output again


  return (0);
}