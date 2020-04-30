#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <ios>
#include <iostream>
#include <random>
#include <string>
#include <vector>

/// Quit with usage message
void usage() {
    std::cerr << "usage: ./retirement <annual_contribution> <interest_rate> <num_years> <std_deviation> <num_iterations>" << std::endl;
    std::exit(1);
}

int main(int argc, char** argv) {
    //
    // Start wall clock & CPU clock
    //

    // get starting wall-clock time
    std::chrono::time_point<std::chrono::system_clock> wall_start = 
        std::chrono::system_clock::now();
    // get starting CPU time
    std::clock_t cpu_start = std::clock();

    //
    // Read simulation parameters from command line
    //
    
    double annual_contribution; // Average annual contribution to retirement fund
    double avg_interest_rate;   // Average interest rate
    int num_years;              // Number of contribution years
    double std_deviation;       // Standard deviation of interest rate
    long num_iterations;        // Number of simulations to run

    if ( argc != 6 ) { usage(); }
    try {
        annual_contribution = std::stod(argv[1]);
        avg_interest_rate = std::stod(argv[2]);
        num_years = std::stoi(argv[3]);
        std_deviation = std::stod(argv[4]);
        num_iterations = std::stol(argv[5]);
    } catch (...) { usage(); }

    //
    // Set up PRNG for Monte Carlo simulation
    //

    // hardware randomness source (slow)
    std::random_device get_random_seed{};
    // pseudo-random number generator (fast); seed based on random device
    std::mt19937 rand{};
    rand.seed( get_random_seed() );
    // normal (bell-curve) distribution with mean of average interest rate, standard 
    // deviation from parameter
    std::normal_distribution<double> annual_interest_rate{avg_interest_rate, std_deviation};

    //
    // Run simulation
    //

    std::vector<double> simulation_results;
    simulation_results.reserve(num_iterations);
    for (long iteration = 0; iteration < num_iterations; ++iteration) {
        // initialize total savings to nothing
        double total_savings = 0.0;
        // calculate each year's savings, plus (randomized) interest
        for (int year = 0; year < num_years; ++year) {
            total_savings += annual_contribution;
            total_savings += total_savings * annual_interest_rate(rand);
        }
        // save simulation results
        simulation_results.push_back(total_savings);
    }

    //
    // Present results
    //

    // sort results to calculate median/percentile
    std::sort(simulation_results.begin(), simulation_results.end());
    // one quarter of the results
    long quartile = num_iterations/4;
    // set output stream to not use scientific notation, round to 2 decimal places
    std::cout << std::fixed << std::setprecision(2);
    // print quartiles
    std::cout << "25th percentile: " << simulation_results[quartile] << "\n"
              << "         median: " << simulation_results[quartile*2] << "\n"
              << "75th percentile: " << simulation_results[quartile*3] << std::endl;
    
    //
    // Print timing results
    //

    // get ending wall-clock time
    std::chrono::time_point<std::chrono::system_clock> wall_end = std::chrono::system_clock::now();
    // get ending CPU time
    std::clock_t cpu_end = std::clock();
    
    // compute number of seconds in each
    std::chrono::duration<double> wall_time = wall_end - wall_start;
    double cpu_time = (cpu_end - cpu_start) / (double)CLOCKS_PER_SEC;

    // print results
    std::cout << "\n--Sequential--\n"
              << "wall: " << wall_time.count() << " sec\n"
              << " CPU: " << cpu_time << " sec" << std::endl;
}