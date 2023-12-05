/**
 * @file HelperFunctions.cxx
 * @author Kierran Falloon (kierran.falloon@strath.ac.uk)
 * @version 1.0
 * @date 5-12-2023
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <array>

std::vector<double> read_file()
{

    std::ifstream inputfile; // Open file
    std::string filepath = "Outputs/data/MysteryData04113.txt";
    inputfile.open(filepath);

    if (inputfile.fail() || !inputfile.is_open())
    { // If file cannot be opened, print error message and exit
        std::cout << "Could not open file " + filepath + "" << std::endl;
        exit(1);
    }
    else
    { // If file is opened successfully, print success message
        std::cout << "File " + filepath + " opened successfully." << std::endl;
    }

    std::vector<double> data; // File data: dynamic data structure of form [ [ x, y ], [ x, y ], ... ]
    std::string line;

    while (getline(inputfile, line))
    { // Read file line by line

        double x = std::stod(line); // convert string to double
        data.push_back(x);          // add to data std::vector
    }

    inputfile.close(); // Close file

    std::cout << "File " + filepath + " read successfully." << std::endl;
    std::cout << "Number of lines read: " + std::to_string(data.size()) + "\n"
              << std::endl;

    return data;
}

std::array<double,2> data_range(std::vector<double> data) {
    std::array<double,2> data_range;
    double min = data[0];
    double max = data[0];
    for (int i = 0; i < data.size(); i++)
    {
        if (data[i] < min)
        {
            min = data[i];
        }
        if (data[i] > max)
        {
            max = data[i];
        }
    }
    data_range[0] = min;
    data_range[1] = max;
    return data_range;
}