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
#include "QatGenericFunctions/Cos.h"
#include "QatGenericFunctions/Sin.h"
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
  rect.setXmin(0.0);
  rect.setXmax(2*M_PI);
  rect.setYmin(0.0);
  rect.setYmax(2*M_PI);
  
  RKIntegrator integrator;
  Variable Theta1(0,4),Theta2(1,4),P1(2,4),P2(3,4);
  
  double m1 = 1.0; // kg
  double m2 = 1.0; // kg
  double l1 = 1.0; // m
  double l2 = 1.0; // m
  double g = 9.8; // m/s^2
  
  double theta1_0 = M_PI/12;
  double theta2_0 = M_PI/12;
  
  Cos cos;
  Sin sin;
  GENFUNCTION S = m1 + m2*sin(Theta1-Theta2)*sin(Theta1-Theta2);
  GENFUNCTION C1 = P1*P2*sin(Theta1-Theta2)/(l1*l2*S);
  GENFUNCTION C2 = (l2*l2*m2*P1*P1+l1*l1*(m1+m2)
		    *P2*P2-l1*l2*m2*P1*P2*cos(Theta1-Theta2))
                    *sin(2*(Theta1-Theta2))
                    /(2*l1*l1*l2*l2*S*S);

  GENFUNCTION DT1DT = (l2*P1-l1*P2*cos(Theta1-Theta2))/(l1*l1*l2*S);
  GENFUNCTION DT2DT = (l1*(m1+m2)*P2-l2*m2*P1*cos(Theta1-Theta2))
                    /(l1*l2*l2*m2*S);
  GENFUNCTION DP1DT = -(m1+m2)*g*l1*sin(Theta1)-C1+C2;
  GENFUNCTION DP2DT = -m2*g*l2*sin(Theta2)+C1-C2;

  integrator.addDiffEquation(&DT1DT, "T1_0", theta1_0);
  integrator.addDiffEquation(&DT2DT, "T2_0", theta2_0);
  integrator.addDiffEquation(&DP1DT, "P1_0", 0);
  integrator.addDiffEquation(&DP2DT, "P2_0", 0);

  GENFUNCTION theta1 = *integrator.getFunction(Theta1);
  GENFUNCTION theta2 = *integrator.getFunction(Theta2);

  PlotView view(rect);
  window.setCentralWidget(&view);

  CubicSplinePolynomial cSpline;
  for (unsigned int t=0;t<10;t++){
    cSpline.addPoint(theta1(t),theta2(t));
  }

  PlotFunction1D pF(cSpline);
  
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

