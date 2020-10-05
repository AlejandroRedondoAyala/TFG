#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <boost/filesystem.hpp>
#include <string>
#include <boost/sort/spreadsort/string_sort.hpp>
#include <fstream>

/*ordenar_string_names solo es válido en este caso que los números no continenen 0s delante, si tuvieran 0s no vale*/
bool ordenar_string_names (const std::string& s1, const std::string& s2) {
    return s1.size() < s2.size() || (s1.size() == s2.size() && s1 < s2);
    }

int main (){

   
    std::vector<std::string> ficheros_dm;
    std::vector<std::string> ficheros_random_dm;
    std::vector<std::string> ficheros_test_dm;
    std::string path_depth_map_1 = "/home/alejandro/catkin_ws/src/mis_programas/bagfiles/experimento1_64_real/depth_map";
    std::string path_train_1 = "/home/alejandro/catkin_ws/src/mis_programas/image_set_pruebas/train";
    std::string path_test_1 = "/home/alejandro/catkin_ws/src/mis_programas/image_set_pruebas/test";
    
    std::vector <std::string> rutas_ficheros_1;

    for(const auto &narchivos : boost::filesystem::directory_iterator(path_depth_map_1)){
        ficheros_dm.push_back(narchivos.path().c_str());
    }

    std::sort(ficheros_dm.begin(),ficheros_dm.end(), ordenar_string_names);
    /*std::sort(ficheros_dm.begin(),ficheros_dm.end(), [] (const std::string& s1, const std::string& s2) {
    return s1.size() < s2.size() || (s1.size() == s2.size() && s1 < s2);
    });*/

    //boost::sort::spreadsort::string_sort(ficheros_dm.begin(), ficheros_dm.end());
    int numero_ficheros = ficheros_dm.size();
    std::cout << "El numero de archivos es: " << ficheros_dm.size() << "\n";
    std::cout << "El 80% es: " << 0.8*numero_ficheros << "\n";
    
    std::srand(time(NULL));
    int n = rand() % (numero_ficheros-1) + 0;
    std::cout << n << "\n";
    for (int i = 0; i < ficheros_dm.size(); i++){
        std::cout << ficheros_dm[i] << "\n";
    }
    std::cout << "\n";
    for (int i = 0; i < (0.8*(numero_ficheros)); i++){
        int p = rand() % (numero_ficheros-1) + 0;
        std::cout << "La p es: "<< p << "\n"; 
        if(ficheros_random_dm.empty()){
            ficheros_random_dm.push_back(ficheros_dm[p]);
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
            }
            else{
                --i;
            }

        }

    }
    std::sort(ficheros_random_dm.begin(),ficheros_random_dm.end(),ordenar_string_names);
    
    for (int i = 0; i < ficheros_random_dm.size(); i++){
        std::cout << ficheros_random_dm[i] << "\n ";
    }

    for(int i = 0; i < ficheros_random_dm.size(); i++){
        
        boost::filesystem::copy_file(ficheros_random_dm[i],(path_train_1 + "/" + std::to_string(i) + ".png"), boost::filesystem::copy_option::overwrite_if_exists);
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
        }

    }
    std::cout << "Los ficheros que van a test son \n \n";
    for (int i = 0; i < ficheros_test_dm.size(); i++){
        std::cout << ficheros_test_dm[i] << "\n ";
    }

     for(int i = 0; i < ficheros_test_dm.size(); i++){
        
        boost::filesystem::copy_file(ficheros_test_dm[i],(path_test_1 + "/" + std::to_string(i) + ".png"), boost::filesystem::copy_option::overwrite_if_exists);
    }


    std::cout << "\n";
    std::cout << "El numero de archivos es: " << ficheros_dm.size() << "\n";
    std::cout << "El 80% es: " << 0.8*numero_ficheros << "\n";
    int a = 001;
    std::cout << a << "\n";

    std::fstream file;
    file.open("/home/alejandro/catkin_ws/src/mis_programas/image_set_pruebas/prueba.txt", std::fstream::out);
    file << "Esto es una prueba de escritura\n";
    file.close();
    file.open("/home/alejandro/catkin_ws/src/mis_programas/image_set_pruebas/prueba.txt", std::fstream::out | std::fstream::app);
    file << "¿Se sobreescribira el texto anterior?\n";
    file.close();
    file.open("/home/alejandro/catkin_ws/src/mis_programas/image_set_pruebas/prueba.txt", std::fstream::out | std::fstream::app);
    file << "Es necesario añadir std::fstream::app para evitar que se sobreescriba el contenido ya existente\n";
    file.close();
    

    return 0;
}