/**
 * @file HelperFunctions.h
 * @author Kierran Falloon (kierran.falloon@strath.ac.uk)
 * @date 5-12-2023
 */

#pragma once

#include <iostream>
#include <vector>
#include <array>

std::vector<double> read_file();
std::array<int,2> data_range(std::vector<double>);
double get_mean(std::vector<double>);
double stdev(std::vector<double>, double);