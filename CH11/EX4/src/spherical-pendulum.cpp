#include "QatPlotWidgets/PlotView.h"
#include "QatPlotting/PlotStream.h"
#include <QApplication>
#include <QMainWindow>
#include <QToolBar>
#include <QAction>
#include <cstdlib>
#include <iostream>
#include <string>

#include <cmath>
#include "QatGenericFunctions/Sin.h"
#include "QatGenericFunctions/Cos.h"
#include "QatGenericFunctions/Variable.h"
#include "QatGenericFunctions/RKIntegrator.h"
#include "QatPlotting/PlotFunction1D.h"
#include "QatGenericFunctions/CubicSplinePolynomial.h"

int main (int argc, char * * argv) {

  using namespace Genfun;
  RKIntegrator integrator;

  Sin sin;
  Cos cos;

  Variable Theta(0,4), Phi(1,4), VT(2,4), VP(3,4);
  double a = 1.0; // m
  double g = 9.8; // m/s/s
  double theta0 = M_PI/10.; // rad
  double lambda = 0.5; // rad/s

  GENFUNCTION DThetaDT = VT;
  GENFUNCTION DPhiDT = VP;
  GENFUNCTION DVTDT = VP*VP*sin(Theta)*cos(Theta)-g/a*sin(Theta);
  GENFUNCTION DVPDT = -2.*VP*VT*cos(Theta)/sin(Theta);
  
  integrator.addDiffEquation(&DThetaDT, "Theta0", theta0);
  integrator.addDiffEquation(&DPhiDT, "Phi0", 0);
  integrator.addDiffEquation(&DVTDT, "VT0", 0);
  integrator.addDiffEquation(&DVPDT, "VP0", lambda/a*sin(theta0));

  GENFUNCTION theta = *integrator.getFunction(Theta);
  GENFUNCTION phi = *integrator.getFunction(Phi);

  CubicSplinePolynomial cSpline;
  for (unsigned int t=0;t<10;t++){
    cSpline.addPoint(sin(theta(t))*sin(phi(t)),sin(theta(t))*cos(phi(t)));
  }

  PlotFunction1D pF(cSpline);
  

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
  

  PlotView view(rect);
  window.setCentralWidget(&view);

  view.add(&pF);
  
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
  
  
  
  window.show();
  app.exec();
  return 1;
}

