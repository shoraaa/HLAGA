/**
 * @author: Rafał Skinderowicz (rafal.skinderowicz@us.edu.pl)
 */
#include <functional>
#include <string>
#include <vector>
#include <iostream>

#include "progargs.h"
#include "include/cxxopts/cxxopts.hpp"

template<typename T>
std::string to_string(const T &value) { return std::to_string(value); }

std::string to_string(const std::string &value) { return value; }


struct OptionsParser {
    cxxopts::Options options_{"TODO", "Focused ACO for TSP"};
    std::vector<std::function<void (cxxopts::ParseResult &)>> parse_callbacks_;

    OptionsParser() {
        options_.add_options()("h,help", "Print usage");
    }

    void parse(int argc, char **argv) {
        auto args = options_.parse(argc, argv);

        if (args.count("help")) {
            std::cout << options_.help() << std::endl;
            exit(0);
        }

        for (auto &fn : parse_callbacks_) {
            fn(args);
        }
    }

    template<typename T>
    void add(const std::string &switches,
             const std::string &desc,
             T &arg) {
        options_.add_options()(switches, desc,
                               cxxopts::value<T>()->default_value(to_string(arg)));

        auto pos = switches.find(',');
        std::string flag = (pos != std::string::npos)
                         ? switches.substr(0, pos)
                         : switches;

        parse_callbacks_.emplace_back( [&arg,flag] (cxxopts::ParseResult &args) {
            arg = args[flag].as<T>(); 
        } );
    }
};


ProgramOptions parse_program_options(int argc, char *argv[]) {
    ProgramOptions opts;
    OptionsParser p;
    p.add("alg", "Algorithm name [faco,mmas]", opts.algorithm_);

    p.add("a,ants", "Number of ants", opts.ants_count_);

    p.add("backup-list-size", "Size of the backup list", opts.backup_list_size_);
    
    p.add("beta", "Rel. importance of heuristic information", opts.beta_);

    p.add("cand-list-size", "Size of the candidate list", opts.cand_list_size_);

    p.add("id", "Id of the experiment (optional)", opts.id_);

    p.add("gbest-as-source-prob",
          "Prob. of using the current global best as a source sol.",
          opts.gbest_as_source_prob_);

    p.add("i,iterations", "Iterations count", opts.iterations_);

    p.add("local-search", "Should local search be used", opts.local_search_);

    p.add("ls-cand-list-size", "# of nearest nodes considered by the local search", opts.ls_cand_list_size_);

    p.add("min-new-edges", "Min # of new edges in a constructed sol.", opts.min_new_edges_);

    p.add("p-best", "p_best parameter of the MMAS", opts.p_best_);

    p.add("picture", "Generate route picture in SVG format?", opts.save_route_picture_);

    p.add("p,problem", "Path to a TSP instance in the TSPLIB format",
               opts.problem_path_);

    p.add("results-dir", "Where to store the results", opts.results_dir_);

    p.add("rho", "How much of the pheromone remains after evaporation", opts.rho_);

    p.add("seed", "Initial Random seed", opts.seed_);

    p.add("r,repeat", "How many trials should be executed", opts.repeat_);

    p.add("threads", "If > 0 then sets the # of threads used", opts.threads_);

    p.add("keep-better-ant-sol", "Only update ant solution with a better one", opts.keep_better_ant_sol_);

    p.add("source-sol-local-update", "Immediately update local source sol. if a better one is found", opts.source_sol_local_update_);

    p.add("count-new-edges", "Should the actual # of new edges be checked", opts.count_new_edges_);

    p.add("rho-min", "Minimum pheromone for SMMAS algorithm", opts.rho_min_);

    p.add("min-ants", "Minimum # of ants for FLARE-ACO", opts.min_ants_);

    p.add("max-ants", "Maximum # of ants for FLARE-ACO", opts.max_ants_);

    p.add("time-limit", "Time limit for FLARE-ACO", opts.time_limit_);

    p.add("pop-size", "Population size for GA", opts.pop_size_);

    p.add("use-ga", "Use GA in FLARE-ACO", opts.use_ga_);

    p.add("init-pop-size", "Initial population size for inital GA", opts.init_pop_size_);

    p.add("init-kid-size", "Initial kids size for initial GA", opts.init_kids_size_);

    p.add("kid-size", "Kids size for GA", opts.kids_size_);

    p.add("smooth", "Use smooth MMAS", opts.smooth_);

    p.add("three-level", "Use 3-level MMAS", opts.three_level_);

    p.add("lazy-pheromone-update", "Use lazy pheromone update", opts.lazy_pheromone_update_);

    p.add("path-length", "Path length for FLARE-ACO", opts.path_length_);
    
    p.add("count-delete-edges", "Count delete edges for FLARE-ACO", opts.count_delete_edges_);
    
    p.add("diff-edges-pheromone-gain", "Difference edges pheromone gain for FLARE-ACO", opts.diff_edges_pheromone_gain_);

    p.add("force-new-edges", "Force new edges for FLARE-ACO", opts.force_new_edges_);

    p.parse(argc, argv);

    return opts;
}
