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

  // My Code
  std::string title;
  switch(1)
  {
    case(1): PlotFunction1D pfunc1=Genfun::Sin();
      {
        title = "Sin(x)";
        PlotFunction1D::Properties prop;
        prop.pen.setWidth(3);
        pfunc1.setProperties(prop);
      }
      // Add to plotter
      view.add(&pfunc1);
      break;

    case(2): PlotFunction1D pfunc2=Genfun::Sin();
      {
        //Genfun::Variable X;
        //Genfun::Sin() sin;
        //pfunc = Genfun::GENFUNCTION sin(5.0*X);
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

