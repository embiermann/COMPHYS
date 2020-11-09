#include "QatPlotWidgets/PlotView.h"
#include "QatPlotting/PlotStream.h"
#include <QApplication>
#include <QMainWindow>
#include <QToolBar>
#include <QAction>
#include <cstdlib>
#include <iostream>
#include <string>

#include "QatGenericFunctions/Variable.h"
#include "QatGenericFunctions/RKIntegrator.h"
#include "QatGenericFunctions/SimpleIntegrator.h"
#include "QatGenericFunctions/QuadratureRule.h"
#include "QatGenericFunctions/FixedConstant.h"
#include "QatGenericFunctions/PhaseSpace.h"
#include "QatGenericFunctions/RungeKuttaClassicalSolver.h"

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

  //
  // Dambed Harmonic oscillator:
  //

  Variable X(0,2),N(1,2);

  GENFUNCTION DXDT=N;
  GENFUNCTION DNDT=-N-X;

  RKIntegrator integrator1;
  integrator1.addDiffEquation(&DXDT,"X0",0);
  integrator1.addDiffEquation(&DNDT,"P0", 1);
  GENFUNCTION   x_rk = *integrator1.getFunction(X);
  GENFUNCTION   n_rk = *integrator1.getFunction(N);

  SimpleIntegrator integrator2(0,1,MidpointRule());
  integrator2.addDiffEquation(&DXDT,"X0",0);
  integrator2.addDiffEquation(&DNDT,"P0", 1);
  GENFUNCTION   x_e = *integrator2.getFunction(X);
  GENFUNCTION   n_e = *integrator2.getFunction(N);

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
  
  
  
  window.show();
  app.exec();
  return 1;
}

