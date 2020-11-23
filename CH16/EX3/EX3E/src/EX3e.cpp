#include "QatDataAnalysis/OptParse.h"
#include "QatPlotting/PlotStream.h"
#include "QatPlotWidgets/PlotView.h"
#include "QatPlotWidgets/MultipleViewWindow.h"
#include "QatDataAnalysis/Hist1D.h"
#include "QatPlotting/PlotHist1D.h"
#include "QatPlotting/PlotProfile.h"
#include "QatPlotting/PlotFunction1D.h"
#include "QatPlotting/PlotPoint.h"
#include "QatPlotting/PlotKey.h"
#include "QatDataModeling/HistChi2Functional.h"
#include "QatDataModeling/HistLikelihoodFunctional.h"
#include "QatDataModeling/MinuitMinimizer.h"
#include "QatGenericFunctions/Sqrt.h"
#include "QatGenericFunctions/Exp.h"
#include "QatGenericFunctions/Variable.h"
#include "QatGenericFunctions/Parameter.h"
#include "QatGenericFunctions/IncompleteGamma.h"
#include "Eigen/Dense"
#include "QatGenericFunctions/Variable.h"
#include <QMainWindow>
#include <QApplication>
#include <QToolBar>
#include <QAction>
#include <QtGui>
#include <iostream>
#include <string>
#include <random>
#include <map>
#include <cmath>
#include <fstream>

class SignalCatcher : public QObject {
  Q_OBJECT
public slots:
  void quit() {
    exit(0);
  }
};

