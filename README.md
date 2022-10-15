# WIP Diver Decompression Model

Based on robertjkerr/Diver-Decompression

Currently runs the Buhlmann ZHL-16C algorithm with a Fortran backend, with plans to extend to a VPM model.

## Capabilities and build instructions

The C++ `Buhlmann` class is similar to the `compartments` class in robertjkerr/Diver-Decompression. However, unlike the latter, it minimises on the use of OOP, and instead of having individual objects for each tissue compartment, tissue pressures are stored as arrays and manipulated using vector operations within Fortran. 

`Segment` objects are used to invoke dive segments on a `Buhlmann` object, and the effect on the body will be reflected by changes in the compartment partial pressures. `Buhlmann::get_ceiling()` returns the shallowest depth that the body can go to, and this is being exploited to build a decompression algorithm.

`main.cpp` is a short sample main file, which has a `Buhlmann` object and invokes a dive segment of 60m for 45 mins breathing trimix 20/20, and then prints the resultant ceiling.

`make` will compile the library object files, `make main` will compiler objects and link with the main object to make executable, `make clean` deletes the objects and `make remove` deletes all objects and executables.

## Buhlmann algorithm background

In this model, we assume there are 16 tissue compartments. Inert gases (Nitrogen and Helium) will become dissolved in them when there is a positive difference in partial pressure between the environment and the compartment. Therefore for each of the 16 tissues, we have 2 gas partial pressures to keep a track of, and each of them follow this equation, similar to Newton's cooling law:

$$
\frac{dP}{dt} = k (P_{ambient} - P)
$$

So, if $P_{ambient}>P$, $P$ goes up (i.e. the compartment is ongassing), and vice-versa if the compartment is offgassing. This is a simple first-order ordinary differential equation, and it is still easy to solve even when the ambient (environment) pressure is changing linearly with time e.g. $P_{ambient}(t) = Rt+P_{ambient, t=0}$:

$$
\frac{dP}{dt} +kP(t)=kRt+kP_{ambient,t=0}
$$

$$
\implies \frac{dP}{dt} +p(t) P(t)=q(t)
$$

Finding the integrating factor from $p(t)=p=1/k$, we have:
$$
\mu=e^{\int dt/k} = e^{kt}
$$
$$
\implies \mu\frac{dP}{dt} +\mu p(t) P(t)=\mu q(t)
$$
$$
\implies \frac{d}{dt}(\mu P(t)) = \mu q(t)
$$
We must integrate next:
$$
\mu P(t) = \int \mu q(t) dt
$$
$$
e^{kt} P(t) = \int e^{kt} (kRt+kP_{ambient,t=0}) dt
$$
$$
e^{kt} P(t) = kP_{ambient,t=0}t + kR \int te^{kt} dt
$$
Using integration by parts:
$$
e^{kt} P(t) = kP_{ambient,t=0}t + kR(\frac{t}{k}e^{kt}) - kR\int \frac{1}{k}e^{kt}dt
$$
$$
e^{kt} P(t) = kP_{ambient,t=0}te^{kt} + Rte^{kt} - \frac{R}{k}e^{kt} + C
$$
$$
\implies P(t) =kP_{ambient,t=0}t + Rt - \frac{R}{k} + Ce^{-kt} 
$$
With the intial condition of $P(0)=P_{t=0}$:
$$
P(t) = P_{ambient,t=0}(1-e^{-kt})+R(t+\frac{e^{-kt}-1}{k})+P_{t=0}e^{-kt}
$$
