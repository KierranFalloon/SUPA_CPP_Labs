/**
 * @file CustomFunctions.cpp
 * @author Kierran Falloon (kierran.falloon@strath.ac.uk)
 * @version 1.0
 * @date 25-11-2023
 * @headerfile CustomFunctions.h
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <cmath>

using namespace std;

struct fileData {
    string filename;
    vector <array<double, 2>> data;
};

/**
 * Reads data from a file and returns it as a vector of arrays.
 * Each array contains two elements: x and y coordinates.
 * 
 * @param filepath The path of the file to be read (relative allowed).
 * @return fileData struct containing the file name and data.
 */
fileData read_file(string filepath){

    if (filepath == "") { // If filepath is empty, prompt user for input
        cout << "Enter filepath: ", cin >> filepath;
    }

    ifstream file; // Open file
    file.open(filepath);

    if (file.fail() || !file.is_open()) {
        cerr << "Error: Could not open file " << filepath << endl;
        exit(1);
    } else {
        cout << "Log: File " << filepath << " opened successfully." << endl;
    }

    vector <array<double, 2>> data; // File data: dynamic data structure of form [ [ x, y ], [ x, y ], ... ]
    string line;

    while (getline(file, line)) {
        if (line == "x,y") {
            continue; // Ignore header
        } else {
            // unpack line into x and y using comma delimiter
            string x_str = line.substr(0, line.find(","));
            string y_str = line.substr(line.find(",") + 1, line.length());
            
            double x = stod(x_str);
            double y = stod(y_str);

            array<double, 2> xy = {x, y}; // pack into [x,y]
            data.push_back(xy); // add to data vector
        }
    }
    cout << "Log: File read successfully.\n\n" << endl;

    return {filepath, data};
}

/**
 * Calculates the magnitude of each vector in the given data.
 * 
 * @param data The vector of 2D arrays representing the data from read_file().
 * @return A vector of floats representing the magnitudes of the vectors.
 */
vector<float> calculate_magnitude(vector <array<double, 2>> &data) {
    const int size = data.size();
    vector<float> mag_data;

    for (int i = 0; i < size; i++) {
        double mag = sqrt(data[i][0]*data[i][0] + data[i][1]*data[i][1]);
        mag_data.push_back(mag);
    }
    cout << endl; // extra line for readability
    return mag_data;
}


/**
 * Calculates the chi-squared value for a given set of data points and a linear fit.
 * 
 * @param data The vector of data points, where each element is an array of size 2 representing (x, y) coordinates.
 * @param size The size of the data vector.
 * @param m The gradient of the linear fit.
 * @param c The y-intercept of the linear fit.
 * @return The reduced chi-squared value.
 */
float chi_squared_fit(vector <array<double, 2>> data, int size, float m, float c) {

    int rows = data.size();
    int cols = data[0].size();

    int NDF = (rows - 1) * (cols - 1);

    fileData error_data = read_file("../../error2D_float.txt");
    const int err_size = error_data.data.size();

    if (size != err_size) {
        cerr << "Error: Size of data and error data vectors do not match." << endl;
        exit(1);
    }

    float chi_squared = 0;

    float x, y, y_err, y_fit;

    for (int i = 0; i < size; i++) {
        x = data[i][0];
        y = data[i][1];
        y_err = error_data.data[i][1];
        y_fit = m*x + c;

        chi_squared += ( (y-y_fit)*(y-y_fit) ) / ( (y_err*y_err) );
    }

    float reduced_chi_squared = chi_squared/NDF;

    return reduced_chi_squared;
}

/**
 * Calculates the least squares fit for a given set of data points, given by NΣxy - ΣxΣy / NΣx^2 - (Σx)^2
 * 
 * @param data The vector of data points, where each data point is represented as an array of size 2.
 *             The first element of the array represents the x-coordinate, and the second element represents the y-coordinate.
 * @return The equation of the least squares fit in the form "y = mx + c", where m is the gradient and c is the y-intercept.
 */
string least_squares_fit(vector <array<double, 2>> &data) {
    
    int size = data.size();
    double sum_x, sum_y, sum_x_y, sum_x_squared = 0;

    for (int i = 0; i < size; i++) {
        sum_x += data[i][0];
        sum_y += data[i][1];
        sum_x_y += data[i][0]*data[i][1];
        sum_x_squared += data[i][0]*data[i][0];
    }

    float m = (size*sum_x_y - sum_x*sum_y) / (size*sum_x_squared - sum_x*sum_x);
    float c = (sum_y - m*sum_x) / size;

    float chi = chi_squared_fit(data, size, m, c);

    string lsf = "y = " + to_string(m) + "x + " + to_string(c);
    string lsf_file_format = 
        "Least Squares Fit:\n"
        "" + lsf + "\n\n"
        "Reduced χ2 (chi-squared) = " + to_string(chi) + "\n\n"
        "Fit parameters:\n"
        "m = " + to_string(m) + "\n"
        "c = " + to_string(c) + "\n";

    return lsf_file_format;
}

