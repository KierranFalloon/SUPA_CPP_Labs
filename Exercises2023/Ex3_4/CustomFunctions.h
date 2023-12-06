/**
 * @file CustomFunctions.h
 * @author Kierran Falloon (kierran.falloon@strath.ac.uk)
 * @date 5-12-2023
 */

#include "FiniteFunctions.h"

#pragma once //Replacement for IFNDEF

class NormalDistributionFunction : public FiniteFunction{
  
public:
  NormalDistributionFunction() : FiniteFunction() {m_mu = 0.0; m_sigma = 1.0;}; //Empty constructor
  NormalDistributionFunction(double range_min, double range_max, std::string outfile, double mu=0.0, double sigma=1.0) : FiniteFunction(range_min, range_max, outfile) {m_mu = mu; m_sigma = sigma;}; //Variable constructor
  virtual void printInfo(); //Dump parameter info about the current function
  virtual double callFunction(double x); //Call the function with value x

private:
  double m_mu;
  double m_sigma;
  double normal(double x, double mu, double sigma);
};

class CauchyLorentzDistribution : public FiniteFunction{

public:
  CauchyLorentzDistribution() : FiniteFunction() {m_x0 = 0.0; m_gamma = 1.0;}; //Empty constructor
  CauchyLorentzDistribution(double range_min, double range_max, std::string outfile, double x0=0.0, double gamma=1.0) : FiniteFunction(range_min, range_max, outfile) {m_x0 = x0; m_gamma = gamma;}; //Variable constructor
  virtual void printInfo(); //Dump parameter info about the current function
  virtual double callFunction(double x); //Call the function with value x

private:
  double m_x0;
  double m_gamma;
  double cauchy(double x, double gamma);
};

class NegativeCrystalBallDistribution : public FiniteFunction{

public:
  NegativeCrystalBallDistribution() : FiniteFunction() {m_xbar = 0.0; m_sigma = 1.0; m_alpha = 1.0; m_n = 1.0;}; //Empty constructor
  NegativeCrystalBallDistribution(double range_min, double range_max, std::string outfile, double xbar=0.0, double sigma=1.0, double alpha=1.0, double n=1.0) : FiniteFunction(range_min, range_max, outfile) {m_xbar = xbar; m_sigma = sigma; m_alpha = alpha; m_n = n;}; //Variable constructor
  virtual void printInfo(); // Dump parameter info about the current function
  virtual double callFunction(double x); //Call the function with value x

private:
  double m_alpha;
  double m_n;
  double m_xbar;
  double m_sigma;
  double negativeCrystalBall(double x, double xbar, double sigma, double alpha, double n);
};

class MetropolisHastings : public FiniteFunction{

public:
  MetropolisHastings() : FiniteFunction() {}; //Empty constructor
  MetropolisHastings(FiniteFunction* function) : FiniteFunction() { //Variable constructor
    m_Function = function; // Set function
    setRangeMin(function->rangeMin()); // Unpack lower bound
    setRangeMax(function->rangeMax()); // Unpack upper bound
  }
  ~MetropolisHastings(); //Destructor
  std::vector<double> sample(int nSamples); // Sampling function

private:
  FiniteFunction* m_Function;
  double random(int min, int max); // Uniform random number
  double random_normal(double mu, double sigma); // Normal sampled random number

};
