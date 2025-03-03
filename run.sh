#! /bin/bash

./faco --alg meta-flaco --problem instances/pla7397.tsp -i 200 -r 5 -a 1 --count-delete-edges 1000
./faco --alg meta-flaco --problem instances/rl11849.tsp -i 200 -r 5 -a 1 --count-delete-edges 1000 
./faco --alg meta-flaco --problem instances/usa13509.tsp -i 200 -r 5 -a 1 --count-delete-edges 1000 
./faco --alg meta-flaco --problem instances/d15112.tsp -i 200 -r 5 -a 1 --count-delete-edges 1000 
./faco --alg meta-flaco --problem instances/d18512.tsp -i 200 -r 5 -a 1 --count-delete-edges 1000