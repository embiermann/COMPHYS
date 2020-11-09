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
#include "QatGenericFunctions/AssociatedLegendre.h"
#include "QatGenericFunctions/Square.h"
#include "QatDataAnalysis/Hist1D.h"
#include "QatPlotting/PlotFunction1D.h"
#include "QatPlotting/PlotHist1D.h"

typedef std::mt19937 EngineType;

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

  // Define Function
  GENFUNCTION f = Square()(sqrt(3)/sqrt(8)   * AssociatedLegendre(1,0)
			   - sqrt(7)/sqrt(6)   * AssociatedLegendre(3,0)
			   + sqrt(11)/sqrt(24) * AssociatedLegendre(5,0)
			   - sqrt(15)/sqrt(6)  * AssociatedLegendre(7,0));

  // Create Data
  EngineType e;
  double pmax = 16; // sqrt(3)/sqrt(8)   + sqrt(7)/sqrt(6)
  // + sqrt(11)/sqrt(14) + sqrt(15)/sqrt(6);
  std::uniform_real_distribution<double> rx(-1., 1.), ry(0,pmax);
  Hist1D hx("X", 100, -1., 1.);
  for (int i=0;i<1000000;i++){
    double x=rx(e);
    double y=ry(e);
    if (y<f(x)){
      hx.accumulate(x);
    }
  }

  // Normalize. Unsure how to do this
  // hx *= (2*pmax)/hx.maxContents();
  // hx -= pmax;

  // Plot
  PlotHist1D px=hx;
  {
    PlotHist1D::Properties prop;
    prop.pen.setColor("blue");
    prop.pen.setWidth(3);
    px.setProperties(prop);
  }

  PlotFunction1D pf = f*hx.binWidth()*hx.sum();
  {
    PlotFunction1D::Properties prop;
    prop.pen.setWidth(3);
    pf.setProperties(prop);
  }

  
  // Plot View

  PlotView view(px.rectHint());
  window.setCentralWidget(&view);

  view.add(&pf);
  view.add(&px);
  
  PlotStream titleStream(view.titleTextEdit());
  titleStream << PlotStream::Clear()
	      << PlotStream::Center() 
	      << PlotStream::Family("Sans Serif") 
	      << PlotStream::Size(16)
              << "Angular distribution of visible daughter particle"
	      << PlotStream::EndP();
  
  
  PlotStream xLabelStream(view.xLabelTextEdit());
  xLabelStream << PlotStream::Clear()
	       << PlotStream::Center()
	       << PlotStream::Family("Sans Serif")
	       << PlotStream::Size(16)
               << "cos(theta)"
	       << PlotStream::EndP();
  
  PlotStream yLabelStream(view.yLabelTextEdit());
  yLabelStream << PlotStream::Clear()
	       << PlotStream::Center()
	       << PlotStream::Family("Sans Serif")
	       << PlotStream::Size(16)
               << "Distribution"
	       << PlotStream::EndP();
  
  
  
  window.show();
  app.exec();
  return 1;
}

