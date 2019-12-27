#ifndef _CANVAS_CPP_
#define _CANVAS_CPP_

#include "Canvas.h"

#include <QMouseEvent>
#include <QMessageBox>
#include <iostream>

using std::cerr;
using std::cout;
using std::endl;



#include "control.h"
//#include "ui_control.h"


static void checkForGLError (const char * where)
{
	GLuint error = glGetError();
	if (error != GL_NO_ERROR) {
		cerr << "GL Error at " << where << " : " << gluErrorString(error) << endl;
	}
}


Canvas:: Canvas ( QWidget * parent) :
	QGLWidget( 	//setup opengl context
		QGLFormat(
			QGL::DoubleBuffer |
			QGL::DepthBuffer |
			QGL::Rgba |
			QGL::AlphaChannel |
			//QGL::AccumBuffer |
			//QGL::StencilBuffer |
			//QGL::StereoBuffers |
			QGL::DirectRendering |
			//QGL::HasOverlay |

			//QGL::SingleBuffer |
			//QGL::NoDepthBuffer |
			//QGL::ColorIndex |
			//QGL::NoAlphaChannel |
			QGL::NoAccumBuffer |
			QGL::NoStencilBuffer |
			QGL::NoStereoBuffers |
			//QGL::IndirectRendering |
			QGL::NoOverlay
		),
		parent
	)
{
  this->last_drag.setX( -1 );
  this->last_drag.setY( -1 );
  this->shift_down = false;
  this->tool_drag = false;
  u_drag = false;
  pxMult = 1;
  //this->resize(WINDOW_PX,WINDOW_PX) ;
  //uYOffset = 740, uXOffset = 20;
}

Canvas:: ~Canvas () {}

void Canvas:: initializeGL ()
{
	/* This sets the background color. When you call glClear(), it makes
	   the whole window this color. The arguments are floating point red, green
	   blue and alpha (opacity) values between 0 and 1. Don't worry about the
	   alpha channel. Just make it 1. Here we have a white background. */
	glClearColor(1.0, 1.0, 1.0, 1.0);

	/* This makes it so that when we plot GL_POINTS, each point will be a
	   8x8 block of pixels on the screen. We'll make our "virtual pixels"
	   nice and fat so we can see your lines/polygons in all of their
	   pixel-perfect glory.*/
	glPointSize(this->pxMult);
	//glPointSize(1);

	/* It's always wise to check for GL errors at the end of every function
	   where you make OpenGL calls */
	checkForGLError("initializeGL");
}


void Canvas:: resizeGL ( int w, int h )
{
	/* resizeGL: This function will be called when you resize the gl
	   window. It will also be called when the window is first created.
	   The two int arguments will tell you what the new width and
	   height are for the window */

	/* let OpenGL now that we are now drawing on a grid from (0,0) to (w,h) */
	glViewport(0, 0, w, h);

	/* this part sets up the projection matrix, which transforms points from
	   model/view space into screen space */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity(); /* load an identity matrix */

	/* This makes an orthographic projection (ask Bernd in class) which goes
	   from 0,0 in the lower-left corner, to w/8,h/8 in the upper-right.
	   Remeber that our "virtual pixels" take up 8x8 real screen pixels, so our
	   coordinate system is smaller than the screen's. */
	gluOrtho2D(0, w/this->pxMult, 0, h/this->pxMult);
	//gluOrtho2D(0, w, 0, h);

	/* this part sets up the model/view matrix, we'll learn about this when
	   we move on to 3D */
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	checkForGLError("resizeGL");
}


void Canvas:: paintGL ()
{
	/* paintGL: This function will be called whenever the window needs to
	   be redrawn. This happens when you tell it to with the updateGL method,
	   or when you move another window (like your web browser) over the top of
	   this window, and then move it away. */

//	engine->paint(this->view);
glClearColor(1.0, 1.0, 1.0, 1.0);
	this->engine.paint();
/*
	glColor3f(0,0,0);
	if( bezier.bezierMode )
		renderText(20, 30, "Bézier Mode");
	else
		renderText(20, 30, "B-spline Mode");

	
	
	if( bezier.editingLine != -1 )
	{
	line &line = bezier.lines[ bezier.editingLine ];	
		if( !line.bezier )
		{
			renderText(uXOffset, uYOffset, "Knot Editor");
			char buf[32];
			uStart = line.u[0];
			uEnd = line.u[line.num + line.k];
			uLen = uEnd - uStart;
			for( int i = 0; i <= line.num+line.k; i++ )
			{
				renderText( (int)( uXOffset + (line.u[i]-uStart)/(uLen)* DISPLAY_WIDTH + 0.5f ), uYOffset+20, "X" );

				sprintf( buf, "%.3f", line.u[i] );
				renderText( (int)( uXOffset + (line.u[i]-uStart)/(uLen) * DISPLAY_WIDTH + 0.5f ), uYOffset+30, QString( buf ) );
			}
			glBegin(GL_LINES);
		glVertex2i( uXOffset, WINDOW_PX - uYOffset - 16);
		glVertex2i( uXOffset + DISPLAY_WIDTH, WINDOW_PX - uYOffset - 16);
		glEnd();
		}
		
	}
*/
}








