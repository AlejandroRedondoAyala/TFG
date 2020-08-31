# TFG
### Uso
#### 1. Crear ficheros rosbag de los experimentos.
En un terminal ejecutar:
```
roslauch mis_programas experimento.launch world_name:=real laser:=64 grabar:=true
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

#### 2. Generar los ficheros .pcd necesarios para generar los depth_maps

En el terminal donde se guarden los rosbag cuya ruta deberia ser 
```
/home/.../catkin_ws/src/mis_programas/bagfiles/experimento5_64_real
```
Èjecutar el siguiente comando:
```
