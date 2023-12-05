#include <iostream>
#include <string>
#include <vector>
#include "FiniteFunctions.h"
#include <filesystem> //To check extensions in a nice way

#include "gnuplot-iostream.h" //Needed to produce plots (not part of the course) 

using std::filesystem::path;

//Empty constructor
FiniteFunction::FiniteFunction(){
  m_RMin = -5.0;
  m_RMax = 5.0;
  this->checkPath("DefaultFunction");
  m_Integral = NULL;
}

//initialised constructor
FiniteFunction::FiniteFunction(double range_min, double range_max, std::string outfile){
  m_RMin = range_min;
  m_RMax = range_max;
  m_Integral = NULL;
  this->checkPath(outfile); //Use provided string to name output files
}

//Plots are called in the destructor
//SUPACPP note: They syntax of the plotting code is not part of the course
FiniteFunction::~FiniteFunction(){
  Gnuplot gp; //Set up gnuplot object
  this->generatePlot(gp); //Generate the plot and save it to a png using "outfile" for naming 
}

/*
###################
//Setters
###################
*/ 
void FiniteFunction::setRangeMin(double RMin) {m_RMin = RMin;};
void FiniteFunction::setRangeMax(double RMax) {m_RMax = RMax;};
void FiniteFunction::setOutfile(std::string Outfile) {this->checkPath(Outfile);};

/*
###################
//Getters
###################
*/ 
double FiniteFunction::rangeMin() {return m_RMin;};
double FiniteFunction::rangeMax() {return m_RMax;};

/*
###################
//Function eval
###################
*/ 
double FiniteFunction::invxsquared(double x) {return 1/(1+x*x);};
double FiniteFunction::callFunction(double x) {return this->invxsquared(x);}; //(overridable)

/*
###################
Integration by hand using Simpson's rule
###################
*/
double FiniteFunction::integrate(int Ndiv){ // private
  double h = (m_RMax - m_RMin)/Ndiv; // determine x steps from overall range and number of divisions
  double integral = 0; // initialise integral as 0
  double S_zero, S_one, S_two; // Simpson's rule: I = h/3*(S0 + 4S1 + 2S2)

  for (int n = 0; n <= Ndiv; n++){ // loop over divisions
    double x = m_RMin + n*h; // x value
    double fx = this->callFunction(x); // f(x_n)

    if (n == 0 || n == Ndiv) 
      S_zero += fx; // S0 = f(0) + f(Ndiv)
    else if (n % 2 != 0) 
      S_one += fx; // S1 = Σf(x_n) for odd n
    else
      S_two += fx; // S2 = Σf(x_n) for even n
  }

  integral = (h/3) * (S_zero + 4*S_one + 2*S_two);
  return integral; // sum of parabolic areas approximating integral. large Ndiv = decreased error.
}
double FiniteFunction::integral(int Ndiv) { //public
  if (Ndiv <= 0){
    std::cout << "Invalid number of divisions for integral, setting Ndiv to 1000" <<std::endl;
    Ndiv = 1000;
  }
  if (m_Integral == NULL || Ndiv != m_IntDiv){
    m_IntDiv = Ndiv;
    m_Integral = this->integrate(Ndiv);
    return m_Integral;
  }
  else return m_Integral; //Don't bother re-calculating integral if Ndiv is the same as the last call
}

/*
###################
//Helper functions 
###################
*/
// Generate paths from user defined stem
void FiniteFunction::checkPath(std::string outfile){
 path fp = outfile;
 m_FunctionName = fp.stem(); 
 m_OutData = m_FunctionName+".data";
 m_OutPng = m_FunctionName+".png";
}

//Print (overridable)
void FiniteFunction::printInfo(){
  std::cout << "rangeMin: " << m_RMin << std::endl;
  std::cout << "rangeMax: " << m_RMax << std::endl;
  std::cout << "integral: " << m_Integral << ", calculated using " << m_IntDiv << " divisions" << std::endl;
  std::cout << "function: " << m_FunctionName << std::endl;
}

/*
###################
//Plotting
###################
*/

//Hack because gnuplot-io can't read in custom functions, just scan over function and connect points with a line... 
void FiniteFunction::plotFunction(){
  m_function_scan = this->scanFunction(10000);
  m_plotfunction = true;
}

