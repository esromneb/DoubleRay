#ifndef _CONTROL_H_
#define _CONTROL_H_

#include "ui_control.h"
#include <QGLWidget>


#include "fileio.h"
#include "Canvas.h"

#include <iostream>
using namespace std;

class controlData : public QWidget, public Ui::control
{
	Q_OBJECT
public:

	//members
	int tool;
	//TreDEngine* engine;
	Canvas* canvas1;
	Vec3 obj;
	bool lightUpdate;
	controlData(QWidget *parent = 0)
	{
		tool = 0;
		obj[0] = -1;
//		iLightEdit = 0;
		lightUpdate = false;
	}



	//we have to call this aferward, or else radioButton's won't be initialized (which happens in setupUI)
	void activateSlots( void )
	{
		
/*		connect( radioButton, SIGNAL( clicked() ), this, SLOT( move_click() ) );
		connect( radioButton_2, SIGNAL( clicked() ), this, SLOT( rot_click() ) );
		connect( radioButton_3, SIGNAL( clicked() ), this, SLOT( scale_click() ) );*/
		connect( c, SIGNAL( textChanged(QString) ), this, SLOT( c_change(QString) ) );
		connect( nEdit, SIGNAL( textChanged(QString) ), this, SLOT( n_change(QString) ) );
		//connect( il, SIGNAL( textChanged(QString) ), this, SLOT( il_change(QString) ) );
		//connect( ia, SIGNAL( textChanged(QString) ), this, SLOT( ia_change(QString) ) );
		connect( iaR, SIGNAL( textChanged(QString) ), this, SLOT( iaR_change(QString) ) );
		connect( iaG, SIGNAL( textChanged(QString) ), this, SLOT( iaG_change(QString) ) );
		connect( iaB, SIGNAL( textChanged(QString) ), this, SLOT( iaB_change(QString) ) );
		connect( lightEdit, SIGNAL( textChanged(QString) ), this, SLOT( lightEdit_change(QString) ) );
		connect( lightx, SIGNAL( textChanged(QString) ), this, SLOT( lightx_change(QString) ) );
		connect( lighty, SIGNAL( textChanged(QString) ), this, SLOT( lighty_change(QString) ) );
		connect( lightz, SIGNAL( textChanged(QString) ), this, SLOT( lightz_change(QString) ) );
		connect( lightR, SIGNAL( textChanged(QString) ), this, SLOT( lightR_change(QString) ) );
		connect( lightG, SIGNAL( textChanged(QString) ), this, SLOT( lightG_change(QString) ) );
		connect( lightB, SIGNAL( textChanged(QString) ), this, SLOT( lightB_change(QString) ) );
		connect( camerax, SIGNAL( textChanged(QString) ), this, SLOT( camerao_change(QString) ) );
		connect( cameray, SIGNAL( textChanged(QString) ), this, SLOT( camerao_change(QString) ) );
		connect( cameraz, SIGNAL( textChanged(QString) ), this, SLOT( camerao_change(QString) ) );
		connect( cameradx, SIGNAL( textChanged(QString) ), this, SLOT( camerad_change(QString) ) );
		connect( camerady, SIGNAL( textChanged(QString) ), this, SLOT( camerad_change(QString) ) );
		connect( cameradz, SIGNAL( textChanged(QString) ), this, SLOT( camerad_change(QString) ) );
		connect( upx, SIGNAL( textChanged(QString) ), this, SLOT( cameraup_change(QString) ) );
		connect( upy, SIGNAL( textChanged(QString) ), this, SLOT( cameraup_change(QString) ) );
		connect( upz, SIGNAL( textChanged(QString) ), this, SLOT( cameraup_change(QString) ) );
		connect( kdR, SIGNAL( textChanged(QString) ), this, SLOT( kd_change(QString) ) );
		connect( kdG, SIGNAL( textChanged(QString) ), this, SLOT( kd_change(QString) ) );
		connect( kdB, SIGNAL( textChanged(QString) ), this, SLOT( kd_change(QString) ) );
		connect( ka, SIGNAL( sliderMoved(int) ), this, SLOT( ka_change(int) ) );
		connect( kr, SIGNAL( sliderMoved(int) ), this, SLOT( kr_change(int) ) );
		connect( ks, SIGNAL( sliderMoved(int) ), this, SLOT( ks_change(int) ) );
		connect( kt, SIGNAL( sliderMoved(int) ), this, SLOT( kt_change(int) ) );
		connect( maxDepth, SIGNAL( textChanged(QString) ), this, SLOT( depth_change(QString) ) );
		connect( resolution, SIGNAL( textChanged(QString) ), this, SLOT( resolution_change(QString) ) );

		connect( traceButton, SIGNAL( clicked() ), this, SLOT( trace_click() ) );
		connect( exitButton, SIGNAL( clicked() ), this, SLOT( exit_click() ) );
		//connect( reloadButton, SIGNAL( clicked() ), this, SLOT( reload_click() ) );
		/*
		connect( resolutionSlider, SIGNAL( sliderMoved(int) ), this, SLOT( resolution_change(int) ) );
		connect( orderSlider, SIGNAL( sliderMoved(int) ), this, SLOT( order_change(int) ) );
		
		connect( connectPoints, SIGNAL( toggled(bool) ), this, SLOT( connect_click(bool) ) );
		connect( saveButton, SIGNAL( clicked() ), this, SLOT( save_click() ) );*/
	}

//public :




public slots:

