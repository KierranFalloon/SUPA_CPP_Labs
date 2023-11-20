/**
 * @file HelperFunctions.cpp
 * @author Kierran Falloon (kierran.falloon@strath.ac.uk)
 * @version 1.0
 * @date 25-11-2023
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
    "\t\t i.e. \"./build/AnalyseData.exe ./data/data.txt\"\n"
    "----------------------------------------------------------------------------------------\n\n";

    print_log(paragraph);
}

/**
 * @brief A sequence of characters representing a text value.
 * 
 * @return The (possibly updated) filepath.
 */
string handle_arguments(int argc, char *argv[]) {
    string filepath;
        switch (argc) {
        case 1: {
            break;
        }
        case 2: {
            cout << "Filepath = " << argv[1] << "\n" << endl;
            filepath = argv[1];
            break;
        }
        default: {
            cerr << "Ignoring extra args: " << endl;
            for (int i = 2; i < argc; i++) {
                cerr << "Arg " << i << " = " << argv[i] << endl;
        }
            cout << "Filepath = " << argv[1] << "\n" << endl;
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
 * @return The (possibly updated, if file has been changed) data vector.
 */
vector <array<double, 2>> handle_choice(int choice, vector <array<double, 2>> &data) {
    
    switch (choice) {
        case 1: {
            print_log(data);
            break;
        }
        case 2: {
            vector<float> mag_data = calculate_magnitude(data);
            print_log(mag_data);
            break;
        }
        case 3: {
            string lsf = least_squares_fit(data);
            print_log(lsf);
            break;
        }
        case 4: {
            vector<float> powers = custom_power(data);
            print_log(powers);
            break;
        }
        case 5: {
            data = read_file(""); // change filepath - "" signals to prompt user for input
            break;
        }
        case 6: {
            cout << "Exiting program.\n\n";
            exit(0);
            break;
        }
        default: {
            cerr << "Error: Invalid choice.\n\n";
            exit(1);
            break;
        }
    }
    return data;
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

    print_log(choices_paragraph);
    cout << "Enter choice: ", cin >> choice;
    cout << endl;

    return choice;
}