//Transform data points into a format gnuplot can use (histogram) and set flag to enable drawing of data to output plot
//set isdata to true (default) to plot data points in black, set to false to plot sample points in blue
void FiniteFunction::plotData(std::vector<double> &points, int Nbins, bool isdata){
  if (isdata){
    m_data = this->makeHist(points,Nbins);
    m_plotdatapoints = true;
  }
  else{
    m_samples = this->makeHist(points,Nbins);
    m_plotsamplepoints = true;
  }
}


/*
  #######################################################################################################
  ## SUPACPP Note:
  ## The three helper functions below are needed to get the correct format for plotting with gnuplot
  ## In theory you shouldn't have to touch them
  ## However it might be helpful to read through them and understand what they are doing
  #######################################################################################################
 */

//Scan over range of function using range/Nscan steps (just a hack so we can plot the function)
std::vector< std::pair<double,double> > FiniteFunction::scanFunction(int Nscan){
  std::vector< std::pair<double,double> > function_scan;
  double step = (m_RMax - m_RMin)/(double)Nscan;
  double x = m_RMin;
  //We use the integral to normalise the function points
  if (m_Integral == NULL) {
    std::cout << "Integral not set, doing it now" << std::endl;
    this->integral(Nscan);
    std::cout << "integral: " << m_Integral << ", calculated using " << Nscan << " divisions" << std::endl;
  }
  //For each scan point push back the x and y values 
  for (int i = 0; i < Nscan; i++){
    function_scan.push_back( std::make_pair(x,this->callFunction(x)/m_Integral));
    x += step;
  }
  return function_scan;
}

//Function to make histogram out of sampled x-values - use for input data and sampling
std::vector< std::pair<double,double> > FiniteFunction::makeHist(std::vector<double> &points, int Nbins){

  std::vector< std::pair<double,double> > histdata; //Plottable output shape: (midpoint,frequency)
  std::vector<int> bins(Nbins,0); //vector of Nbins ints with default value 0 
  int norm = 0;
  for (double point : points){
    //Get bin index (starting from 0) the point falls into using point value, range, and Nbins
    int bindex = static_cast<int>(floor((point-m_RMin)/((m_RMax-m_RMin)/(double)Nbins)));
    if (bindex<0 || bindex>Nbins){
      continue;
    }
    bins[bindex]++; //weight of 1 for each data point
    norm++; //Total number of data points
  }
  double binwidth = (m_RMax-m_RMin)/(double)Nbins;
  for (int i=0; i<Nbins; i++){
    double midpoint = m_RMin + i*binwidth + binwidth/2; //Just put markers at the midpoint rather than drawing bars
    double normdata = bins[i]/((double)norm*binwidth); //Normalise with N = 1/(Ndata*binwidth)
    histdata.push_back(std::make_pair(midpoint,normdata));
  }
  return histdata;
}

