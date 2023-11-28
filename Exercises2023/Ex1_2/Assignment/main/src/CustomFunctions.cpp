/**
 * @file CustomFunctions.cpp
 * @author Kierran Falloon (kierran.falloon@strath.ac.uk)
 * @version 1.0
 * @date 26-11-2023
 * @headerfile CustomFunctions.h
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <cmath>
#include <functional>

using namespace std;

/**
 * @brief Prints the log message to the console.
 * 
 * @param log The log message to be printed.
 * @param error Indicates whether the log is an error message or not.
 */
void print_log(string &log, bool error) {
    if (error) {
        cerr << "Error: " << log << endl; // print to cerr for error messages
        cerr << endl; 
    } else {
        cout << "Log: " << log << endl; // print to cout for normal messages
        cout << endl; // new line for readability
    }
}

/**
 * @brief Requests user input for a string value.
 * 
 * @param prompt The prompt message to display to the user.
 * @return The string value entered by the user.
 */
string request_string(string prompt) {
    string input;
    cout << prompt, cin >> input;
    if (cin.fail()) { // robustify input
        string error = "Invalid input. Please enter a valid string.";
        print_log(error, true);
        cin.clear(); // clear error flag so future I/O operations work correctly
        cin.ignore(10000, '\n'); // skip to next newline ignoring up to 10000 characters to avoid parse errors
        input = request_string(prompt); // recursive call
    }
    return input;
}

/**
 * @brief Requests user input for a string value.
 * 
 * @param prompt The prompt message to display to the user.
 * @return The integer value entered by the user.
 * @overload request_string(string prompt)
 */
int request_int(string prompt) {
    int input;
    cout << prompt, cin >> input;
    if (cin.fail()) { // robustify input
        string error = "Invalid input. Please enter an integer.";
        print_log(error, true);
        cin.clear(); // clear error flag so future I/O operations work correctly
        cin.ignore(10000, '\n'); // skip to next newline ignoring up to 10000 characters to avoid parse errors
        input = request_int(prompt); // recursive call
    }
    return input;
}

/**
 * @brief Prints a float to console.
 * 
 * @param log The float value to be printed.
 * @overload print_log(string &log)
 */
void print_log(float &log) {
    cout << "Log: " << log << endl; // print to cout for normal messages
    cout << endl;
}

/**
 * @brief Prints a specified number of lines from a vector of float values to console.
 * 
 * @param log_vec The vector of arrays containing the data to be printed.
 * @overload print_log(string &log)
 */
void print_log(vector<float> &log_vec) {
    const int size = log_vec.size(); // size of vector
    int n; // number of lines to print
    string print_string = "Enter number of lines to print out of " + to_string(size) + ": ";
    n = request_int(print_string); // request user input

    if (n == 0) {
        return; // exit function if lines to print = 0
    } else if (n > size) { // if lines to print > size of data, print error message and default to 5 lines
        print_string = "n (" + to_string(n) + ") is greater than the number of lines (" + to_string(size) + ") in the file.\nDefaulting to 5 lines.";
        print_log(print_string, true);
        n = 5;
    }

    for (int i = 0; i < n; i++) {
        cout << "Line " << i+1 << ": " << log_vec[i] << endl; // print each line
    }
    cout << endl; // new line for readability
}

/**
 * @brief Prints a specified number of lines from a vector of arrays to console.
 * 
 * @param log_vec The vector of arrays containing the data to be printed.
 * @overload print_log(string &log)
 */
void print_log(vector<array<double,2>> &log_vec) {
    const int size = log_vec.size(); // size of vector
    int n; // number of lines to print
    string print_string = "Enter number of lines to print out of " + to_string(size) + ": ";
    n = request_int(print_string); // request user input

    if (n == 0) {
        return; // exit function if lines to print = 0
    } else if (n > size) { // if lines to print > size of data, print error message and default to 5 lines
        print_string = "n (" + to_string(n) + ") is greater than the number of lines (" + to_string(size) + ") in the file.\nDefaulting to 5 lines.";
        print_log(print_string, true);
        n = 5;
    }

    for (int i = 0; i < n; i++) {
        cout << "Line " << i+1 << ": " << log_vec[i][0] << ", " << log_vec[i][1] << endl; // print each line as x, y
    }
    cout << endl; // new line for readability
}

/**
 * @brief Struct to store file data.
 * 
 * This struct is used to store file data, including the filename for dynamically naming output files
 * and the data itself, which is a dynamic data structure of form [ [ x, y ], [ x, y ], ... ].
 */
struct fileData { // Struct to store file data
    string filename; // File name for dynamically naming output files
    vector <array<double, 2>> data; // File data: dynamic data structure of form [ [ x, y ], [ x, y ], ... ]
};

/**
 * @brief Reads data from a file and returns it as a vector of arrays.
 * Each array contains two elements: x and y coordinates.
 * 
 * @param filepath The path of the file to be read (relative allowed).
 * @return fileData struct containing the file name and data.
 */
