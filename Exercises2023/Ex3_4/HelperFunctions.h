/**
 * @file HelperFunctions.h
 * @author Kierran Falloon (kierran.falloon@strath.ac.uk)
 * @date 05-12-2023
 */

#include <iostream>
#include <vector>
#include <array>

#pragma once

std::vector<double> read_file();
std::array<int,2> data_range(std::vector<double>);
double get_mean(std::vector<double>);
double stdev(std::vector<double>, double);