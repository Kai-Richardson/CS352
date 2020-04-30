use std::env;
use std::thread;
use std::time::{Duration, SystemTime};
use rand::prelude::*;

/// Print usage message and return error result
fn usage() -> Result<(),()> {
    println!("usage: ./retirement_par <annual_contribution> <interest_rate> <num_years> <std_deviation> <num_iterations> <num_threads>");
    Err(())
}

/// Throw away specific error results from parse and just print usage
fn parse<T : std::str::FromStr>(s: &String) -> Result<T,()> {
    match s.parse::<T>() {
        Ok(val) => Ok(val),
        Err(_) => { usage()?; Err(()) }
    }
}

fn main() -> Result<(),()> {
    //
    // Start wall clock & CPU clock
    //
    let wall_start = SystemTime::now();
    let cpu_start = cpu::Instant::now();

    //
    // Read simulation parameters from command line
    //

    let annual_contribution: f64; // Average annual contribution to retirement fund
    let avg_interest_rate: f64;   // Average interest rate
    let num_years: i32;           // Number of contribution years
    let std_deviation: f64;       // Standard deviation of interest rate
    let num_iterations: usize;    // Number of simulations to run
    let num_threads: usize;       // Number of threads to use

    let args : Vec<String> = env::args().collect();
    if args.len() != 7 { usage()?; }
    annual_contribution = parse(&args[1])?;
    avg_interest_rate = parse(&args[2])?;
    num_years = parse(&args[3])?;
    std_deviation = parse(&args[4])?;
    num_iterations = parse(&args[5])?;
    num_threads = parse(&args[6])?;

    //
    // Set up PRNG for Monte Carlo simulation
    //
    
    // thread-local pseudo-random number generator, automatically seeded
    let mut rand = thread_rng();
    // normal (bell-curve) distribution with mean of average interest rate, standard 
    // deviation from parameter
    let annual_interest_rate = 
        rand_distr::Normal::new(avg_interest_rate, std_deviation).unwrap();

    //
    // Run simulation
    //

    let mut simulation_results = Vec::with_capacity(num_iterations);
    for _ in 0..num_iterations {
        // initialize total savings to nothing
        let mut total_savings = 0.0;
        // calculate each year's savings, plus (randomized) interest
        for _ in 0..num_years {
            total_savings += annual_contribution;
            total_savings += total_savings * rand.sample(annual_interest_rate);
        }
        // save simulation results
        simulation_results.push(total_savings);
    }

    //
    // Present results
    //

    // sort results to calculate median/percentile
    simulation_results.sort_by(|a, b| a.partial_cmp(b).unwrap());
    // one quarter of the results
    let quartile = num_iterations/4;
    // print quartiles
    println!("25th percentile: {:.2}", simulation_results[quartile]);
    println!("         median: {:.2}", simulation_results[quartile*2]);
    println!("75th percentile: {:.2}", simulation_results[quartile*3]);

    //
    // Print timing results
    //
    let wall_end = SystemTime::now();
    let cpu_end = cpu::Instant::now();

    let wall_time = match wall_end.duration_since(wall_start) {
        Ok(dur) => dur,
        // time went backwards; assume just too little to measure
        Err(_) => Duration::from_secs(0)
    };
    let cpu_time = cpu_end.duration_since(cpu_start);
    
    println!("\n--{}-way Parallel--", num_threads);
    println!("wall: {}.{}", wall_time.as_secs(), wall_time.subsec_millis()/10);
    println!(" CPU: {}.{}", cpu_time.as_secs(), cpu_time.subsec_millis()/10);

    Ok(())
}
