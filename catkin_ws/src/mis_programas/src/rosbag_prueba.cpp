#include <ros/ros.h>
#include <rosbag/bag.h>
#include <sensor_msgs/PointCloud2.h>
#include <time.h>
#include <rosgraph_msgs/Clock.h>
#include <iostream>
#include <nav_msgs/Odometry.h>
/*librerías para la sincronización de mensajes*/
#include <message_filters/subscriber.h>
#include <message_filters/synchronizer.h>
#include <message_filters/sync_policies/exact_time.h>
/*librerías para la sincronización de mensajes*/


rosbag::Bag bag;

void bag_callback(const sensor_msgs::PointCloud2::ConstPtr &puntos, const nav_msgs::Odometry::ConstPtr &firefly1_odom, const nav_msgs::Odometry::ConstPtr &firefly2_odom ){
     if ((ros::Time::now() >= ros::Time(16.0))&&((ros::Time::now() <= (ros::Time(16.0) + ros::Duration(14.0))))){
        std::cout << ros::Time::now() << "\n";
        bag.write("/firefly_1/firefly_1/os1_cloud_node/points",ros::Time::now(),puntos);
        bag.write("/firefly_1/odometry_sensor1/odometry",ros::Time::now(),firefly1_odom);
        bag.write("/firefly_2/odometry_sensor1/odometry",ros::Time::now(),firefly2_odom);
    }
    /*if ((ros::Time::now() > ros::Time(30.0))){
        ROS_INFO("Finalizando grabado rosbag");
        bag.close();
    }*/

    if((ros::Time::now() > ros::Time(31.0))){
        ROS_INFO("Finalizando grabado rosbag");
        bag.close();
        ros::shutdown();
    }

}




/*void time_callback(const sensor_msgs::PointCloud2::ConstPtr &puntos){
    //sensor_msgs::PointCloud2 puntos;
    //rosgraph_msgs::Clock tiempo_msgs;
    //tiempo_msgs = *tiempo;
    //std::cout << "Mensaje de /clock: \n";
    //std::cout << tiempo_msgs.clock << '\n';
    std::cout << "mensaje de ros::Time: \n";
    std::cout << ros::Time::now() << "\n";
    

    if ((ros::Time::now() == ros::Time(15.5))){

        ROS_INFO("Iniciando grabado rosbag");
    }


    if ((ros::Time::now() >= ros::Time(16.0))&&((ros::Time::now() <= ros::Time(30.0)))){
        std::cout << ros::Time::now() << "\n";
        bag.write("/firefly_1/firefly_1/os1_cloud_node/points",ros::Time::now(),puntos);
    }
    /*if ((ros::Time::now() > ros::Time(30.0))){
        ROS_INFO("Finalizando grabado rosbag");
        bag.close();
    }*/
/*
    if((ros::Time::now() > ros::Time(31.0))){
        ROS_INFO("Finalizando grabado rosbag");
        bag.close();
        ros::shutdown();
    }
    

    

}*/

int main(int argc, char **argv){
    ros::init(argc,argv,"prueba_rosbag");
    ros::NodeHandle nh;
    while(ros::Time::now() < ros::Time(15.0)){

    }
    
    
    //ros::Subscriber sub_time = nh.subscribe("firefly_1/firefly_1/os1_cloud_node/points",1000000,time_callback);

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


    bag.open("/home/alejandro/catkin_ws/src/mis_programas/bagfiles/prueba_C.bag", rosbag::bagmode::Write );
    ROS_INFO("Iniciando grabado rosbag");
    
    //bag.write("firefly_1/firefly_1/os1_cloud_node/points",ros::Time::now());
    ros::spin();
    return 0;

}


