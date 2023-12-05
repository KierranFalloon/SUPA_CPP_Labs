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
std::array<double,2> data_range(std::vector<double>);