int main (int argc, char * * argv) {

  using namespace Genfun;

  // Automatically generated:-------------------------:

  std::string usage= std::string("usage: ") + argv[0]; 
  if (argc!=1) {
    std::cout << usage << std::endl;
  }


  QApplication     app(argc,argv);
  MultipleViewWindow window;
  
  QToolBar *toolBar=window.addToolBar("Tools");
  QAction  *nextAction=toolBar->addAction("Next");
  nextAction->setShortcut(QKeySequence("n"));
  QObject::connect(nextAction, SIGNAL(triggered()), &app, SLOT(quit()));

  SignalCatcher signalCatcher;
  QAction *quitAction=toolBar->addAction("Quit");
  quitAction->setShortcut(QKeySequence("q"));
  QObject::connect(quitAction, SIGNAL(triggered()), &signalCatcher, SLOT(quit()));

  // Make 2 plot view
  PlotView view1, view2;
  window.add(&view1, "Fits");
  window.add(&view2, "Quality");

  // Plot Labels
  std::map<const PlotView *, std::string>
    xLabelMap={{&view1, "x"}, {&view2, "Probability chi^2"}},
    yLabelMap={{&view1, "p(x)"},{&view2, "fit quality"}},
    titleMap={{&view1, "Probability chi^2="},{&view2, "fit quality"}};

  // Format and label plots
  for (PlotView * view : {&view1, &view2}){
    view->setXZero(false);
    view->setYZero(false);
    view->setGrid(false);
    view->setBox(false);
    PlotStream xLabelStream(view->xLabelTextEdit());
    xLabelStream
      << PlotStream::Clear()
      << PlotStream::Center()
      << PlotStream::Family("Sans Serif")
      << PlotStream::Size(16)
      << xLabelMap[view]
      << PlotStream::EndP();
    PlotStream yLabelStream(view->yLabelTextEdit());
    yLabelStream 
	  << PlotStream::Clear()
	  << PlotStream::Center() 
	  << PlotStream::Family("Sans Serif")  
	  << PlotStream::Size(16)
	  << yLabelMap[view]
	  << PlotStream::EndP();
    PlotStream titleStream(view->titleTextEdit());
    titleStream 
	  << PlotStream::Clear()
	  << PlotStream::Center() 
	  << PlotStream::Family("Sans Serif")  
	  << PlotStream::Size(16)
	  << titleMap[view]
	  << PlotStream::EndP();
    
  }

  QFont font;
  font.setPointSize(16);


  // Read data into histogram
  Hist1D hist("Spectrum", 100, 0, 1);
  
  std::ifstream indata;
  double dat;
  indata.open("data04.dat");
  if(!indata){
    std::cerr<<"Error: file could not be opened" << std::endl;
    exit(1);
  }
  indata >> dat;
  while(!indata.eof()){
    hist.accumulate(dat);
    indata >> dat;
  }
  indata.close();
    

  // Hist Functional
  HistChi2Functional objectiveFunction(&hist);
  
  // Double Peak Gaussian*Lorenzian Fit
  Parameter pMu1("Mu1", 0.5, 0.1, 4.0);
  Parameter pSig1("Sig1", 0.5, 0.1, 4.0);
  Parameter pMu2("Mu2", 0.5, 0.1, 4.0);
  Parameter pSig2("Sig2", 0.5, 0.1, 4.0);
  Parameter pGam1("Gamma1", 0.5, 0.1, 4.0);
  Parameter pGam2("Gamma2", 0.5, 0.1, 4.0);
  Parameter pT("Temperature", 5.e3, 1.e3, 1.e4);

  double h = 4.1357e-15; // eV s
  double c = 2.99792458e8; // m/s
  double k = 8.617333262e-5; // ev/K

  Sqrt sqrt;
  Exp exp;
  Variable X;
  GENFUNCTION lines = 1./(sqrt(2.*M_PI)*pSig1)*exp(-(X-pMu1)*(X-pMu1)
						  /(2.*pSig1*pSig1))
    *1./(M_PI*pGam1*(1+(X-pMu1)*(X-pMu1)/(pGam1*pGam1)))
    +1./(sqrt(2.*M_PI)*pSig2)*exp(-(X-pMu2)*(X-pMu2)/(2.*pSig2*pSig2))
    *1./(M_PI*pGam2*(1+(X-pMu2)*(X-pMu2)/(pGam2*pGam2)));
  GENFUNCTION V = c/X;
  GENFUNCTION blackbody = 2.*h*V*V*V/(c*c*(exp(h*V/(k*pT))-1));
  GENFUNCTION dist = lines*blackbody;
  
  GENFUNCTION f = hist.sum()*dist;

  // Engine for minimizing likelihood by varying parameters
  bool verbose=true;
  MinuitMinimizer minimizer(verbose);
  minimizer.addParameter(&pMu1);
  minimizer.addParameter(&pSig1);
  minimizer.addParameter(&pMu2);
  minimizer.addParameter(&pSig2);
  minimizer.addParameter(&pGam1);
  minimizer.addParameter(&pGam2);
  minimizer.addParameter(&pT);
  minimizer.addStatistic(&objectiveFunction,&f);
  minimizer.minimize();

  // Print Energy, Width, Temperature
  std::cout<<"E1 = "<<minimizer.getValue(&pMu1)<<std::endl;
  std::cout<<"E2 = "<<minimizer.getValue(&pMu2)<<std::endl;
  std::cout<<"T = "<<minimizer.getValue(&pT)<<std::endl;
  
  // Fit Quality
  Hist1D fitQuality ("FitQuality", 100, 0, 1);
  
  double fitQualityProb = 0;
  {
    double chiSquareQuality = minimizer.getFunctionValue();
    double degreesofFreedom=hist.nBins()-2;
    IncompleteGamma cumulativeChiSquareQuality=IncompleteGamma(IncompleteGamma::P);
    cumulativeChiSquareQuality.a().setValue(degreesofFreedom/2.0);
    fitQualityProb=1-cumulativeChiSquareQuality(chiSquareQuality/2.0);
    fitQuality.accumulate(fitQualityProb);
  }

  // Histogram of input data
  PlotHist1D pHist(hist);
  PlotHist1D::Properties prop;
  prop.brush.setStyle(Qt::SolidPattern);
  prop.pen.setWidth(1);
  prop.plotStyle=PlotHist1D::Properties::SYMBOLS;
  prop.symbolSize=6;
  pHist.setProperties(prop);
  {
    PRectF rect=pHist.rectHint();
    rect.setYmin(0.0);
    view1.setRect(rect);
  }

  // Fitting Function
  PlotFunction1D pGauss(f*hist.binWidth());

  view1.add(&pHist);
  view1.add(&pGauss);

  // Add fit quality value to title of plot 1
  {
    PlotStream titleStream(view1.titleTextEdit());
    titleStream
      << PlotStream::Clear()
      << PlotStream::Center()
      << PlotStream::Size(18)
      << titleMap[&view1]
      << fitQualityProb
      << PlotStream::EndP();
  }

  // Fit Quality Plot
  PlotHist1D pHistQ(fitQuality);
  view2.add(&pHistQ);
  {
    PRectF rect=pHistQ.rectHint();
    rect.setYmin(0.0);
    view2.setRect(rect);
  }  
  
  // Interact
  window.show();
  app.exec();

  // Clear
  view1.clear();
  view2.clear();
  
  return 1;
}

