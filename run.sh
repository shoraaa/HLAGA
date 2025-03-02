#! /bin/bash

./faco --alg meta-flaco --problem instances/pla7397.tsp -i 200 -r 5 --ls-cand-list-size 1000 -a 1 --diff-edges-pheromone-gain 0.01
./faco --alg meta-flaco --problem instances/rl11849.tsp -i 200 -r 5 --ls-cand-list-size 1000 -a 1 --diff-edges-pheromone-gain 0.01
./faco --alg meta-flaco --problem instances/usa13509.tsp -i 200 -r 5 --ls-cand-list-size 1000 -a 1 --diff-edges-pheromone-gain 0.01
./faco --alg meta-flaco --problem instances/d15112.tsp -i 200 -r 5 --ls-cand-list-size 1000 -a 1 --diff-edges-pheromone-gain 0.01
./faco --alg meta-flaco --problem instances/d18512.tsp -i 200 -r 5 --ls-cand-list-size 1000 -a 1 --diff-edges-pheromone-gain 0.01