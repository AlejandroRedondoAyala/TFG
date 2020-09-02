#include <ros/ros.h>
#include <rosbag/bag.h>
#include <sensor_msgs/PointCloud2.h>
#include <time.h>
#include <iostream>
#include <nav_msgs/Odometry.h>
/*librerías para la sincronización de mensajes*/
#include <message_filters/subscriber.h>
#include <message_filters/synchronizer.h>
#include <message_filters/sync_policies/exact_time.h>
/*librerías para la sincronización de mensajes*/
#include <boost/filesystem.hpp>

rosbag::Bag bag;
double record_duration;

void bag_callback(const sensor_msgs::PointCloud2::ConstPtr &puntos, const nav_msgs::Odometry::ConstPtr &firefly1_odom, const nav_msgs::Odometry::ConstPtr &firefly2_odom ){
     if ((ros::Time::now() >= ros::Time(17.0))&&((ros::Time::now() <= (ros::Time(17.0) + ros::Duration(record_duration))))){
        bag.write("/firefly_1/firefly_1/os1_cloud_node/points",ros::Time::now(),puntos);
        bag.write("/firefly_1/odometry_sensor1/odometry",ros::Time::now(),firefly1_odom);
        bag.write("/firefly_2/odometry_sensor1/odometry",ros::Time::now(),firefly2_odom);
    }

    if((ros::Time::now() > ros::Time(17.0)+ ros::Duration(record_duration)+ ros::Duration(0.5))){
        ROS_INFO("Finalizando grabado rosbag");
        bag.close();
        ros::shutdown();
    }

}


int main(int argc, char **argv){
    ros::init(argc,argv,"my_rosbag_record");
    
    ros::V_string args;
    ros::removeROSArgs(argc,argv,args);
    std::string experimento;
    std::string laser;
    std::string escenario;
    if(args.size() == 5){

        experimento = args.at(1);
        laser = args.at(2);
        record_duration = std::stod(args.at(3));
        escenario = args.at(4);
        ROS_INFO_STREAM("Grabacion experimento: " << experimento << " planos verticales: " << laser <<"iniciada correctamente. Duracion (s)= " << record_duration);
    }
    else{
        ROS_ERROR("ERROR");
        return -1;
    }
    
    ros::NodeHandle nh;
    while(ros::Time::now() < ros::Time(16.0)){  //Espera a que se lance la simulación de Gazebo

    }
    
    /*objetos necesarios para la sincronización*/
    message_filters::Subscriber<sensor_msgs::PointCloud2> pointCloud_sub (nh,"/firefly_1/firefly_1/os1_cloud_node/points",1);
    message_filters::Subscriber<nav_msgs::Odometry> firefly1_Odom_sub (nh,"/firefly_1/odometry_sensor1/odometry",1);
    message_filters::Subscriber<nav_msgs::Odometry> firefly2_Odom_sub (nh,"/firefly_2/odometry_sensor1/odometry",1);
    /*objetos necesarios para la sincronización*/
    /*Se crea un tipo con la politica de sincronización que se desea, en este caso ExactTime*/
    typedef message_filters::sync_policies::ExactTime<sensor_msgs::PointCloud2, nav_msgs::Odometry, nav_msgs::Odometry> MySync;
    /*Se crea un tipo con la politica de sincronización que se desea, en este caso ExactTime*/

    message_filters::Synchronizer<MySync> sinc(MySync(10),pointCloud_sub,firefly1_Odom_sub, firefly2_Odom_sub);

    sinc.registerCallback(boost::bind(&bag_callback, _1, _2, _3));
    std::string directorio_bagfiles = "/home/alejandro/catkin_ws/src/mis_programas/bagfiles/" + experimento +"_" + laser +"_" + escenario;
    
    if(!(boost::filesystem::exists(directorio_bagfiles))){
        ROS_WARN_STREAM (" No existe el directorio " << directorio_bagfiles << " se va a crear");
        if(boost::filesystem::create_directory(directorio_bagfiles)){
            ROS_INFO_STREAM(directorio_bagfiles << " creada correctamente");
        }
        else{
            ROS_ERROR_STREAM("ERROR: no se pudo crear " << directorio_bagfiles);
            return -1;
        }
    }
    if((boost::filesystem::exists(directorio_bagfiles + "/point_clouds")))
    {
        ROS_WARN_STREAM ("El directorio " << directorio_bagfiles << "/point_clouds ya existe. \n");
        std::cout << "Para hacer una nueva grabación es necesario eliminar el directorio point_cloud y sus ficheros\n";
        std::cout << "Se van a eliminar dichos ficheros. \n\n";
        boost::filesystem::remove_all(directorio_bagfiles + "/point_clouds");
    }
    directorio_bagfiles += "/"+ experimento +"_" + laser + "_" + escenario + ".bag";

    bag.open(directorio_bagfiles, rosbag::bagmode::Write );
    ROS_INFO("Iniciando grabado rosbag");
    ros::spin();
    return 0;

}