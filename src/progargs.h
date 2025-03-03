/**
 * @author: Rafał Skinderowicz (rafal.skinderowicz@us.edu.pl)
 */
#pragma once

#include <string>
#include <cstdint>

struct ProgramOptions {
    std::string algorithm_ = "faco";

    // If #ants is set to 0 then a default strategy is used to initiate it
    uint32_t ants_count_ = 0; 

    // When looking for a next node to visit it may happen that all of the
    // nodes on the candidates list were visited -- in such case we choose
    // one of the nodes from a "backup" list
    uint32_t backup_list_size_ = 64;

    // Relative importance of heuristic information, i.e. distances between
    // nodes
    double beta_ = 1;

    uint32_t cand_list_size_ = 16;

    std::string id_ = "default";  // Id of the comp. experiment

    // Probability of using the current global best as a source solution
    double gbest_as_source_prob_ = 0.1;

    int32_t iterations_ = 5 * 1000;

    int32_t local_search_ = 1;  // 0 - no local search, 1 - default LS

    uint32_t ls_cand_list_size_ = 20u;  // #nodes used by the LS heuristics

    uint32_t min_new_edges_ = 8;

    // Prob. that a solution will contain only edges with the
    // highest pheromone levels. Used to calculate pheromone trail limits.
    double p_best_ = 0.1;

    std::string problem_path_ = "kroA100.tsp";

    // By default the results will be stored in "results" folder
    std::string results_dir_ = "results";

    // How much of the pheromone remains after a single evaporation event
    double rho_ = 0.5;

    // Should a picture of the solution (route) be stored into SVG file?
    bool save_route_picture_ = true;

    // Random number generator seed -- 0 means that seed should be 
    // based on the built-in std::random_device
    uint64_t seed_ = 0;

    int32_t repeat_ = 1;

    int32_t threads_ = 0;  // If > 0 then force specific # of threads in OpenMP

    // Modified FACO -- should we keep the previous ant solution if new one
    // is worse? Default: true
    int32_t keep_better_ant_sol_ = 1;

    // Modified FACO -- should the (local) source solution be immediately
    // replaced with a new better solution (if its found) in the current iteration
    int32_t source_sol_local_update_ = 1;

    // Modified FACO -- should the actual # of new edges in the constructed
    // solutions be checked?
    int32_t count_new_edges_ = 0;


    // FLARE-ACO -- minimum rho for smmas
    double rho_min_ = -1;

    // FLARE-ACO -- minimum ant
    int32_t min_ants_ = 16;

    // FLARE-ACO -- maximum ant
    int32_t max_ants_ = 1024;

    // FLARE-ACO -- time limit
    int32_t time_limit_ = 0;

    // FLARE-ACO -- use GA
    int32_t use_ga_ = 0;

    // FLARE-ACO -- init population size
    int32_t init_pop_size_ = 10;

    // FLARE-ACO -- population size
    int32_t pop_size_ = 100;

    // FLARE-ACO -- init kids size
    int32_t init_kids_size_ = 10;

    // FLARE-ACO -- kids size
    int32_t kids_size_ = 30;

    // FLARE-ACO -- smmas
    int32_t smooth_ = 0;

    // FLARE-ACO -- 3las
    int32_t three_level_ = 0;

    // FLARE-ACO -- lazy pheromone update
    int32_t lazy_pheromone_update_ = 0;

    // FLARE-ACO -- path length
    int32_t path_length_ = 128;

    // FLARE-ACO -- count delete edges
    int32_t count_delete_edges_ = 500;

    // FLARE-ACO -- Difference edges pheromone gain
    double diff_edges_pheromone_gain_ = 0.01;

    // force new edges
    int32_t force_new_edges_ = 1;
};


template<typename MapT>
void dump(const ProgramOptions &opt, MapT &map) {
    map["alg"] = opt.algorithm_;
    map["ants"] = opt.ants_count_;
    map["backup list size"] = opt.backup_list_size_;
    map["beta"] = opt.beta_;
    map["cand list size"] = opt.cand_list_size_;
    map["id"] = opt.id_;
    map["gbest as source prob"] = opt.gbest_as_source_prob_;
    map["iterations"] = opt.iterations_;
    map["local search"] = opt.local_search_;
    map["ls cand list size"] = opt.ls_cand_list_size_;
    map["min new edges"] = opt.min_new_edges_;
    map["p best"] = opt.p_best_;
    map["problem"] = opt.problem_path_;
    map["results dir"] = opt.results_dir_;
    map["rho"] = opt.rho_;
    map["seed"] = opt.seed_;
    map["picture"] = opt.save_route_picture_;
    map["repeat"] = opt.repeat_;
    map["threads"] = opt.threads_;
    map["keep better ant sol"] = opt.keep_better_ant_sol_;
    map["source sol local update"] = opt.source_sol_local_update_;
    map["count new edges"] = opt.count_new_edges_;

    map["rho min"] = opt.rho_min_;
    map["min ants"] = opt.min_ants_;
    map["max ants"] = opt.max_ants_;
    map["time limit"] = opt.time_limit_;
    map["pop size"] = opt.pop_size_;
    map["use ga"] = opt.use_ga_;
    map["init pop size"] = opt.init_pop_size_;
    map["kids size"] = opt.kids_size_;
    map["init kids size"] = opt.init_kids_size_;
    map["smooth"] = opt.smooth_;
    map["three level"] = opt.three_level_;
    map["lazy pheromone update"] = opt.lazy_pheromone_update_;
    map["path length"] = opt.path_length_;
    map["count delete edges"] = opt.count_delete_edges_;

    map["diff edges pheromone gain"] = opt.diff_edges_pheromone_gain_;
    map["force new edges"] = opt.force_new_edges_;
}

ProgramOptions parse_program_options(int argc, char *argv[]);
