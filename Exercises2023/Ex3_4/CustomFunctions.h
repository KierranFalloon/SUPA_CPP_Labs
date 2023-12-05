/**
 * @file CustomFunctions.h
 * @author Kierran Falloon (kierran.falloon@strath.ac.uk)
 * @date 5-12-2023
 */

#include <string>
#include <vector>
#include "FiniteFunctions.h"

#pragma once //Replacement for IFNDEF

class NormalDistributionFunction : public FiniteFunction{
  
public:
  NormalDistributionFunction(); //Empty constructor
  NormalDistributionFunction(double range_min, double range_max, std::string outfile, double mu=0.0, double sigma=1.0); //Variable constructor
  virtual void printInfo(); //Dump parameter info about the current function
  virtual double callFunction(double x); //Call the function with value x

private:
  double m_mu;
  double m_sigma;
  double normal(double x, double mu, double sigma);
};

class CauchyLorentzDistribution : public FiniteFunction{

public:
  CauchyLorentzDistribution(); //Empty constructor
  CauchyLorentzDistribution(double range_min, double range_max, std::string outfile, double x0=0.0, double gamma=1.0); //Variable constructor
  virtual void printInfo(); //Dump parameter info about the current function
  virtual double callFunction(double x); //Call the function with value x

private:
  double m_x0;
  double m_gamma;
  double cauchy(double x, double gamma);
};

class NegativeCrystalBallDistribution : public FiniteFunction{

public:
  NegativeCrystalBallDistribution(); //Empty constructor
  NegativeCrystalBallDistribution(double range_min, double range_max, std::string outfile, double xbar=0.0, double sigma=1.0, double alpha=1.0, double n=1.0); //Variable constructor
  virtual void printInfo(); // Dump parameter info about the current function
  virtual double callFunction(double x); //Call the function with value x

private:
  double m_alpha;
  double m_n;
  double m_xbar;
  double m_sigma;
  double negativeCrystalBall(double x, double xbar, double sigma, double alpha, double n);
};