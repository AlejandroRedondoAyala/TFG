#include "ros/ros.h"
#include "Eigen/Core"
#include "ros/ros.h"
#include "Eigen/Core"
#include "mav_msgs/conversions.h"
#include "mav_msgs/default_topics.h"
#include "trajectory_msgs/MultiDOFJointTrajectory.h"

#include "nav_msgs/Odometry.h"
#include "eigen_conversions/eigen_msg.h"

#include <iostream>

double max_vel = 0.25;
double max_yawrate = 0.349; //en radianes 20º

ros::Publisher trajectory_pub;


void odom_callback(const nav_msgs::Odometry::ConstPtr & msg){
    //FUNCION
    nav_msgs::Odometry odom_msg;
    odom_msg = *msg;
    bool init_pose_set = false;
    static ros::Time prev_time ;
    static Eigen::Vector3d init_position;
    static double init_yaw;
    

    //std::cout << "Antes del if: " << init_pose_set << '\n';
    if(init_pose_set == false){
        Eigen::Affine3d eigen_affine;
        tf::poseMsgToEigen(odom_msg.pose.pose, eigen_affine);

        init_position = eigen_affine.matrix().topRightCorner<3,1>();
       //init_yaw = eigen_affine.matrix().topLeftCorner<3,3>().eulerAngles(0,1,2)(2);
        Eigen::Matrix3d dcm = eigen_affine.matrix().topRightCorner<3, 3>();
        double phi = asin(dcm(2,1));
        double cosphi = cos(phi);
        double the = atan2(-dcm(2,0) /cosphi, dcm(2,2) / cosphi);
        double psi = atan2(-dcm(0,1)/cosphi, dcm(1,1) / cosphi);
        init_yaw = psi;

        init_pose_set = true;       

    }

    //std::cout << "Despues del if: " << init_pose_set << '\n';

    double dt = (ros::Time::now()-prev_time).toSec();
    //std::cout <<std::setprecision(20)<< dt << " seconds"<<'\n';
    //std::cout << "--------------------\n";
    //std::cout << "prev_ time de antes "<<'\n' << prev_time << '\n';
    prev_time = ros::Time::now();
    //std::cout << "prev_time de después " << prev_time << '\n';
    //std::cout << prev_time << '\n';

    Eigen::Vector3d desired_position (0.0 , 0.0, max_vel*10*dt); //Poner max_vel*10*dt, en el eje en el que se quiera controlar linealmente la velocidad
    //std::cout << desired_position << '\n';
    init_position += desired_position;
    double yaw = 0.0;
    //init_yaw = init_yaw + max_yawrate*yaw*dt;
    init_yaw = 0.0;
    //std::cout << "Lo que envío" << '\n';
    //std::cout << init_position << '\n'; 
    //std::cout << init_yaw << '\n';

    static trajectory_msgs::MultiDOFJointTrajectory trajectory_msg;
    trajectory_msg.header.stamp = ros::Time::now();
    trajectory_msg.header.seq++;
    //std::cout << "Antes:" << '\n';
    //std::cout << trajectory_msg << '\n';

    mav_msgs::msgMultiDofJointTrajectoryFromPositionYaw(init_position, init_yaw, &trajectory_msg);
    trajectory_msg.points[0].time_from_start = ros::Duration(1.0);
    
    //Las siguientes tres líneas de código son para asegurar que solo se mueve en un eje (si es eso lo que queremos)
    // ya que en desplazamientos largos puede variar ligeramente la posición en los otros ejes al que nos estemos moviendo
    //especialmente si nos movemos en el eje Z

    trajectory_msg.points[0].transforms[0].translation.x = 15.0; 
    trajectory_msg.points[0].transforms[0].translation.y = 0.0;
    //trajectory_msg.points[0].transforms[0].translation.z = 1.0; //Conveniente si se va a mover mucho en X o en Y para que no suba mucho, comentar esta línea si se desea mover el dron en Z

    //std::cout << "la final es:" << '\n';
    //std::cout << trajectory_msg << '\n';
    if( ((odom_msg.pose.pose.position.z > 10.0) && (max_vel > 0.0)) ||(((odom_msg.pose.pose.position.z < 2.0) && (max_vel < 0.0))) ){
        max_vel = -max_vel;
    }

    trajectory_pub.publish(trajectory_msg);
    ros::Rate(10).sleep();

    
}

int main (int argc, char** argv){
    ros::init(argc, argv , "control_velocidad");
    ros::NodeHandle n;

    trajectory_pub = n.advertise<trajectory_msgs::MultiDOFJointTrajectory>(mav_msgs::default_topics::COMMAND_TRAJECTORY, 10);

    ROS_INFO("Iniciado Experimento 4.");
    ros::V_string args;
    ros::removeROSArgs(argc,argv,args);

    double delay;

    if(args.size() == 2){
        max_vel = std::stof(args.at(1));
        ROS_INFO("Iniciado correctamente. Velocidad seleccionada V(m/s)= %f : ", max_vel);
    }
    else if(args.size() == 1){
        ROS_WARN("No se ha indicado velocidad. Se va a usar la velocidad por defecto V(m/s)= %f", max_vel);
    }
    else{
        ROS_ERROR("Uso: rosrun mis_programas experimento4 <velocidad>");
        return -1;
    }

    ros::Duration(15.0).sleep();
    ROS_INFO("Iniciando experimento en dron: %s : velocidad seleccionada: %f m/s", n.getNamespace().c_str(),max_vel);


    ros::Subscriber odom_sub = n.subscribe("odometry_sensor1/odometry", 10, odom_callback);

    ros::spin();

    return 0;
}
