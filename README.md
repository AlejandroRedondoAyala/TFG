# TFG
### Uso
#### 1. Crear ficheros rosbag de los experimentos con escenario real.
En un terminal ejecutar:
```
roslauch mis_programas experimento5.launch world_name:=real laser:=64 grabar:=true
```

Los parámetros que necesita son tres:

* **world_name**\
El valor por defecto es vacio.\
Hay dos opciones:
  - world_name:=**real**: Se muestra el escenario completo con coches y edificios.
  - world_name:=**vacio**: Solo los drones, se usa para etiquetar las imágenes antes de entrenar el modelo.
  
* **laser**
Indica el número de planos verticales del LIDAR.\
Puede ser 32 o 64.\
Valor por defecto: 64

* **grabar**
Indica si se debe grabar un rosbag o simplemente visualizar el experimento.\
Puede ser: **true** o **false**.\
Valor por defecto: false.

Tras esto en la carpeta `bafiles` del paquete `mis_programas` se creará una carpeta con el nombre experimento5_64_real o el que corresponda.

#### 2. Generar los ficheros .pcd necesarios para generar los depth_maps
En un terminal arrancar el ROS_MASTER con el comando `roscore`.\
En el terminal donde se guarden los rosbag cuya ruta deberia ser 
```
/home/.../catkin_ws/src/mis_programas/bagfiles/experimento5_64_real
```
Ejecutar el siguiente comando:
```
rosrun pcl_ros bag_to_pcd experimento5_64_real.bag /firefly_1/firefly_1/os1_cloud_node/points /home/alejandro/catkin_ws/src/mis_programas/bagfiles/experimento5_64_real/point_clouds
```
Hay que indicarle al comando **el fichero .bag**, el **topic** de la nube de puntos, que es siempre el mismo, y por último el directorio donde se va a guardar los .pcd.\
Por tanto sólo hay que cambiar de ese comando el nombre del fichero .bag y en la ruta del directorio point_cloud, cambiaremos `experimento5_64_real` por el experimento que corresponda.\
Con lo que dentro del directorio `experimento5_64_real` se creará una carpeta llamada `point_cloud` que contiene los ficheros .pcd, que los vamos a emplear para generar los depth_maps.

#### 3. Generar los depth_map
En un terminal arrancar (si no está ya activo) el ROS_MASTER con el comando `roscore`.\
En un terminal ejecutar el siguiente comando:
```
rosrun mis_programas pclToDepthMap_V2 experimento5_64_real
```
Es muy importante pasar un SOLO argumento correctamente, este indica el experimento, los planos verticales del láser y el escenario en el que se hizo la simulación.\
Tras esto se creará la carpeta `depth_map` dentro de `mis_programas/bagfiles/experimento5_64_real`. que contiene los depth_map de la simulación real.

#### 4. Grabar las simulaciones con el mundo vacío.
Necesarias para el etiquetado de las imágenes. Para ello hacer lo mismo que en el paso 1 cambiando real por vacio:
```
roslauch mis_programas experimento5.launch world_name:=vacio laser:=64 grabar:=true
```
Es muy importante que las velocidades de los drones en ambas grabaciones (escenario real y vacio) sean las mismas, ya que, si no no serían comparables y el etiquetado no funcionaria.

#### 5. Generar los ficheros .pcd del experimento vacío.
Al igual que en el paso 2, en un terminal arrancar el ROS_MASTER con el comando `roscore`.\
En el terminal donde se guarden los rosbag cuya ruta deberia ser 
```
/home/.../catkin_ws/src/mis_programas/bagfiles/experimento5_64_vacio
```
Ejecutar el siguiente comando:
```
rosrun pcl_ros bag_to_pcd experimento5_64_vacio.bag /firefly_1/firefly_1/os1_cloud_node/points /home/alejandro/catkin_ws/src/mis_programas/bagfiles/experimento5_64_vacio/point_clouds
```
Hay que indicarle al comando **el fichero .bag**, el **topic** de la nube de puntos, que es siempre el mismo, y por último el directorio donde se va a guardar los .pcd.\
Por tanto sólo hay que cambiar de ese comando el nombre del fichero .bag y en la ruta del directorio point_cloud, cambiaremos `experimento5_64_vacio` por el experimento que corresponda.\
Con lo que dentro del directorio `experimento5_64_vacio` se creará una carpeta llamada `point_cloud` que contiene los ficheros .pcd, que los vamos a emplear para generar las imágenes necesarias para el etiquetado.

#### 6. Etiquetado.
En un terminal arrancar (si no está ya activo) el ROS_MASTER con el comando `roscore`.\
En un terminal ejecutar el siguiente comando:
```
rosrun mis_programas my_image_labeller experimento5_64
```
El argumento solo hay que indicar el número de experimento y los planos verticales del láser.\
Por tanto, sólo habrá que cambiar `experimento5_64` por el que corresponda.\
Este comando genera en la carpeta `/mis_programas/bagfiles/experimento5_64_real/bounding_map` las imágenes con los boundingBox.\






