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
#include <random>
#include "QatGenericFunctions/F1D.h"
#include "QatDataAnalysis/Hist1D.h"
#include "QatPlotting/PlotFunction1D.h"
#include "QatPlotting/PlotHist1D.h"

typedef std::mt19937 EngineType;

double f(double x){ return 2./sqrt(M_PI) * x * exp(-x); }

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
  rect.setXmax(10.0);
  rect.setYmin(0.0);
  rect.setYmax(1.0);
  

  //PlotView view(rect);

  // Plot Distribution
  
  PlotFunction1D pF=F1D(f);
  {
    PlotFunction1D::Properties prop;
    prop.pen.setWidth(3);
    pF.setProperties(prop);
  }

  // Create data and plot histogram
  EngineType e;
  Hist1D histogram ("MVD", 100, 0.0, 10.0);
  
  std::gamma_distribution<double> g(2.0);
  for (int i=0;i<100000;i++){
    double x = 2./sqrt(M_PI) * g(e);
    histogram.accumulate(x);
  }

  // Normalize
  double max = 2./(sqrt(M_PI)*exp(1));
  histogram *= max/histogram.maxContents();

  PlotHist1D pH=histogram;
  
  PlotView view(pH.rectHint());
  window.setCentralWidget(&view);

  // Add to plot
  view.add(&pF);
  view.add(&pH);
  
  PlotStream titleStream(view.titleTextEdit());
  titleStream << PlotStream::Clear()
	      << PlotStream::Center() 
	      << PlotStream::Family("Sans Serif") 
	      << PlotStream::Size(16)
              << "Maxwell Velocity Distribution"
	      << PlotStream::EndP();
  
  
  PlotStream xLabelStream(view.xLabelTextEdit());
  xLabelStream << PlotStream::Clear()
	       << PlotStream::Center()
	       << PlotStream::Family("Sans Serif")
	       << PlotStream::Size(16)
               << " mv^2/2tau "
	       << PlotStream::EndP();
  
  PlotStream yLabelStream(view.yLabelTextEdit());
  yLabelStream << PlotStream::Clear()
	       << PlotStream::Center()
	       << PlotStream::Family("Sans Serif")
	       << PlotStream::Size(16)
               << " rho(u) "
	       << PlotStream::EndP();
  
  
  
  window.show();
  app.exec();
  return 1;
}

