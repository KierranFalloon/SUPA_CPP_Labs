/**
 * @file main.cxx
 * @author Kierran Falloon (kierran.falloon@strath.ac.uk)
 * @version 1.0
 * @date 07-12-2023
*/

#include <iostream>
#include <vector>
#include <array>
#include <cmath>

#include "PiHelperFunctions.h"

/**
 * @brief Main function. Called via ./EstimatePi
 * Estimates pi by comparing the area of a circle to the area of a square through monte carlo sampling.
 * 
 * π = 4 * A_circle / A_square
 * 
 * Where A_circle and A_square can be approximated by counting the number of points in each shape, for a high enough number of points.
 * 
 * @param argc Number of arguments passed to the program.
 * @param argv Array of arguments passed to the program.
 * 
 * @return int Exit code.
 */
int main(int argc, char *argv[]) {

  // Get args
  Args args = handle_arguments(argc, argv);

  // Generate random points
  std::vector<std::array<double, 2>> random = generate_random(args.radius, args.nRandomPoints);

  // Count points in circle
  int nInCircle = 0;
  for (auto point : random) {
    if (is_in_circle(point, args.radius)) {
      nInCircle++;
    }
  }

  std::cout << "LOG: Number of points in circle = " << nInCircle << " out of " << args.nRandomPoints << std::endl;

  // Calculate pi and error
  double pi = 4.0 * nInCircle / args.nRandomPoints;
  double piError = error(pi);

  // Log results
  std::cout << std::fixed; // Show trailing zeros
  std::cout.precision(10); // Set precision to 10 decimal places
  std::cout << "LOG: Estimated π (pi) = " << pi << std::endl;
  std::cout << "LOG: Percentage Error = " << piError << "%" << std::endl;
  std::cout << std::endl;

  return 0;

};