# WIP Diver Decompression Model

## Based on robertjkerr/Diver-Decompression

Currently runs the Buhlmann ZHL-16C algorithm with a Fortran backend, with plans to extend to a VPM model.

## Capabilities and Build instructions

The C++ `Buhlmann` class is similar to the `compartments` class in robertjkerr/Diver-Decompression. However, unlike the latter, it minimises on the use of OOP, and instead of having individual objects for each tissue compartment, tissue pressures are stored as arrays and manipulated using vector operations within Fortran. 

`Segment` objects are used to invoke dive segments on a `Buhlmann` object, and the effect on the body will be reflected by changes in the compartment partial pressures. `Buhlmann::get_ceiling()` returns the shallowest depth that the body can go to, and this is being exploited to build a decompression algorithm.

To compile the module object files, use `make`, and if you'd like to run the sample program `main.cpp`, use `make`, then `make main`.


