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
#include "QatGenericFunctions/Variable.h"
#include "QatGenericFunctions/RKIntegrator.h"
#include "QatPlotting/PlotFunction1D.h"
#include "QatGenericFunctions/CubicSplinePolynomial.h"

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
  

  //
  // SEIR
  //

  double ndays = 3.0e3;

  // Rates
  double beta = 0.2;
  double gamma = 0.1;
  double b = 1.e-4;
  double d = 1.e-4;
  double alpha = 0.1;
  double nu = 1.e-3;

  // Initial Conditions
  double I_0 = 1.e-6;
  double N_0 = 1.;
  double S_0 = N_0 - I_0;
  double E_0 = 0.;
  double R_0 = 0.;

  // Variables
  Variable S(0,4), E(1,4), I(2,4), R(3,4);
  GENFUNCTION N = S + E + I + R;
  GENFUNCTION lambda = beta/N;

  // DiffEqs
  GENFUNCTION DSDT = b*N - d*S - lambda*S;
  GENFUNCTION DEDT = lambda*S - d*E - alpha*E;
  GENFUNCTION DIDT = alpha*E - d*I - gamma*I;
  GENFUNCTION DRDT = alpha*I - nu*R - d*R;
    
  // Integration
  RKIntegrator integrator;
  integrator.addDiffEquation(&DSDT, "S", S_0);
  integrator.addDiffEquation(&DEDT, "E", E_0);
  integrator.addDiffEquation(&DIDT, "I", I_0);
  integrator.addDiffEquation(&DRDT, "R", R_0);
  GENFUNCTION suc = *integrator.getFunction(S);
  GENFUNCTION exp = *integrator.getFunction(E);
  GENFUNCTION inf = *integrator.getFunction(I);
  GENFUNCTION rec = *integrator.getFunction(R);
  GENFUNCTION infRat = inf / (suc+exp+inf+rec);

  // Plot
  PlotFunction1D pF(infRat);

  PRectF rect;
  rect.setXmin(1.0);
  rect.setXmax(ndays);
  rect.setYmin(1.e-6);
  rect.setYmax(1.0);

  PlotView view(rect);
  view.setLogX(true);
  view.setLogY(true);
  window.setCentralWidget(&view);

  view.add(&pF);
  
  PlotStream titleStream(view.titleTextEdit());
  titleStream << PlotStream::Clear()
	      << PlotStream::Center() 
	      << PlotStream::Family("Sans Serif") 
	      << PlotStream::Size(16)
              << "Flatten the Curve!"
	      << PlotStream::EndP();
  
  
  PlotStream xLabelStream(view.xLabelTextEdit());
  xLabelStream << PlotStream::Clear()
	       << PlotStream::Center()
	       << PlotStream::Family("Sans Serif")
	       << PlotStream::Size(16)
               << "Time [days]"
	       << PlotStream::EndP();
  
  PlotStream yLabelStream(view.yLabelTextEdit());
  yLabelStream << PlotStream::Clear()
	       << PlotStream::Center()
	       << PlotStream::Family("Sans Serif")
	       << PlotStream::Size(16)
               << "Infected Population Ratio"
	       << PlotStream::EndP();
  
  
  
  window.show();
  app.exec();
  return 1;
}

