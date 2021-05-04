# hpc-project

C++ parallel solver for the 2D heat equation, with Dirichlet boundary conditions, using the Finite Differences Method.

The code was validated with test cases, and parallelized using the MPI library.

## Compilation and execution

To compile the parallel code in release mode, assuming you are in the root directory, type the following commands :

```shell
cd parallel
make release
```shell

This command will produce an executable called <code>main</code>. To execute the program with the parameters written in <code>parameters.txt</code>, you can now type
```shell
mpirun ./main parameters
```shell

## Credits
All developpers are students at ENSEIRB-MATMECA, a french engineering school located in Talence.

* Geoffrey Lebaud
* Rémi Pégouret
* Gabriel Suau

## Check-list
- [x] Make a working sequential version of the code (time integration : Explicit Euler, Implicit Euler)
- [x] Parallelize the linear solver (Conjugate Gradient)
- [ ] Automatize the strong scalability tests with a Bash script
