#ifndef CUSTOM_FUNCTIONS_H
#define CUSTOM_FUNCTIONS_H

#include <iostream>
#include <vector>
#include <array>

std::vector <std::array<double, 2>> read_file(std::string);
std::vector<float> calculate_magnitude(std::vector <std::array<double, 2>>);
std::string least_squares_fit(std::vector <std::array<double, 2>>);
std::vector<float> custom_power(std::vector <std::array<double, 2>>);
void print_log(std::string &);
void print_log(float &);
void print_log(std::vector<float> &);
void print_log(std::vector<std::array<double,2>> &);

#endif
