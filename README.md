# Minimal graphs for contractible and dismantlable properties
In this repository is shown how to implement the algorithms used in the article *Minimal graphs for contractible and dismantlable properties*
 ([arXiv:2109.06729 [math.CO]](https://arxiv.org/abs/2109.06729)).

This work considers simple connected graphs up to 11 vertices.

## Connected graphs
The connected graphs were taken from the well-known repository of professor Brendan McKay (avalilable online at https://users.cecs.anu.edu.au/~bdm/data/graphs.html). The files of connected graphs are splited by its numeber of vertices: `graph2c.g6`, `graph3c.g6`, ... , `graph10c.g6`, `graph11.g6`. The last two files need to be unzipped due to their size.

**Remark**: The file `graph11.g6` contains connected and disconnected graphs, the other ones consists of only connected graphs.

For more details about the g6 format (among other aspects) consult: https://users.cecs.anu.edu.au/~bdm/data/formats.html

## Setup files 
To facilitate the work we have divided the graphs into subsets by vertices and edges. Even so, there are files with more than a million graphs. For files with graphs of 11 vertices with more than a million graphs, we have created a folder that contains several files of at most a million graphs. The first of these files are
`11v17e-001` and `11v17e-002`.

Additionally, we have introduced a slight variant to the g6 format. This consists of ignoring the data that indicates the number of vertices, called N(n) by McKay. We have called this format \_g6. The number of vertices is known because we know which file the graph comes from.

Compiling and running the program [split.cpp](split.cpp) the file structure contained in the `cg` folder will be generated containing the graphs in \_g6 format, also the files `#cgV.dat` and `#cgVE.dat` containing cardinalities.

**Note**: In the code should include the operating system of your choice: 0 for GNU/Linux or 1 for Microsoft Windows.

The working folder is where the `cg` folder is located. From now on, all graphs are stored in \_g6 format.

## Acyclic graphs
We have generated an adaptation of the [Ripser](https://github.com/Ripser/ripser) program to obtain acyclic graphs.

Compiling and running the program [acyclic.cpp](./acyclic.cpp) a structure will be generated with the `ag` folder containing acyclic graphs from the simplicial point at view or, in other words, graphs with trivial homology.

For the execution of acyclic.cpp the `Flag.dat` file is required, which contains a 0 to indicate that the file structure of `ag` has not been created yet, its content are going to change to 1 with the first execution of acyclic.cpp program.

Simultaneous executions of acyclic.cpp can be performed. Choosing the operating system will also be necessary.

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

The suggestion is to run in parallel with a computer using GNU/Linux operating system. Otherwise a couple of weeks of computation may be required.

At the end of the complete list of executions, the [Get#ag_n_Check_ag.cpp](Get#ag_n_Check_ag.cpp) program must be compiled and executed to collect the cardinalities of acyclic graphs and the files `#agV.dat` and `#agVE.dat` will be generated, if any file is missing due to executing a cyclic program, it will be informed. If so desired, the output of these runs can be downloaded from the page [Geometric and Combinatorial Structures](http://gcs.mat.uson.mx/index.php/8-research/4-acyclic-graphs).

## Strong-I-Contractible but Not Strong-I-Contractible by vertices graphs

Based on the acyclic graphs we will obtain the graphs that are SIC but not SICv, compiling and executing the program [GetSpecialG.cpp](GetSpecialG.cpp). Then, 12 graphs will be obtained, these are in [SpecialG.dat](SpecialG.dat).

The run takes a few minutes.

## Ivashchenko's axiom.
The program [V_IA.cpp](V_IA.cpp) examines graphs up to 9 vertices and provides adjacency matrices for graphs that violate this "axiom", there are in [V_IA.dat](V_IA.dat).

## Acyclic graphs but not 0-dismantables
Compiling and running de program [ag_Not0Dis.cpp](ag_Not0Dis.cpp), the 7 graphs are in [ag_Not0Dis.dat](ag_Not0Dis.dat).

