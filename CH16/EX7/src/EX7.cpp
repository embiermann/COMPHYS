#include "QatPlotWidgets/PlotView.h"
#include "QatPlotting/PlotStream.h"
#include <QApplication>
#include <QMainWindow>
#include <QToolBar>
#include <QAction>
#include <cstdlib>
#include <iostream>
#include <string>

#include "EarthMars.h"
#include "IKE.h"
#include <fstream>
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

  // Create EarthMars structure
  EarthMars earthmars;

  // Extract Data from file
  
  std::ifstream fin;
  fin.open("Mars.dat");

  // Ignore first four lines
  fin.ignore(100, '\n');
  fin.ignore(100, '\n');
  fin.ignore(100, '\n');
  fin.ignore(100, '\n');

  std::string line;
  std::string s_date, s_time;
  double ra1, ra2, ra3, dec1, dec2, dec3;
  while (getline(fin, line)){
    std::istringstream ss(line);
    if (ss >> s_date >> s_time >>
	ra1 >> ra2 >> ra3 >>
	dec1 >> dec2 >> dec3){

      // Extract year, month, and day
      double y = std::stod(s_date.substr(0,4));
      std::string s_month = s_date.substr(5,3);
      double m;
      if(s_month == "Jan") m = 1;
      else if(s_month == "Dec") m = 12;
      double d = std::stod(s_date.substr(9,2));

      // Convert to JDN (from wiki)
      double JDN = (1461*(y+4800+(m-14)/12))/4+(367*(m-2-12*((m-14)/12)))-(3*((y+4900+(m-14)/12)/100))/4 + d - 32075;

      // Convert RA to decimal
      double RA = ra1 + ra2/60. + ra3/3600.;

      // Conver DEC to decimal
      double DEC = dec1 - dec2/60. - dec3/3600.;

      // Add point
      earthmars.addPoint(JDN, RA, DEC);
      
    } 
  }

  // Close File
  fin.close();

  PlotView view(rect);
  window.setCentralWidget(&view);
  
  PlotStream titleStream(view.titleTextEdit());
  titleStream << PlotStream::Clear()
	      << PlotStream::Center() 
	      << PlotStream::Family("Sans Serif") 
	      << PlotStream::Size(16)
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
	       << PlotStream::EndP();
  
  
  
  //window.show();
  app.exec();
  return 1;
}

