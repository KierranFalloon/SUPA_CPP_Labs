/**
 * @file PiHelperFunctions.h
 * @author Kierran Falloon (kierran.falloon@strath.ac.uk)
 * @date 07-12-2023
 */

#include <array>
#include <vector>

#pragma once

struct Args {
    double radius;
    int nRandomPoints;
};

Args handle_arguments(int argc, char *argv[]); // Unpack arguments into Args struct
std::vector<std::array<double, 2>> generate_random(double radius, int nRandomPoints); // Generate nRandomPoints random points within a square of side length 2*radius
bool is_in_circle(std::array<double, 2> point, double radius); // Check if a point is within a circle of radius radius
double error(double pi); // Calculate the percentage error of the estimate of pi