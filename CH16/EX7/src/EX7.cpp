#include "QatPlotting/PlotHist1D.h"
#include "QatPlotting/PlotProfile.h"
#include "QatPlotting/PlotFunction1D.h"
#include "QatPlotting/PlotPoint.h"
#include "QatPlotting/PlotKey.h"
#include "QatDataModeling/HistChi2Functional.h"
#include "QatDataModeling/HistLikelihoodFunctional.h"
#include "QatDataModeling/MinuitMinimizer.h"
#include "QatGenericFunctions/Cos.h"
#include "QatGenericFunctions/Variable.h"
#include "QatGenericFunctions/Parameter.h"
#include "QatGenericFunctions/IncompleteGamma.h"
#include "Eigen/Dense"
#include "QatGenericFunctions/Variable.h"
#include <QMainWindow>
#include <QApplication>
#include <QToolBar>
#include <QAction>
#include <QtGui>
#include <iostream>
#include <string>
#include <random>
#include <map>
#include <cmath>
#include <fstream>

#include "EarthMars.h"
#include "IKE.h"
#include <fstream>
int main (int argc, char * * argv) {

  using namespace Genfun;

  // Automatically generated:-------------------------:

  std::string usage= std::string("usage: ") + argv[0]; 
  if (argc!=1) {
    std::cout << usage << std::endl;
  }


  QApplication     app(argc,argv);
  
  QMainWindow window;
  QToolBar *toolBar=window.addToolBar("Tools");
  QAction  *quitAction=toolBar->addAction("Quit");
  
  quitAction->setShortcut(QKeySequence("q"));
  
  QObject::connect(quitAction, SIGNAL(triggered()), &app, SLOT(quit()));
  
  PRectF rect;
  rect.setXmin(0.0);
  rect.setXmax(1.0);
  rect.setYmin(0.0);
  rect.setYmax(1.0);

  // Create EarthMars structure
  EarthMars earthmars;

  // Extract Data from file
  
  std::ifstream fin;
  fin.open("Mars.dat");

  // Ignore first four lines
  fin.ignore(100, '\n');
  fin.ignore(100, '\n');
  fin.ignore(100, '\n');
  fin.ignore(100, '\n');

  std::string line;
  std::string s_date, s_time;
  double ra1, ra2, ra3, dec1, dec2, dec3;
  while (getline(fin, line)){
    std::istringstream ss(line);
    if (ss >> s_date >> s_time >>
	ra1 >> ra2 >> ra3 >>
	dec1 >> dec2 >> dec3){

      // Extract year, month, and day
      double y = std::stod(s_date.substr(0,4));
      std::string s_month = s_date.substr(5,3);
      double m;
      if(s_month == "Jan") m = 1;
      else if(s_month == "Dec") m = 12;
      double d = std::stod(s_date.substr(9,2));

      // Convert to JDN (from wiki)
      double JDN = (1461*(y+4800+(m-14)/12))/4+(367*(m-2-12*((m-14)/12)))-(3*((y+4900+(m-14)/12)/100))/4 + d - 32075;

      // Convert RA to decimal
      double RA = ra1 + ra2/60. + ra3/3600.;

      // Conver DEC to decimal
      double DEC = dec1 - dec2/60. - dec3/3600.;

      // Add point
      earthmars.addPoint(JDN, RA, DEC);
      
    } 
  }

  // Close File
  fin.close();

  // Add points to histogram
  Hist1D histEarth("EarthDat", 100, 0, 1);
  histEarth.accumulate(earthmars.earth);
  Hist1D histMars("MarsDat", 100, 0, 1);
  histMars.accumulate(earthmars.mars);

  // Hist Functional
  HistChi2Functional ofEarth(&histEarth);
  HistChi2Functional ofMars(&histMars);

  // Modeling Functions r(phi)
  Cos cos;
  Variable PHI;
  GENFUNCTION EarthOrbit = earthmars.a1*(1.-earthmars.e1*earthmars.e1)/(1.-PHI);
  GENFUNCTION MarsOrbit = earthmars.a2*(1.-earthmars.e2*earthmars.e2)/(1.-PHI);

  // Minimize likelihood
  bool verbose=true;
  MinuitMinimizer minimizer1(verbose);
  minimizer1.addParameter(&earthmars.e1);
  minimizer1.addParameter(&earthmars.a1);
  //minimizer1.addParameter(&earthmars.t1);
  //minimizer1.addParameter(&earthmars.phi1);
  //minimizer1.addParameter(&earthmars.theta1);
  //minimizer1.addParameter(&earthmars.psi1);
  minimizer1.addStatistic(&ofEarth, &EarthOrbit);
  minimizer1.minimize();

  MinuitMinimizer minimizer2(verbose);
  minimizer2.addParameter(&earthmars.e2);
  minimizer2.addParameter(&earthmars.a2);
  minimizer2.addParameter(&earthmars.phi2);
  //minimizer2.addParameter(&earthmars.t2);
  //minimizer2.addParameter(&earthmars.theta2);
  //minimizer2.addParameter(&earthmars.psi2);
  //minimizer2.addStatistic(&ofMars, &MarsOrbit);
  minimizer2.minimize();

  // Print Values
  std::cout<<"a_earth = "<<minimizer1.getValue(&a1)<<std::endl;
  std::cout<<"a_mars = "<<minimizer1.getValue(&a2)<<std::endl;
  std::cout<<"e_earth = "<<<<minimizer1.getValue(&e1)<<std::endl;
  std::cout<<"e_mars = "<<<<minimizer1.getValue(&e2)<<std::endl;

  PlotView view(rect);
  window.setCentralWidget(&view);
  
  PlotStream titleStream(view.titleTextEdit());
  titleStream << PlotStream::Clear()
	      << PlotStream::Center() 
	      << PlotStream::Family("Sans Serif") 
	      << PlotStream::Size(16)
	      << PlotStream::EndP();
  
  
  PlotStream xLabelStream(view.xLabelTextEdit());
  xLabelStream << PlotStream::Clear()
	       << PlotStream::Center()
	       << PlotStream::Family("Sans Serif")
	       << PlotStream::Size(16)
	       << PlotStream::EndP();
  
  PlotStream yLabelStream(view.yLabelTextEdit());
  yLabelStream << PlotStream::Clear()
	       << PlotStream::Center()
	       << PlotStream::Family("Sans Serif")
	       << PlotStream::Size(16)
	       << PlotStream::EndP();
  
  
  
  //window.show();
  app.exec();
  return 1;
}

