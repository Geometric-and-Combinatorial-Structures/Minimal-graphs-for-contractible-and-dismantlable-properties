# Minimal graphs for contractible and dismantlable properties
In this repository we show how to implement the algorithms used in the article *Minimal graphs for contractible and dismantlable properties*
 ([arXiv:2109.06729 [math.CO]](https://arxiv.org/abs/2109.06729)).

This work considers simple connected graphs on up to 11 vertices.

## Connected graphs
The connected graphs were taken from the well-known repository of Professor Brendan McKay (available online at [Graphs](https://users.cecs.anu.edu.au/~bdm/data/graphs.html)). There the graphs are organized into files according to the number of vertices: `graph2c.g6`, `graph3c.g6`, ... , `graph10c.g6`, `graph11.g6`. The last two files need to be unzipped due to their size.

**Remark**: The file `graph11.g6` contains connected and disconnected graphs, the other ones consist only of connected graphs.

For more details about the g6 format (among other aspects) consult: [graph formats](https://users.cecs.anu.edu.au/~bdm/data/formats.html).

## Setup files 
To facilitate the work we have further divided the files according to how many edges the graphs have. For files with graphs of 11 vertices with more than one million graphs, we have created a folder that contains several files of at most one million graphs. The first of these files are
`11v17e-001` and `11v17e-002`.

Additionally, we have introduced a slight variant to the g6 format. This consists of ignoring the data that indicates the number of vertices, called N(n) by McKay. We have called this format \_g6. The number of vertices is known based on which file the graph comes from.

Compiling and running the program [split.cpp](split.cpp), the file structure contained in the `cg` folder will be generated containing the graphs in \_g6 format, as well as the files `#cgV.dat` and `#cgVE.dat` containing cardinalities.

**Note**: In the code one should indicate the operating system of your choice: 0 for GNU/Linux or 1 for Microsoft Windows.

The working folder is where the `cg` folder is located. From now on, all graphs are stored in \_g6 format.

## Acyclic graphs
We have produced an adaptation of the [Ripser](https://github.com/Ripser/ripser) program in order to generate acyclic graphs (that is graphs whose clique complex have trivial homology over F_2)


Compiling and running the program [acyclic.cpp](./acyclic.cpp) a structure will be generated in the `ag` folder containing all acyclic graphs on the specicied number of vertices (and edges, if desired).


For the execution of `acyclic.cpp` the `Flag.dat` file is required, which contains a 0 to indicate that the file structure of `ag` has not been created yet. Its value will change to 1 with the first execution of the `acyclic.cpp` program.

Simultaneous executions of `acyclic.cpp` can be performed. Choosing the operating system will also be necessary.

This is part of the suggested list to run:<br />
acyclic 1<br />
acyclic 2<br />
... <br />
acyclic 10<br />
acyclic 11 10<br />
acyclic 11 11<br />
...<br />
acyclic 11 16<br />
acyclic 11 40<br />
acyclic 11 41<br />
...<br />
acyclic 11 55<br />
acyclic 11 17 1<br />
acyclic 11 17 2<br />
acyclic 11 18 1<br />
acyclic 11 18 2<br />
acyclic 11 18 3<br />
acyclic 11 18 4<br />
acyclic 11 19 1<br />
...<br />
acyclic 11 19 8<br />
acyclic 11 20 1<br />
...<br />
acyclic 11 39 2<br />
...<br />
The complete detailed list to execute can be found in [acyclic_run_par.dat](acyclic_run_par.dat).

We suggest running these commands in parallel with a computer using GNU/Linux operating system. Otherwise a couple of weeks of computation may be required.

At the end of the complete list of executions, the [Get#ag_n_Check.cpp](Get#ag_n_Check.cpp) program must be compiled and executed to collect the cardinalities of acyclic graphs, and the files `#agV.dat` and `#agVE.dat` will be generated. If any file is missing after one of the `acyclic.cpp` program executions, the execution of `Get#ag_n_Check.cpp` will inform the user. It took two weeks to run this program on our laptops. If so desired, the output of these runs can be downloaded from the page [Geometric and Combinatorial Structures](http://gcs.mat.uson.mx/index.php/8-research/4-acyclic-graphs).

## Graphs that are Strong I-Contractible but not Strong Vertex I-Contractible

From the collection of acyclic graphs we obtain the graphs that are SIC but not SVIC by compiling and executing the program [GetSpecialG.cpp](GetSpecialG.cpp). From this we obtain 12 graphs, which are collected in [SpecialG.dat](SpecialG.dat). Such graphs are depicted in Figure 1 of the article [Minimal graphs for contractible and dismantlable properties](https://arxiv.org/abs/2109.06729).

![Figure 1.](./images/Fig-1.PNG "Figure 1.")
**Figure 1.**

The run takes a few minutes. 

## Ivashchenko's axiom
The program [V_IA.cpp](V_IA.cpp) examines graphs up to 9 vertices and provides adjacency matrices for graphs that violate this "axiom", there are in [V_IA.dat](V_IA.dat).

## Acyclic graphs that are not 0-dismantable
We obtain these graphs by compiling and running the program [ag_Not0Dis.cpp](ag_Not0Dis.cpp).  The resulting 7 graphs are in [ag_Not0Dis.dat](ag_Not0Dis.dat) and corresponds to the graphs depicted in Figure 5 of the article [Minimal graphs for contractible and dismantlable properties](https://arxiv.org/abs/2109.06729).

![Figure 5.](./images/Fig-5.PNG "Figure 5.")
**Figure 5.**

## Contact
For more information or issues regarding the code, please email hector.hernandez@unison.mx or jesusfrancisco.espinoza@unison.mx.
