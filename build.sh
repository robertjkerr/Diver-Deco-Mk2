gfortran -c -g -Wall -Wextra -Werror -pedantic src/model/compartments/f90/constants.f90
gfortran -c -g -Wall -Wextra -Werror -pedantic src/model/compartments/f90/buhl.f90
gfortran -c -g -Wall -Wextra -Werror -pedantic src/model/compartments/f90/module.f90
g++ -c -g -Wall -Wextra -Werror -pedantic src/model/compartments/buhlmann.cpp
g++ -c -g -Wall -Wextra -Werror -pedantic src/model/types_constants/types.cpp 
g++ -c -g -Wall -Wextra -Werror -pedantic src/model/algorithm/deco_algorithm.cpp
g++ -c -g -Wall -Wextra -Werror -pedantic main.cpp
gfortran -o main.exe *.o -lstdc++

