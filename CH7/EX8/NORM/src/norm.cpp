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

double psi(double d, double r, double theta, bool S=1){
  double phi1 = 1./sqrt(M_PI) * exp(-sqrt(r*r-d/2.*cos(theta)));
  double phi2 = 1./sqrt(M_PI) * exp(-sqrt(r*r+d/2.*cos(theta)));

  if(S){ return phi1+phi2; }
  else{return phi1-phi2; }
}

double normS(double d){
  std::mt19937 e;
  std::uniform_real_distribution<double> flat;
  const int N=100000;

  double sum=0.0;
  for(int i=0;i<N;i++){x
    double r = flat(e);
    double theta = flat(e);
    double y = psi(d,r,theta,1) * psi(d, r, theta, 1);
    sum += y;
  }

  return 1./sqrt(sum/N);
}

double normA(double d){
  std::mt19937 e;
  std::uniform_real_distribution<double> flat;
  const int N=100000;

  double sum=0.0;
  for(int i=0;i<N;i++){
    double r = flat(e);
    double theta = flat(e);
    double y = psi(d,r,theta,1) * psi(d, r, theta, 0);
    sum += y;
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
  rect.setXmax(1.0);
  rect.setYmin(0.0);
  rect.setYmax(1.0);
  

  PlotView view(rect);
  window.setCentralWidget(&view);

  PlotFunction1D pf1=Genfun::F1D(normS);
  {
    PlotFunction1D::Properties prop;
    prop.pen.setWidth(3);
    pf1.setProperties(prop);
  }
  PlotFunction1D pf2=Genfun::F1D(normA);
  {
    PlotFunction1D::Properties prop;
    prop.pen.setWidth(3);
    prop.pen.setColor("blue");
    pf2.setProperties(prop);
  }

  view.add(&pf1);
  view.add(&pf2);
  
  PlotStream titleStream(view.titleTextEdit());
  titleStream << PlotStream::Clear()
	      << PlotStream::Center() 
	      << PlotStream::Family("Sans Serif") 
	      << PlotStream::Size(16)
              << "Normalization of S (black) and A (blue)"
	      << PlotStream::EndP();
  
  
  PlotStream xLabelStream(view.xLabelTextEdit());
  xLabelStream << PlotStream::Clear()
	       << PlotStream::Center()
	       << PlotStream::Family("Sans Serif")
	       << PlotStream::Size(16)
               << "d"
	       << PlotStream::EndP();
  
  PlotStream yLabelStream(view.yLabelTextEdit());
  yLabelStream << PlotStream::Clear()
	       << PlotStream::Center()
	       << PlotStream::Family("Sans Serif")
	       << PlotStream::Size(16)
               << "Norm"
	       << PlotStream::EndP();
  
  
  
  window.show();
  app.exec();
  return 1;
}

