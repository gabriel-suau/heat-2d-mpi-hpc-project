# hpc-project

C++ parallel solver for the 2D heat equation, with Dirichlet boundary conditions, using the Finite Differences Method.

Work in progess...

The code will be validated with test cases, and then parallelized using the MPI library.

## Credits
All developpers are students at ENSEIRB-MATMECA, a french engineering school located in Talence.

* Geoffrey Lebaud
* Rémi Pégouret
* Gabriel Suau

## Check-list
- [x] Make a working sequential version of the code (time integration : Explicit Euler, Implicit Euler)
- [x] Parallelize the linear solver (Conjugate Gradient)
- [ ] Automatize convergence/scalability tests with Bash/Python scripts
