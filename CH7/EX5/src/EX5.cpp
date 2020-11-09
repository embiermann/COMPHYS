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
#include "QatGenericFunctions/Exp.h"
#include "QatGenericFunctions/Erf.h"
#include "QatGenericFunctions/Variable.h"
#include "QatPlotting/PlotFunction1D.h"
#include "QatDataAnalysis/Hist1D.h"
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

  double tau = 3.0;
  double sigma = 2.0;

  // Histogram
  Hist1D histogram("CONV", 100, -10.,10.);

  
  // Plot Function
  Variable u;
  //GENFUNCTION f=tau/sqrt(sigma)*Exp()(-tau*u+2*tau*tau/sigma);
  //PlotFunction1D pf = f;
  Erf erf;
  GENFUNCTION erfc=1.0-erf;
  Exp exp;
  GENFUNCTION f=0.5/tau*exp(sigma*sigma/2/tau/tau-u/tau)*erfc(1.0/sqrt(2.0)*(sigma/tau-u/sigma));
  PlotFunction1D pf = f*histogram.binWidth()*100000;

  {
    PlotFunction1D::Properties prop;
    prop.pen.setWidth(3);
    pf.setProperties(prop);
  }

  EngineType e;
  
  std::exponential_distribution p(1/tau);
  std::normal_distribution n(0.,sigma);
  for(int i=0;i<100000;i++){
    double x1 = p(e);
    double x2 = n(e);
    histogram.accumulate(x1+x2);
  }

  PlotHist1D pH = histogram;
  {
    PlotHist1D::Properties prop;
    prop.pen.setColor("green");
    prop.pen.setWidth(3);
    pH.setProperties(prop);
  }

  // Rejection Method
  double pmax = 1/sigma/tau; //tau/sqrt(sigma)*exp(2.*tau*tau/sigma);
  std::uniform_real_distribution<double> rx(-10., 10), ry(0.,pmax);
  Hist1D hx("X", 100, -10., 10.);
  for (int i=0;i<1000000;i++){
    double x=rx(e);
    double y=ry(e);
    if (y<f(x)){
      hx.accumulate(x);
    }
  }

 // Normalize hx to histogram:
  hx*=(histogram.sum()/hx.sum());

  
  PlotHist1D px=hx;
  {
    PlotHist1D::Properties prop;
    prop.pen.setColor("blue");
    prop.pen.setWidth(3);
    px.setProperties(prop);
  }

  PlotView view(pH.rectHint());
  window.setCentralWidget(&view);

  view.add(&pH);
  view.add(&pf);
  view.add(&px);
  
  PlotStream titleStream(view.titleTextEdit());
  titleStream << PlotStream::Clear()
	      << PlotStream::Center() 
	      << PlotStream::Family("Sans Serif") 
	      << PlotStream::Size(16)
              << "Exponential Convolved with Gaussian"
	      << PlotStream::EndP();
  
  
  PlotStream xLabelStream(view.xLabelTextEdit());
  xLabelStream << PlotStream::Clear()
	       << PlotStream::Center()
	       << PlotStream::Family("Sans Serif")
	       << PlotStream::Size(16)
               << "u=x1+x2"
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

