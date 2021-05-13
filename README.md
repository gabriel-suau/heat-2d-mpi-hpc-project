# hpc-project

C++ parallel solver for the 2D heat equation, with Dirichlet boundary conditions, using the Finite Differences Method.

The code was validated with test cases, and parallelized using the MPI library.


## Installation, compilation and execution

You can get the sources from here by typing in your terminal :

```shell
git clone https://github.com/gabriel-suau/heat-2d-mpi-hpc-project.git mpi_heat_2D
```

To compile the parallel code in release mode, you can type the following commands :

```shell
cd mpi_heat_2D/parallel
make release
```

This command will produce an executable called <code>main</code>. To execute the program with the parameters written in <code>parameters.txt</code>, you can use either <code>mpiexec</code> or <code>mpirun</code>. For example, to execute the program with 4 MPI processes (assuming your machine has the required number of cores), you can type :

```shell
mpirun -n 4 ./main parameters.txt
```

or

```shell
mpiexec -n 4 ./main parameters.txt
```


## Outputs

The outputs of the computation are written in the directory <code>resultsDir</code> specified in <code>parameters.txt</code>. Each MPI process writes its own results files. These files can directly be plotted using <code>gnuplot</code>. The results file names are in the form :

```shell
solution_scenario_%SCENARIO%_%MPIRANK%_%SAVEITERATION%.dat
```

For example, let's say you simulated the scenario n°1 with 4 MPI processes. To visualise the whole solution at the time iteration n°10, you can type

```shell
gnuplot
splot for [i=0:3] "solution_scenario_1_".i."_10.dat"
```


## Documentation

A documentation for the parallel code can be automatically generated with [Doxygen](https://www.doxygen.nl/index.html). Just type :

```shell
doxygen doxygen.cfg
```

This command will produce a <code>doc/</code> directory containing an HTML documentation in the <code>html/</code> directory and a PDF documentation in the <code>latex</code> directory. To read the HTML documentation using <code>firefox</code>, just type the following command (assuming you are in the root directory)

```shell
firefox doc/html/index.html
```

## Credits
All developpers are students at ENSEIRB-MATMECA, a french engineering school located in Talence.

* Geoffrey Lebaud
* Rémi Pégouret
* Gabriel Suau


## License

This project is distributed under the [GNU-GPLv3](https://www.gnu.org/licenses/gpl-3.0.html) license. A copy of the whole license is included in the repository.


## Check-list
- [x] Make a working sequential version of the code (time integration : Explicit Euler, Implicit Euler)
- [x] Parallelize the linear solver (Conjugate Gradient)
- [ ] Automatize the strong scalability tests with a Bash script
