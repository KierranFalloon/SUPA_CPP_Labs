/**
 * @file Test.cxx
 * @author Kierran Falloon (kierran.falloon@strath.ac.uk)
 * @version 1.0
 * @date 5-12-2023
 */

#include "FiniteFunctions.h"
#include <iostream>
#include <fstream>
#include "HelperFunctions.h"

int main()
{
    // Read data from file
    std::vector<double> data = read_file();

    // Find range of data
    std::array<double,2> min_max = data_range(data);
    float min = min_max[0];
    float max = min_max[1];

    FiniteFunction function(min, max, "Outputs/png/Inv_X_Squared.png");
    // Plot function
    function.plotFunction();
    // Plot data
    function.plotData(data, 50, true);
    // Print info
    function.printInfo();

    sleep(2);
    NormalDistributionFunction normalFunc(min, max, "Outputs/png/Normal.png", 2.0, 1.5);
    normalFunc.plotFunction();
    normalFunc.plotData(data, 50, true);
    normalFunc.printInfo();

    sleep(2);
    CauchyLorentzDistribution cauchyFunc(min, max, "Outputs/png/Cauchy-Lorentz.png", 2.0, 1.5);
    cauchyFunc.plotFunction();
    cauchyFunc.plotData(data, 50, true);
    cauchyFunc.printInfo();

    return 0;
}