//Function which handles generating the gnuplot output, called in destructor
//If an m_plot... flag is set, the we must have filled the related data vector
//SUPACPP note: They syntax of the plotting code is not part of the course
void FiniteFunction::generatePlot(Gnuplot &gp){

  if (m_plotfunction==true && m_plotdatapoints==true && m_plotsamplepoints==true){
    gp << "set terminal pngcairo\n";
    gp << "set output 'Outputs/png/"<<m_FunctionName<<".png'\n"; 
    gp << "set xrange ["<<m_RMin<<":"<<m_RMax<<"]\n";
    gp << "set style line 1 lt 1 lw 2 pi 1 ps 0\n";
    gp << "plot '-' with linespoints ls 1 title '"<<m_FunctionName<<"', '-' with points ps 2 lc rgb 'blue' title 'sampled data', '-' with points ps 1 lc rgb 'black' pt 7 title 'data'\n";
    gp.send1d(m_function_scan);
    gp.send1d(m_samples);
    gp.send1d(m_data);
  }
  else if (m_plotfunction==true && m_plotdatapoints==true){
    gp << "set terminal pngcairo\n";
    gp << "set output 'Outputs/png/"<<m_FunctionName<<".png'\n"; 
    gp << "set xrange ["<<m_RMin<<":"<<m_RMax<<"]\n";
    gp << "set style line 1 lt 1 lw 2 pi 1 ps 0\n";
    gp << "plot '-' with linespoints ls 1 title '"<<m_FunctionName<<"', '-' with points ps 1 lc rgb 'black' pt 7 title 'data'\n";
    gp.send1d(m_function_scan);
    gp.send1d(m_data);
  }
  else if (m_plotfunction==true && m_plotsamplepoints==true){
    gp << "set terminal pngcairo\n";
    gp << "set output 'Outputs/png/"<<m_FunctionName<<".png'\n"; 
    gp << "set xrange ["<<m_RMin<<":"<<m_RMax<<"]\n";
    gp << "set style line 1 lt 1 lw 2 pi 1 ps 0\n";
    gp << "plot '-' with linespoints ls 1 title '"<<m_FunctionName<<"', '-' with points ps 2 lc rgb 'blue' title 'sampled data'\n";
    gp.send1d(m_function_scan);
    gp.send1d(m_samples);
  }
  else if (m_plotfunction==true){
    gp << "set terminal pngcairo\n";
    gp << "set output 'Outputs/png/"<<m_FunctionName<<".png'\n"; 
    gp << "set xrange ["<<m_RMin<<":"<<m_RMax<<"]\n";
    gp << "set style line 1 lt 1 lw 2 pi 1 ps 0\n";
    gp << "plot '-' with linespoints ls 1 title 'function'\n";
    gp.send1d(m_function_scan);
  }

  else if (m_plotdatapoints == true){
    gp << "set terminal pngcairo\n";
    gp << "set output 'Outputs/png/"<<m_FunctionName<<".png'\n"; 
    gp << "set xrange ["<<m_RMin<<":"<<m_RMax<<"]\n";
    gp << "plot '-' with points ps 1 lc rgb 'black' pt 7 title 'data'\n";
    gp.send1d(m_data);
  }

  else if (m_plotsamplepoints == true){
    gp << "set terminal pngcairo\n";
    gp << "set output 'Outputs/png/"<<m_FunctionName<<".png'\n"; 
    gp << "set xrange ["<<m_RMin<<":"<<m_RMax<<"]\n";
    gp << "plot '-' with points ps 2 lc rgb 'blue' title 'sampled data'\n";
    gp.send1d(m_samples);
  }
}

/*
###################
//Normal Distribution Function
###################
*/

//Empty constructor
NormalDistributionFunction::NormalDistributionFunction() {
    m_mu = 0.0;
    m_sigma = 1.0;
}

//Initialised constructor
NormalDistributionFunction::NormalDistributionFunction(double range_min, double range_max, std::string outfile, double mu, double sigma) {
    m_mu = mu;
    m_sigma = sigma;
    m_RMin = range_min;
    m_RMax = range_max;
    m_Integral = NULL;
    this->checkPath(outfile);
}

/*
###################
//Setters
###################
*/
void NormalDistributionFunction::setMu(double mu) {m_mu = mu;};
void NormalDistributionFunction::setSigma(double sigma) {m_sigma = sigma;};

/*
###################
//Getters
###################
*/
double NormalDistributionFunction::mu() {return m_mu;};
double NormalDistributionFunction::sigma() {return m_sigma;};

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

//Empty constructor
CauchyLorentzDistribution::CauchyLorentzDistribution() {
    m_x0 = 0.0;
    m_gamma = 1.0;
}

//Initialised constructor
CauchyLorentzDistribution::CauchyLorentzDistribution(double range_min, double range_max, std::string outfile, double x0, double gamma) {
    m_x0 = x0;
    m_gamma = gamma;
    m_RMin = range_min;
    m_RMax = range_max;
    m_Integral = NULL;
    this->checkPath(outfile);

    if (m_gamma == 0) {m_gamma = 1.0;};
}

/*
###################
//Setters
###################
*/
void CauchyLorentzDistribution::setx0(double x0) {m_x0 = x0;};
void CauchyLorentzDistribution::setGamma(double gamma) {m_gamma = gamma;};

/*
###################
//Getters
###################
*/
double CauchyLorentzDistribution::x0() {return m_x0;};
double CauchyLorentzDistribution::gamma() {return m_gamma;};

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
    std::cout << "rangeMin: " << m_RMin << std::endl;
    std::cout << "rangeMax: " << m_RMax << std::endl;
    std::cout << "integral: " << m_Integral << ", calculated using " << m_IntDiv << " divisions" << std::endl;
    std::cout << "function: " << m_FunctionName << std::endl;
    std::cout << "x0: " << m_x0 << std::endl;
    std::cout << "gamma: " << m_gamma << std::endl;
};