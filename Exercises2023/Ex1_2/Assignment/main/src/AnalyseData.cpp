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
 * @brief Main function. Called via ./AnalyseData.out [args]
 * 
 * @param argc The number of arguments passed to the program.
 * @param argv The arguments passed to the program.
 * @return 0 if successful.
 */
int main(int argc, char *argv[]) {

    print_author_info(); // Print authorship information
    string filepath = handle_arguments(argc, argv); // handle filepath argument(s)
    fileData file = read_file(filepath); // Read file and store data in fileData struct
    cout << "Log: File " << file.filename << " contains " << file.data.size() << " data points." << endl;
    
    
    while (true) { // Loop until user exits
        int choice = select_choice();
        file = handle_choice(choice, file);
    }

    return 0;
}