#include "QatPlotWidgets/PlotView.h"
#include "QatPlotting/PlotStream.h"
#include <QApplication>
#include <QMainWindow>
#include <QToolBar>
#include <QAction>
#include <cstdlib>
#include <iostream>
#include <string>

#include <Eigen/Dense>
#include "QatPlotting/PlotProfile.h"
#include "QatPlotting/PlotFunction1D.h"
#include "QatGenericFunctions/InterpolatingFunction.h"

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
  rect.setXmin(150.);
  rect.setXmax(1050.);
  rect.setYmin(1.3);
  rect.setYmax(1.4);
  

  PlotView view(rect);
  window.setCentralWidget(&view);

  // Add Points, interpolate
  Eigen::VectorXd indexRefrac(17);
  indexRefrac << 1.396, 1.362, 1.349, 1.343,
                 1.339, 1.337, 1.335, 1.333,
                 1.332, 1.331, 1.331, 1.330,
                 1.329, 1.329, 1.328, 1.327,
                 1.327;
  PlotProfile indexRefracPOINTS;
  Genfun::InterpolatingFunction indexRefracFUNC;
  int i=0;
  for(double wave=200.; wave<1050.; wave+=50.){
    indexRefracPOINTS.addPoint(wave,indexRefrac(i));
    indexRefracFUNC.addPoint(wave,indexRefrac(i));
    i++;
  }
  {
    PlotProfile::Properties prop;
    prop.symbolSize=5;
    prop.brush.setStyle(Qt::SolidPattern);
    indexRefracPOINTS.setProperties(prop);
  }
  view.add(&indexRefracPOINTS);

  // Plot Function
  PlotFunction1D pF=indexRefracFUNC;
  {
    PlotFunction1D::Properties prop;
    prop.pen.setWidth(3);
    pF.setProperties(prop);
  }
  view.add(&pF);
  
  
  PlotStream titleStream(view.titleTextEdit());
  titleStream << PlotStream::Clear()
	      << PlotStream::Center() 
	      << PlotStream::Family("Sans Serif") 
	      << PlotStream::Size(16)
              << "Index of Refraction in Water"
	      << PlotStream::EndP();
  
  
  PlotStream xLabelStream(view.xLabelTextEdit());
  xLabelStream << PlotStream::Clear()
	       << PlotStream::Center()
	       << PlotStream::Family("Sans Serif")
	       << PlotStream::Size(16)
               << "Wavelength (nm)"
	       << PlotStream::EndP();
  
  PlotStream yLabelStream(view.yLabelTextEdit());
  yLabelStream << PlotStream::Clear()
	       << PlotStream::Center()
	       << PlotStream::Family("Sans Serif")
	       << PlotStream::Size(16)
               << "Index of Refraction"
	       << PlotStream::EndP();
  
  
  
  window.show();
  app.exec();
  return 1;
}

