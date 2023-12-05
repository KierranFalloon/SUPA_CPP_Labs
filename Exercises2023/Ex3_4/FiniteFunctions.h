#include <string>
#include <vector>
#include "gnuplot-iostream.h"

#pragma once //Replacement for IFNDEF

class FiniteFunction{

public:
  FiniteFunction(); //Empty constructor
  FiniteFunction(double range_min, double range_max, std::string outfile); //Variable constructor
  ~FiniteFunction(); //Destructor
  double rangeMin(); //Low end of the range the function is defined within
  double rangeMax(); //High end of the range the function is defined within
  double integral(int Ndiv = 1000); 
  std::vector< std::pair<double,double> > scanFunction(int Nscan = 1000); //Scan over function to plot it (slight hack needed to plot function in gnuplot)
  void setRangeMin(double RMin);
  void setRangeMax(double RMax);
  void setOutfile(std::string outfile);
  void plotFunction(); //Plot the function using scanFunction
  
  //Plot the supplied data points (either provided data or points sampled from function) as a histogram using NBins
  void plotData(std::vector<double> &points, int NBins, bool isdata=true); //NB! use isdata flag to pick between data and sampled distributions
  virtual void printInfo(); //Dump parameter info about the current function (Overridable)
  virtual double callFunction(double x); //Call the function with value x (Overridable)

  //Protected members can be accessed by child classes but not users
protected:
  double m_RMin;
  double m_RMax;
  double m_Integral;
  int m_IntDiv = 0; //Number of division for performing integral
  std::string m_FunctionName;
  std::string m_OutData; //Output filename for data
  std::string m_OutPng; //Output filename for plot
  std::vector< std::pair<double,double> > m_data; //input data points to plot
  std::vector< std::pair<double,double> > m_samples; //Holder for randomly sampled data 
  std::vector< std::pair<double,double> > m_function_scan; //holder for data from scanFunction (slight hack needed to plot function in gnuplot)
  bool m_plotfunction = false; //Flag to determine whether to plot function
  bool m_plotdatapoints = false; //Flag to determine whether to plot input data
  bool m_plotsamplepoints = false; //Flag to determine whether to plot sampled data 
  double integrate(int Ndiv);
  std::vector< std::pair<double, double> > makeHist(std::vector<double> &points, int Nbins); //Helper function to turn data points into histogram with Nbins
  void checkPath(std::string outstring); //Helper function to ensure data and png paths are correct
  void generatePlot(Gnuplot &gp); 
  
private:
  double invxsquared(double x); //The default functional form
};

class NormalDistributionFunction : public FiniteFunction{
  
public:
  NormalDistributionFunction(); //Empty constructor
  NormalDistributionFunction(double range_min, double range_max, std::string outfile, double mu=0.0, double sigma=1.0); //Variable constructor
  double mu(); //Mean of the normal distribution
  double sigma(); //Standard deviation of the normal distribution
  void setMu(double mu);
  void setSigma(double sigma);
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
  double x0(); // Center
  double gamma(); //Scale parameter of the distribution
  void setx0(double x0);
  void setGamma(double gamma);
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
  double alpha(); // Tail parameter
  double n(); // Power of the tail
  double xbar(); // Mean
  double sigma(); // Width of the gaussian core
  void setAlpha(double alpha);
  void setN(double n);
  void setxbar(double xbar);
  void setSigma(double sigma);
  virtual void printInfo(); // Dump parameter info about the current function
  virtual double callFunction(double x); //Call the function with value x

private:
  double m_alpha;
  double m_n;
  double m_xbar;
  double m_sigma;
  double negativeCrystalBall(double x, double xbar, double sigma, double alpha, double n);
};