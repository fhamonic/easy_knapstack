#include <filesystem>
#include <iostream>

#include "unbounded_knapsack/branch_and_bound.hpp"

#include "utils/chrono.hpp"
#include "utils/instance_parsers.hpp"

namespace UnboundedKnapsack = fhamonic::unbounded_knapsack;

int main(int argc, const char * argv[]) {
    if(argc < 2) {
        std::cerr << "input requiered : <knapsack_instance_file>" << std::endl;
        return EXIT_FAILURE;
    }
    std::filesystem::path instance_path = argv[1];
    if(!std::filesystem::exists(instance_path)) {
        std::cerr << instance_path << ":"
                  << " File does not exists" << std::endl;
        return EXIT_FAILURE;
    }

    UnboundedKnapsack::Instance<int, int> instance =
        parse_unbounded_instance(instance_path);
    UnboundedKnapsack::BranchAndBound<int, int> solver;

    Chrono chrono;
    UnboundedKnapsack::Solution solution = solver.solve(instance);
    int time_us = chrono.timeUs();

    std::cout << solution.getValue() << " in " << time_us << " µs" << std::endl;

    return EXIT_SUCCESS;
}