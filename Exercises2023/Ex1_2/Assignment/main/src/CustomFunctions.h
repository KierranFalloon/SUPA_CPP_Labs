#ifndef CUSTOM_FUNCTIONS_H
#define CUSTOM_FUNCTIONS_H

#include <iostream>
#include <vector>
#include <array>

std::string request_string(std::string);
int request_int(std::string);
void print_log(std::string &, bool = false);
void print_log(float &);
void print_log(std::vector<float> &);
void print_log(std::vector<std::array<double,2>> &);

struct fileData {
    std::string filename;
    std::vector <std::array<double, 2>> data;
};

fileData read_file(std::string);
std::vector<float> calculate_magnitude(std::vector<std::array<double, 2>>&);
std::string least_squares_fit(std::vector<std::array<double, 2>>&);
std::vector<float> custom_power(std::vector<std::array<double, 2>>&);

void write_file(std::string, std::string, std::string);
void write_file(std::string, std::string, std::vector<float>&);

#endif
