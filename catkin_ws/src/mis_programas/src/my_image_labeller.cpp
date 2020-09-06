#include <iostream>
#include <fstream>
#include <opencv2/core/mat.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <boost/filesystem.hpp>
#include <vector>
#include <string>
#include <rosbag/bag.h>
#include <rosbag/view.h>
#include <sensor_msgs/PointCloud2.h>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <math.h>


int main (int argc, char **argv){
    float _x, _y, _z, _r, _phi, _theta;
    long unsigned int _u, _v;
    double IMAGE_WIDTH = 1024.0;
    double IMAGE_HEIGHT = 64.0 ;
    float MIN_PHI = -M_PI;
    float MAX_PHI = M_PI;
    float MIN_THETA = (3*M_PI)/8;
    float MAX_THETA = (5*M_PI)/8;
    cv::Mat imagen_original;
    std::string experimento;
    if (argc == 2){
        experimento = argv[1];
    }
    else{
        std::cout << "ERROR en argumentos" << std::endl;
        std::cout << "  El comando para ejecutar el programa debe ser del estilo: " << std::endl;
        std::cout << "  rosrun mis_programas my_image_labeller experimento1_64" << std::endl;
        std::cout << "  SOLO debe haber 1 argumento, y este tiene que ser necesariamente de esta forma" <<std::endl;
        std::cout << "  Indicando el numero de experimento y el numero de planos verticales" << std::endl;
        std::cout << "  Es el mismo nombre de la carpeta donde está el .bag correspondiente" << std::endl;
        return -1;
    } 


    std::string imagen_original_path = "/home/alejandro/catkin_ws/src/mis_programas/bagfiles/" + experimento + "_vacio/depth_map";
    std::string directorio_pcd ="/home/alejandro/catkin_ws/src/mis_programas/bagfiles/" + experimento + "_vacio/point_clouds";
    
    std::vector <std::string> nombre_ficheros_pcd;
    std::vector <std::string> rutas_ficheros_pcd;
    std::vector <std::string> nombre_mensajes_real;
    /*Lectura de los nombres de los ficheros .pcd */

    if(!(boost::filesystem::exists(directorio_pcd))){
        std::cout << "ERROR: " << std::endl;
        std::cout << "  No existe el directorio point_clouds puede ser que no se haya creado los ficheros .pcd" << std::endl;
        std::cout << "  Para crear dichos ficheros ejecutar donde tengas el .bag del experimento el siguiente comando en un terminal" << std::endl;
        std::cout << "  rosrun pcl_ros bag_to_pcd "<< experimento <<"_vacio.bag /firefly_1/firefly_1/os1_cloud_node/points /home/alejandro/catkin_ws/src/mis_programas/bagfiles/" + experimento + "_vacio/point_clouds" << std::endl;
        return -1;
    }

    for (const auto &entry : boost::filesystem::directory_iterator(directorio_pcd)){
        //std::cout << entry.path().stem().c_str() << std::endl;
        //std::cout << entry.path().extension() << std::endl;
        nombre_ficheros_pcd.push_back(entry.path().stem().c_str()); //Me guardo solo el nombre sin la extensión en un vector
    }
    std::sort(nombre_ficheros_pcd.begin(), nombre_ficheros_pcd.end()); //Necesario ordenar ya que directory_iterator lee de forma aleatoria

    for (const auto &entry : boost::filesystem::directory_iterator(directorio_pcd)){
        //std::cout << entry.path() << std::endl;
        //std::cout << entry.path().extension() << std::endl;
        if ((entry.path().extension()==".pcd")){
            
            rutas_ficheros_pcd.push_back(entry.path().c_str());
        }

    }

    std::sort(rutas_ficheros_pcd.begin(), rutas_ficheros_pcd.end());
    

    /*Lectura de los nombres de los ficheros .pcd */

    /*Lectura de los timestamp de los mensajes, coincidentes con los nombres de los .pcd*/
    rosbag::Bag bag;
    rosbag::View view;
    rosbag::View::iterator view_it;

    
    try{
        bag.open("/home/alejandro/catkin_ws/src/mis_programas/bagfiles/"+ experimento +"_vacio/" + experimento + "_vacio.bag",rosbag::BagMode::Read);
    }
    catch (const rosbag::BagException&)
    {
        std::cerr << "Error opening file " << std::endl;
        return (-1);
    }
    rosbag::View topic_list_view(bag);

    std::string target_topic;
    std::map<std::string, std::string> topic_list;
    for(rosbag::ConnectionInfo const *ci: topic_list_view.getConnections() )
    {
        std::cout << "los topic del rosbag son: " << std::endl;
        std::cout << ci->topic << std::endl;
        std::cout << "El tipo de mensaje asociado a ese topic es: " << std::endl;
        std::cout << ci->datatype << std::endl << std::endl;
        topic_list[ci->topic] = ci->datatype;
        if(ci->topic == "/firefly_1/firefly_1/os1_cloud_node/points"){
            if(ci->datatype == std::string("sensor_msgs/PointCloud2")){
                target_topic = std::string ("/firefly_1/firefly_1/os1_cloud_node/points");
                view.addQuery(bag, rosbag::TopicQuery(target_topic));
            }
            else{
                std::cerr << "ERROR" << std::endl;
            }
        } 

    }

    view_it = view.begin();
    std::cerr << "Numero de mensajes: " << view.size() << "\n";
    while(view_it != view.end()){
        sensor_msgs::PointCloud2::ConstPtr cloud;
        sensor_msgs::PointCloud2 cloud_t;
        cloud = view_it-> instantiate<sensor_msgs::PointCloud2>();
        cloud_t = *cloud;
        std::stringstream ss;
        ss <<cloud_t.header.stamp;  
        //std::cerr << cloud_t.header.stamp <<std::endl;
        nombre_mensajes_real.push_back(ss.str());
        //std::cerr << "aaaaaa "<< ss.str() <<std::endl;
        ++view_it;
    }
    /*Lectura de los timestamp de los mensajes, coincidentes con los nombres de los .pcd*/

    /*Generación de imágenes para boundingBox y etiquetado*/
    std::string pathLabel = "/home/alejandro/catkin_ws/src/mis_programas/bagfiles/" + experimento + "_real/label/";

    /*COMPROBACIÓN DE QUE EXISTE ESTE DIRECTORIO*/
    if(!(boost::filesystem::exists(pathLabel))){
        std::cout << " No existe el directorio label, se va a crear \n";
        if(boost::filesystem::create_directory(pathLabel)){
            std::cout << pathLabel << " creada correctamente \n";
        }
        else{
            std::cout << "ERROR: no se pudo crear " << pathLabel << std::endl;
            return -1;
        }
    }
        
    unsigned int j = 0; 
    for(unsigned int n = 0; n < nombre_mensajes_real.size(); n++){        
        std::fstream file;
        file.open((pathLabel + std::to_string(n) +".txt"),std::fstream::out);
        if((nombre_mensajes_real[n] == nombre_ficheros_pcd[j])){
            /*Tratamiento de los ficheros .pcd*/
            pcl::PointCloud<pcl::PointXYZ>::Ptr cloud (new pcl::PointCloud<pcl::PointXYZ>);
            cv::Mat depth_float(IMAGE_HEIGHT,IMAGE_WIDTH,CV_32FC1,cv::Scalar::all(75.0));
            cv::Mat depth_float_gray(IMAGE_HEIGHT,IMAGE_WIDTH,CV_32FC1);
            if (pcl::io::loadPCDFile<pcl::PointXYZ> (rutas_ficheros_pcd[j], *cloud) == -1) //* load the file
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

                _phi=-atan2(_y,_x);

                _u=(IMAGE_WIDTH-1)*(_phi-MIN_PHI)/(MAX_PHI-MIN_PHI) + 0.5;
                _v=(IMAGE_HEIGHT-1)*(_theta-MIN_THETA)/(MAX_THETA-MIN_THETA) + 0.5;
                depth_float.at<float>(_v,_u)=_r;

            }  

            double min;
            double max;
            cv::minMaxIdx(depth_float, &min, &max);            
            cv::convertScaleAbs(depth_float, depth_float_gray, 255.0 / max);      
            std::string ruta_depth_map = "/home/alejandro/catkin_ws/src/mis_programas/bagfiles/" + experimento + "_vacio/depth_map";
            
            if(!(boost::filesystem::exists(ruta_depth_map))){
                std::cout << " No existe el directorio depth_map, se va a crear \n";
                if(boost::filesystem::create_directory(ruta_depth_map)){
                    std::cout << ruta_depth_map << " creada correctamente \n";
                }
                else{
                    std::cout << "ERROR: no se pudo crear " << ruta_depth_map << std::endl;
                    return -1;
                }
            }


            ruta_depth_map = ruta_depth_map +"/"+ std::to_string(n) +".png";
            
            cv::imwrite(ruta_depth_map, depth_float_gray);
           
            cv::Mat modificada;
            modificada = depth_float_gray;
            modificada.convertTo(modificada,CV_32FC1);
            /*Escritura del cout en un fichero*/
            //std::ofstream out("error_labeller.txt");
            //std::streambuf *coutbuf = std::cout.rdbuf(); //save old buf
            //std::cout.rdbuf(out.rdbuf());
            /*Escritura del cout en un fichero*/
            //std::cout << "Antes de modificar: \n " << modificada << "\n";
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

            //std::cout << "Despues de modificar: \n " << modificada << "\n";

            cv::minMaxIdx(modificada, &min, &max);
            cv::Mat modificada_2(IMAGE_HEIGHT,IMAGE_WIDTH,CV_32FC1);       
            cv::convertScaleAbs(modificada, modificada_2, 255.0 / max);
            //std::cout << "Despues de escalar: \n " << modificada_2 << "\n";
            //std::cout.rdbuf(coutbuf); //reset to standard output again
            std::string ruta_BW_map = "/home/alejandro/catkin_ws/src/mis_programas/bagfiles/" + experimento + "_vacio/BW_map";
            if(!(boost::filesystem::exists(ruta_BW_map))){
                std::cout << " No existe el directorio BW_map, se va a crear \n";
                if(boost::filesystem::create_directory(ruta_BW_map)){
                    std::cout << ruta_BW_map << " creada correctamente \n";
                }
                else{
                    std::cout << "ERROR: no se pudo crear " << ruta_BW_map << std::endl;
                    return -1;
                }
            }
            ruta_BW_map = ruta_BW_map + "/"+ std::to_string(n) +".png";
            cv::imwrite(ruta_BW_map, modificada_2);
            cv::Rect boundingBox;
            boundingBox = cv::boundingRect(modificada_2);
            cv::Mat final;
            std::string real_depth_map ="/home/alejandro/catkin_ws/src/mis_programas/bagfiles/" + experimento + "_real/depth_map";
            if(!(boost::filesystem::exists(directorio_pcd))){
                std::cout << "ERROR: \n";
                std::cout << "  No existe el directorio: " << real_depth_map << "\n";
                std::cout << "  Para crear dichos ficheros ejecutar \n" ;
                std::cout << "  rosrun mis_programas pclToDepthMap_V2 " << experimento <<"_real " << std::endl;
                return -1;
            }
            final = cv::imread(real_depth_map + "/"+ std::to_string(n) + ".png");
            cv::rectangle(final,boundingBox.tl(),boundingBox.br(), cv::Scalar(0, 255, 0),1,8,0);
            std::string ruta_bounding = "/home/alejandro/catkin_ws/src/mis_programas/bagfiles/" + experimento + "_real/bounding_map";
            
            /*COMPROBAR QUE EXISTE LA RUTA*/
            if(!(boost::filesystem::exists(ruta_bounding))){
                std::cout << " No existe el directorio bounding_map, se va a crear \n";
                if(boost::filesystem::create_directory(ruta_bounding)){
                    std::cout << pathLabel << " creada correctamente \n";
                }
                else{
                    std::cout << "ERROR: no se pudo crear " << ruta_bounding << std::endl;
                    return -1;
                }
            }
            
            ruta_bounding = ruta_bounding + "/"+ std::to_string(n) +".png";
            cv::imwrite(ruta_bounding, final);            
            /*Tratamiento de los ficheros .pcd ver pclToDepthMapV2 */

            file << "0 " << (boundingBox.x + ((boundingBox.width)/2.0)) << " " << (boundingBox.y +((boundingBox.height)/2.0)) << " " << (boundingBox.width)/(IMAGE_WIDTH) << " " << (boundingBox.height)/(IMAGE_HEIGHT);
            //file << "\n height: " << boundingBox.height << "  width: " << boundingBox.width;
            file.close();


            ++j;

        }
        /*Si no son iguales generar imagen en blanco y txt vacío*/
        else{
            cv::Mat blanco (IMAGE_HEIGHT,IMAGE_WIDTH,CV_32FC1,cv::Scalar::all(255.0));
            std::string ruta_depth_map = "/home/alejandro/catkin_ws/src/mis_programas/bagfiles/" + experimento + "_vacio/depth_map";
            if(!(boost::filesystem::exists(ruta_depth_map))){
                std::cout << " No existe el directorio depth_map, se va a crear \n";
                if(boost::filesystem::create_directory(ruta_depth_map)){
                    std::cout << ruta_depth_map << " creada correctamente \n";
                }
                else{
                    std::cout << "ERROR: no se pudo crear " << ruta_depth_map << std::endl;
                    return -1;
                }
            }
            ruta_depth_map = ruta_depth_map +"/"+ std::to_string(n) +".png"; 
            cv::imwrite(ruta_depth_map, blanco);

            cv::Mat negro (IMAGE_HEIGHT,IMAGE_WIDTH,CV_32FC1,cv::Scalar::all(0.0));
            std::string ruta_BW_map = "/home/alejandro/catkin_ws/src/mis_programas/bagfiles/" + experimento + "_vacio/BW_map";
            if(!(boost::filesystem::exists(ruta_BW_map))){
                std::cout << " No existe el directorio BW_map, se va a crear \n";
                if(boost::filesystem::create_directory(ruta_BW_map)){
                    std::cout << ruta_BW_map << " creada correctamente \n";
                }
                else{
                    std::cout << "ERROR: no se pudo crear " << ruta_BW_map << std::endl;
                    return -1;
                }
            }
            ruta_BW_map = ruta_BW_map + "/"+ std::to_string(n) +".png";
            cv::imwrite(ruta_BW_map, negro);

            cv::Mat final;
            std::string real_depth_map ="/home/alejandro/catkin_ws/src/mis_programas/bagfiles/" + experimento + "_real/depth_map";
            if(!(boost::filesystem::exists(directorio_pcd))){
                std::cout << "ERROR: \n";
                std::cout << "  No existe el directorio: " << real_depth_map << "\n";
                std::cout << "  Para crear dichos ficheros ejecutar \n" ;
                std::cout << "  rosrun mis_programas pclToDepthMap_V2 " << experimento <<"_real " << std::endl;
                return -1;
            }
            final = cv::imread(real_depth_map + "/"+ std::to_string(n) + ".png");
            
            
            std::string ruta_bounding = "/home/alejandro/catkin_ws/src/mis_programas/bagfiles/" + experimento + "_real/bounding_map";
            if(!(boost::filesystem::exists(ruta_bounding))){
                std::cout << " No existe el directorio bounding_map, se va a crear \n";
                if(boost::filesystem::create_directory(ruta_bounding)){
                    std::cout << pathLabel << " creada correctamente \n";
                }
                else{
                    std::cout << "ERROR: no se pudo crear " << ruta_bounding << std::endl;
                    return -1;
                }
            }

            ruta_bounding = ruta_bounding + "/"+ std::to_string(n) +".png";
            cv::imwrite(ruta_bounding, final);
            file.close();
        }

        
    }
    /*Generación de imágenes para boundingBox y etiquetado*/




    return 0;
}