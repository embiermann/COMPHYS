#include "QatPlotWidgets/PlotView.h"
#include "QatPlotting/PlotStream.h"
#include "QatPlotting/PlotFunction1D.h"
#include "QatGenericFunctions/Variable.h"
#include "QatGenericFunctions/Sin.h"
#include "QatGenericFunctions/Cos.h"
#include "QatGenericFunctions/Exp.h"
#include <QApplication>
#include <QMainWindow>
#include <QToolBar>
#include <QAction>
#include <cstdlib>
#include <iostream>
#include <string>
int main (int argc, char * * argv) {

  // Automatically generated:-------------------------:

  std::string usage= std::string("usage: ") + argv[0] + " I (1 or 2) " ; 
  if (argc!=2) {
    std::cout << usage << std::endl;
    exit(0);
  }
  int i=atoi(argv[1]);
  

  QApplication     app(argc,argv);
  
  QMainWindow window;
  QToolBar *toolBar=window.addToolBar("Tools");
  QAction  *quitAction=toolBar->addAction("Quit");
  
  quitAction->setShortcut(QKeySequence("q"));
  
  QObject::connect(quitAction, SIGNAL(triggered()), &app, SLOT(quit()));
  
  PRectF rect;
  rect.setXmin(-5.0);
  rect.setXmax(5.0);
  rect.setYmin(-1.2);
  rect.setYmax(1.2);
  

  PlotView view(rect);
  window.setCentralWidget(&view);

  // My Code
  std::string title;

  Genfun::Variable X;
  Genfun::Sin    sin;
  PlotFunction1D pfunc1=sin(X);
  PlotFunction1D pfunc2=sin(5*X);;

  switch(i)
  {
    case 1:
      {
        title = "Sin(x)";
        PlotFunction1D::Properties prop;
        prop.pen.setWidth(3);
        pfunc1.setProperties(prop);
      }
      // Add to plotter
      view.add(&pfunc1);
      break;
    case 2:
      {
         title = "Sin(5x)";
        PlotFunction1D::Properties prop;
        prop.pen.setWidth(3);
        pfunc2.setProperties(prop);
      }
      // Add to plotter
      view.add(&pfunc2);
      break;
  }
  
  PlotStream titleStream(view.titleTextEdit());
  titleStream << PlotStream::Clear()
	      << PlotStream::Center() 
	      << PlotStream::Family("Sans Serif") 
	      << PlotStream::Size(16)
              << title
	      << PlotStream::EndP();
  
  
  PlotStream xLabelStream(view.xLabelTextEdit());
  xLabelStream << PlotStream::Clear()
	       << PlotStream::Center()
	       << PlotStream::Family("Sans Serif")
	       << PlotStream::Size(16)
               << "x (radians)"
	       << PlotStream::EndP();
  
  PlotStream yLabelStream(view.yLabelTextEdit());
  yLabelStream << PlotStream::Clear()
	       << PlotStream::Center()
	       << PlotStream::Family("Sans Serif")
	       << PlotStream::Size(16)
               << "y"
	       << PlotStream::EndP();
  
  
  
  window.show();
  app.exec();
  return 1;
}