	void load_object( bool sphere, Vec3 objectNum, int nIN, Vec3 kd, float ka, float kr, float ks, float kt )
	{
		char buf[256];
		
		obj = objectNum;
		obj[2] = (sphere)?1:0;
		if( sphere )
		{
			sprintf( buf, "%d", objectNum[0] );
			selected->setText( QString( buf ) );
		}
		else
		{
			sprintf( buf, "%d,%d", objectNum[0], objectNum[1] );
			selected->setText( QString( buf ) );
		}

		sprintf( buf, "%g", kd[2] );
		kdB->setText( QString( buf ) );

		sprintf( buf, "%d", nIN );
		nEdit->setText( QString( buf ) );
		
		sprintf( buf, "%g", kd[0] );
		kdR->setText( QString( buf ) );

		sprintf( buf, "%g", kd[1] );
		kdG->setText( QString( buf ) );

		sprintf( buf, "%g", kd[2] );
		kdB->setText( QString( buf ) );


		this->ka->setValue( (int)(ka * 99 + 0.5) );
		this->kr->setValue( (int)(kr * 99 + 0.5) );
		this->ks->setValue( (int)(ks * 99 + 0.5) );
		this->kt->setValue( (int)(kt * 99 + 0.5) );

	}

	/*void resolution_change( int value )
	{
		char buf[256];
		sprintf( buf, "%d", value );
		this->displayResolution->setText( QString( buf ) );
		canvas1->bezier.displayResolution = value;
		canvas1->updateGL();
	}
	void order_change( int value )
	{
		line& line = canvas1->bezier.lines[canvas1->bezier.editingLine];

		if( !line.bezier )
		{
			line.k = value;
			line.forceK();

			char buf[256];
			sprintf( buf, "%d", line.k );
			this->order->setText( QString( buf ) );
			canvas1->updateGL();
		}


	}

	void connect_click( bool checked )
	{
		canvas1->bezier.connectPoints = checked;
		canvas1->updateGL();
	}
	void save_click()
	{
		save(canvas1->bezier);
	}*/