fileData read_file(string filepath){

    string print_string;

    if (filepath == "") { // If filepath is empty, prompt user for input
        print_string = "Enter filepath: ";
        filepath = request_string(print_string);
    }

    ifstream inputfile; // Open file
    inputfile.open(filepath);

    if (inputfile.fail() || !inputfile.is_open()) { // If file cannot be opened, print error message and exit
        print_string = "Could not open file " + filepath + "";
        print_log(print_string, true);
        exit(1);
    } else { // If file is opened successfully, print success message
        print_string = "File " + filepath + " opened successfully.";
        print_log(print_string, false);
    }

    vector <array<double, 2>> data; // File data: dynamic data structure of form [ [ x, y ], [ x, y ], ... ]
    string line;

    while (getline(inputfile, line)) { // Read file line by line
        if (line == "x,y") {
            continue; // Ignore header
        } else {
            // unpack line into x and y using comma delimiter
            string x_str = line.substr(0, line.find(","));
            string y_str = line.substr(line.find(",") + 1, line.length());
            
            double x = stod(x_str);  // convert string to double
            double y = stod(y_str);

            array<double, 2> xy = {x, y}; // pack into [x,y]
            data.push_back(xy); // add to data vector
        }
    }
    inputfile.close(); // Close file

    print_string = "File " + filepath + " read successfully.";
    print_log(print_string, false);

    print_string = "Number of lines read: " + to_string(data.size()) + "\n";
    print_log(print_string, false);

    return {filepath, data}; // Return struct
}

/**
 * @brief Calculates the magnitude of each vector in the given data.
 * 
 * @param data The vector of 2D arrays representing the data from read_file().
 * @return A vector of floats representing the magnitudes of the vectors.
 */
vector<float> calculate_magnitude(vector <array<double, 2>> &data) {
    const int size = data.size(); // size of data vector
    vector<float> mag_data; // initialise new data vector

    float x, y;
    for (int i = 0; i < size; i++) {
        x = data[i][0]; // unpack data
        y = data[i][1];
        double mag = sqrt(x*x + y*y); // magnitude = sqrt(x^2 + y^2)
        mag_data.push_back(mag); // add to new data vector
    }

    return mag_data;
}


/**
 * @brief Calculates the chi-squared value for a given set of data points and a linear fit.
 * 
 * @param data The vector of data points, where each element is an array of size 2 representing (x, y) coordinates.
 * @param size The size of the data vector.
 * @param m The gradient of the linear fit.
 * @param c The y-intercept of the linear fit.
 * @return The reduced chi-squared value.
 */
float chi_squared_fit(vector <array<double, 2>> data, const int size, float m, float c) {

    int rows = data.size(); // number of rows in data vector
    int cols = data[0].size(); // number of columns in data vector

    int NDF = rows - cols; // ν = n − m equals the number of observations n minus the number of fitted parameters m. 

    string message = "Number of degrees of freedom (ν) = " + to_string(NDF);
    print_log(message, false);

    // Prompt user for error data for extra generality
    message = "Default error file format is ../../error2D_float.txt.\n\tCustom error data? (y/n): ";
    string choice = request_string(message);
    string error_file = "../../error2D_float.txt";

    if (choice == "y" || choice == "Y" || choice == "yes" || choice == "Yes") {
        message = "Enter filepath for error data: ";
        error_file = request_string(message);
    } else if (choice == "n" || choice == "N" || choice == "no" || choice == "No") {
        message = "Defaulting error data.";
        print_log(message, false);
    } else {
        message = "Invalid choice. Defaulting error data.";
        print_log(message, true);
    }

    fileData error_data = read_file(error_file); // read error data file
    const int err_size = error_data.data.size();

    if (size != err_size) { // check that size of data and error data vectors match
        string error = "Size of data and error data vectors do not match.";
        print_log(error, true);
        exit(1);
    }

    float chi_squared = 0; // initialise chi-squared value

    float x, y, y_err, x_err, y_fit; // initialise variables

    for (int i = 0; i < size; i++) { // loop through data vector
        x = data[i][0]; 
        y = data[i][1]; 
        y_err = error_data.data[i][1]; // get y error from error data vector
        x_err = m*error_data.data[i][0];  // get x error of fit using gradient
        y_fit = m*x + c; // calculate y-value for given x-value using linear fit

        chi_squared += ( (y-y_fit)*(y-y_fit) ) / ( (y_err*y_err) + (x_err*x_err) ); // calculate chi-squared value
    }

    float reduced_chi_squared = chi_squared/NDF; // calculate reduced chi-squared value

    return reduced_chi_squared;
}

