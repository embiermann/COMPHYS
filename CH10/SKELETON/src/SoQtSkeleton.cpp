// SoQt includes
#include <Inventor/Qt/SoQt.h>
#include <Inventor/Qt/viewers/SoQtExaminerViewer.h>
// Coin includes
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoSphere.h>
#include <Inventor/nodes/SoMaterial.h>
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

  //SoCone *cone = new SoCone;
  //cone->bottomRadius.setValue(10.);
  //root->addChild(cone);

  SoSphere *bigSphere = new SoSphere;
  bigSphere->radius.setValue(2.);
  SoMaterial *red = new SoMaterial;
  red->diffuseColor.setValue(1.0,0,0);

  SoSeparator *sep1 = new SoSeparator;
  sep1->addChild(red);
  sep1->addChild(bigSphere);
  
  SoSphere *smallSphere = new SoSphere;
  SoMaterial *white = new SoMaterial;
  white->diffuseColor.setValue(1.,1.,1.);
  smallSphere->radius.setValue(1.);

  SoSeparator *sep2 = new SoSeparator;
  sep2->addChild(white);
  sep2->addChild(smallSphere);

  root->addChild(sep1);
  root->addChild(sep2);
  
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