	void load_initial()
	{
		char buf[256];
		
		sprintf( buf, "%d", canvas1->engine.nLight );
		numLights->setText( QString( buf ) );
	
		//numLights->
		
		sprintf( buf, "%g", canvas1->engine.c );
		c->setText( QString( buf ) );

		sprintf( buf, "%g", canvas1->engine.ia[0] );
		iaR->setText( QString( buf ) );

		sprintf( buf, "%g", canvas1->engine.ia[1] );
		iaG->setText( QString( buf ) );

		sprintf( buf, "%g", canvas1->engine.ia[2] );
		iaB->setText( QString( buf ) );

		sprintf( buf, "%g", canvas1->engine.camera.o[0] );
		camerax->setText( QString( buf ) );

		sprintf( buf, "%g", canvas1->engine.camera.o[1] );
		cameray->setText( QString( buf ) );

		sprintf( buf, "%g", canvas1->engine.camera.o[2] );
		cameraz->setText( QString( buf ) );

		sprintf( buf, "%g", canvas1->engine.camera.d[0] );
		cameradx->setText( QString( buf ) );

		sprintf( buf, "%g", canvas1->engine.camera.d[1] );
		camerady->setText( QString( buf ) );

		sprintf( buf, "%g", canvas1->engine.camera.d[2] );
		cameradz->setText( QString( buf ) );

		sprintf( buf, "%g", canvas1->engine.up[0] );
		upx->setText( QString( buf ) );

		sprintf( buf, "%g", canvas1->engine.up[1] );
		upy->setText( QString( buf ) );

		sprintf( buf, "%g", canvas1->engine.up[2] );
		upz->setText( QString( buf ) );

		sprintf( buf, "%d", canvas1->engine.px );
		resolution->setText( QString( buf ) );

		sprintf( buf, "%d", canvas1->engine.depth );
		maxDepth->setText( QString( buf ) );







		sprintf( buf, "%g", canvas1->engine.lights[ 0 ].d[1] );
		lighty->setText( QString( buf ) );

		sprintf( buf, "%g", canvas1->engine.lights[ 0 ].d[2] );
		lightz->setText( QString( buf ) );

		sprintf( buf, "%g", canvas1->engine.lights[ 0 ].color[0] );
		lightR->setText( QString( buf ) );

		sprintf( buf, "%g", canvas1->engine.lights[ 0 ].color[1] );
		lightG->setText( QString( buf ) );

		sprintf( buf, "%g", canvas1->engine.lights[ 0 ].color[2] );
		lightB->setText( QString( buf ) );



	}

	void trace_click()
	{
		canvas1->engine.render();
		canvas1->updateGL();
	}
	void exit_click()
	{
		exit(0);
	}

	void reload_click()
	{
		read( canvas1->engine );
	}

	void c_change( QString txt )
	{
		canvas1->engine.c = txt.toInt();
	}
	void n_change( QString txt )
	{
		if( obj[2] && obj[0] != -1 ) //if sphere
		{
			canvas1->engine.spheres[ (int) obj[0] ].n = txt.toDouble();
		}
		else
		{
			canvas1->engine.polygons[ (int) obj[0] ].n = txt.toDouble();
		}
	}
	void il_change( QString txt )
	{
		//extern TreDEngine *globalEngine;
		//globalEngine->il = txt.toInt();
	}
	void ia_change( QString txt )
	{
		//extern TreDEngine *globalEngine;
		//globalEngine->ia = txt.toInt();
	}

	void lightEdit_change( QString txt )
	{
		char buf[256];
		
		if( txt.toInt() >= canvas1->engine.nLight )
			return;

		sprintf( buf, "%g", canvas1->engine.lights[ txt.toInt() ].d[0] );
		lightx->setText( QString( buf ) );

		sprintf( buf, "%g", canvas1->engine.lights[ txt.toInt() ].d[1] );
		lighty->setText( QString( buf ) );

		sprintf( buf, "%g", canvas1->engine.lights[ txt.toInt() ].d[2] );
		lightz->setText( QString( buf ) );

		sprintf( buf, "%g", canvas1->engine.lights[ txt.toInt() ].color[0] );
		lightR->setText( QString( buf ) );

		sprintf( buf, "%g", canvas1->engine.lights[ txt.toInt() ].color[1] );
		lightG->setText( QString( buf ) );

		sprintf( buf, "%g", canvas1->engine.lights[ txt.toInt() ].color[2] );
		lightB->setText( QString( buf ) );

	}
	void lightx_change( QString txt )
	{
		canvas1->engine.lights[ lightEdit->text().toInt() ].d[0] = txt.toDouble();
	}

