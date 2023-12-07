/**
 * @file Test.cxx
 * @author Kierran Falloon (kierran.falloon@strath.ac.uk)
 * @version 1.0
 * @date 5-12-2023
 */

#include "FiniteFunctions.h"
#include <iostream>
#include "HelperFunctions.h"
#include "CustomFunctions.h"

template <typename T>
void processFunction(T& function, std::vector<double>& data) {
  function.integral(1000); // Calculate integral using N intermediate sample points
  function.plotFunction(); // Plot function
  function.plotData(data, 50, true); // Plot data
  function.printInfo(); // Dump info

  // Get Metropolis-Hasings samples and plot them on the same graph
  MetropolisHastings metropolisFunc(&function, 10000); // Create Metropolis func with nSample points
  metropolisFunc.printInfo(); // Log info
  
  std::vector<double> metropolisData = metropolisFunc.sample(); // Gather samples 
  function.plotData(metropolisData, 100, false); // Plot sampled points
}

int main()
{
  // Read data from file
  std::vector<double> data = read_file();

  // Find range of data, mean and standard deviation for more accurate graphical comparisons
  std::array<int,2> min_max = data_range(data);
  float min = min_max[0];
  float max = min_max[1];
  double mean = get_mean(data);
  double standard_dev = stdev(data, mean);

  FiniteFunction function(min, max, "./Outputs/png/Inv-X-Squared.png");
  processFunction(function, data);

  // mu, sigma
  NormalDistributionFunction normalFunc(min, max, "./Outputs/png/Normal-Dist.png", mean, standard_dev);
  processFunction(normalFunc, data);

  // x0, gamma
  CauchyLorentzDistribution cauchyFunc(min, max, "./Outputs/png/Cauchy-Lorentz.png", mean, 0.80);
  processFunction(cauchyFunc, data);

  // xbar, sigma, alpha, n
  NegativeCrystalBallDistribution crystalFunc(min, max, "./Outputs/png/Negative-Crystal.png", mean, standard_dev, 2.0, 2.0);
  processFunction(crystalFunc, data);

  return 0;
};