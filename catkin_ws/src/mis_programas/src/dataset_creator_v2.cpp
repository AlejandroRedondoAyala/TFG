#include <iostream>
#include <string>
#include <vector>
#include <boost/filesystem.hpp>
#include <ctime>
#include <cstdlib>
#include <fstream>

bool ordenar_nombres_string(const std::string& s1, const std::string& s2){
    return s1.size() < s2.size() || (s1.size() == s2.size() && s1 < s2); 

}


void random_set(unsigned int *n_train_total,unsigned int *n_test_total, std::string path_depth_maps, std::string path_labels_files, std::string path_train, std::string path_test, std::string path_train_TXT, std::string path_test_TXT, std::string path_info_TXT){
    std::vector<std::string> ficheros_dm;
    std::vector<std::string> ficheros_dm_names;
    std::vector<std::string> ficheros_label;
    std::vector<std::string> ficheros_random_dm;
    std::vector<std::string> ficheros_random_label;
    std::vector<std::string> ficheros_test_dm;
    std::vector<std::string> ficheros_test_label;
    std::fstream file_train;
    std::fstream file_test;
    std::fstream file_info;
    //std::vector <std::string> rutas_ficheros;

    for(const auto &narchivos : boost::filesystem::directory_iterator(path_depth_maps)){
        ficheros_dm.push_back(narchivos.path().c_str());
        ficheros_dm_names.push_back(narchivos.path().stem().c_str()); //Guardo solo los nombres para poder asociarlos a los ficheros de texto
    }

    std::sort(ficheros_dm.begin(),ficheros_dm.end(), ordenar_nombres_string);
    std::sort(ficheros_dm_names.begin(),ficheros_dm_names.end(), ordenar_nombres_string);
    

    
    int numero_ficheros = ficheros_dm.size();
    /*std::cout << "El numero de archivos es: " << ficheros_dm.size() << "\n";
    std::cout << "El 80% es: " << 0.8*numero_ficheros << "\n";
    std::cout << "El numero de nombres es: " << ficheros_dm_names.size() << "\n";*/
    
    std::srand(time(NULL));
    int n = rand() % (numero_ficheros-1) + 0;
    //std::cout << n << "\n";

    /*for (int i = 0; i < ficheros_dm.size(); i++){
        std::cout << ficheros_dm[i] << "\n";
    }*/
    /*for (int i = 0; i < ficheros_dm_names.size(); i++){
        std::cout << ficheros_dm_names[i] << "\n";
    }*/

    //std::cout << "\n";
    for (int i = 0; i < (0.8*(numero_ficheros)); i++){
        int p = rand() % (numero_ficheros-1) + 0;
        //std::cout << "La p es: "<< p << "\n"; 
        if(ficheros_random_dm.empty()){
            ficheros_random_dm.push_back(ficheros_dm[p]);
            ficheros_random_label.push_back((path_labels_files + "/" + ficheros_dm_names[p]+ ".txt"));
        }
        else{
            int check = 0;
            for(int j = 0; j < ficheros_random_dm.size(); j++){
                if (ficheros_random_dm[j]==ficheros_dm[p]){
                    check = 1;
                }
            }
            if(check == 0){
                ficheros_random_dm.push_back(ficheros_dm[p]);
                ficheros_random_label.push_back((path_labels_files + "/" + ficheros_dm_names[p]+ ".txt"));
            }
            else{
                --i;
            }

        }

    }
    std::sort(ficheros_random_dm.begin(),ficheros_random_dm.end(),ordenar_nombres_string);
    std::sort(ficheros_random_label.begin(),ficheros_random_label.end(),ordenar_nombres_string);
    
    /*for (int i = 0; i < ficheros_random_dm.size(); i++){
        std::cout << ficheros_random_dm[i] << "\n ";
    }*/

    /*for (int i = 0; i < ficheros_random_label.size(); i++){
        std::cout << ficheros_random_label[i] << "\n ";
    }*/

    for(int i = 0; i < ficheros_random_dm.size(); i++){
        
        boost::filesystem::copy_file(ficheros_random_dm[i],(path_train + "/" + std::to_string(*n_train_total) + ".png"), boost::filesystem::copy_option::overwrite_if_exists);
        boost::filesystem::copy_file(ficheros_random_label[i],(path_train + "/" + std::to_string(*n_train_total) + ".txt"), boost::filesystem::copy_option::overwrite_if_exists);
        file_train.open(path_train_TXT, std::fstream::out | std::fstream::app);
        file_train << "build/darknet/x64/data/obj/train/" << *n_train_total << ".png\n";
        file_train.close();
        *n_train_total = *n_train_total + 1;
    }


    for (int i = 0; i < ficheros_dm.size(); i++){
        int check = 0;
        for(int j = 0; j < ficheros_random_dm.size(); j++){
            if(ficheros_random_dm[j]==ficheros_dm[i]){
                check = 1;
            }
        }
        if(check == 0){
            ficheros_test_dm.push_back(ficheros_dm[i]);
            ficheros_test_label.push_back((path_labels_files + "/" + ficheros_dm_names[i]+ ".txt"));
        }

    }
    //std::cout << "Los ficheros que van a test son \n \n";
    /*for (int i = 0; i < ficheros_test_dm.size(); i++){
        std::cout << ficheros_test_dm[i] << "\n ";
    }*/

    for(int i = 0; i < ficheros_test_dm.size(); i++){
        
        boost::filesystem::copy_file(ficheros_test_dm[i],(path_test + "/" + std::to_string(*n_test_total) + ".png"), boost::filesystem::copy_option::overwrite_if_exists);
        boost::filesystem::copy_file(ficheros_test_label[i],(path_test + "/" + std::to_string(*n_test_total) + ".txt"), boost::filesystem::copy_option::overwrite_if_exists);
        file_test.open(path_test_TXT, std::fstream::out | std::fstream::app);
        file_test << "build/darknet/x64/data/obj/test/" << *n_test_total << ".png\n";
        file_test.close();
        file_info.open(path_info_TXT, std::fstream::out | std::fstream::app);
        file_info << "El fichero:  test/" << *n_test_total << ".png coresponde a:\n";
        file_info << ficheros_test_dm[i] << "\n\n";
        file_info.close();
        *n_test_total = *n_test_total + 1;
    }


    /*std::cout << "\n";
    std::cout << "El numero de archivos es: " << ficheros_dm.size() << "\n";
    std::cout << "El 80% es: " << 0.8*numero_ficheros << "\n";*/
    
}

