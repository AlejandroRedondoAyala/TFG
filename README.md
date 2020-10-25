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
Para el correcto funcionamiento es necesario indicar que se va a usar el mundo real.  

  - world_name:=**real**: Se muestra el escenario completo con coches y edificios.
  
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

#### 3. Generar los depth_map y etiquetado
En un terminal arrancar (si no está ya activo) el ROS_MASTER con el comando `roscore`.\
En un terminal ejecutar el siguiente comando:
```
rosrun mis_programas labeller_paralelepipedo_v4 experimento1_64
```
Es muy importante pasar un SOLO argumento correctamente, este indica el experimento, los planos verticales del láser.  
Tras esto se cren 5 carpetas dentro de `mis_programas/bagfiles/experimento5_64_real`.  

* **depth_map**: En esta carpeta se guardan las imágenes .png correspondientes a los mapas de profundidad.
* **BW_map**: En esta carpeta se guardan las imágenes en blanco y negro que se mandan a la función bounding_rect.  
**NOTA**: no es necesario generar estas imágenes para el correcto etiquetado, ya que internamente el programa trabaja con objetos cv::Mat. El hecho de sacar las imágenes es meramente ilustrativo y puede deshabilitarse sin problema en `labeller_paralelepipedo_v4.cpp`.  
* **bounding_map**: En esta carpeta se guardan los depth_map en los que se ha dibujado el bounding_box generado por bounding_rect(). Nuevamente estas imágenes se generan simplemente de forma ilustrativa y para comprobar si el etiquetado se hace bien. No es necesario guardar estas imágenes para el entrenamiento, y puede desactivarse su generación en el fichero `labeller_paralelepipedo_v4.cpp`.  
* **label**: En esta carpeta se guardan los ficheros .txt que son necesarios para el entrenamiento del modelo.  
* **odom_information**: En esta carpeta se almacena para cada depth_map generado un fichero de texto con la información de los datos de odometría de los drones en la imagen. De esta forma después puedo comprobar cual era la posición real de los drones.
* **all_depth_maps**: En esta carpeta se almacenan todos los depth_map generados, tengan o no tengan dron, para poder pasarselo al modelo entrenado a modo de pruebas después de haber hecho todo el proceso de validación y test. OJO, aquí no se generan etiquetas.
* **extra_information**: En esta carpeta se generan dos ficheros, un .csv para poder pasar los datos de odometría a un formato que es sencillo de abrir en Excel, y otro fichero con las rutas absolutas de las imágenes de `all_depht_maps` para poder comprobar el funcionamiento del modelo entrenado en nuevas condiciones.

Este paso lo hace el fichero `labeller_paralelepipedo_v4.cpp` que está ubicado en la ruta 
`/catkin_ws/src/mis_programas/src`.\
En la nueva versión (V2) de labeller_paralelepipedo,SÓLO se guardan y etiquetan aquellos depth_map que contengan dron, el resto no se guardan, esto es así para facilitar el etiquetado.
En la nueva versión (v3) de labeller_paralelepipedo, se añade la generación de ficheros con información de odometría de los drones.
En la nueva versión (v4) de labeller_paralelepipedo, se añade la generación de ficheros con información de odometría de los drones en formato csv para poder sacar fácilmente gráficas en Excel. También se añade la generación de todos los depth_maps tengan o no tengan dron, eso sí estan sin etiquetar, ya que, no deben usarse no para validación ni para test. Por último se añade la creación de un fochero que facilite, pasar al modelo entrenado en YOLO todas las imágenes para obtener los resultados tras pasar por el modelo entrenado.


#### 4. Generar el data set para entrenar
Esto lo hace el fichero `dataset_creator_v3.cpp`, lo que se hace es generar en la carpeta `/catkin_ws/src/mis_programas` un directorio llamado `image_set`.\
En el cual a su vez se generaran cuatro directorios `train`, `vlid`, `test` e `info` y cuatro ficheros, `train.txt`, `valid.txt`, `test.txt` y `RESUMEN.txt`. Los tres primeros ficheros incluyen las direcciones relativas de las imágenes (de train, valid y test), respecto al ejecutable `darknet` de YOLO. el cuarto fichero contiene un resumen con el número de imágenes que se han guardado para train, valid y test\
Dentro de los directorios creados se guardarán las imágenes junto con sus etiquetas correspondientes. Para la carpeta `train`, se seleccionan de forma aleatoria el 70% de imágenes de cada experimento, para `valid` el 20% y el 10% restante va a `test`.
En el directorio `info_test` e `info_valid` se almacena información sobre la correspondencia de las imágenes de test y valid, con los depth maps de los distintos experimentos. Así se puede saber la posición y velocidad de ambos drones en las imágenes de test, y poder sacar conclusiones del trabajo.\
Para usarlo tras arrancar roscore ejecutar el siguiente comando:
```
rosrun mis_programas dataset_creator
```




