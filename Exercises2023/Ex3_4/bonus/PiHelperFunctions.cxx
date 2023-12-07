/**
 * @file PiHelperFunctions.cxx
 * @author Kierran Falloon (kierran.falloon@strath.ac.uk)
 * @version 1.0
 * @date 07-12-2023
 * @headerfile PiHelperFunctions.h
 */

#include <iostream>
#include <vector>
#include <array>
#include <stdio.h>
#include <random>

/**
 * @brief Struct to hold the arguments for EstimatePi.
 * 
 * @param radius Radius of the circle.
 * @param nRandomPoints Number of random points to generate.
 * 
 */
struct Args {
  double radius;
  int nRandomPoints;
};

/**
 * @brief Handles arguments.
 * 
 * @return Args struct containing the radius and number of random points.
 */
Args handle_arguments(int argc, char *argv[]) {
  std::cout << std::endl;
  double radius = 1.0;
  int nRandomPoints = 1000;

  switch (argc) {
  case 1: {
    std::cout << "LOG: Assuming arguments are: radius = 1, nRandomPoints = 1000" << std::endl;
    break; // No args passed, since argv[0] is the program name
    }
  case 2: {
    std::cout << "LOG: Arg Radius = " << argv[1] << ". Setting nRandomPoints = 1000" << std::endl;
    radius = std::stod(argv[1]);
    break;
    }
  case 3: {
    std::cout << "LOG: Arg Radius = " << argv[1] << ", Arg nRandomPoints = " << argv[2] << std::endl;
    radius = std::stod(argv[1]);
    nRandomPoints = std::stoi(argv[2]);
    break;
    }
  default: {
    std::cout << "LOG: Too many arguments passed. Call with ./EstimatePi [radius = 1.0] [nRandomPoints = 1000]" << std::endl;
    exit(1);
    break;
    }
  }

  return {radius, nRandomPoints};
}

/**
 * @brief Generates a vector of arrays containing nRandomPoints random coordinates within a square of sides 2*radius.
 *
 * @param radius The radius of the circle.
 * @param nRandomPoints The number of random points to generate.
 * @return A vector of arrays, where each array contains the x and y coordinates of a random point.
 */
std::vector<std::array<double, 2>> generate_random(double radius, int nRandomPoints) {
  std::vector<std::array<double, 2>> random;
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<> dis(-radius, radius);

  for (int i = 0; i < nRandomPoints; i++) {
    random.push_back({dis(gen), dis(gen)});
  }

  return random;
}

/**
 * @brief Checks if a given point is inside a circle.
 * 
 * @param point The coordinates of the point.
 * @param radius The radius of the circle.
 * @return True if the point is inside the circle, false otherwise.
 */
bool is_in_circle(std::array<double, 2> point, double radius) {
  // x^2 + y^2 = r^2 is the equation of a circle
  // if x^2 + y^2 < r^2 then the point is inside the circle
  return (point[0] * point[0] + point[1] * point[1]) < radius * radius;
}

/**
 * @brief Calculates the percentage error between the given value of pi and the actual value of pi.
 * 
 * @param pi The value of pi to calculate the error for.
 * @return The percentage error between the given value of pi and the actual value of pi.
 */
double error(double pi) {
  float m_pi = 3.14159265358979323846;

  std::cout << std::endl;
  std::cout << std::fixed;
  std::cout.precision(10);
  std::cout << "LOG: Actual π (pi)    = " << m_pi << std::endl;

  return std::abs(pi - m_pi) / m_pi * 100.0;
}