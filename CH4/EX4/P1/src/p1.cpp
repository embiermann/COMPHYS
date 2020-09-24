#include "QatPlotWidgets/PlotView.h"
#include "QatPlotting/PlotStream.h"
#include "QatPlotting/PlotFunction1D.h"
#include "QatGenericFunctions/Theta.h"
#include "QatGenericFunctions/Variable.h"
#include "QatGenericFunctions/Exp.h"
#include <QApplication>
#include <QMainWindow>
#include <QToolBar>
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QAction>
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <string>
#include <libgen.h>

#include <Eigen/Dense>
#include <cmath>
#include "QatPlotting/PlotPoint.h"
#include "QatPlotting/PlotOrbit.h"
#include "QatGenericFunctions/InterpolatingFunction.h"
#include "QatGenericFunctions/Sin.h"
#include "QatGenericFunctions/Cos.h"


int main (int argc, char * * argv) {

  // Automatically generated:-------------------------:

  std::string usage= std::string("usage: ") + argv[0]; 
  if (argc!=1) {
    std::cout << usage << std::endl;
  }


  QApplication     app(argc,argv);
  
  QMainWindow window;
  QToolBar *toolBar=window.addToolBar("Tools");
  QAction  *nextAction=toolBar->addAction("Next");
  
  nextAction->setShortcut(QKeySequence("n"));
  
  QObject::connect(nextAction, SIGNAL(triggered()), &app, SLOT(quit()));
  
  PRectF rect;
  rect.setXmin(0.0);
  rect.setXmax(631);
  rect.setYmin(0.0);
  rect.setYmax(442);
  
 

  PlotView view(rect);
  view.setXZero(false);
  view.setYZero(false);
  view.setGrid(false);
  view.setFixedWidth(900);
  view.setFixedHeight(700);
  window.setCentralWidget(&view);

  char *wd=dirname(argv[0]);
  std::string imageName=std::string(wd)+"/../../src/p1.png";
  QPixmap imagePix(imageName.c_str());
  QGraphicsPixmapItem imagePixItem;
  imagePixItem.setPixmap(imagePix);
  //imagePixItem.setFlags(QGraphicsItem::ItemIsMovable);
  view.scene()->addItem(&imagePixItem);
  imagePixItem.setScale(1.0);
  imagePixItem.setPos(130,130);

  
  // Define x and y values for points
  Eigen::VectorXd X(9);
  X << 128., 227., 356., 392., 479., 515., 526., 521., 553.;
  Eigen::VectorXd Y(9);
  Y << 225., 303., 287., 300., 268., 237., 192., 114., 83.;

  // Plot Station Points
  PlotPoint PEN(X(0),Y(0));
  PlotPoint HER(X(1),Y(1));
  PlotPoint NEG(X(2),Y(2));
  PlotPoint ELI(X(3),Y(3));
  PlotPoint HOM(X(4),Y(4));
  PlotPoint WIL(X(5),Y(5));
  PlotPoint HAM(X(6),Y(6));
  PlotPoint ROS(X(7),Y(7));
  PlotPoint SWI(X(8),Y(8));

  // Point Properties
  {
    PlotPoint::Properties prop;
    prop.pen.setWidth(3);
    prop.symbolSize = 10;
    PEN.setProperties(prop);
    HER.setProperties(prop);
    NEG.setProperties(prop);
    ELI.setProperties(prop);
    HOM.setProperties(prop);
    WIL.setProperties(prop);
    HAM.setProperties(prop);
    ROS.setProperties(prop);
    SWI.setProperties(prop);
  }

  // Add Points
  view.add(&PEN);
  view.add(&HER);
  view.add(&NEG);
  view.add(&ELI);
  view.add(&HOM);
  view.add(&WIL);
  view.add(&HAM);
  view.add(&ROS);
  view.add(&SWI);

  // Interpolate
  Genfun::InterpolatingFunction ROUTE;
  double origX = 0.;
  double origY = 0.;
  double r, phi, delX, delY;
  for(int i=0; i<X.size(); i++){
    delX = X[i] - origX;
    delY = Y[i] - origY;
    
    r = sqrt(delX*delX + delY*delY);
    phi = 2.*M_PI - atan(delY/delX);
    //std::cout<<"phi = " << phi << "\tn";
    //std::cout<<"r = " << r << "\n";

    ROUTE.addPoint(phi, r);
  }

  Genfun::Variable Phi;
  Genfun::GENFUNCTION fX=ROUTE(Phi)*Genfun::Cos()(Phi);
  Genfun::GENFUNCTION fY=ROUTE(Phi)*Genfun::Sin()(Phi);
  PlotOrbit pF(fX, fY, 5., 7.);
  {
    PlotOrbit::Properties prop;
    prop.pen.setWidth(3);
    pF.setProperties(prop);
  }

  view.add(&pF);
  
  PlotStream titleStream(view.titleTextEdit());
  titleStream << PlotStream::Clear()
	      << PlotStream::Center() 
	      << PlotStream::Family("Sans Serif") 
	      << PlotStream::Size(16)
	      << "P1 Bus interpolated position"
	      << PlotStream::EndP();
  
  
  PlotStream xLabelStream(view.xLabelTextEdit());
  xLabelStream << PlotStream::Clear()
	       << PlotStream::Center()
	       << PlotStream::Family("Sans Serif")
	       << PlotStream::Size(16)
	       << "X position, pixel units"
	       << PlotStream::EndP();
  
  PlotStream yLabelStream(view.yLabelTextEdit());
  yLabelStream << PlotStream::Clear()
	       << PlotStream::Center()
	       << PlotStream::Family("Sans Serif")
	       << PlotStream::Size(16)
	       << "Y position, pixel units"
	       << PlotStream::EndP(); 

  view.show();
  window.show();
  app.exec();
  return 1;
}

