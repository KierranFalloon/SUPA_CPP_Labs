/**
 * @file HelperFunctions.cpp
 * @author Kierran Falloon (kierran.falloon@strath.ac.uk)
 * @version 1.0
 * @date 26-11-2023
 * @headerfile HelperFunctions.h
 */

#include <iostream>
#include <vector>
#include <array>
#include <stdio.h>
#include "CustomFunctions.h"

using namespace std;

/**
 * @brief Prints authorship information upon program launch.
 * It also provides instructions on how to launch the program with a file path as an argument.
 */
void print_author_info() {
    string paragraph = 
    "\n\n----------------------------------------------------------------------------------------\n"
    "Data analysis program written by Kierran Falloon (kierran.falloon@strath.ac.uk).\n"
    "This program can read in a file of 2D data and perform some basic analysis on it.\n"
    "\nNote: Launch the program with a filepath as an argument to read in a file on launch.\n"
    "\t\t i.e. \"./build/AnalyseData.out ../../input2D_float.txt\"\n"
    "----------------------------------------------------------------------------------------\n\n";

    cout << paragraph << endl;
}

/**
 * @brief A sequence of characters representing a text value.
 * 
 * @return The (possibly updated) filepath.
 */
string handle_arguments(int argc, char *argv[]) {
    string filepath;
    string print_string;
        switch (argc) { 
        case 1: {
            break; // No args passed, since argv[0] is the program name
        }
        case 2: {
            print_string = "Filepath = " + string(argv[1]); 
            print_log(print_string, false);
            filepath = argv[1]; // argv[1] is the filepath
            break;
        }
        default: {
            string error = "Ignoring extra args: \n"; // More than one argument passed
            for (int i = 2; i < argc; i++) {
                error += "\t" + string(argv[i]) + "\n";
            }
            print_log(error, true);
            print_string = "Filepath = " + string(argv[1]);
            print_log(print_string, false);
            filepath = argv[1];
            break;
        }
    }
    return filepath;
}

/**
 * @brief Handles the user's choice and performs the corresponding action.
 * 
 * @param choice The user's choice.
 * @param data The data to be processed from file
 * @return The (possibly updated, if file has been changed) fileData structure.
 */
fileData handle_choice(int choice, fileData &file) {
    
    string print_string;
    switch (choice) {
        case 1: {
            print_log(file.data);
            break;
        }
        case 2: {
            vector<float> mag_data = calculate_magnitude(file.data);
            print_log(mag_data);
            write_file(file.filename, "mag", mag_data);
            break;
        }
        case 3: {
            string lsf = least_squares_fit(file.data);
            print_log(lsf, false);
            write_file(file.filename, "lsf", lsf);
            break;
        }
        case 4: {
            vector<float> powers = custom_power(file.data);
            print_log(powers);
            write_file(file.filename, "powers", powers);
            break;
        }
        case 5: {
            fileData file = read_file(""); // change filepath - "" signals to prompt user for input
            break;
        }
        case 6: {
            print_string = "Exiting program.";
            print_log(print_string, false);
            exit(0);
            break;
        }
        default: {
            print_string = "Invalid choice. Please try again.";
            print_log(print_string, true);
            break;
        }
    }
    return {file.filename, file.data};
}

/**
 * @brief Prompts the user to select an option from a menu and returns their choice.
 * 
 * @return The user's selected option as an integer for handle_choice().
 */
int select_choice() {

    int choice;
    string choices_paragraph = 
    "Processing options: \n\n"
    "\t1. Print lines from file\n"
    "\t2. Calculate magnitudes\n"
    "\t3. Fit data via Least Squares\n"
        "\t\t(with χ2 test)\n"
    "\t4. Produce x^y data\n"
        "\t\t(where y is rounded to the nearest integer)\n"
    "\t5. Change file\n"
    "\t6. Exit\n\n";

    print_log(choices_paragraph, false);
    string message = "Enter choice (1-6): ";
    choice = request_int(message);

    return choice;
}