/**
 * @brief Calculates the least squares fit for a given set of data points, given by NΣxy - ΣxΣy / NΣx^2 - (Σx)^2
 * 
 * @param data The vector of data points, where each data point is represented as an array of size 2.
 *             The first element of the array represents the x-coordinate, and the second element represents the y-coordinate.
 * @return The equation of the least squares fit in the form "y = mx + c", where m is the gradient and c is the y-intercept.
 */
string least_squares_fit(vector <array<double, 2>> &data) {
    
    const int size = data.size();
    double sum_x, sum_y, sum_x_y, sum_x_squared = 0; // initialise variables

    for (int i = 0; i < size; i++) { // loop through data vector
        sum_x += data[i][0]; // sum x-values through the loop
        sum_y += data[i][1]; // sum y-values through the loop
        sum_x_y += data[i][0]*data[i][1]; // sum x*y-values through the loop
        sum_x_squared += data[i][0]*data[i][0]; // sum x^2-values through the loop
    }

    float m = (size*sum_x_y - sum_x*sum_y) / (size*sum_x_squared - sum_x*sum_x); // calculate gradient
    float c = (sum_y - m*sum_x) / size; // calculate y-intercept

    float chi = chi_squared_fit(data, size, m, c); // calculate reduced chi-squared value

    string lsf = "y = " + to_string(m) + "x + " + to_string(c); // strings for printing and file output
    string lsf_file_format = 
        "Least Squares Fit:\n"
        "\t" + lsf + "\n\n"
        "Reduced χ2 (chi-squared) = " + to_string(chi) + "\n\n"
        "Fit parameters:\n"
        "\tm = " + to_string(m) + "\n"
        "\tc = " + to_string(c); // format string for file output

    return lsf_file_format; // return string
}

/**
 * @brief Calculates the power x^y for each element [xi, yi] in the given data vector using recursive calls to a function.
 * This is done using the formula x^y = e^(y*ln(x)), where y is rounded to the nearest integer.
 *
 * @param data The vector of arrays containing the data elements.
 * @return A vector of floats.
 */
vector<float> custom_power(vector <array<double, 2>> &data) {
    float x;
    int y;
    const int size = data.size(); // size of data vector

    auto compute_power = [](float x, int y) {
        return exp(y * log(x)); // x^y => ln(x^y) => y*ln(x) => e^(y*ln(x))
    };

    // create new data vector
    vector<float> x_pow_y;

    function<void(int)> compute_recursive; // recursive function
    compute_recursive = [&](int i) {
        if (i < size) { // stop calling function when end of data vector is reached
            x = data[i][0]; // unpack data
            y = round(data[i][1]); // round y to nearest integer
            x_pow_y.push_back(compute_power(x, y)); // add result to new data vector
            compute_recursive(i + 1); // recursive call
        }
    };

    compute_recursive(0); // initialise recursion

    return x_pow_y;
}

/**
 * @brief Removes the file extension from a given filename.
 * 
 * @param filename The filename from which to remove the extension.
 * @return The filename without the extension.
 */
string remove_extension(string filename) {
    size_t last_dot = filename.rfind("."); // Find last dot in filename
    if (last_dot == string::npos) // No dot found
        return filename;
    return filename.substr(0, last_dot); // Return filename without extension
};

/**
 * @brief Writes the given data to a file with the specified filename and extension.
 * The file is created in the same directory as the input filename, with the extension appended to the filename.
 * If the file already exists, its contents will be overwritten.
 *
 * @param filename The name of the file to write to.
 * @param extension The extension to append to the filename.
 * @param data The data to write to the file.
 */
void write_file(string filename, string extension, string data) {

    string filename_path = remove_extension(filename); // remove extension from filename
    string out_file = filename_path + "_" + extension + ".txt"; // append new extension to filename

    ofstream outfile; // create output file stream
    outfile.open(out_file); // open file
    outfile << data; // write data to file (this is only used for writing the least squares fit, so no header needed)
    outfile.close(); // close file

    string success_msg = "File " + out_file + " written successfully.";
    print_log(success_msg, false);
}

/**
 * @brief Writes the data to a file with the given filename and extension.
 * The file is created in the same directory as the input filename.
 * The data is written as a sequence of floats, with each float on a new line.
 *
 * @param filename The name of the file to write to.
 * @param extension The extension to append to the filename.
 * @param data The vector of floats to write to the file.
 * @overload write_file(string filename, string extension, string data)
 */
void write_file(string filename, string extension, vector<float> &data) {

    const int size = data.size(); // size of data vector
    string filename_path = remove_extension(filename); // remove extension from filename
    string out_file = filename_path + "_" + extension + ".txt"; // append new extension to filename

    ofstream outfile; // create output file stream
    outfile.open(out_file); // open file
    outfile << extension << endl; // write extension to file as a header 
    for (int i = 0; i < size; i++) { 
        outfile << data[i] << endl; // write data to file line by line
    }
    outfile.close(); // close file

    string success_msg = "File " + out_file + " written successfully.";
    print_log(success_msg, false); 
}
