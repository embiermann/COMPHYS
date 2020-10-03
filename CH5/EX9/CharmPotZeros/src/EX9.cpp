#include "QatPlotWidgets/PlotView.h"
#include "QatPlotting/PlotStream.h"
#include <QApplication>
#include <QMainWindow>
#include <QToolBar>
#include <QAction>
#include <cstdlib>
#include <iostream>
#include <string>

#include "QatGenericFunctions/Variable.h"
#include "QatPlotting/PlotFunction1D.h"
#include "QatPlotting/RealArg.h"
#include "QatGenericFunctions/FixedConstant.h"
#include "QatPlotting/PlotPoint.h"
#include "QatGenericFunctions/RombergIntegrator.h"
#include "QatGenericFunctions/Sqrt.h"

double newtonRaphson(Genfun::GENFUNCTION f, double x){
  double xold;
  xold = x;
  while(1){
    x -= f(x)/f.prime()(x);
    if (fabs(x-xold) < 1.0E-12) return x;
    xold=x;
  }
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
  rect.setXmax(1.5);
  rect.setYmin(-3000.0);
  rect.setYmax(3000.0);

  PlotView view(rect);
  window.setCentralWidget(&view);

  for (double E=-2000;E<900;E+=5){

    using namespace Genfun;
    Variable R;
    const double c=2.999792458e11; // mm s^-1
    const double hbar=6.5821e-10; // MeV s
    const double alpha=0.38;
    const double a=2.43e-3; // MeV^-1
  
    GENFUNCTION V=-alpha*4.*hbar*c/(3*R) + R/(hbar*c*a*a);
    PlotFunction1D pV(V,RealArg::Gt(0.0));
  
    FixedConstant fE(E);
    PlotFunction1D pE=fE;

    GENFUNCTION T=fE-V;
    double rmax=newtonRaphson(T,0.05);

    PlotPoint p(rmax,E);

    view.add(&pV);
    view.add(&pE);
    view.add(&p);

    double mC = 1370; // MeV/c^2
    double hbarC = 1.973E-15; // MeV*mm
    GENFUNCTION integrand=Sqrt()(mC*T)/(M_PI*hbarC);

    RombergIntegrator integrator(0.0,rmax, RombergIntegrator::OPEN);
    double N = integrator(integrand) - 0.75; // l=0
  
    PlotStream titleStream(view.titleTextEdit());
    titleStream << PlotStream::Clear()
    	        << PlotStream::Center() 
	        << PlotStream::Family("Sans Serif") 
	        << PlotStream::Size(16)
      //<< "Charmonium Energy Levels"
		<< "E = " << E <<"[MeV]  "
                << "N = " << N
	        << PlotStream::EndP();
  
  
    PlotStream xLabelStream(view.xLabelTextEdit());
    xLabelStream << PlotStream::Clear()
	         << PlotStream::Center()
	         << PlotStream::Family("Sans Serif")
	         << PlotStream::Size(16)
                 << "r [mm]"
	         << PlotStream::EndP();
  
    PlotStream yLabelStream(view.yLabelTextEdit());
    yLabelStream << PlotStream::Clear()
	         << PlotStream::Center()
	         << PlotStream::Family("Sans Serif")
	         << PlotStream::Size(16)
                 << "E [MeV]"
	         << PlotStream::EndP();
  
  
  
    window.show();
    app.exec();
    view.clear();
  }
  return 1;
}

