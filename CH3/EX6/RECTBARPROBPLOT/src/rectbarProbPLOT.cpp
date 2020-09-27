#include "QatPlotWidgets/PlotView.h"
#include "QatPlotting/PlotStream.h"
#include <QApplication>
#include <QMainWindow>
#include <QToolBar>
#include <QAction>
#include <cstdlib>
#include <iostream>
#include <string>

#include "rectbarProb.h"

// Probability Density Function:
double rectbarProb(double x){

  double v=0.5;
  double k=0.2;

  static Eigen::VectorXcd BCDF=coeff(v,k);
  
  static Complex I(0,1.0);
  static Complex nk=k*sqrt(Complex(1-v));
  static Complex B=BCDF(0);
  static Complex C=BCDF(1);
  static Complex D=BCDF(2);
  static Complex F=BCDF(3);

  //  Complex func_c = norm(B) + norm(C) + norm(D) + norm(F)
  //  + B*std::exp(-2.0*I*k*x) + std::conj(B)*std::exp(2.0*I*k*x)
  //  + std::conj(C)*D*std::exp(-2.0*I*nk*x)
  //  + std::conj(D)*C*std::exp(2.0*I*I*nk*x);


  Complex func_c;
  if (x<-1) {
    func_c=exp(I*k*x)+B*exp(-I*k*x);
  }
  else if (x<1) {
    func_c=C*exp(I*nk*x)+ D*exp(-I*nk*x);
  }
  else{
    func_c=F*exp(I*k*x);
  }
	
  return norm(func_c);;
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
  rect.setXmin(-20.0);
  rect.setXmax(20.0);
  rect.setYmin(-2.0);
  rect.setYmax(2.0);
  

  PlotView view(rect);
  window.setCentralWidget(&view);

  // Define Function to Plot
  PlotFunction1D pF=Genfun::F1D(rectbarProb);
  {
    // Set properties
    PlotFunction1D::Properties prop;
    prop.pen.setWidth(3);
    pF.setProperties(prop);
  }

  // Add to plotter
  view.add(&pF);
  
  PlotStream titleStream(view.titleTextEdit());
  titleStream << PlotStream::Clear()
	      << PlotStream::Center() 
	      << PlotStream::Family("Sans Serif") 
	      << PlotStream::Size(16)
              << "Probability Density of Step Function"
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
               << "Probability Density"
	       << PlotStream::EndP();
  
  
  
  window.show();
  app.exec();
  return 1;
}