//------------------mouse events ---------------------



void Canvas:: mousePressEvent (QMouseEvent * e)
{

	vec3 ee = engine.camera.o;//( -0.1, 0, 0 );
	vec3 a = ee + engine.camera.d;//( 0.4f, 0, 0 );
	vec3 w = ee-a;
	w.normalize();
	bool bSphere;
	vec3 objectNum;
	ray r;
	vec3 pixel;
	double cu,cv;

	vec3 u = cross( engine.up, ee-a );
	u.normalize();
	vec3 v = cross( w, u );

	int i = e->x();
	int j = engine.px - e->y();

	cu = ((2.0f*i + 1)/(2.0f*engine.px) - 0.5f);
	cv = ((2.0f*j + 1)/(2.0f*engine.px) - 0.5f);
	pixel = a + u*cu + v*cv;
	r.o = ee;
	r.d = pixel-ee;
	r.d.normalize();
	//red = green = blue = 0;
	engine.trace( r, 0, 0, pixel, true, bSphere, objectNum, false );
	if( objectNum[0] != -1 )
	{
		if( bSphere )
		{
			sphere &s = engine.spheres[ (int)objectNum[0] ];
			this->ctrl->load_object( bSphere, objectNum, s.n, s.kd, s.ka, s.kr, s.ks, s.kt );
			//this->ctrl->nEdit->setText( "d" );
//			this->ctrl->iaB->setText("h");
		}
		else
		{
			Poly &p = engine.polygons[ (int)objectNum[0] ];
			this->ctrl->load_object( bSphere, objectNum, p.n, p.kd, p.ka, p.kr, p.ks, p.kt );
		}
	}
//	this->r[i+j*px] = color[0];			
//	this->g[i+j*px] = color[1];
//	this->b[i+j*px] = color[2];


//	engine.trace( 
/*
	moving = bezier.findNear( e->x(), WINDOW_PX - e->y() );
	
	switch (e->button()) {
	case Qt::LeftButton :
	  if( this->shift_down )
		  {
			  this->bezier.insertPoint( e->x(), WINDOW_PX - e->y() );
			  //polygons[numPoly].insert( revTransformX( e->x() ), revTransformY(600- e->y() ) );
			cout << "adding point" << endl;
		  }
		  else
		  {
			if( moving != 0 )
			{
				this->bezier.editingLine = this->bezier.lastLine;
			  tool_drag = true;
			  //this->selected = poly;
			  cout << "selecting: " << endl;
			  drag_start.setX( e->x() );
			  drag_start.setY( e->y() );
			}//if we hit a poly
		   }
	  if( bezier.editingLine >= 0 )
	  {
		  line &line = bezier.lines[ bezier.editingLine ];
		  float Start = line.u[0];
		  float End = line.u[line.num + line.k];
		  float Len = uEnd - uStart;
	  for( int i = 0; i < line.num+line.k; i++ )
	  {
		  int ptx = uXOffset + (line.u[i]-Start)/(Len)* DISPLAY_WIDTH;
		  int pty = uYOffset+16;

		  if( abs( ptx - e->x() ) <= U_HITBOX )
				if( abs( pty - e->y() ) <= U_HITBOX )
				{
					//bezier.editingU = i;
					editU = i;
					u_drag = true;
					break;
				}
	  }
	  }
		break;
		case Qt::RightButton:
			//cout << "right button down!" << endl;
			if( !tool_drag )
				bezier.deleteNear( e->x(), WINDOW_PX - e->y() );
			break;
		case Qt::MidButton  : cout << "middle button down!" << endl; break;
		default : cout << "how many mouse buttons do you have?" << endl;
  }

		
	e->accept();*/
}




