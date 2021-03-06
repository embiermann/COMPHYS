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

double f(double x){
  const double M=100 ;
  const double GAMMA=10;
  return sqrt(M*M+M*GAMMA*tan(M*GAMMA*x));
}

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

  F1D S=f;

  // Plot Analytical Distribution
  PlotFunction1D pS = (1./S).prime();
  {
    PlotFunction1D::Properties prop;
    prop.pen.setWidth(3);
    pS.setProperties(prop);
  }

  // Get Data
  EngineType e;
  std::uniform_real_distribution<double> x(0,1.);
  Hist1D hist("DIST",200,0.,200);
  for (int i=0;i<1000000;i++){
    double y=S(x(e));
    if (finite(y)) hist.accumulate(y);
  }

  // Plot
  PlotHist1D ph=hist;
  {
    PlotHist1D::Properties prop;
    prop.pen.setColor("blue");
    prop.pen.setWidth(3);
    ph.setProperties(prop);
  }

  PlotView view(ph.rectHint());
  window.setCentralWidget(&view);

  view.add(&pS);
  view.add(&ph);
  
  PlotStream titleStream(view.titleTextEdit());
  titleStream << PlotStream::Clear()
	      << PlotStream::Center() 
	      << PlotStream::Family("Sans Serif") 
	      << PlotStream::Size(16)
              << "Ch7 Example 12 Part B"
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
               << "counts"
	       << PlotStream::EndP();
  
  
  
  window.show();
  app.exec();
  return 1;
}

