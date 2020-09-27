#include "QatPlotWidgets/PlotView.h"
#include "QatPlotting/PlotStream.h"
#include <QApplication>
#include <QMainWindow>
#include <QToolBar>
#include <QAction>
#include <cstdlib>
#include <iostream>
#include <string>

#include "integrate.h"
#include "QatPlotting/PlotProfile.h"
#include "QatPlotting/PlotFunction1D.h"
#include "QatGenericFunctions/F1D.h"
#include <Eigen/Dense>
#include <cmath>


int main (int argc, char * * argv) {

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

  // Plot Points
  Eigen::VectorXd thetaMax(7);
  thetaMax << M_PI/12., M_PI/6., M_PI/3.,
    M_PI/2., M_PI*2./3., M_PI*5./6., M_PI*11./12.;
  PlotProfile integralPoints;
  for(int i=0.; i<7; i++){
    integralPoints.addPoint(thetaMax[i],integrate(thetaMax[i]));
  }
  {
    PlotProfile::Properties prop;
    prop.symbolSize = 5;
    prop.brush.setStyle(Qt::SolidPattern);
    integralPoints.setProperties(prop);
  }
  view.add(&integralPoints);

  // Plot Integral Function
  
  PlotFunction1D pF=Genfun::F1D(integrate);
  {
    PlotFunction1D::Properties prop;
    prop.pen.setWidth(3);
    pF.setProperties(prop);
  }
  view.add(&pF);
  
  PlotStream titleStream(view.titleTextEdit());
  titleStream << PlotStream::Clear()
	      << PlotStream::Center() 
	      << PlotStream::Family("Sans Serif") 
	      << PlotStream::Size(16)
              << "Pendulum Period"
	      << PlotStream::EndP();
  
  
  PlotStream xLabelStream(view.xLabelTextEdit());
  xLabelStream << PlotStream::Clear()
	       << PlotStream::Center()
	       << PlotStream::Family("Sans Serif")
	       << PlotStream::Size(16)
               << "theta max"
	       << PlotStream::EndP();
  
  PlotStream yLabelStream(view.yLabelTextEdit());
  yLabelStream << PlotStream::Clear()
	       << PlotStream::Center()
	       << PlotStream::Family("Sans Serif")
	       << PlotStream::Size(16)
               << "T/T_0"
	       << PlotStream::EndP();
  
  
  
  window.show();
  app.exec();
  return 1;
}

