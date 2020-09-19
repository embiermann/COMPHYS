#include "QatPlotWidgets/PlotView.h"
#include "QatPlotting/PlotStream.h"
#include <QApplication>
#include <QMainWindow>
#include <QToolBar>
#include <QAction>
#include <cstdlib>
#include <iostream>
#include <string>

#include "QatPlotting/PlotFunction1D.h"
#include "QatGenericFunctions/F1D.h"
#include "QatPlotting/PlotWave1D.h"
#include "QatGenericFunctions/F2D.h"
#include "pwbarrier.h"

// Define Global Variables
double v = 1.5;
double k = 2.0;

// Define Functions to be plotted
double fREAL(double x,double t){
  double v = v;
  double k = k;
  Complex I(0,1.0);

  Complex statwave = pwFunc(x,v,k);
  Complex wave = std::exp(-I*t)*statwave;

  return std::real(wave);
}

double fIMAG(double x,double t){
  double v = v;
  double k = k;
  Complex I(0,1.0);

  Complex statwave = pwFunc(x,v,k);
  Complex wave = std::exp(-I*t)*statwave;

  return std::imag(wave);
}

double fSQUARE(double x){
  double v = v;
  double k = k;
  Complex I(0,1.0);

  Complex statwave = pwFunc(x,v,k);

  return std::real(std::conj(statwave)*statwave);
}


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

  // Plot Real part of wavefunction
  PlotWave1D pF1=Genfun::F2D(fREAL);
  {
    PlotWave1D::Properties prop1;
    prop1.pen.setWidth(3);
    pF1.setProperties(prop1);
  }
  view.add(&pF1);

  // Plot Imaginary part of wavefunction
  PlotWave1D pF2=Genfun::F2D(fIMAG);
  {
    PlotWave1D::Properties prop2;
    prop2.pen.setWidth(3);
    prop2.pen.setStyle(Qt::DashLine);
    pF2.setProperties(prop2);
  }
  view.add(&pF2);

  // Plot Prob. Dist.
  PlotFunction1D pF3=Genfun::F1D(fSQUARE);
  {
    PlotFunction1D::Properties prop3;
    prop3.pen.setWidth(3);
    prop3.pen.setStyle(Qt::DotLine);
    pF3.setProperties(prop3);
  }
  view.add(&pF2);
  
  PlotStream titleStream(view.titleTextEdit());
  titleStream << PlotStream::Clear()
	      << PlotStream::Center() 
	      << PlotStream::Family("Sans Serif") 
	      << PlotStream::Size(16)
              << "Piecewise Barrier Wavefunction"
	      << PlotStream::EndP();
  
  
  PlotStream xLabelStream(view.xLabelTextEdit());
  xLabelStream << PlotStream::Clear()
	       << PlotStream::Center()
	       << PlotStream::Family("Sans Serif")
	       << PlotStream::Size(16)
               << "x"
	       << PlotStream::EndP();
  
  PlotStream yLabelStream(view.yLabelTextEdit());
  yLabelStream << PlotStream::Clear()
	       << PlotStream::Center()
	       << PlotStream::Family("Sans Serif")
	       << PlotStream::Size(16)
               << "y"
	       << PlotStream::EndP();
  
  
  
  window.show();
  app.exec();
  return 1;
}

