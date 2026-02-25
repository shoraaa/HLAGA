
# LNS-based ACO with GA Repair Mechanic Algorithm for Large Scale TSP (HLAGA)

[![Status](https://img.shields.io/badge/Status-Research-blue.svg)]()
[![Dataset](https://img.shields.io/badge/Dataset-TSPLIB%20%7C%20DIMACS-green.svg)]()

This repository contains the reference implementation of **HLAGA** (Hybrid Large Neighborhood Search-based Ant Colony Optimization with Genetic Algorithm), a novel metaheuristic algorithm designed to solve Large-Scale Travelling Salesman Problem (TSP) instances. 

The algorithm is capable of achieving near-optimal solutions (error gap $\le 0.1\%$) for massive TSP instances featuring up to **100,000 nodes** in under **30 minutes** on standard consumer hardware.

## 📖 Table of Contents
- [Overview](#overview)
- [Algorithm Architecture](#algorithm-architecture)
- [Experimental Results](#experimental-results)
  - [HLAGA Performance](#1-hlaga-performance-on-tsplib-and-dimacs)
  - [Comparison with State-of-the-Art](#2-comparison-with-faco-and-ga-eax)
- [Getting Started](#getting-started)
- [Citation](#citation)

## 💡 Overview

While exact solvers like Concorde struggle with randomized large-scale datasets, and powerful heuristics like GA-EAX or FACO face bottlenecks with convergence speed or local optima traps on massive instances, HLAGA proposes a hybrid solution. 

By framing the TSP within a **Large Neighborhood Search (LNS)** framework, HLAGA utilizes:
1. **Ant Colony Optimization (ACO)** as an intelligent, reinforcement-learning-guided **Destroy operator**. It preserves high-quality edges based on pheromone trails.
2. **Genetic Algorithm (GA)**, specifically a modified GA-EAX, as an efficient **Repair operator**. The un-destroyed edges are compressed into subproblems and re-optimized.
3. An **AACO**-based fast initialization method to quickly supply a high-quality starting solution.

## ⚙️ Algorithm Architecture
* **Intelligent Destroy (ACO):** Starting from a random node, the algorithm sequentially deletes a fixed number of edges (`CDE`). Edges with higher pheromone concentrations have a higher probability of being preserved. 
* **Sub-problem Compression:** The surviving edges are compressed into fixed paths, drastically shrinking the problem size and computational overhead.
* **GA Repair:** A specialized GA-EAX resolves the compressed sub-problem. 
* **Targeted Pheromone Update:** Unlike traditional ACO, pheromones are *only* updated on newly modified edges, paired with a very low evaporation rate ($\rho = 0.01$) to preserve the memory of good edges.

## 📊 Experimental Results

**Hardware Setup:** Intel Core i5-13400F @ 2.50GHz, 32 GB RAM. 
All evaluations were averaged over 10 independent runs. The "%" represents the error gap compared to the Best Known Solution (BKS).

### 1. HLAGA Performance on TSPLIB and DIMACS
HLAGA achieves near-optimal solutions across the board. The maximum error gap does not exceed `0.095%` on average, and execution times stay comfortably between 10 to 30 minutes.

| Instance | BKS | HLAGA Best Gap | HLAGA Mean Gap | Time (s) |
| :--- | :--- | :--- | :--- | :--- |
| **pla7397** | 23,260,728 | 0.066% | 0.084% | 827 |
| **rl11849** | 923,288 | 0.082% | 0.095% | 1,143 |
| **usa13509** | 19,982,859 | 0.000% | 0.003% | 593 |
| **d15112** | 1,573,084 | 0.001% | 0.017% | 827 |
| **d18512** | 645,238 | 0.000% | 0.001% | 1,178 |
| **E10k.0** | 71,865,826 | 0.010% | 0.018% | 609 |
| **E31k.0** | 127,281,803 | 0.038% | 0.052% | 782 |
| **E100k.0** | 225,783,795 | **0.083%** | **0.088%** | **1,605** |
| **E100k.1** | 225,653,450 | **0.082%** | **0.086%** | **1,724** |

### 2. Comparison with FACO and GA-EAX
We compared HLAGA against two State-of-the-Art algorithms: **FACO** (Focused ACO - SOTA for large ACO instances) and **GA-EAX** (SOTA Genetic Algorithm). 

*Highlights:*
* For instances around 10,000 nodes, GA-EAX excels but requires significantly more time (~3 hours vs HLAGA's ~10 mins).
* For instances **$\ge$ 30,000 nodes**, GA-EAX struggles to converge (taking up to 55+ hours with large errors on 100k). FACO runs fast but stalls at a ~0.6% error gap.
* **HLAGA scales exceptionally**, remaining the *only* algorithm to deliver sub-0.1% error in under 30 minutes on 100,000-node instances.

*(Values show Best Gap / Mean Gap over 10 runs)*

| Instance | FACO Error | FACO Time | GA-EAX Error | GA-EAX Time | HLAGA Error | HLAGA Time |
| :--- | :--- | :--- | :--- | :--- | :--- | :--- |
| **E10k.0** | 0.34% / 0.35% | 886s | **0.00% / 0.00%** | 11,382s | 0.01% / 0.01% | **609s** |
| **E10k.2** | 0.19% / 0.20% | 854s | **0.00% / 0.00%** | 11,212s | 0.00% / 0.01% | **635s** |
| **E31k.0** | 0.42% / 0.44% | 863s | 0.22% / 0.25% | 63,252s | **0.03% / 0.05%** | **782s** |
| **E31k.1** | 0.46% / 0.47% | 902s | 0.24% / 0.26% | 63,251s | **0.04% / 0.05%** | **791s** |
| **E100k.0**| 0.61% / 0.63% | 1,736s| 5.41% / 5.49% | 200,034s| **0.08% / 0.08%** | **1,605s** |
| **E100k.1**| 0.61% / 0.62% | 1,772s| 5.46% / 5.53% | 200,037s| **0.08% / 0.08%** | **1,724s** |

---

## 🚀 Getting Started

*(Note: Add your build/run instructions here when uploading your code)*

```bash
# Example Placeholder Instructions
git clone https://github.com/shoraaa/HLAGA
cd HLAGA
make
./faco
```

## 📝 Citation
If you use this code or our algorithm in your research, please cite our paper:

```bibtex
@article{dat2024hlaga,
  title={LNS-based ACO with GA repair mechanic algorithm for solving large scale TSP instances},
  author={Trần Thành Đạt},
  institution={VNU University of Engineering and Technology},
  year={2024}
}
```

## 🙏 Acknowledgments
* **Dr. Đỗ Đức Đông** for his research supervision.
* **Rafał Skinderowicz** for his support with the FACO implementation and experimental comparisons.
* **Nagata Yuichi** for the open-source GA-EAX algorithm.
