/**
 * @file CustomFunctions.cxx
 * @author Kierran Falloon (kierran.falloon@strath.ac.uk)
 * @date 5-12-2023
 */

#include "FiniteFunctions.h"
#include "CustomFunctions.h"
#include <random>

/*
###################
//Normal Distribution Function
###################
*/

double NormalDistributionFunction::getMean(){return m_mu;};

/*
###################
//Function eval
###################
*/
double NormalDistributionFunction::normal(double x, double mu, double sigma) {
  return (1/(sigma*sqrt(2*M_PI)))*exp(-0.5*pow((x-mu)/sigma, 2));
}
double NormalDistributionFunction::callFunction(double x) {return this->normal(x, m_mu, m_sigma);}

/*
###################
//Helper functions
###################
*/
//Print
void NormalDistributionFunction::printInfo() {
  std::cout << std::endl;
  std::cout << "function: " << m_FunctionName << std::endl;
  std::cout << "rangeMin: " << m_RMin << std::endl;
  std::cout << "rangeMax: " << m_RMax << std::endl;
  std::cout << "integral: " << m_Integral << ", calculated using " << m_IntDiv << " divisions" << std::endl;
  std::cout << "mu: " << m_mu << std::endl;
  std::cout << "sigma: " << m_sigma << std::endl;
};

/*
###################
//Cauchy-Lorentz Distribution Function
###################
*/

double CauchyLorentzDistribution::getMean(){return m_x0;};

/*
###################
//Function eval
###################
*/
double CauchyLorentzDistribution::cauchy(double x, double gamma) {
  return 1/( (M_PI*gamma) * 1+pow((x-m_x0)/gamma, 2));
}
double CauchyLorentzDistribution::callFunction(double x) {return this->cauchy(x, m_gamma);};

/*
###################
//Helper functions
###################
*/
//Print
void CauchyLorentzDistribution::printInfo() {
  std::cout << std::endl;
  std::cout << "function: " << m_FunctionName << std::endl;
  std::cout << "rangeMin: " << m_RMin << std::endl;
  std::cout << "rangeMax: " << m_RMax << std::endl;
  std::cout << "integral: " << m_Integral << ", calculated using " << m_IntDiv << " divisions" << std::endl;
  std::cout << "x0: " << m_x0 << std::endl;
  std::cout << "gamma: " << m_gamma << std::endl;
};

/*
###################
//Negative Crystal Ball distribution
###################
*/

double NegativeCrystalBallDistribution::getMean(){return m_xbar;};

/*
###################
//Function eval
###################
*/
double NegativeCrystalBallDistribution::negativeCrystalBall(double x, double xbar, double sigma, double alpha, double n) {
  alpha = abs(alpha);
  double z = (x-xbar)/sigma; // for convenience
  double A = pow(n/alpha, n) * exp(-pow(alpha, 2)/2);
  double B = n/alpha - alpha;
  double C = n/alpha * (1/(n-1)) * exp(-pow(alpha, 2)/2);
  double D = sqrt(M_PI/2) * (1 + erf(alpha/sqrt(2)));
  double N = 1/(sigma * (C+D));
  if (z <= -alpha) {
    return N * A * pow(B-z, -n);
  }
  else {
    return N * exp(-pow(z, 2)/2);
  }
}
double NegativeCrystalBallDistribution::callFunction(double x) {return this->negativeCrystalBall(x, m_xbar, m_sigma, m_alpha, m_n);};

/*
###################
//Helper functions
###################
*/
//Print
void NegativeCrystalBallDistribution::printInfo() {
  std::cout << std::endl;
  std::cout << "function: " << m_FunctionName << std::endl;
  std::cout << "rangeMin: " << m_RMin << std::endl;
  std::cout << "rangeMax: " << m_RMax << std::endl;
  std::cout << "integral: " << m_Integral << ", calculated using " << m_IntDiv << " divisions" << std::endl;
  std::cout << "xbar: " << m_xbar << std::endl;
  std::cout << "sigma: " << m_sigma << std::endl;
  std::cout << "alpha: " << m_alpha << std::endl;
  std::cout << "n: " << m_n << std::endl;
};

/*
###################
//Metropolis-Hastings Algorithm
// Initialised as a FiniteFunction class that takes input of a function, such that this->callFunction can be used.
###################
*/

MetropolisHastings::~MetropolisHastings() {} // Destructor

// Random number generator
double MetropolisHastings::random(int min, int max) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<> dis(min, max);
  return dis(gen);
}

// Random number generator with normal distribution
double MetropolisHastings::random_normal(double norm_sigma) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::normal_distribution<> dis(m_norm_mean, norm_sigma);
  return dis(gen);
}

//Print
void MetropolisHastings::printInfo() {
  std::cout << std::endl;
  std::cout << "Sampling function with " << nSamples << " points with Metropolis-Hastings Algorithm with between " << m_Function->rangeMin() << " and " << m_Function->rangeMax() << std::endl;
};

// Metropolis-Hastings algorithm
std::vector<double> MetropolisHastings::sample() {
  std::vector<double> m_Samples;
  double x = random(m_RMin, m_RMax); // Initial random x value

  while (m_Samples.size() < nSamples) {
    double y = random_normal(2.5); // Random y value from normal distribution with standard deviation
    double fx = m_Function->callFunction(x); // Call function to get f(x)
    double fy = m_Function->callFunction(y); // Call function to get f(y)
    double A = std::min(1.0, fy/fx); 
    double T = random(0, 1);

    if (T < A) { // Accept y
      m_Samples.push_back(y);
      x = y; // Set next x
    }
    else { // Reject y
      x = x; // Don't change x
    }
  }

  return m_Samples;
}