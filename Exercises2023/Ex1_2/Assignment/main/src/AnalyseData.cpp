/**
 * @file AnalyseData.cpp
 * @author Kierran Falloon (kierran.falloon@strath.ac.uk)
 * @version 1.0
 * @date 25-11-2023
*/

#include <iostream>
#include <vector>
#include <array>
#include <stdio.h>
#include "CustomFunctions.h" // Required functions
#include "HelperFunctions.h" // Helper functions

using namespace std;

/**
 * @brief Main function. Called via ./AnalyseData.out [args].
 * Accepted args are a filepath to a data file with 2D data delimited by spaces.
 * 
 * @param argc The number of arguments passed to the program.
 * @param argv The arguments passed to the program.
 * @return 0 if successful.
 */
int main(int argc, char *argv[]) {

    print_author_info(); // Print authorship information
    string filepath = handle_arguments(argc, argv); // handle filepath argument(s)
    fileData file = read_file(filepath); // Read file and store data in fileData struct
    
    bool program_loop = true;
    while (program_loop) { // Loop until user exits
        int choice = select_choice(); // Select choice from menu
        file = handle_choice(choice, file); // Handle choice
    }
    program_loop = false; // Exit program

    return 0;
}
