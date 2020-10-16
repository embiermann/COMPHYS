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
#include "QatGenericFunctions/Variable.h"
#include "QatGenericFunctions/Exp.h"
#include "QatGenericFunctions/Sqrt.h"
#include "QatGenericFunctions/Cos.h"
#include "QatGenericFunctions/Sin.h"
#include "QatGenericFunctions/F1D.h"
#include "QatPlotting/PlotFunction1D.h"

using namespace Genfun;

GENFUNCTION Laplace(GENFUNCTION f){
  Variable R;
  Variable Theta;
  return 1./(R*R)*(R*R*f.partial(&R)).partial(&R)
    +1./(R*R*Sin(Theta))*(Sin(Theta)*f.partial(&Theta)).partial(&Theta);
}

GENFUNCTION Hamiltonian(GENFUNCTION f){
  Variable R;
  Variable Theta;
  GENFUNCTION H=-0.5*Laplace(f)
               -1./Sqrt(R*R+d/2.*Cos(Theta))*f
               +1./Sqrt(R*R-d/2.*Cos(Theta))*f;
  return H;
}

double energyS(double d){
  Variable R;
  Variable Theta;
  GENFUNCTION phi1 = 1./sqrt(M_PI) * Exp(-Sqrt(R*R-d/2.*Cos(Theta)));
  GENFUNCTION phi2 = 1./sqrt(M_PI) * Exp(-Sqrt(R*R+d/2.*Cos(Theta)));
  GENFUNCTION psi = phi1+phi2;
  GENFUNCTION E=psi*H(psi);
  
  std::mt19937 e;
  std::uniform_real_distribution<double> flat;
  const int N=100000;

  double sum=0.0;
  for(int i=0;i<N;i++){
    double r = flat(e);
    double theta = flat(e);
    double y = E(R=r,Theta=theta);
    sum += y;
  }
  return 1./Sqrt(sum/N);
}

double energyA(double d){
  Variable R;
  Variable Theta;
  GENFUNCTION phi1 = 1./sqrt(M_PI) * Exp(-Sqrt(R*R-d/2.*Cos(Theta)));
  GENFUNCTION phi2 = 1./sqrt(M_PI) * Exp(-Sqrt(R*R+d/2.*Cos(Theta)));
  GENFUNCTION psi = phi1-phi2;
  GENFUNCTION E=psi*H(psi);
  
  std::mt19937 e;
  std::uniform_real_distribution<double> flat;
  const int N=100000;

  double sum=0.0;
  for(int i=0;i<N;i++){
    double r = flat(e);
    double theta = flat(e);
    double y = E(R=r,Theta=theta);
    sum += y;
  }
  return 1./Sqrt(sum/N);
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

  PlotFunction1D pf1=Genfun::F1D(energyS);
  {
    PlotFunction1D::Properties prop;
    prop.pen.setWidth(3);
    pf1.setProperties(prop);
  }
  PlotFunction1D pf2=Genfun::F1D(energyA);
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
              << "Energy of S (black) and A (blue)"
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
               << "Energy"
	       << PlotStream::EndP();
  
  
  
  window.show();
  app.exec();
  return 1;
}

