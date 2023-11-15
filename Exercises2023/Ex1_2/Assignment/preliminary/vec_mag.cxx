#include <iostream>
#include <cmath>

double calculate_magnitude(double x, double y) {
    return sqrt(x*x + y*y);
}

int main() {
    double x = 2.3;
    double y = 4.5;

    std::cout << "This will calculate the magnitude of an input 2D vector, (x, y)." << std::endl;
    std::cout << "Enter x and y coordinates of a vector: " << std::endl;
    std::cout << "(_, y): ", std::cin >> x;
    std::cout << "("<<x<<", _): ", std::cin >> y;

    double mag = calculate_magnitude(x, y);

    std::cout << "Magnitude of vector (" << x << ", " << y << ") is " << mag << std::endl;

    return mag;
}