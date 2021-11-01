# WIP Diver Decompression Model

Based on robertjkerr/Diver-Decompression

Currently runs the Buhlmann ZHL-16C algorithm with a Fortran backend, with plans to extend to a VPM model.

## Capabilities and build instructions

The C++ `Buhlmann` class is similar to the `compartments` class in robertjkerr/Diver-Decompression. However, unlike the latter, it minimises on the use of OOP, and instead of having individual objects for each tissue compartment, tissue pressures are stored as arrays and manipulated using vector operations within Fortran. 

`Segment` objects are used to invoke dive segments on a `Buhlmann` object, and the effect on the body will be reflected by changes in the compartment partial pressures. `Buhlmann::get_ceiling()` returns the shallowest depth that the body can go to, and this is being exploited to build a decompression algorithm.

`main.cpp` is a short sample main file, which has a `Buhlmann` object and invokes a dive segment of 60m for 45 mins breathing trimix 20/20, and then prints the resultant ceiling.

`make` will compile the library object files, `make main` will compiler objects and link with the main object to make executable, `make clean` deletes the objects and `make remove` deletes all objects and executables.
