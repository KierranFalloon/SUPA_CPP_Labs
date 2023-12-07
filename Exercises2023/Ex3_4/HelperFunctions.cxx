/**
 * @file HelperFunctions.cxx
 * @author Kierran Falloon (kierran.falloon@strath.ac.uk)
 * @date 05-12-2023
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <cmath>

// read file
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

// get integer bounds of the data
std::array<int,2> data_range(std::vector<double> data) {
  std::array<int,2> data_range;
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
  // bounds slightly wider than data range
  data_range[0] = std::floor(min) - 2;
  data_range[1] = std::ceil(max) + 2;
  return data_range;
}

// return mean of data
double get_mean(std::vector<double> data)
{
  double sum = 0;
  for (int i = 0; i < data.size(); i++)
  {
    sum += data[i];
  }
  return sum / data.size();
}

// return standard deviation of data
double stdev(std::vector<double> data, double mean_value)
{
  double sum = 0;
  for (int i = 0; i < data.size(); i++)
  {
    sum += pow(data[i] - mean_value, 2);
  }
  return sqrt(sum / data.size());
}