void Canvas:: mouseMoveEvent (QMouseEvent *e)
{
	/*if( tool_drag )
	{
		if( last_drag.x() != -1 )
		{
			moving->translate( drag_start.x() - last_drag.x(), last_drag.y() - drag_start.y() );
		}
		moving->translate( e->x() - drag_start.x(), drag_start.y() - e->y() );

		last_drag.setX( e->x() );
		last_drag.setY( e->y() );
	}

	if( u_drag )
	{
		line &line = bezier.lines[ bezier.editingLine ];
		
		  float Start = line.u[0];
		  float End = line.u[line.num + line.k];
		  float Len = uEnd - uStart;

		line.u[ editU ] = ( e->x() - uXOffset)*( Len )/(float)DISPLAY_WIDTH + Start ;
		//cout << "Setting u of " << bezier.editingU << " to ";
		//cout << line.u[ bezier.editingU ] << endl;
		if( editU > 0 )
			if( line.u[ editU ] < line.u[ editU - 1] )
				line.u[ editU ] = line.u[ editU - 1];

		if( line.u[ editU ] > line.u[ editU + 1] )
			line.u[ editU ] = line.u[ editU + 1];

		if( line.u[ editU ] < 0 )
			line.u[ editU ] = 0;
	}

	e->accept();
	if( tool_drag || u_drag )
	{
		updateGL();
		//	multUpdateGL();
	}*/
}
void Canvas:: mouseReleaseEvent (QMouseEvent * e)
{
	/*tool_drag = false;
	u_drag = false;
	last_drag.setX( -1 );
	last_drag.setY( -1 );
	cout << "... and up!" << endl;
	updateGL();
	e->accept();*/
}


void Canvas:: keyPressEvent ( QKeyEvent * e ) 
{
	/*cout << (int)e->key() << endl;

	//ctrl
	if( (int)e->key() == 16777249 )
		bezier.bezierMode = true;
	//alt
	if( (int)e->key() == 16777251 )
		bezier.bezierMode = false;
	//ctrl or alt
	if( (int)e->key() == 16777249 || (int)e->key() == 16777251)
	{
		cout << bezier.lines[ bezier.num - 1].num << endl;
		if( bezier.lines[ bezier.num - 1  ].num !=0 )
			bezier.num++;
		bezier.editingLine = bezier.num - 1;
		bezier.lines[ bezier.num - 1 ].bezier = bezier.bezierMode;
	}
	
	//for some reason I can't use Qt::Key_Shift
  if( (int)e->key() == 16777248 )
  { 
    if( !this->shift_down )
      cout << "shift down" << endl;
    this->shift_down = true;
  }
  /*
	switch(e->key()) {
		case Qt::Key_W : cout << "W is " << e->state() << endl; break;
		case Qt::Key_A : cout << "A" << endl; break;
		case Qt::Key_S : cout << "S" << endl; break;
		case Qt::Key_D : cout << "D" << endl; break;
		default:;
	}
	e->accept();
	updateGL();*/
}

void Canvas::keyReleaseEvent(QKeyEvent *e)
{
	/*
  if( !e->isAutoRepeat() && e->key() == 16777248 )
  {
    cout << "shift up" << endl;
    this->shift_down = false;
  }
    //cout << "W is releasing " << e->state() << endl;
  e->accept();
  updateGL();*/
}


/*
void Canvas:: keyPressEvent ( QKeyEvent * e )
{
  if( e->key() == Qt::Key_A )
  { 
   // if( !this->shift_down )
     cout << "a down" << endl;
    this->shift_down = true;
  }
	e->accept();
}

void Canvas:: keyReleaseEvent ( QKeyEvent * e )
{
  if( e->key() == Qt::Key_A )
  { 
  //  if( !this->shift_down )
      cout << "a up" << endl;
    this->shift_down = false;
  }
	e->accept();
}
*/
void Canvas:: mouseDoubleClickEvent ( QMouseEvent * e )
{
	cout << "double click at " << e->x() << ',' << e->y() << endl;
	e->accept();
}

void Canvas::wheelEvent( QWheelEvent *e )
{
	if (e->delta() > 0) {
		cout << "wheel up" << endl;
	} else if (e->delta() < 0) {
		cout << "wheel down" << endl;
	}

	updateGL();
	e->accept();
}




#endif



//------------Directors Cut------------
//     This is the cutting room floor. literally heh...    

//multupdateGl

/*
void Canvas::multUpdateGL( void )
{
	updateGL();
	alt1->updateGL();
	alt2->updateGL();

}
*/
