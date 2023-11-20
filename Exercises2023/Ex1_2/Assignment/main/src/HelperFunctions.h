#ifndef HELPERFUNCTIONS_H
#define HELPERFUNCTIONS_H

#include <iostream>
#include <vector>
#include <array>
#include <string>

void print_author_info();
std::string handle_arguments(int, char**);
std::vector<std::array<double, 2>> handle_choice(int, std::vector<std::array<double, 2>> &);
int select_choice();

#endif // HELPERFUNCTIONS_H
