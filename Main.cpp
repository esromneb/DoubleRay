

#include <iostream>
#include <QGLWidget>

#include <QApplication>

#include <QtDesigner/QtDesigner>
#include "Canvas.h"


//#include "ui_control.h"

#include <QWidget>

#include "raytrace.h"

#include "control.h"
#include "fileio.h"
//Canvas *globalCanvas1;
using namespace::Ui;


//TreDEngine *globalEngine;

int main ( int argc, char ** argv )
{
	QApplication app( argc, argv );



	Canvas * canvas1 = new Canvas(NULL); 

	canvas1->resize(400,400);
	canvas1->engine.resize( 400 );
	canvas1->setWindowTitle( "Ben Morse Hw 5" );
	//creating a widget doesn't make it visible.
	//we have to do that by calling show()
	canvas1->show();

	read( canvas1->engine );


	QWidget w;
	controlData ctrl;
	ctrl.canvas1 = canvas1;
	ctrl.setupUi(&w); //initilize the ui
	ctrl.load_initial(); //load initial values from engine
	ctrl.activateSlots(); //setup slots
	w.show(); //show window

	canvas1->ctrl = &ctrl;
/*
	//tell the canvas's about the toolbox

	canvas2->ctrl = &ctrl;
	canvas3->ctrl = &ctrl;
*/
	
	//canvas1->activateWindow();
	
//  ctrl.tool = 0;
	app.connect( &app, SIGNAL( lastWindowClosed() ), &app, SLOT( quit() ) );
	return app.exec(); //here we enter the Qt main event loop

}
