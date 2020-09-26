#include "QatPlotWidgets/PlotView.h"
#include "QatPlotting/PlotStream.h"
#include <QApplication>
#include <QMainWindow>
#include <QToolBar>
#include <QAction>
#include <cstdlib>
#include <iostream>
#include <string>

#include <Eigen/Dense>
#include <cmath>
#include "QatGenericFunctions/Tanh.h"
#include "QatPlotting/PlotProfile.h"
#include "integrate.h"

using namespace Genfun;

int main (int argc, char * * argv) {

  GENFUNCTION f=Tanh();
  double trueSoln=log(cosh(1.0));
  double Nmax = 1.e3;

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
  rect.setXmin(1/Nmax);
  rect.setXmax(1.0);
  rect.setYmin(1.e-17);
  rect.setYmax(1.e-6);
  

  PlotView view(rect);
  view.setLogY(true);
  view.setLogX(true);
  window.setCentralWidget(&view);

  // Integrate and add points
  Eigen::Vector3d solns;
  PlotProfile rectInt, trapInt, simpsInt;
  for(double n=2; n<=Nmax; n+=2){
    solns = Integral(f,0.,1.,n);
    rectInt.addPoint(1./n,abs(trueSoln-solns[0]));
    trapInt.addPoint(1./n,abs(trueSoln-solns[1]));
    simpsInt.addPoint(1./n,abs(trueSoln-solns[2]));
    }

  // Define Properties
  {
    PlotProfile::Properties prop;
    prop.symbolSize = 5;
    prop.brush.setStyle(Qt::SolidPattern);
    prop.brush.setColor("blue");
    prop.pen.setColor("blue");
    rectInt.setProperties(prop);
  }
  
  {
    PlotProfile::Properties prop;
    prop.symbolSize = 5;
    prop.brush.setStyle(Qt::SolidPattern);
    prop.brush.setColor("orange");
    prop.pen.setColor("orange");
    trapInt.setProperties(prop);
  }
  {
    PlotProfile::Properties prop;
    prop.symbolSize = 5;
    prop.brush.setStyle(Qt::SolidPattern);
    prop.brush.setColor("green");
    prop.pen.setColor("green");
    simpsInt.setProperties(prop);
  }
  
  view.add(&rectInt);
  view.add(&trapInt);
  view.add(&simpsInt);
  
  PlotStream titleStream(view.titleTextEdit());
  titleStream << PlotStream::Clear()
	      << PlotStream::Center() 
	      << PlotStream::Family("Sans Serif") 
	      << PlotStream::Size(16)
              << "Integral of tanh(x) from 0 t 1 using \n"
              << PlotStream::Color("blue")
              << "Midpoint Rule "
	      << PlotStream::Color("orange")
              << "Trapezoid Rule "
	      << PlotStream::Color("green")
              << "Simpson's Rule"
	      << PlotStream::EndP();
  
  
  PlotStream xLabelStream(view.xLabelTextEdit());
  xLabelStream << PlotStream::Clear()
	       << PlotStream::Center()
	       << PlotStream::Family("Sans Serif")
	       << PlotStream::Size(16)
               << "Mesh Spacing: 1/n"
	       << PlotStream::EndP();
  
  PlotStream yLabelStream(view.yLabelTextEdit());
  yLabelStream << PlotStream::Clear()
	       << PlotStream::Center()
	       << PlotStream::Family("Sans Serif")
	       << PlotStream::Size(16)
               << "Numerical - True Result"
	       << PlotStream::EndP();
  
  
  
  window.show();
  app.exec();
  return 1;
}

