# Minimal graphs for contractible and dismantlable properties
In this repository is shown how implement the algorithms used in the article
Minimal Gaphs for contracible and dismatable properties
(arXiv:2109.06729 [math.CO]).
This work considers graphs from 1 vertex to 11 vertices.

## Connected graphs
The connected graphs were taken from the well-known repository of Brendan McKay:
https://users.cecs.anu.edu.au/~bdm/data/graphs.html
contained in the files:
graph2c.g6
graph3c.g6
...
graph10c.g6
graph11.g6
the last two need to be unzipped due to their size.

Remark: the file graph11.g6 is the only one that contains connected and disconnected graphs.
To understand the g6 format (among other aspects)
McKay explains it in: https://users.cecs.anu.edu.au/~bdm/data/formats.html

## Setup files 
To facilitate the work we have divided the graphs into subsets by vertices and edges
(v,e)
Even so, there are files with more than a million graphs. For files with graphs of eleven 11 vertices with more than a million graphs, we have created a folder that contains several files of at most a million graphs.
The first of these files are
11v17e-001 and 11v17e-002.

Additionally we have introduced a slight variant to the g6 format. This consists of ignoring the data that indicates the number of vertices, called N(n) by McKay. We have called this format _g6. The number of vertices is known because we know which file the graph comes from.

Compiling and running the program Split.cpp the file structure contained in the cg folder will be generated  containing the graphs in _g6 format, also the files #cgV.dat and #cgVE.dat containing cardinalities.
Note: In the code should include the operating system of your choice:
0 by linux
1 by MsDos/Windows.

The execution could take one to two hours.

By the way, the working folder is where the cg folder is located.
From now on, all graphs are stored in _g6 format.

## Aciclic graphs (simplicial point at view).
We have generated an adaptation of the Ripser.cpp program to obtain acyclic graphs.

Compiling and running the program Th.cpp a structure will be generated with the ag folder containing acyclic graphs from the simplicial point at view or, in other words, graphs with trivial homology.

For the execution of Th.cpp the Flag.dat file is required
contains a 0, this indicates that the ag file structure has not been created yet, its content are going to change to 1 with the first execution of Th automatically.

To save time simultaneous executions of Th.cpp can be performed. Choosing the operating system will also be necessary.

This is part of the suggested list of Th to run
Th1 , Th2 , ... , Th10 ,
Th 11 10 ,
Th 11 11 ,
... ,
Th 11 16 ,
Th 11 40 ,
Th 11 41 ,
... ,
Th 11 55 ,
Th 11 17 1 ,
Th 11 17 2 ,
Th 11 18 1 ,
Th 11 18 2 ,
Th 11 18 3 ,
Th 11 18 4 ,
Th 11 19 1 ,
... ,
Th 11 19 8 ,
Th 11 20 1 ,
... ,
Th 11 39 2 ,
...
The complete detailed list to execute can be found in Th_Run_par.dat

The best suggestion is to run in parallel with a computer with a Linux operating system.

Otherwise a couple of weeks of computation may be required.

At the end of the complete list of executions, the GetCard_ag.cpp program must be compiled and executed to collect the cardinalities of acyclic graphs and the files #adV.day and #agVE.dat will be generated

If so desired, the output of these runs can be downloaded from ag.zip

## Strog-I-Contractible but Not Strong-I-Contractible by vertices graphs.

Based on the acyclic graphs we will obtain the graphs that are SIC but not SICv, compiling and executing the program GetSpecialG.cpp

12 graphs will be obtained, these are in SpecialG.dat.

The run takes a few minutes.

## Ivashchenko's axiom.
The program V_IA.cpp examines graphs up to 9 vertices and provides adjacency matrices for graphs that violate this "axiom", there are in V_IA.dat

# Aciclic graphs but not 0-dismatables
Compiling an running de program ag_Not0Dis.cpp , the 7 graphs are in ag_Not0Dis.dat

