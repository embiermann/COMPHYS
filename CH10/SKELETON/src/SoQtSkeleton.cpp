// SoQt includes
#include <Inventor/Qt/SoQt.h>
#include <Inventor/Qt/viewers/SoQtExaminerViewer.h>
// Coin includes
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoCone.h>
// Inventor includes:
#include <QApplication>
#include <QWidget>

#include "Inventor/sensors/SoTimerSensor.h"
#include <iostream>

int timeCounter=0;

void callback(void *, SoSensor *){
  std::cout<<"Hello from Callback"<<std::endl;
  timeCounter++;
}
int main(int argc, char **argv)
{ 
  // Initialize the Qt system:
  QApplication app(argc, argv);
  
  // Make a main window:
  QWidget mainwin;
  mainwin.resize(400,400);

  // Initialize SoQt 
  SoQt::init(&mainwin);

  // Schedule the update:
  SoTimerSensor * timerSensor = new SoTimerSensor;
  timerSensor->setFunction(callback);
  timerSensor->setInterval(0.01);
  //timerSensor->schedule();
  
  // The root of a scene graph
  SoSeparator *root = new SoSeparator;
  root->ref();

  SoCone *cone = new SoCone;
  cone->bottomRadius.setValue(10.);
  root->addChild(cone);
  
  // Initialize an examiner viewer:
  SoQtExaminerViewer * eviewer = new SoQtExaminerViewer(&mainwin);
  eviewer->setSceneGraph(root);
  eviewer->show();
  
  // Pop up the main window.
  SoQt::show(&mainwin);

  // Loop until exit.
  SoQt::mainLoop();

  // Clean up resources.
  delete eviewer;
  root->unref();
}
