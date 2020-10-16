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
#include "QatPlotting/PlotFunction1D.h"

double flux(double lambda){
  std::mt19937 e;
  std::exponential_distribution<double> dist(1./lambda);
  const int N=100000;
  double sum=0.0;
  for (int i=0; i<N; i++){
    double x = dist(e);
    sum += x;
  }
  return 1./sqrt(sum/N);
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
  rect.setXmax(10.0);
  rect.setYmin(0.0);
  rect.setYmax(1.0);

  PlotFunction1D pf=Genfun::F1D(flux);
  {
    PlotFunction1D::Properties prop;
    prop.pen.setWidth(3);
    pf.setProperties(prop);
  }
  

  PlotView view(rect);
  window.setCentralWidget(&view);

  view.add(&pf);
  
  PlotStream titleStream(view.titleTextEdit());
  titleStream << PlotStream::Clear()
	      << PlotStream::Center() 
	      << PlotStream::Family("Sans Serif") 
	      << PlotStream::Size(16)
              << "Gamma Decay"
	      << PlotStream::EndP();
  
  
  PlotStream xLabelStream(view.xLabelTextEdit());
  xLabelStream << PlotStream::Clear()
	       << PlotStream::Center()
	       << PlotStream::Family("Sans Serif")
	       << PlotStream::Size(16)
               << "lambda"
	       << PlotStream::EndP();
  
  PlotStream yLabelStream(view.yLabelTextEdit());
  yLabelStream << PlotStream::Clear()
	       << PlotStream::Center()
	       << PlotStream::Family("Sans Serif")
	       << PlotStream::Size(16)
               << "Flux"
	       << PlotStream::EndP();
  
  
  
  window.show();
  app.exec();
  return 1;
}

