// SoQt includes
#include <Inventor/Qt/SoQt.h>
#include <Inventor/Qt/viewers/SoQtExaminerViewer.h>
// Coin includes
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoCube.h>
#include <Inventor/nodes/SoCylinder.h>
#include <Inventor/nodes/SoMaterial.h>
#include <Inventor/nodes/SoTranslation.h>
#include <Inventor/nodes/SoRotationXYZ.h>
#include <Inventor/nodes/SoTexture2.h>
//#include <Inventor/draggers/SoTranslate2Dragger.h>
// Inventor includes:
#include <QApplication>
#include <QWidget>

#include <iostream>
#include <cmath>

// Make a black box in xy plane:
SoSeparator *makeBlackBox(int x, int y){
  SoSeparator *sep=new SoSeparator();

  //SoMaterial *black = new SoMaterial;
  //black->diffuseColor.setValue(0,0,0);
  //sep->addChild(black);

  SoTexture2 *txt=new SoTexture2;
  txt->filename="wood.jpg";
  sep->addChild(txt);

  SoTranslation *translation = new SoTranslation();
  translation->translation.setValue(x,y,0);
  sep->addChild(translation);

  SoCube *box = new SoCube;
  box->width=1;
  box->height=1;
  box->depth=0.1;
  sep->addChild(box);

  return sep;
}

// Make a light box in xy plane:
SoSeparator *makeRedBox(int x, int y){
  SoSeparator *sep=new SoSeparator();

  SoTexture2 *txt=new SoTexture2;
  txt->filename="wood2.jpg";
  sep->addChild(txt);

  SoTranslation *translation = new SoTranslation();
  translation->translation.setValue(x,y,0);
  sep->addChild(translation);

  SoCube *box = new SoCube;
  box->width=1;
  box->height=1;
  box->depth=0.1;
  sep->addChild(box);

  return sep;
}

// Make a black checker in xy plane:
SoSeparator *makeBlackChecker(int x, int y){
  SoSeparator *sep=new SoSeparator();

  SoMaterial *black = new SoMaterial;
  black->diffuseColor.setValue(0,0,0);
  sep->addChild(black);

  SoTranslation *translation = new SoTranslation();
  translation->translation.setValue(x,y,0.1);
  sep->addChild(translation);

  SoRotationXYZ *rotation = new SoRotationXYZ();
  //rotation->axis.setValue("Y");
  rotation->angle.setValue(M_PI/2.);
  sep->addChild(rotation);

  SoCylinder *check = new SoCylinder;
  check->radius=0.5;
  check->height=0.3;
  sep->addChild(check);

  return sep;
}

// Make a red checker in xy plane:
SoSeparator *makeRedChecker(int x, int y){
  SoSeparator *sep=new SoSeparator();

  SoMaterial *red = new SoMaterial;
  red->diffuseColor.setValue(1,0,0);
  sep->addChild(red);

  SoTranslation *translation = new SoTranslation();
  translation->translation.setValue(x,y,0.1);
  sep->addChild(translation);

  SoRotationXYZ *rotation = new SoRotationXYZ();
  //rotation->axis.setValue("Y");
  rotation->angle.setValue(M_PI/2.);
  sep->addChild(rotation);

  SoCylinder *check = new SoCylinder;
  check->radius=0.5;
  check->height=0.3;
  sep->addChild(check);

  return sep;
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
  
  // The root of a scene graph
  SoSeparator *root = new SoSeparator;
  root->ref();

  // Create Objects
  bool even=0;
  for(int j=0;j<8;j++){
    if(even){even=0;}
    else{even=1;}
    for(int i=0;i<8;i++){
      if((i+j)%2 == 0){
	root->addChild(makeBlackBox(i,j));
	if(j<3){root->addChild(makeBlackChecker(i,j));}
	if(j>5){root->addChild(makeRedChecker(i,j));}
	even = 0;
      }
      else{
	root->addChild(makeRedBox(i,j));
	even = 1;
      }
			 
    }
  }

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
