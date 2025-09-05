# HLAGA - Hybrid LNS-based ACO with GA repair mechanic Algorithm

The Travelling Salesman Problem (TSP) is a classic combinatorial optimization problem with numerous real-world applications. However, existing algorithms still struggle with both computational efficiency and solution quality.

This project introduces a new TSP solver based on the Large Neighborhood Search (LNS) framework. The algorithm works by repeatedly destroying and repairing solutions to explore better neighborhoods.

## Key Features

Hybrid Approach:

Uses Ant Colony Optimization (ACO) with reinforcement-style learning to preserve high-quality edges during solution destruction.

Compresses the problem into smaller subproblems.

Applies a Genetic Algorithm (GA) to rebuild solutions and search for improved neighborhoods.

Scalability: Designed to handle very large datasets (up to 100,000 nodes).

Performance: Achieves near-optimal solutions with error ≤ 0.1% within 30 minutes, outperforming all current ACO methods and competing with the most advanced TSP algorithms available.

<img width="907" height="390" alt="Untitled" src="https://github.com/user-attachments/assets/9f66b56e-5edd-4225-bb98-1de52c6054e5" />
