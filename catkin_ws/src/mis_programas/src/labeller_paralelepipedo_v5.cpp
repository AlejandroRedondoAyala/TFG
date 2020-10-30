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
#include <nav_msgs/Odometry.h>

int main (int argc, char ** argv){

    float _x, _y, _z, _r, _phi, _theta;
    long unsigned int _u, _v;
    double IMAGE_WIDTH = 1024.0;
    double IMAGE_HEIGHT = 64.0;
    float MIN_PHI = -M_PI;
    float MAX_PHI = M_PI;
    float MIN_THETA = (3*M_PI)/8;
    float MAX_THETA = (5*M_PI)/8;

    //Definicion de la caja que contiene al dron

    float x_box = 0.65, y_box = 0.65, z_box = 0.45;
    

    std::string experimento;
    /*Lectura de argumentos*/
    if(argc == 3){
        experimento = argv[1];
        IMAGE_HEIGHT = atof(argv[2]);
        std::cerr << argv[1];
        std::cerr << "Imagen de ancho: " << IMAGE_WIDTH << " y alto: " << IMAGE_HEIGHT << "\n";
        /*if((argv[1] == "experimento1_64")||(argv[1] == "experimento2_64")||(argv[1] == "experimento3_64")||(argv[1] == "experimento4_64")||(argv[1] == "experimento5_64")){
            experimento = argv[1];
        }
        else{
            std::cerr << "ERROR: \n";
            std::cerr << "uso : rosrun mis_programas labeller_paralelepipedo <argumento> \n";
            std::cerr << "Donde <argumento> es uno de los siguientes: \n";
            std::cerr << "experimento1_64 \n";
            std::cerr << "experimento2_64 \n";
            std::cerr << "experimento3_64 \n";
            std::cerr << "experimento4_64 \n";
            std::cerr << "experimento5_64 \n";
            return -1;
        }*/
    }
    else{
        std::cerr << "ERROR: \n";
        std::cerr << "uso : rosrun mis_programas labeller_paralelepipedo <argumento> <HEIGHT>\n";
        std::cerr << "Donde <argumento> es uno de los siguientes: \n";
        std::cerr << "experimento1_64 \n";
        std::cerr << "experimento2_64 \n";
        std::cerr << "experimento3_64 \n";
        std::cerr << "experimento4_64 \n";
        std::cerr << "experimento5_64 \n";
        std::cerr << "y HEIGHT es 32, 64 o 128 \n";
        return -1;
    }
    /*Lectura de argumentos*/

    /*Rutas de ficheros de guardado*/
    std::string label_path = "/home/alejandro/catkin_ws/src/mis_programas/bagfiles/" + experimento + "_real/label";
    std::string depth_map_path = "/home/alejandro/catkin_ws/src/mis_programas/bagfiles/" + experimento +"_real/depth_map";
    std::string all_depth_map_path = "/home/alejandro/catkin_ws/src/mis_programas/bagfiles/" + experimento +"_real/all_depth_map";
    std::string BW_map_path = "/home/alejandro/catkin_ws/src/mis_programas/bagfiles/" + experimento +"_real/BW_map";    
    std::string bounding_map_path = "/home/alejandro/catkin_ws/src/mis_programas/bagfiles/" + experimento +"_real/bounding_map";
    std::string odom_information  = "/home/alejandro/catkin_ws/src/mis_programas/bagfiles/" + experimento +"_real/odom_information";
    std::string extra_information  = "/home/alejandro/catkin_ws/src/mis_programas/bagfiles/" + experimento +"_real/extra_information";
    std::string pos1_info  = "/home/alejandro/catkin_ws/src/mis_programas/bagfiles/" + experimento +"_real/pos1_info";
    std::string pos2_info  = "/home/alejandro/catkin_ws/src/mis_programas/bagfiles/" + experimento +"_real/pos2_info";
    /*Rutas de ficheros de guardado*/

    /*Comprobación de existencia ficheros de guardado*/
    if(!(boost::filesystem::exists(label_path))){
        std::cout << " No existe el directorio label_path, se va a crear \n";
        if(boost::filesystem::create_directory(label_path)){
            std::cout << label_path << " creada correctamente \n";
        }
        else{
            std::cout << "ERROR: no se pudo crear " << label_path << std::endl;
            return -1;
        }
    }

    if(!(boost::filesystem::exists(depth_map_path))){
        std::cout << " No existe el directorio depth_map, se va a crear \n";
        if(boost::filesystem::create_directory(depth_map_path)){
            std::cout << depth_map_path << " creada correctamente \n";
        }
        else{
            std::cout << "ERROR: no se pudo crear " << depth_map_path << std::endl;
            return -1;
        }
    }

    if(!(boost::filesystem::exists(BW_map_path))){
        std::cout << " No existe el directorio BW_map, se va a crear \n";
        if(boost::filesystem::create_directory(BW_map_path)){
            std::cout << BW_map_path << " creada correctamente \n";
        }
        else{
            std::cout << "ERROR: no se pudo crear " << BW_map_path << std::endl;
            return -1;
        }
    }
    
    if(!(boost::filesystem::exists(bounding_map_path))){
        std::cout << " No existe el directorio BW_map, se va a crear \n";
        if(boost::filesystem::create_directory(bounding_map_path)){
            std::cout << bounding_map_path << " creada correctamente \n";
        }
        else{
            std::cout << "ERROR: no se pudo crear " << bounding_map_path << std::endl;
            return -1;
        }
    }

    if(!(boost::filesystem::exists(odom_information))){
        std::cout << " No existe el directorio odom_information, se va a crear \n";
        if(boost::filesystem::create_directory(odom_information)){
            std::cout << odom_information << " creada correctamente \n";
        }
        else{
            std::cout << "ERROR: no se pudo crear " << odom_information << std::endl;
            return -1;
        }
    }

    if(!(boost::filesystem::exists(all_depth_map_path))){
        std::cout << " No existe el directorio all_depth_map, se va a crear \n";
        if(boost::filesystem::create_directory(all_depth_map_path)){
            std::cout << all_depth_map_path << " creada correctamente \n";
        }
        else{
            std::cout << "ERROR: no se pudo crear " << all_depth_map_path << std::endl;
            return -1;
        }
    }

    if(!(boost::filesystem::exists(extra_information))){
        std::cout << " No existe el directorio extra_information, se va a crear \n";
        if(boost::filesystem::create_directory(extra_information)){
            std::cout << extra_information << " creada correctamente \n";
        }
        else{
            std::cout << "ERROR: no se pudo crear " << extra_information << std::endl;
            return -1;
        }
    }

    if(!(boost::filesystem::exists(pos1_info))){
        std::cout << " No existe el directorio extra_information, se va a crear \n";
        if(boost::filesystem::create_directory(pos1_info)){
            std::cout << pos1_info << " creada correctamente \n";
        }
        else{
            std::cout << "ERROR: no se pudo crear " << pos1_info << std::endl;
            return -1;
        }
    }

    if(!(boost::filesystem::exists(pos2_info))){
        std::cout << " No existe el directorio extra_information, se va a crear \n";
        if(boost::filesystem::create_directory(pos2_info)){
            std::cout << pos2_info << " creada correctamente \n";
        }
        else{
            std::cout << "ERROR: no se pudo crear " << pos2_info << std::endl;
            return -1;
        }
    }

    /*Comprobación de existencia ficheros de guardado*/





    /*Apertura de rosbag*/
    std::string bag_path = "/home/alejandro/catkin_ws/src/mis_programas/bagfiles/" + experimento + "_real";
    //Comprobación de existencia
    if(!(boost::filesystem::exists(bag_path))){
        std::cerr << "ERROR: \n";
        std::cerr << "No existe el directorio " << bag_path << "\n";
        std::cerr << "Es posible que no se haya grabado ningún experimento. Usar el siguiente comando \n";
        std::cerr << "roslaunch mis_programas experimento1.launch laser:=64 grabar:=true world_name:=real \n";
        std::cerr << "cambiando experimento1.launch por el que corresponda";
        return -1;
    }
    rosbag::Bag bag;

    try{
        bag.open(bag_path+"/"+experimento+"_real.bag");
    }
    catch(const rosbag::BagException&){
        std::cerr << "ERROR: No se pudo abrir " << bag_path << "/" << experimento << "_real.bag \n";
        return -1;
    }
    /*Apertura de rosbag*/

    /*Objetos iteradores del rosbag*/
    rosbag::View cloud_view;
    rosbag::View::iterator cloud_view_it;

    rosbag::View odom1_view;
    rosbag::View::iterator odom1_view_it;

    rosbag::View odom2_view;
    rosbag::View::iterator odom2_view_it;

    rosbag::View topic_list_view(bag);
    std::map<std::string, std::string> topic_list;
    
    for(rosbag::ConnectionInfo const *ci: topic_list_view.getConnections()){
        topic_list[ci->topic] = ci->datatype;
        if(ci->topic == std::string("/firefly_1/firefly_1/os1_cloud_node/points")){
            cloud_view.addQuery(bag,rosbag::TopicQuery(std::string("/firefly_1/firefly_1/os1_cloud_node/points")));
        }
        if(ci->topic == std::string("/firefly_1/odometry_sensor1/odometry")){
            odom1_view.addQuery(bag,rosbag::TopicQuery(std::string("/firefly_1/odometry_sensor1/odometry")));
        }
        if(ci->topic == std::string("/firefly_2/odometry_sensor1/odometry")){
            odom2_view.addQuery(bag,rosbag::TopicQuery(std::string("/firefly_2/odometry_sensor1/odometry")));
        }        
    }
    /*Objetos iteradores del rosbag*/

    /*Apertura de ficheros .pcd*/
    std::string pcd_path = "/home/alejandro/catkin_ws/src/mis_programas/bagfiles/" + experimento +"_real/point_clouds";
    //Compruebo que existan
    if(!(boost::filesystem::exists(pcd_path))){
        std::cout << "ERROR: " << std::endl;
        std::cout << "  No existe el directorio point_clouds puede ser que no se haya creado los ficheros .pcd" << std::endl;
        std::cout << "  Para crear dichos ficheros ejecutar donde tengas el .bag del experimento el siguiente comando en un terminal" << std::endl;
        std::cout << "  rosrun pcl_ros bag_to_pcd "<< experimento <<"_real.bag /firefly_1/firefly_1/os1_cloud_node/points /home/alejandro/catkin_ws/src/mis_programas/bagfiles/" + experimento + "_real/point_clouds" << std::endl;
        return -1;
    }
    std::vector <std::string> nombres_ficheros_pcd;
    std::vector <std::string> rutas_ficheros_pcd;
    for(const auto &entry : boost::filesystem::directory_iterator(pcd_path)){
        rutas_ficheros_pcd.push_back(entry.path().c_str()); //guardo la ruta completa
        nombres_ficheros_pcd.push_back(entry.path().stem().c_str()); //Guardo los nombres sin extension
    }

    std::sort(rutas_ficheros_pcd.begin(), rutas_ficheros_pcd.end());
    std::sort(nombres_ficheros_pcd.begin(), nombres_ficheros_pcd.end());

    /*Apertura de ficheros .pcd*/
    odom1_view_it = odom1_view.begin();
    odom2_view_it = odom2_view.begin();

    std::fstream csv_file;
    csv_file.open((extra_information + "/Odometria_Excel.csv"),std::fstream::out | std::fstream::app);
    csv_file << "ficheroPNG; tsimulacion; tgraficas; x1; y1; z1; x2; y2; z2; Vx1; Vy1; Vz1; Vx2; Vy2; Vz2; x2-x1; y2-y1; z2-z1; Vx2-Vx1; Vy2-Vy1; Vz2-Vz1; Drelativa; Vrelativa"<<"\n";
    csv_file.close();

    for(int n = 0; n < rutas_ficheros_pcd.size(); n++){
        



        /*Comenzamos localizando la posición real de los drones*/
        float x1 , y1, z1, x2, y2, z2;
        nav_msgs::Odometry::ConstPtr odom1;
        nav_msgs::Odometry odom1_t;
        
        odom1 = odom1_view_it -> instantiate<nav_msgs::Odometry>();
        
        odom1_t = *odom1;
        x1 = odom1_t.pose.pose.position.x;
        y1 = odom1_t.pose.pose.position.y;
        z1 = odom1_t.pose.pose.position.z;
        z1 = z1 - 0.0365; //El origen del LIDAR no coincide con el origen del dron


        nav_msgs::Odometry::ConstPtr odom2;
        nav_msgs::Odometry odom2_t;
        odom2 = odom2_view_it -> instantiate<nav_msgs::Odometry>();
        odom2_t = *odom2;
        x2 = odom2_t.pose.pose.position.x;
        y2 = odom2_t.pose.pose.position.y;
        z2 = odom2_t.pose.pose.position.z;
        /*Comenzamos localizando la posición real de los drones*/

        /*Ahora lo traducimos a las distancias que vería el LIDAR*/
        float x_pose, y_pose, z_pose;
        x_pose = x2 - x1;
        y_pose = y2 - y1;
        z_pose = z2 - z1;
        /*Ahora lo traducimos a las distancias que vería el LIDAR*/

        /*Registro de estos datos en un fichero*/
        float Vx1, Vx2, Vy1, Vy2, Vz1, Vz2;
        Vx1 = odom1_t.twist.twist.linear.x;
        Vy1 = odom1_t.twist.twist.linear.y;
        Vz1 = odom1_t.twist.twist.linear.z;
        Vx2 = odom2_t.twist.twist.linear.x;
        Vy2 = odom2_t.twist.twist.linear.y;
        Vz2 = odom2_t.twist.twist.linear.z;
        float x_rel, y_rel, z_rel, Vx_rel, Vy_rel, Vz_rel;
        x_rel = (x2 -x1);
        y_rel = (y2 - y1);
        z_rel = (z2 -(z1+0.0365));
        Vx_rel = (Vx2 - Vx1);
        Vy_rel = (Vy2 - Vy1);
        Vz_rel = (Vz2 - Vz1);

        /*Abrimos el fichero de posicion*/
        std::fstream position_file;
        position_file.open((odom_information + "/odom_" + std::to_string(n) +".txt"),std::fstream::out);
        /*Abrimos el fichero de posicion*/
        position_file << "Informacion odometria del " << experimento << "\n";
        position_file << "Time stamp 1: "<< odom1_t.header.stamp << "\n";
        position_file << "Time stamp 2: "<< odom2_t.header.stamp << "\n \n";
        position_file << "Firefly_1 dron portador del LIDAR\n";
        position_file << "x1: " << x1 << " y1: " << y1 << " z1: " << (z1 + 0.0365) << "\n";
        position_file << "Vx1: " << Vx1 << " Vy1: " << Vy1 << " Vz1: " << Vz1 << "\n \n"; 
        position_file << "Firefly_2 dron objetivo, que quiero detectar\n";
        position_file << "x2: " << x2 << " y2: " << y2 << " z2: " << z2 << "\n";
        position_file << "Vx2: " << Vx2 << " Vy2: " << Vy2 << " Vz2: " << Vz2<< "\n\n";
        position_file << "Posicion relativa:\n";
        position_file << "x_relativa: " << x_rel << " y_relativa: " << y_rel << " z_relativa: " << z_rel << "\n\n";
        position_file << "Posicion absoluta o distancia:\n";
        position_file << "d =  " << sqrt((x_rel*x_rel) + (y_rel*y_rel) + (z_rel*z_rel)) << "\n\n";
        position_file << "Velocidad relativa:\n";
        position_file << "Vx_relativa: " << Vx_rel << " Vy_relativa: " << Vy_rel << " Vz_relativa: " << Vz_rel << "\n\n";
        position_file << "Velocidad relativa absoluta:\n";
        position_file << "Velocidad relativa =  " << sqrt((Vx_rel*Vx_rel) + (Vy_rel*Vy_rel) + (Vz_rel*Vz_rel)) << "\n\n";
        position_file.close();

        /*Registro de estos datos en un fichero*/
        
        /*Fichero .csv para análisis en Excel*/
        csv_file.open((extra_information + "/Odometria_Excel.csv"),std::fstream::out | std::fstream::app);
        csv_file << n << ";" << odom1_t.header.stamp << ";"<< "0" << ";" << x1 << ";" << y1 << ";" << (z1 +0.0365) << ";" << x2 << ";" << y2 << ";" << z2 << ";" << Vx1 << ";" << Vy1 << ";" << Vz1 << ";" << Vx2 << ";" << Vy2 << ";" << Vz2 << ";" << x_rel << ";"<< y_rel << ";" << z_rel << ";" << Vx_rel << ";" << Vy_rel << ";" << Vz_rel << ";" << sqrt((x_rel*x_rel) + (y_rel*y_rel) + (z_rel*z_rel)) << ";" << sqrt((Vx_rel*Vx_rel) + (Vy_rel*Vy_rel) + (Vz_rel*Vz_rel)) << "\n";
        csv_file.close();    
        /*Fichero .csv para análisis en Excel*/

        std::fstream pos1_file;
        pos1_file.open((pos1_info + "/" + std::to_string(n) +".txt"),std::fstream::out );
        pos1_file << x1 <<" "<< y1 << " " << z1;
        pos1_file.close();
        std::fstream pos2_file;
        pos2_file.open((pos2_info + "/" + std::to_string(n) +".txt"),std::fstream::out );
        pos2_file << x2 <<" "<< y2 << " " << z2;
        pos2_file.close();


        /*Defino los objetos necesario para generar y tratar las imágenes*/
        cv::Mat depth_map(IMAGE_HEIGHT, IMAGE_WIDTH, CV_32FC1, cv::Scalar::all(75.0));
        cv::Mat BW_image(IMAGE_HEIGHT, IMAGE_WIDTH, CV_32FC1, cv::Scalar::all(0.0));
        cv::Mat bounding_map;
        cv::Mat all_depth_map;

        /*Defino los objetos necesario para generar y tratar las imágenes*/

        
        /*Lectura de la nube de puntos registrada por el LIDAR*/        
        pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_pcl (new pcl::PointCloud<pcl::PointXYZ>);

        if(pcl::io::loadPCDFile<pcl::PointXYZ>(rutas_ficheros_pcd[n], *cloud_pcl) == -1){
            PCL_ERROR("No se pudo leer el fichero \n");
            return -1;
        }

        for(size_t i = 0; i < cloud_pcl->points.size(); ++i){
            _x = cloud_pcl->points[i].x;
            _y = cloud_pcl->points[i].y;
            _z = cloud_pcl->points[i].z;
            _r = sqrt(_x*_x + _y*_y +_z*_z);

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

            if ( ((_x > (x_pose - (x_box/2.0))) && (_x < (x_pose + (x_box/2.0)))) && ((_y > (y_pose-(y_box/2.0)))&&(_y < (y_pose + (y_box/2.0)))) && ((_z > (z_pose - (z_box/2.0))) && (_z < (z_pose + (z_box/2.0)))) ){

                BW_image.at<float>(_v,_u) = 255;
                
            }

            //depth_map.at<float>(_v,_u)=_r;
            depth_map.at<float>(_v,_u)=_x;



        }

        /*Cálculo del BoundingBox*/
        cv::Rect boundingBox;
        
        cv::convertScaleAbs(BW_image, BW_image, 1.0);// necesario para que funcione el boundingRect

        boundingBox = cv::boundingRect(BW_image);
            

        double min;
        double max;
        cv::minMaxIdx(depth_map, &min, &max);        
        cv::convertScaleAbs(depth_map, depth_map, 255.0 / max);
        cv::cvtColor(depth_map, bounding_map, CV_GRAY2RGB);

        cv::rectangle(bounding_map, boundingBox.tl(), boundingBox.br(), cv::Scalar(0, 255, 0),1,8,0);

        /*Etiquetado solo si no está vacío*/
        if(!(boundingBox.empty())){
            cv::imwrite( (depth_map_path + "/"+ std::to_string(n) +".png"), depth_map);
            /*Abrimos el fichero de etiquetado*/
            std::fstream file;
            file.open((label_path + "/" + std::to_string(n) +".txt"),std::fstream::out);
            /*Abrimos el fichero de etiquetado*/
            file << "0 " << ((boundingBox.x + ((boundingBox.width)/2.0))/IMAGE_WIDTH) << " " << ((boundingBox.y +((boundingBox.height)/2.0))/IMAGE_HEIGHT) << " " << (boundingBox.width)/(IMAGE_WIDTH) << " " << (boundingBox.height)/(IMAGE_HEIGHT);
            file.close();
            /*Etiquetado*/
        }
        

        /*Escritura de imágenes*/
       
        cv::imwrite( (all_depth_map_path + "/"+ std::to_string(n) +".png"), depth_map);
        cv::imwrite( (BW_map_path + "/"+ std::to_string(n) +".png"), BW_image);
        cv::imwrite( (bounding_map_path + "/"+ std::to_string(n) +".png"), bounding_map);

        ++odom1_view_it;
        ++odom2_view_it;

        //Fichero para tener localizados las imágenes a fin de probar todas a la vez con el comando de YOLO que me permite
        //evaluar las detecciones y meter los resultados a un fichero de texto
        std::fstream info_test;
        info_test.open(((extra_information)+"/"+experimento+".txt"),std::fstream::out | std::fstream::app);
        info_test << all_depth_map_path << "/"<< std::to_string(n) <<".png" << "\n";
        info_test.close();

        


    }//siguiente fichero .pcd


    return 0;
}