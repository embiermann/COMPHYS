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
#include "QatPlotting/PlotPoint.h"
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
  rect.setXmin(2005.);
  rect.setXmax(2014.);
  rect.setYmin(250.);
  rect.setYmax(2000.);
  

  PlotView view(rect);
  window.setCentralWidget(&view);

  // Add Points
  Eigen::VectorXd YEAR(5);
  YEAR << 2007., 2008., 2009., 2010., 2011;
  Eigen::VectorXd PRICE(5);
  PRICE << 346., 654., 724., 873., 1410.;

  // Plot Points 
  PlotPoint P1(YEAR(0),PRICE(0));
  PlotPoint P2(YEAR(1),PRICE(1));
  PlotPoint P3(YEAR(2),PRICE(2));
  PlotPoint P4(YEAR(3),PRICE(3));
  PlotPoint P5(YEAR(4),PRICE(4));
  {
    PlotPoint::Properties prop;
    prop.pen.setWidth(3);
    prop.symbolSize = 10;
    P1.setProperties(prop);
    P2.setProperties(prop);
    P3.setProperties(prop);
    P4.setProperties(prop);
    P5.setProperties(prop);
  }
  view.add(&P1);
  view.add(&P2);
  view.add(&P3);
  view.add(&P4);
  view.add(&P5);

  // Interpolate
  Genfun::InterpolatingFunction PriceTrend;
  for(int i=0; i<YEAR.size(); i++){
    PriceTrend.addPoint(YEAR[i],PRICE[i]);
  }

  PlotFunction1D pF=PriceTrend;
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
              << "Price of Chateau Lafitte Rothschild \n"
              << "Today: $" << PriceTrend(2020.) << "\t"
	      << " Profit: $" << PriceTrend(2021) - PriceTrend(2020.)
	      << PlotStream::EndP();
  
  
  PlotStream xLabelStream(view.xLabelTextEdit());
  xLabelStream << PlotStream::Clear()
	       << PlotStream::Center()
	       << PlotStream::Family("Sans Serif")
	       << PlotStream::Size(16)
               << "Year"
	       << PlotStream::EndP();
  
  PlotStream yLabelStream(view.yLabelTextEdit());
  yLabelStream << PlotStream::Clear()
	       << PlotStream::Center()
	       << PlotStream::Family("Sans Serif")
	       << PlotStream::Size(16)
               << "Price, USD"
	       << PlotStream::EndP();
  
  
  
  window.show();
  app.exec();
  return 1;
}

