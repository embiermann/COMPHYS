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
#include "QatGenericFunctions/Sin.h"
#include "QatGenericFunctions/Cos.h"
#include "QatGenericFunctions/Exp.h"
#include "QatGenericFunctions/ButcherTableau.h"
#include "QatGenericFunctions/RKIntegrator.h"
#include "QatGenericFunctions/SimpleRKStepper.h"
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
  
  PRectF rect;
  rect.setXmin(1.0);
  rect.setXmax(100.);
  rect.setYmin(1.0);
  rect.setYmax(100.);

  //
  // Damped Harmonic oscillator:
  //

  Variable X(0,2),N(1,2);

  Sin sin;
  Cos cos;
  Exp exp;

  double T=10.;
  double x = 2.*exp(-T/2.)*sin(sqrt(3.)*T/2.)/sqrt(3.)
    + 1./3.*exp(-T/2.)*(sqrt(3.)*sin(sqrt(3.)*T/2.)+3.*cos(sqrt(3.)*T/2));
  double n = 1./3.*exp(-T/2.)*(3.*cos(sqrt(3.)*T/2.)
				    -sqrt(3.)*sin(sqrt(3.)*T/2.))
    -2.*exp(-T/2.)*sin(sqrt(3.)*T/2.)/sqrt(3.);

  GENFUNCTION DXDT=N;
  GENFUNCTION DNDT=-N-X;

  CubicSplinePolynomial del_rk;
  CubicSplinePolynomial del_mp;
  CubicSplinePolynomial del_eu;
  CubicSplinePolynomial del_tp;
  for(double h=0.001;h<1;h+=0.005){

    RK31Tableau rk31;
    SimpleRKStepper stepper1(rk31,h);
    RKIntegrator integrator1(&stepper1);
    integrator1.addDiffEquation(&DXDT,"X0",1);
    integrator1.addDiffEquation(&DNDT,"N0", 1);
    GENFUNCTION   x_rk = *integrator1.getFunction(X);
    GENFUNCTION   n_rk = *integrator1.getFunction(N);
    del_rk.addPoint(h,abs(x - x_rk(T)));

    MidpointTableau midpoint;
    SimpleRKStepper stepper2(midpoint,h); // 0.001=stepsize
    RKIntegrator integrator2(&stepper2);
    integrator2.addDiffEquation(&DXDT,"X0",1);
    integrator2.addDiffEquation(&DNDT,"N0", 1);
    GENFUNCTION   x_mp = *integrator2.getFunction(X);
    GENFUNCTION   n_mp = *integrator2.getFunction(N);
    del_rk.addPoint(h,abs(x - x_mp(T)));

    EulerTableau euler;
    SimpleRKStepper stepper3(euler,h); // 0.001=stepsize
    RKIntegrator integrator3(&stepper3);
    integrator3.addDiffEquation(&DXDT,"X0",1);
    integrator3.addDiffEquation(&DNDT,"N0", 1);
    GENFUNCTION   x_eu = *integrator3.getFunction(X);
    GENFUNCTION   n_eu = *integrator3.getFunction(N);
    del_rk.addPoint(h,abs(x - x_eu(T)));

    TrapezoidTableau trapezoid;
    SimpleRKStepper stepper4(trapezoid,h); // 0.001=stepsize
    RKIntegrator integrator4(&stepper4);
    integrator4.addDiffEquation(&DXDT,"X0",1);
    integrator4.addDiffEquation(&DNDT,"N0", 1);
    GENFUNCTION   x_tp = *integrator3.getFunction(X);
    GENFUNCTION   n_tp = *integrator3.getFunction(N);
    del_rk.addPoint(h,abs(x - x_tp(T)));
  }

  PlotFunction1D pF_rk(del_rk);
  PlotFunction1D pF_mp(del_mp);
  PlotFunction1D pF_eu(del_eu);
  PlotFunction1D pF_tp(del_tp);
  
  
  PlotView view(rect);
  view.setLogX(true);
  view.setLogY(true);
  window.setCentralWidget(&view);

  view.add(&pF_rk);
  view.add(&pF_mp);
  view.add(&pF_eu);
  view.add(&pF_tp);
  
  PlotStream titleStream(view.titleTextEdit());
  titleStream << PlotStream::Clear()
	      << PlotStream::Center() 
	      << PlotStream::Family("Sans Serif") 
	      << PlotStream::Size(16)
              << "Damped Harmonic Oscillator Solution"
	      << PlotStream::EndP();
  
  
  PlotStream xLabelStream(view.xLabelTextEdit());
  xLabelStream << PlotStream::Clear()
	       << PlotStream::Center()
	       << PlotStream::Family("Sans Serif")
	       << PlotStream::Size(16)
               << "Step Size"
	       << PlotStream::EndP();
  
  PlotStream yLabelStream(view.yLabelTextEdit());
  yLabelStream << PlotStream::Clear()
	       << PlotStream::Center()
	       << PlotStream::Family("Sans Serif")
	       << PlotStream::Size(16)
               << "|analytical solution - numerical solution|"
	       << PlotStream::EndP();
  
  
  
  window.show();
  app.exec();
  return 1;
}

