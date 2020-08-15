#include <iostream>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <math.h>
#include <opencv2/core/mat.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <boost/filesystem.hpp>
#include <vector>
#include <string>
#include <algorithm>


int main (int argc, char** argv)
{
    std::string experimento;
    if (argc == 2){
        experimento = argv[1];
    }
    else{
        std::cout << "ERROR en argumentos" << std::endl;
        std::cout << "  El comando para ejecutar el programa debe ser del estilo: " << std::endl;
        std::cout << "  rosrun mis_programas PruebaPCLtoDM experimento1_64" << std::endl;
        std::cout << "  SOLO debe haber 1 argumento, y este tiene que ser necesariamente de esta forma" <<std::endl;
        std::cout << "  Indicando el numero de experimento y el numero de planos verticales en él" << std::endl;
        std::cout << "  Es el mismo nombre de la carpeta donde está el .bag correspondiente" << std::endl;
        return -1;
    }

    float _x, _y, _z, _r, _phi, _theta;
    long unsigned int _u, _v;
    int IMAGE_WIDTH = 1024;
    int IMAGE_HEIGHT = 64;
    float MIN_PHI = -M_PI;
    float MAX_PHI = M_PI;
    float MIN_THETA = (3*M_PI)/8;
    float MAX_THETA = (5*M_PI)/8;

    /*Prueba lectura de varios ficheros en un directorio*/
    //namespace fs = boost::filesystem;
    std::string directorio_pcd = "/home/alejandro/catkin_ws/src/mis_programas/bagfiles/" + experimento + "/point_clouds";
    if(!(boost::filesystem::exists(directorio_pcd))){
        std::cout << "ERROR: " << std::endl;
        std::cout << "  No existe el directorio point_clouds puede ser que no se haya creado los ficheros .pcd" << std::endl;
        std::cout << "  Para crear dichos ficheros ejecutar donde tengas el .bag del experimento el siguiente comando en un terminal" << std::endl;
        std::cout << "  rosrun pcl_ros bag_to_pcd experimento3_64.bag /firefly_1/firefly_1/os1_cloud_node/points /home/alejandro/catkin_ws/src/mis_programas/bagfiles/experimento3_64/point_clouds" << std::endl;
        std::cout << "  Cambiando experimento3_64 por el que corresponda" << std::endl;
        return -1;
    }

    
    std::vector<boost::filesystem::path> ficheros;
    for (const auto &entry : boost::filesystem::directory_iterator(directorio_pcd)){
        std::cout << entry.path() << std::endl;
        std::cout << entry.path().extension() << std::endl;
        if ((entry.path().extension()==".pcd")){
            
            ficheros.push_back(entry.path());
        }

    }
    for(const auto &prueba : ficheros){
        std::cout << "Antes de ordenar: " << std::endl;
        std::cout << prueba.filename() << std::endl;
    }
    /*Es necesario ordenar el vector, ya que, cuando se leen los ficheros en el directorio se hace en orden aleatorio*/
    std::sort(ficheros.begin(), ficheros.end()); 

    for(const auto &prueba : ficheros){
        std::cout << "Despues de ordenar: " << std::endl;
        std::cout << prueba.filename() << std::endl;
    }




    std::cout << "Numero de ficheros .pcd =  "<< ficheros.size() << std::endl; 

    unsigned int numero_imagen = 0; //Variable para nombrar las imágenes png

    for(const auto &rutas : ficheros){
        
       
        pcl::PointCloud<pcl::PointXYZ>::Ptr cloud (new pcl::PointCloud<pcl::PointXYZ>);

        cv::Mat depth_float(IMAGE_HEIGHT,IMAGE_WIDTH,CV_32FC1,cv::Scalar::all(75.0));
        //cv::Mat depth_float(IMAGE_HEIGHT,IMAGE_WIDTH,CV_32FC1);
        cv::Mat depth_float_gray(IMAGE_HEIGHT,IMAGE_WIDTH,CV_32FC1);

         if (pcl::io::loadPCDFile<pcl::PointXYZ> (rutas.c_str(), *cloud) == -1) //* load the file
        {
            PCL_ERROR ("Couldn't read file \n");
            return (-1);
        }
        
        for (size_t i = 0; i < cloud->points.size (); ++i){
            

        
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
            }*/
            _phi=-atan2(_y,_x);

            _u=(IMAGE_WIDTH-1)*(_phi-MIN_PHI)/(MAX_PHI-MIN_PHI) + 0.5;
            _v=(IMAGE_HEIGHT-1)*(_theta-MIN_THETA)/(MAX_THETA-MIN_THETA) + 0.5;
            depth_float.at<float>(_v,_u)=_r;

        }  
        //Para pasar a escala de grises
        double min;
        double max;
        cv::minMaxIdx(depth_float, &min, &max);
        
        cv::convertScaleAbs(depth_float, depth_float_gray, 255.0 / max);
        
        
       
        std::string ruta_depth_map = "/home/alejandro/catkin_ws/src/mis_programas/bagfiles/" + experimento + "/depth_map";
        
        if(!(boost::filesystem::exists(ruta_depth_map))){
            std::cout << " No existe el directorio depth_map, se va a crear" << std::endl;
            if(boost::filesystem::create_directory(ruta_depth_map)){
                std::cout << ruta_depth_map << " creada correctamente" << std::endl;
            }
            else{
                std::cout << "ERROR: no se pudo crear " << ruta_depth_map << std::endl;
                return -1;
            }
        }


        ruta_depth_map = ruta_depth_map +"/"+ std::to_string(numero_imagen) +".png";
        
        cv::imwrite(ruta_depth_map, depth_float_gray);
            

       

        numero_imagen ++;

    }
    


    /*Prueba lectura de varios ficheros en un directorio*/
    return (0);
}