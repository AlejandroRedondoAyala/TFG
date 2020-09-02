#include <rosbag/bag.h>
#include <rosbag/view.h>
#include <sensor_msgs/PointCloud2.h>
#include <boost/filesystem.hpp>
#include <vector>
#include <fstream> //Libreria necesaria para trabajar con ficheros
#include <iostream> //Librería también necesaria para trabajar con ficheros

int main (int argc, char ** argv){
    rosbag::Bag bag;
    rosbag::View view;
    rosbag::View::iterator view_it;
    std::string pathFichero = "/home/alejandro/catkin_ws/src/mis_programas/bagfiles/experimento5_64_vacio/ficheros/";

    std::vector<std::string> nombre_mensajes_real;//Aquí guardo el nombre de los ficheros que se tendrian que haber generado
    std::vector<std::string> nombre_ficheros_pcd; //Aquí guardo el nombre de los ficheros pcd que se han generado para poder compararlos

    std::string directorio_pcd = "/home/alejandro/catkin_ws/src/mis_programas/bagfiles/experimento5_64_vacio/point_clouds";
    for (const auto &entry : boost::filesystem::directory_iterator(directorio_pcd)){
        std::cout << entry.path().stem().c_str() << std::endl;
        std::cout << entry.path().extension() << std::endl;
        nombre_ficheros_pcd.push_back(entry.path().stem().c_str()); //Me guardo solo el nombre sin la extensión en un vector
    }
    std::sort(nombre_ficheros_pcd.begin(), nombre_ficheros_pcd.end()); //Necesario ordenar ya que directory_iterator lee de forma aleatoria
    
    std::fstream file;
    file.open("hola.txt", std::fstream::out);
    //file.open("hola.txt");
    if(!file){
        std::cerr << "ERROR abriendo fichero \n";
        return -1;
    }
    file << "Hola";
    file.close();

    
    
    try{
        bag.open("/home/alejandro/catkin_ws/src/mis_programas/bagfiles/experimento5_64_vacio/experimento5_64_vacio.bag",rosbag::BagMode::Read);
    }
    catch (const rosbag::BagException&)
    {
        std::cerr << "Error opening file " << argv[1] << std::endl;
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
        std::cerr << cloud_t.header.stamp <<std::endl;
        nombre_mensajes_real.push_back(ss.str());
        std::cerr << "aaaaaa "<< ss.str() <<std::endl;
        ++view_it;
    }

    
    unsigned int j = 0; 
    for(unsigned int i = 0; i < nombre_mensajes_real.size(); i++){
        std::fstream file;
        file.open((pathFichero + std::to_string(i) +".txt"),std::fstream::out);

        if(nombre_mensajes_real[i] == nombre_ficheros_pcd[j]){
            file << "Son iguales \n";
            file << "Timestamp del mensaje " << nombre_mensajes_real[i] << "\n";
            file << "Timestamp de los pcd " << nombre_ficheros_pcd[j] << "\n";
            file.close();
            ++j;

        }
        else{
            
            
        }

        std::cout << pathFichero + std::to_string(i) +".txt" << "\n";
        
    }



    return 0;
}