#include "QatPlotWidgets/PlotView.h"
#include "QatPlotting/PlotStream.h"
#include <QApplication>
#include <QMainWindow>
#include <QToolBar>
#include <QAction>
#include <cstdlib>
#include <iostream>
#include <string>

#include "QatGenericFunctions/FixedConstant.h"
#include "charmS.h"

#include "QatPlotting/PlotFunction1D.h"

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
  rect.setYmax(1000);
  

  PlotView view(rect);
  window.setCentralWidget(&view);

  double mC = 1370; // MeV c^-2
  FixedConstant ES0(charmE(0) + 2.*mC);
  FixedConstant ES1(charmE(1) + 2.*mC);
  FixedConstant ES2(charmE(2) + 2.*mC);
  FixedConstant EP0(charmE(0,5.,0) + 2.*mC);
  FixedConstant EP1(charmE(1,5.,0) + 2.*mC);
  FixedConstant EP2(charmE(2,5.,0) + 2.*mC);

  PlotFunction1D pES0=ES0;
  PlotFunction1D pES1=ES1;
  PlotFunction1D pES2=ES2;
  PlotFunction1D pEP0=ES0;
  PlotFunction1D pEP1=ES1;
  PlotFunction1D pEP2=ES2;

  view.add(&pES0);
  view.add(&pES1);
  view.add(&pES2);
  view.add(&pEP0);
  view.add(&pEP1);
  view.add(&pEP2);
  
  PlotStream titleStream(view.titleTextEdit());
  titleStream << PlotStream::Clear()
	      << PlotStream::Center() 
	      << PlotStream::Family("Sans Serif") 
	      << PlotStream::Size(16)
              << "Energy Levels of Charmonium System"
	      << PlotStream::EndP();
  
  
  PlotStream xLabelStream(view.xLabelTextEdit());
  xLabelStream << PlotStream::Clear()
	       << PlotStream::Center()
	       << PlotStream::Family("Sans Serif")
	       << PlotStream::Size(16)
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
  return 1;
}