/**
 * Calculates the power x^y for each element [xi, yi] in the given data vector.
 * This is done using the formula x^y = e^(y*ln(x)), where y is rounded to the nearest integer.
 *
 * @param data The vector of arrays containing the data elements.
 * @return A vector of floats.
 */
vector<float> custom_power(vector <array<double, 2>> &data) {
    float x;
    int y;
    const int size = data.size();

    auto compute_power = [](float x, int y) {
        return exp(y * log(x));
    };

    // create new data vector
    vector<float> x_pow_y;
    for (int i = 0; i < size; i++) {
        x = data[i][0];
        y = round(data[i][1]);
        x_pow_y.push_back(compute_power(x, y));
    }

    return x_pow_y;
}

/**
 * Prints a string to console.
 * 
 * @param data The string to be printed.
 */
void print_log(string &log) {
    cout << log << endl;
    cout << endl;
}

/**
 * Prints a string to console.
 * 
 * @param data The float value to be printed.
 * 
 * @overload print_log(string &log)
 */
void print_log(float &log) {
    cout << log << endl;
    cout << endl;
}

/**
 * Prints a specified number of lines from a vector of float values to console.
 * 
 * @param data The vector of arrays containing the data to be printed.
 * 
 * @overload print_log(string &log)
 */
void print_log(vector<float> &log_vec) {
    const int size = log_vec.size();
    int n;
    cout << "Enter number of lines to print out of " << size <<": ", cin >> n;
    cout << endl;

    if (n == 0) {
        return;
    }

    if (n > size) {
        cerr << "\nError: n is greater than the number of lines ("<< size <<") in the file." << endl;
        cerr << "Defaulting to 5 lines.\n\n";
        n = 5;
    }

    for (int i = 0; i < n; i++) {
        cout << "Line " << i+1 << ": " << log_vec[i] << endl;
    }
    cout << endl;
}

/**
 * Prints a specified number of lines from a vector of arrays to console.
 * 
 * @param log_vec The vector of arrays containing the data to be printed.
 * 
 * @overload print_log(string &log)
 */
void print_log(vector<array<double,2>> &log_vec) {
    const int size = log_vec.size();
    int n;
    cout << "Enter number of lines to print out of " << size <<": ", cin >> n;
    cout << endl;

    if (n == 0) {
        return;
    }

    if (n > size) {
        cerr << "\nError: n is greater than the number of lines ("<< size <<") in the file." << endl;
        cerr << "Defaulting to 5 lines.\n\n";
        n = 5;
    }

    for (int i = 0; i < n; i++) {
        cout << "Line " << i+1 << ": " << log_vec[i][0] << ", " << log_vec[i][1] << endl;
    }
    cout << endl;
}

/**
 * @brief Removes the file extension from a given filename.
 * 
 * @param filename The filename from which to remove the extension.
 * @return The filename without the extension.
 */
string remove_extension(string filename) {
    size_t last_dot = filename.rfind(".");
    if (last_dot == string::npos) // No dot found
        return filename;
    return filename.substr(0, last_dot);
};

/**
 * Writes the given data to a file with the specified filename and extension.
 * The file is created in the same directory as the input filename, with the extension appended to the filename.
 * If the file already exists, its contents will be overwritten.
 *
 * @param filename The name of the file to write to.
 * @param extension The extension to append to the filename.
 * @param data The data to write to the file.
 */
void write_file(string filename, string extension, string data) {

    string filename_path = remove_extension(filename);
    string out_file = filename_path + "_" + extension + ".txt";

    ofstream myfile;
    myfile.open(out_file);
    myfile << data;
    myfile.close();

    string success_msg = "Log: File " + out_file + " written successfully.\n";
    print_log(success_msg);
}

/**
 * Writes the data to a file with the given filename and extension.
 * The file is created in the same directory as the input filename.
 * The data is written as a sequence of floats, with each float on a new line.
 *
 * @param filename The name of the file to write to.
 * @param extension The extension to append to the filename.
 * @param data The vector of floats to write to the file.
 * @overload write_file(string filename, string extension, string data)
 */
void write_file(string filename, string extension, vector<float> &data) {

    const int size = data.size();
    string filename_path = remove_extension(filename);
    string out_file = filename_path + "_" + extension + ".txt";

    ofstream myfile;
    myfile.open(out_file);
    myfile << extension << endl;
    for (int i = 0; i < size; i++) {
        myfile << data[i] << endl;
    }
    myfile.close();

    string success_msg = "Log: File " + out_file + " written successfully.\n";
    print_log(success_msg);
}