int main(){
    unsigned int n_total_train = 0;
    unsigned int n_total_test = 0;
    std::string path_image_set = "/home/alejandro/catkin_ws/src/mis_programas/image_set";
    std::string path_train_txt = path_image_set + "/train.txt";
    std::string path_test_txt = path_image_set + "/test.txt";
    std::string path_train = path_image_set + "/train";
    std::string path_test = path_image_set + "/test";
    std::string path_info = path_image_set + "/info";

    std::string path_depth_map_1 = "/home/alejandro/catkin_ws/src/mis_programas/bagfiles/experimento1_64_real/depth_map";    
    std::string path_label_1 ="/home/alejandro/catkin_ws/src/mis_programas/bagfiles/experimento1_64_real/label";

    std::string path_depth_map_2 = "/home/alejandro/catkin_ws/src/mis_programas/bagfiles/experimento2_64_real/depth_map";    
    std::string path_label_2 ="/home/alejandro/catkin_ws/src/mis_programas/bagfiles/experimento2_64_real/label";

    std::string path_depth_map_3 = "/home/alejandro/catkin_ws/src/mis_programas/bagfiles/experimento3_64_real/depth_map";    
    std::string path_label_3 ="/home/alejandro/catkin_ws/src/mis_programas/bagfiles/experimento3_64_real/label";

    std::string path_depth_map_4 = "/home/alejandro/catkin_ws/src/mis_programas/bagfiles/experimento4_64_real/depth_map";    
    std::string path_label_4 ="/home/alejandro/catkin_ws/src/mis_programas/bagfiles/experimento4_64_real/label";

    std::string path_depth_map_5 = "/home/alejandro/catkin_ws/src/mis_programas/bagfiles/experimento5_64_real/depth_map";    
    std::string path_label_5 ="/home/alejandro/catkin_ws/src/mis_programas/bagfiles/experimento5_64_real/label";

    if(!(boost::filesystem::exists(path_image_set))){
        std::cerr << "AVISO: \n";
        std::cerr << "NO existe el directorio " << path_image_set << "\n";
        std::cerr << "Se va a crear. \n";
        if(boost::filesystem::create_directory(path_image_set)){
            std::cout << path_image_set << " creada correctamente \n";
        }
        else{
            std::cout << "ERROR: no se pudo crear " << path_image_set << std::endl;
            return -1;
        }        
    }
    if((boost::filesystem::exists(path_train_txt))){
        std::cerr << "ERROR: \n";
        std::cerr << "Ya existe el fichero " << path_train_txt << "\n";
        std::cerr << "Para evitar errores hay que borrarlo. \n";
        return -1;
    }
    if((boost::filesystem::exists(path_test_txt))){
        std::cerr << "ERROR: \n";
        std::cerr << "Ya existe el fichero " << path_test_txt << "\n";
        std::cerr << "Para evitar errores hay que borrarlo. \n";
        return -1;
    }

    if(!(boost::filesystem::exists(path_train))){
        std::cerr << "AVISO: \n";
        std::cerr << "NO existe el directorio " << path_train << "\n";
        std::cerr << "Se va a crear. \n";
        if(boost::filesystem::create_directory(path_train)){
            std::cout << path_train << " creada correctamente \n";
        }
        else{
            std::cout << "ERROR: no se pudo crear " << path_train << std::endl;
            return -1;
        }        
    }
    else{
        
        if(!(boost::filesystem::is_empty(path_train))){
            std::cerr << "Atención NO está vacío el directorio " << path_train <<"\n";
            std::cerr << "Para evitar sobreesritura accidental se detiene este programa \n";
            std::cerr << "Para vaciar el fichero en la carpeta de la que cuelga ejecutar este comando: \n";
            std::cerr << "rm -r train/*\n";
            return -1;
        }
    }

    if(!(boost::filesystem::exists(path_test))){
        std::cerr << "AVISO: \n";
        std::cerr << "NO existe el directorio " << path_test << "\n";
        std::cerr << "Se va a crear. \n";
        if(boost::filesystem::create_directory(path_test)){
            std::cout << path_train << " creada correctamente \n";
        }
        else{
            std::cout << "ERROR: no se pudo crear " << path_test << std::endl;
            return -1;
        }        
    }
    else{
        if(!(boost::filesystem::is_empty(path_test))){
            std::cerr << "Atención NO está vacío el directorio " << path_test <<"\n";
            std::cerr << "Para evitar sobreesritura accidental se detiene este programa \n";
            std::cerr << "Para vaciar el fichero en la carpeta de la que cuelga ejecutar este comando: \n";
            std::cerr << "rm -r test/*\n";
            return -1;
        }
    }

    if(!(boost::filesystem::exists(path_info))){
        std::cerr << "AVISO: \n";
        std::cerr << "NO existe el directorio " << path_info << "\n";
        std::cerr << "Se va a crear. \n";
        if(boost::filesystem::create_directory(path_info)){
            std::cout << path_info << " creada correctamente \n";
        }
        else{
            std::cout << "ERROR: no se pudo crear " << path_info << std::endl;
            return -1;
        }        
    }

    if(!(boost::filesystem::exists(path_depth_map_1))){
        std::cerr << "ERROR: \n";
        std::cerr << "NO existe el fichero " << path_depth_map_1 << "\n";
        std::cerr << "Revisar si se ha creado los ficheros correspondientes. \n";
        return -1;
    }
    if(!(boost::filesystem::exists(path_label_1))){
        std::cerr << "ERROR: \n";
        std::cerr << "NO existe el fichero " << path_label_1 << "\n";
        std::cerr << "Revisar si se ha creado los ficheros correspondientes. \n";
        return -1;
    }

    std::fstream file_info;

    file_info.open(path_info +"/experimento_1.txt",std::fstream::out | std::fstream::app);
    file_info << "Experimento 1\n";
    file_info << "Correspondencia ficheros test con los ficheros originales: \n\n";
    file_info.close();
    random_set(&n_total_train,&n_total_test, path_depth_map_1,path_label_1,path_train,path_test,path_train_txt,path_test_txt,(path_info +"/experimento_1.txt"));
    unsigned int train_1 = n_total_train;
    unsigned int test_1 = n_total_test;
    
    file_info.open(path_info +"/experimento_2.txt",std::fstream::out | std::fstream::app);
    file_info << "Experimento 2\n";
    file_info << "Correspondencia ficheros test con los ficheros originales: \n\n";
    file_info.close();
    random_set(&n_total_train,&n_total_test, path_depth_map_2,path_label_2,path_train,path_test,path_train_txt,path_test_txt,(path_info +"/experimento_2.txt"));
    unsigned int train_2 = n_total_train - train_1;
    unsigned int test_2 = n_total_test - test_1;

    file_info.open(path_info +"/experimento_3.txt",std::fstream::out | std::fstream::app);
    file_info << "Experimento 3\n";
    file_info << "Correspondencia ficheros test con los ficheros originales: \n\n";
    file_info.close();
    random_set(&n_total_train,&n_total_test, path_depth_map_3,path_label_3,path_train,path_test,path_train_txt,path_test_txt, (path_info +"/experimento_3.txt"));
    unsigned int train_3 = n_total_train - train_1 - train_2;
    unsigned int test_3 = n_total_test - test_1 - test_2;

    file_info.open(path_info +"/experimento_4.txt",std::fstream::out | std::fstream::app);
    file_info << "Experimento 4\n";
    file_info << "Correspondencia ficheros test con los ficheros originales: \n\n";
    file_info.close();
    random_set(&n_total_train,&n_total_test, path_depth_map_4,path_label_4,path_train,path_test,path_train_txt,path_test_txt, (path_info +"/experimento_4.txt"));
    unsigned int train_4 = n_total_train - train_1 - train_2 -train_3;
    unsigned int test_4 = n_total_test - test_1 - test_2 - test_3;

    file_info.open(path_info +"/experimento_5.txt",std::fstream::out | std::fstream::app);
    file_info << "Experimento 5\n";
    file_info << "Correspondencia ficheros test con los ficheros originales: \n\n";
    file_info.close();
    random_set(&n_total_train,&n_total_test, path_depth_map_5,path_label_5,path_train,path_test,path_train_txt,path_test_txt, (path_info +"/experimento_5.txt"));
    unsigned int train_5 = n_total_train - train_1 - train_2 - train_3 - train_4;
    unsigned int test_5 = n_total_test - test_1 - test_2 - test_3 - test_4;

    std::fstream file_resumen;
    file_resumen.open(path_image_set + "/RESUMEN.txt", std::fstream::out);
    file_resumen <<"Resumen creación DATA_SET. \n";
    file_resumen <<"Total imagenes: " << n_total_test + n_total_train << "\n";
    file_resumen <<"Total imagenes train: " << n_total_train << "\n";
    file_resumen <<"Total imagenes test: " << n_total_test << "\n \n";

    file_resumen << "EXPERIMENTO 1\n";
    file_resumen <<"Total imagenes 1: " << train_1 + test_1 << "\n";
    file_resumen <<"Total imagenes train 1: " << train_1 << "\n";
    file_resumen <<"Total imagenes test 1: " << test_1 << "\n \n";

    file_resumen << "EXPERIMENTO 2\n";
    file_resumen <<"Total imagenes 2: " << train_2 + test_2 << "\n";
    file_resumen <<"Total imagenes train 2: " << train_2 << "\n";
    file_resumen <<"Total imagenes test 2: " << test_2 << "\n \n";

    file_resumen << "EXPERIMENTO 3\n";
    file_resumen <<"Total imagenes 3: " << train_3 + test_3 << "\n";
    file_resumen <<"Total imagenes train 3: " << train_3 << "\n";
    file_resumen <<"Total imagenes test 3: " << test_3 << "\n \n";

    file_resumen << "EXPERIMENTO 4\n";
    file_resumen <<"Total imagenes 4: " << train_4 + test_4 << "\n";
    file_resumen <<"Total imagenes train 4: " << train_4 << "\n";
    file_resumen <<"Total imagenes test 4: " << test_4 << "\n \n";

    file_resumen << "EXPERIMENTO 5\n";
    file_resumen <<"Total imagenes 5: " << train_5 + test_5 << "\n";
    file_resumen <<"Total imagenes train 5: " << train_5 << "\n";
    file_resumen <<"Total imagenes test 5: " << test_5 << "\n \n";

    file_resumen.close();

    std::cout << "Ficheros procesados: " << n_total_train + n_total_test << "\n";
    std::cout << "Ficheros train: " << n_total_train << "\n";
    std::cout << "Ficheros test: " << n_total_test << "\n";

    return 0;
}