	void lighty_change( QString txt )
	{
		canvas1->engine.lights[ lightEdit->text().toInt() ].d[1] = txt.toDouble();
	}
	void lightz_change( QString txt )
	{
		canvas1->engine.lights[ lightEdit->text().toInt() ].d[2] = txt.toDouble();
	}
	void lightR_change( QString txt )
	{
		canvas1->engine.lights[ lightEdit->text().toInt() ].color[0] = txt.toDouble();
	}

	void lightG_change( QString txt )
	{
		canvas1->engine.lights[ lightEdit->text().toInt() ].color[0] = txt.toDouble();
	}

	void lightB_change( QString txt )
	{
		canvas1->engine.lights[ lightEdit->text().toInt() ].color[0] = txt.toDouble();
	}

	void camerao_change( QString txt )
	{
		canvas1->engine.camera.o[0] = camerax->text().toDouble();
		canvas1->engine.camera.o[1] = cameray->text().toDouble();
		canvas1->engine.camera.o[2] = cameraz->text().toDouble();
	}

	void camerad_change( QString txt )
	{
		canvas1->engine.camera.d[0] = cameradx->text().toDouble();
		canvas1->engine.camera.d[1] = camerady->text().toDouble();
		canvas1->engine.camera.d[2] = cameradz->text().toDouble();
	}

	void cameraup_change( QString txt )
	{
		canvas1->engine.up[0] = upx->text().toDouble();
		canvas1->engine.up[1] = upy->text().toDouble();
		canvas1->engine.up[2] = upz->text().toDouble();
	}

	void iaR_change( QString txt )
	{
		canvas1->engine.ia[0] = txt.toDouble();
	}
	
	void iaG_change( QString txt )
	{
		canvas1->engine.ia[1] = txt.toDouble();
	}

	void iaB_change( QString txt )
	{
		canvas1->engine.ia[2] = txt.toDouble();
	}

	void ka_change( int val )
	{
		if( obj[2] && obj[0] != -1 ) //if sphere
		{
			canvas1->engine.spheres[ (int) obj[0] ].ka = (float) val / 100;
		}
		else
		{
			canvas1->engine.polygons[ (int) obj[0] ].ka = (float) val / 100;
		}
	}
	void kr_change( int val )
	{
		if( obj[2] && obj[0] != -1 ) //if sphere
		{
			canvas1->engine.spheres[ (int) obj[0] ].kr = (float) val / 100;
		}
		else
		{
			canvas1->engine.polygons[ (int) obj[0] ].kr = (float) val / 100;
		}
	}
	void ks_change( int val )
	{
		if( obj[2] && obj[0] != -1 ) //if sphere
		{
			canvas1->engine.spheres[ (int) obj[0] ].ks = (float) val / 100;
		}
		else
		{
			canvas1->engine.polygons[ (int) obj[0] ].ks = (float) val / 100;
		}
	}
	void kt_change( int val )
	{
		if( obj[2] && obj[0] != -1 ) //if sphere
		{
			canvas1->engine.spheres[ (int) obj[0] ].kt = (float) val / 100;
		}
		else
		{
			canvas1->engine.polygons[ (int) obj[0] ].kt = (float) val / 100;
		}
	}

	void kd_change( QString txt )
	{
		if( obj[2] && obj[0] != -1 ) //if sphere
		{
			canvas1->engine.spheres[ (int) obj[0] ].kd[0] = this->kdR->text().toDouble();
			canvas1->engine.spheres[ (int) obj[0] ].kd[1] = this->kdG->text().toDouble();
			canvas1->engine.spheres[ (int) obj[0] ].kd[2] = this->kdB->text().toDouble();
		}
		else
		{
			canvas1->engine.polygons[ (int) obj[0] ].kd[0] = this->kdR->text().toDouble();
			canvas1->engine.polygons[ (int) obj[0] ].kd[1] = this->kdG->text().toDouble();
			canvas1->engine.polygons[ (int) obj[0] ].kd[2] = this->kdB->text().toDouble();
		}
	}

	void depth_change( QString txt )
	{
		canvas1->engine.depth = txt.toInt();
	}

	void resolution_change( QString txt )
	{
		canvas1->engine.px = txt.toInt();
		canvas1->resize( canvas1->engine.px, canvas1->engine.px );
	}
};


#endif
