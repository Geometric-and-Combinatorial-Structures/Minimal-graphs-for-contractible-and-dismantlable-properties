# Minimal graphs for contractible and dismantlable properties
In this repository we show how to implement the algorithms used in the article *Minimal graphs for contractible and dismantlable properties*
 ([arXiv:2109.06729 [math.CO]](https://arxiv.org/abs/2109.06729)), in order to obtain the cardinalities in Table 1 of such article:
 

This work considers simple connected graphs on up to 11 vertices.

## Connected graphs
The connected graphs were taken from the well-known repository of Professor Brendan McKay (available online at [Graphs](https://users.cecs.anu.edu.au/~bdm/data/graphs.html)). There the graphs are organized into files according to the number of vertices: `graph2c.g6`, `graph3c.g6`, ... , `graph10c.g6`, `graph11.g6`. The last two files need to be unzipped due to their size.

**Remark**: The file `graph11.g6` contains connected and disconnected graphs, the other ones consist only of connected graphs.

For more details about the g6 format (among other aspects) consult: [graph formats](https://users.cecs.anu.edu.au/~bdm/data/formats.html).

## Setup files 
To facilitate the work we have further divided the files according to how many edges the graphs have. For files with graphs of 11 vertices with more than one million graphs, we have created a folder that contains several files of at most one million graphs. The first of these files are
`11v17e-001` and `11v17e-002`.

Additionally, we have introduced a slight variant to the g6 format. This consists of ignoring the data that indicates the number of vertices, called N(n) by McKay. We have called this format \_g6. The number of vertices is known based on which file the graph comes from.

Compiling and running the program [Windows/split.cpp](./Windows/split.cpp), the file structure contained in the `cg` folder will be generated containing the connected graphs up to 11 vertices in \_g6 format, as well as the files `#cgV.dat` and `#cgVE.dat` containing cardinalities. The output of such script is written in the second column in Table 1 of the paper *Minimal graphs for contractible and dismantlable properties* ([arXiv:2109.06729 [math.CO]](https://arxiv.org/abs/2109.06729)).

Under GNU/Linux can be used the script [GNU-Linux/split.cpp](./GNU-Linux/split.cpp), which can be compiled and executed in the terminal as:
```
> g++ split.cpp -o split
> ./split
```
We have used the following version of the compiler:
```
> g++ --version
g++ (Debian 10.2.1-6) 10.2.1 20210110
```
In a laptop with a processor Intel(R) Xeon(R) CPU E3-1535M v6 @ 3.10GHz, the execution of the script `split.cpp` takes about 25 minutes, no more than 4 GiB of RAM, and the output consists of 1169 files distributed in 34 sub-folders in `./cg`, with a total size of 10.4 GiB.

The working folder is where the `cg` folder is located. From now on, all graphs are stored in \_g6 format.

## Acyclic graphs
We have produced an adaptation of the [Ripser](https://github.com/Ripser/ripser) program in order to generate acyclic graphs (that is graphs whose clique complex have trivial homology over F_2).

Compiling and running the program [Windows/acyclic.cpp](./Windows/acyclic.cpp) a structure will be generated in the `ag` folder containing all acyclic graphs on the specified number of vertices (and edges, if desired).

For the execution of `acyclic.cpp` the `FlagAcyclic.dat` file is required, which contains a 0 to indicate that the file structure of `ag` has not been created yet. Its value will change to 1 with the first execution of the `acyclic.cpp` program.

Under GNU/Linux can be used the script [GNU-Linux/acyclic.cpp](./GNU-Linux/acyclic.cpp), which can be compiled and executed in the terminal as:
```
> g++ acyclic.cpp -o acyclic
> ./acyclic
```
In this case, also the file `FlagAcyclic.dat` must be located in the work directory and initialized in 0; otherwise, a "Segmentation fault" message will be displayed.

Simultaneous executions of `acyclic.cpp` can be performed under Windows by opening several instances. Under GNU/Linux can be run the bash script [GNU-Linux/acyclic_runner](./GNU-Linux/acyclic_runner), to send all the processes to the background and use all the available cores of the computer. 
```
> chmod a+x acyclic_runner
> ./acyclic_runner
```
In our personal computer this script takes about 4 days to be completed, no more than 8 GiB of RAM, and the output consists of 2338 files distributed in 34 sub-folders in `ag`, with a total size of 1.7 GiB.

Of course, in Windows as well as in GNU/Linux, the script `acyclic` can be executed manually as follows:<br />
acyclic 1<br />
acyclic 2<br />
... <br />
acyclic 10<br />
acyclic 11 10<br />
acyclic 11 11<br />
...<br />
acyclic 11 16<br />
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
acyclic 11 38 3<br />
acyclic 11 39 1<br />
acyclic 11 39 2<br />
acyclic 11 40<br />
acyclic 11 41<br />
...<br />
acyclic 11 55<br />

The complete detailed list to execute, under Windows, can be found in [Windows/acyclic_run_parallel.dat](./Windows/acyclic_run_parallel.dat). We suggest running these commands in parallel with a computer using GNU/Linux operating system. Otherwise a couple of weeks of computation may be required. If so desired, the output of these runs can be downloaded from the page [Geometric and Combinatorial Structures](http://gcs.mat.uson.mx/index.php/8-research/4-acyclic-graphs).

At the end of the complete list of executions, the [Windows/acyclic_cardinalities.cpp](./Windows/acyclic_cardinalities.cpp) program must be compiled and executed to collect the cardinalities of acyclic graphs, and the files `#agV.dat` and `#agVE.dat` will be generated. If any file is missing after one of the `acyclic.cpp` program executions, the execution of `acyclic_cardinalities.cpp` will inform the user. Under GNU/Linux, the same script ([GNU-Linux/acyclic_cardinalities.cpp](./GNU-Linux/acyclic_cardinalities.cpp)) works well:
```
> g++ acyclic_cardinalities.cpp -o acyclic_cardinalities
> ./acyclic_cardinalities
```
The output of such script is written in the third column in Table 1 of the paper *Minimal graphs for contractible and dismantlable properties* ([arXiv:2109.06729 [math.CO]](https://arxiv.org/abs/2109.06729)).

## The family of Strong I-Contractible graphs
Independently of the computation of the family of acyclic graphs, can be performed the computation of the family of Strong I-Contractible graphs. For this, can be compiled and executed the script [Windows/Sic.cpp](./Windows/Sic.cpp) under Windows; or [GNU-Linux/Sic.cpp](./GNU-Linux/Sic.cpp) under GNU/Linux:
```
> g++ Sic.cpp -o Sic
> ./Sic 1
> ./Sic 2
...
> ./Sic 10
> ./Sic 11 10
> ./Sic 11 11
...
> ./Sic 11 16
> ./Sic 11 17 1
> ./Sic 11 17 2
> ./Sic 11 18 1
> ./Sic 11 18 2
> ./Sic 11 18 3
> ./Sic 11 18 4
> ./Sic 11 19 1
...
> ./Sic 11 19 8
> ./Sic 11 20 1
...
> ./Sic 11 38 3
> ./Sic 11 39 1
> ./Sic 11 39 2
> ./Sic 11 40
...
> ./Sic 11 55
```
Same list as for the acyclic ones. Of course, simultaneous executions of `Sic.cpp` can be performed under Windows by opening several instances. Under GNU/Linux can be run the bash script [GNU-Linux/Sic_runner](./GNU-Linux/Sic_runner), to send all the processes to the background and use all the available cores of the computer. In our personal computer such bash script takes about 40 minutes to be completed, no more than 4 GiB of RAM, and the output consists of 2338 files distributed in 34 sub-folders in `sic`, with a total size of 1.7 GiB.

After the above computation, can be compiled and executed the script [Windows/SIC_cardinalities.cpp](./Windows/SIC_cardinalities.cpp), or [GNU-Linux/SIC_cardinalities.cpp](./GNU-Linux/SIC_cardinalities.cpp) if corresponds, to collect the cardinality of the strong I-contractible graphs, partitionated by number or vertices. 
```
> g++ SIC_cardinalities.cpp -o SIC_cardinalities
> ./SIC_cardinalities
```
The cardinalities obtained in the file `#sicV.dat` corresponds the the numbers in the 5-th column in Table 1 of the paper *Minimal graphs for contractible and dismantlable properties* ([arXiv:2109.06729 [math.CO]](https://arxiv.org/abs/2109.06729)). On the other hand, as every strong I-contractible graph is I-contractible, therefore acyclic, and the number of acyclic and strong I-contractible graphs coincide for every number of vertices (up to 11), then the fourth columns (related to the I-contractible graphs) must be coincide with those.

As was proved in [Collapsibility and homological properties of I-contractible transformations](https://arxiv.org/pdf/1808.07461.pdf), every strong I-contractible graph es collapsible, then acyclic, 


## Graphs that are Strong I-Contractible but not Strong Vertex I-Contractible

From the collection of acyclic graphs we obtain the graphs that are SIC but not SVIC by compiling and executing the program [GetSpecialG.cpp](GetSpecialG.cpp). From this we obtain 12 graphs, which are collected in [SpecialG.dat](SpecialG.dat). Such graphs are depicted in Figure 1 of the article [Minimal graphs for contractible and dismantlable properties](https://arxiv.org/abs/2109.06729).

![Figure 1.](./images/Fig-1.PNG "Figure 1.")
**Figure 1.** Minimal examples of graphs that are in SIC but not in SVIC.

The run takes a few minutes.

Under GNU/Linux, ...

## Ivashchenko's axiom
The program [V_IA.cpp](V_IA.cpp) examines graphs up to 9 vertices and provides adjacency matrices for graphs that violate this "axiom", there are in [V_IA.dat](V_IA.dat).

## Acyclic graphs that are not 0-dismantable
We obtain these graphs by compiling and running the program [ag_Not0Dis.cpp](ag_Not0Dis.cpp).  The resulting 7 graphs are in [ag_Not0Dis.dat](ag_Not0Dis.dat) and corresponds to the graphs depicted in Figure 5 of the article [Minimal graphs for contractible and dismantlable properties](https://arxiv.org/abs/2109.06729).

![Figure 5.](./images/Fig-5.PNG "Figure 5.")
**Figure 5.** The smallest graphs that are 1-dismantlable (and hence strong vertex I-contractible) but not 0-dismantlable.

## Contact
For more information or issues regarding the code, please email hector.hernandez@unison.mx or jesusfrancisco.espinoza@unison.mx.
