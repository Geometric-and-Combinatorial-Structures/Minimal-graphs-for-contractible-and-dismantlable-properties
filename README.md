# Minimal graphs for contractible and dismantlable properties
Repository for the article arXiv:2109.06729 [math.CO].

Tomamos las graficas del banco


https://users.cecs.anu.edu.au/~bdm/data/graphs.html

graph2c.g6
graph3c.g6
...
graph10c.g6
graph11.g6


Separate.cpp

generará
la carpeta cg
que contiene   capteras
1v
2v
...
11v

con archivos  de la forma 
    nvme._g6          (en separate.cpp dice en que consiste _g6)


Para 11 vertices hay archivos con menos de un millon de graficas,
y en el caso de los archivos con mas de un millon, se partcicional en archivos de a lo mas un millon
y quedan dentro de una carpeta
(para no saturar la vista)

Separate puede tardar de una a dos horas dependiendo del equipo.


Filtra las graficas con homologia trivial (aciclicas)


th.cpp      (trivial homology)
Genera el conjunto de graficas con homologia trivial
requiere de un archivo con nombre flag.dat
cuyo contenido debe ser     
       0
indica que no está creada la estructura de directorio con la misma forma de cg
la primer a que se ejecuta th
se crea esta estructura y en flag.dat se almacena un 1
(indeica que la esstructura ya está creada y que no intente crearla de nuevo)

genera archivos      nvme._g6
sabemos que son graficas vde homologya trivial, pues están en el direcdtorio
ag

th tiene opciones de ejecucion
sugerimos ejecutar
th 1
th 2
...
th 10   genera todas las graficas de v vertices con el  numero aristas posibles (v-1,...., v(v-1)/2 )

th 11 10
th 11 11
...
th 11 16
th 11 17 1         big files
th 11 17 2  
th 11 18 1


th tiene opcion de elegir ejecutar para linux y para windows




AHora hay que filtrar de las graficas anteriores

sabemos que para 11 vertices
ag    y las SIC conciden

filtraemos aquellas NO SICv

(salen 12)
