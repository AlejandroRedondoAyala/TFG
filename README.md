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
rosrun pcl_ros bag_to_pcd experimento5_64_real.bag /firefly_1/firefly_1/os1
_cloud_node/points /home/alejandro/catkin_ws/src/mis_programas/bagfiles/experimento5_64_real/point_clouds
```
Con lo que dentro del directoripo `experimento5_64_real` se creará una carpeta llamada `point_cloud` que contiene los ficheros .pcd, que los vamos a emplear para generar los depth_maps.

#### 3. Generar los depth_map
En un terminal arrancar (si no está ya activo) el ROS_MASTER con el comando `roscore`.\
En un terminal ejecutar el siguiente comando:
```
rosrun mis_programas pclToDepthMap_V2 experimento5_64_real
```
Es muy importante pasar un SOLO argumento correctamente, este indica el experimento, los planos verticales del láser y el escenario en el que se hizo la simulación.\
Tras esto se creará la carpeta `depth_map` dentro de `mis_programas/bagfiles/experimento5_64_real`. que contiene los depth_map de la simulación real.

#### 4. Grabar las simulaciones con el mundo vacio
Necesarias para el etiquetado de las imágenes. Para ello hacer lo mismo que en el paso 1 cambiando real por vacio:
```
roslauch mis_programas experimento5.launch world_name:=vacio laser:=64 grabar:=true
```
Es muy importante que las velocidades de los drones en ambas grabaciones (escenario real y vacio) sean las mismas, ya que, si no no serían comparables y el etiquetado no funcionaria.




