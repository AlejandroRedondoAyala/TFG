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
    double IMAGE_HEIGHT = 64.0 ;
    float MIN_PHI = -M_PI;
    float MAX_PHI = M_PI;
    float MIN_THETA = (3*M_PI)/8;
    float MAX_THETA = (5*M_PI)/8;
    cv::Mat imagen_original;
    std::string experimento;
    std::string imagen_original_path = "/home/alejandro/catkin_ws/src/mis_programas/bagfiles/experimento5_64_real/depth_map";
    std::string directorio_pcd ="/home/alejandro/catkin_ws/src/mis_programas/bagfiles/experimento3_64_real/point_clouds/34.810000000.pcd";

   
    std::vector <std::string> nombre_ficheros_pcd;
    std::vector <std::string> rutas_ficheros_pcd;
    std::vector <std::string> nombre_mensajes_real; 

    rosbag::Bag bag;
    rosbag::View view;
    rosbag::View::iterator view_it;

    
    try{
        bag.open("/home/alejandro/catkin_ws/src/mis_programas/bagfiles/experimento3_64_real/experimento3_64_real.bag",rosbag::BagMode::Read);
    }
    catch (const rosbag::BagException&)
    {
        std::cerr << "Error opening file " << std::endl;
        return (-1);
    }
    rosbag::View topic_list_view(bag);

    std::string target_topic;
    std::map<std::string, std::string> topic_list;

    /*nuevos*/
    rosbag::View odom1_view;
    rosbag::View::iterator odom1_view_it;
    rosbag::View odom2_view;
    rosbag::View::iterator odom2_view_it;


    /*nuevos*/
    std::vector <double> pose_1;
    std::vector <double> pose_2;

    double x_pose , y_pose , z_pose;

    for(rosbag::ConnectionInfo const *ci: topic_list_view.getConnections() ){
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

        if(ci->topic == std::string("/firefly_1/odometry_sensor1/odometry")){
            odom1_view.addQuery(bag,rosbag::TopicQuery(std::string("/firefly_1/odometry_sensor1/odometry")));
        }
        if(ci->topic == std::string("/firefly_2/odometry_sensor1/odometry")){
            odom2_view.addQuery(bag,rosbag::TopicQuery(std::string("/firefly_2/odometry_sensor1/odometry")));
        }

        view_it = view.begin();
        std::cerr << "Numero de mensajes point: " << view.size() << "\n";
        odom1_view_it = odom1_view.begin();
        std::cerr << "Numero de mensajes odom1: " << odom1_view.size() << "\n";
        odom2_view_it = odom2_view.begin();
        std::cerr << "Numero de mensajes odom2: " << odom2_view.size() << "\n";

        std::cerr << "odometría dron 1: \n";
        

        while(odom1_view_it != odom1_view.end()){

            nav_msgs::Odometry::ConstPtr odom1;
            nav_msgs::Odometry odom1_t;
            odom1 = odom1_view_it -> instantiate<nav_msgs::Odometry>();
            odom1_t = *odom1;
            std::stringstream sstream;
            std::cerr << odom1_t.header.stamp.toSec() << "\n";
            std::cerr << "Posicion x: " << odom1_t.pose.pose.position.x << "\n";
            std::cerr << "Posicion y: " << odom1_t.pose.pose.position.y << "\n";
            std::cerr << "Posicion z: " << odom1_t.pose.pose.position.z << "\n";
            
            if(odom1_t.header.stamp.toSec() == 34.810000000 ){
                pose_1.push_back(odom1_t.pose.pose.position.x);
                pose_1.push_back(odom1_t.pose.pose.position.y); 
                pose_1.push_back(odom1_t.pose.pose.position.z);
            }

            ++odom1_view_it;
        }

        std::cerr << "odometría dron 2: \n";

        while(odom2_view_it != odom2_view.end()){

            nav_msgs::Odometry::ConstPtr odom2;
            nav_msgs::Odometry odom2_t;
            odom2 = odom2_view_it -> instantiate<nav_msgs::Odometry>();
            odom2_t = *odom2;
            std::stringstream sstream;
            std::cerr << odom2_t.header.stamp << "\n";
            std::cerr << "Posicion x: " << odom2_t.pose.pose.position.x << "\n";
            std::cerr << "Posicion y: " << odom2_t.pose.pose.position.y << "\n";
            std::cerr << "Posicion z: " << odom2_t.pose.pose.position.z << "\n";

            if(odom2_t.header.stamp.toSec() == 34.810000000 ){
                pose_2.push_back(odom2_t.pose.pose.position.x);
                pose_2.push_back(odom2_t.pose.pose.position.y); 
                pose_2.push_back(odom2_t.pose.pose.position.z);
            }


            ++odom2_view_it;
        }

        
    }

    std::cerr << "La posición del dron 1 guardada es:\n";
    std::cerr << "x: " << pose_1[0] << " y: " << pose_1[1] << " z: " << pose_1[2] << "\n";
    std::cerr << "La posición del dron 2 guardada es:\n";
    std::cerr << "x: " << pose_2[0] << " y: " << pose_2[1] << " z: " << pose_2[2] << "\n";
    
    cv::Mat BW_image(IMAGE_HEIGHT,IMAGE_WIDTH, CV_32FC1, cv::Scalar::all(0.0));
    cv::Mat depth_float(IMAGE_HEIGHT,IMAGE_WIDTH,CV_32FC1,cv::Scalar::all(75.0));

    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud (new pcl::PointCloud<pcl::PointXYZ>);

   if (pcl::io::loadPCDFile<pcl::PointXYZ> (directorio_pcd, *cloud) == -1) //* load the file
  {
    PCL_ERROR ("Couldn't read file test_pcd.pcd \n");
    return (-1);
  }
  std::cout << "Loaded "
            << cloud->width * cloud->height
            << " data points from test_pcd.pcd with the following fields: "
            << std::endl;


    std::ofstream out("prueba_paralelepipedo_3.txt");
    std::streambuf *coutbuf = std::cout.rdbuf(); //save old buf
    std::cout.rdbuf(out.rdbuf());
    x_pose = (pose_2[0] - pose_1[0]);
    y_pose = (pose_2[1] - pose_1[1]);
    std::cerr << "pose_1[2]" << pose_1[2] << " pose_2[2]: " << pose_2[2] << std::endl;
    pose_1[2] = (pose_1[2] - 0.0365);
    z_pose = (pose_2[2] - pose_1[2]);



  for (size_t i = 0; i < cloud->points.size (); ++i){
    /*std::cerr << "X:  " << cloud->points[i].x
              << "  Y:  "    << cloud->points[i].y
              << "  Z:  "    << cloud->points[i].z << std::endl;*/

        
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
        depth_float.at<float>(_v,_u)=_x;
        
        if((_x > 10)&& (_x < 14)&&(_z > 0)){
            std::cout <<"Punto de la nube: \n";
            std::cout << "x: " << _x << "\n";
            std::cout << "y: " << _y << "\n";
            std::cout << "z: " << _z << "\n";
            std::cout << "_phi: " <<_phi;
            std::cout << "_theta: " <<_theta << std::endl;
            std::cout << " u: " <<_u;
            std::cout << " v: " <<_v << std::endl;
        }
        

        if ( ((_x > (x_pose - 0.325)) && (_x < (x_pose + 0.325))) && ((_y > (y_pose-0.325))&&(_y < (y_pose + 0.325))) && ((_z > (z_pose - 0.225)) && (_z < (z_pose + 0.225))) ){
            std::cout <<"Nuevo punto \n";
            std::cout << "x: " << _x << "\n";
            std::cout << "y: " << _y << "\n";
            std::cout << "z: " << _z << "\n";
            std::cout << "r: " << _r << "\n";  
            BW_image.at<float>(_v,_u) = 255;
            std::cout << "_phi: " <<_phi;
            std::cout << "_theta: " <<_theta << std::endl;
            std::cout << " u: " <<_u;
            std::cout << " v: " <<_v << std::endl;
            std::cout << "\n \n";
        }
    }
    
    double min;
    double max;
    cv::minMaxIdx(depth_float, &min, &max);
    cv::convertScaleAbs(depth_float, depth_float, 255.0 / max);
    cv::convertScaleAbs(BW_image, BW_image, 1.0);

    //std::cout << "Depth_map es \n" << depth_float;

    

    double r_pose;
    
    
    r_pose = sqrt(x_pose*x_pose + y_pose*y_pose + z_pose*z_pose);
    std::cerr << "x_pose: " << x_pose << "\n";
    std::cerr << "y_pose: " << y_pose << "\n";
    std::cerr << "z_pose: " << z_pose << "\n";
    std::cerr << "r_pose: " << r_pose << "\n";

    cv::namedWindow("BW_Image_Antes", CV_WINDOW_AUTOSIZE);
    cv::imshow("BW_Image_Antes", BW_image);
    std::cout << "BW_Image_Antes es \n" << BW_image << "\n";

    cv::convertScaleAbs(BW_image, BW_image, 1.0);// necesario para que funcione el boundingRect
    
    cv::namedWindow("BW_Image_Despues", CV_WINDOW_AUTOSIZE);
    cv::imshow("BW_Image_Despues", BW_image);
    std::cout << "BW_Image_despues es \n" << BW_image << "\n";

    cv::Rect boundingBox;
    boundingBox = cv::boundingRect(BW_image);

    std::cout << "Bounding box es:  \n";
    std::cout << "height: "<< boundingBox.height << std::endl;
    std::cout << "width: " << boundingBox.width << std::endl;
    std::cout << "x: " << boundingBox.x << std::endl;
    std::cout << "y: " << boundingBox.y << std::endl;
    std::cout << "tl: " << boundingBox.tl() << std::endl;
    std::cout << "br: " << boundingBox.br() << std::endl;
    std::cout << "size: " << boundingBox.size() << std::endl;
    std::cout << "area: " << boundingBox.area() << std::endl;

    cv::namedWindow("window", CV_WINDOW_AUTOSIZE);
    cv::imshow("window", depth_float);

    
    cv::Mat bounding_map;
    cv::minMaxIdx(depth_float, &min, &max);        
    cv::convertScaleAbs(depth_float, depth_float, 255.0 / max);
    cv::cvtColor(depth_float, bounding_map, CV_GRAY2RGB);

    cv::rectangle(bounding_map, cv::Point(boundingBox.x,boundingBox.y), cv::Point((boundingBox.x + boundingBox.width -1),(boundingBox.y + boundingBox.height-1)), cv::Scalar(0, 255, 0),1,8,0);

    cv::namedWindow("recuadrado", CV_WINDOW_AUTOSIZE);
    cv::imshow("recuadrado", bounding_map);

    std::cout.rdbuf(coutbuf); //reset to standard output again

    cv::waitKey(0);


    return 0;
}