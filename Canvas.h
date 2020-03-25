#ifndef CANVAS_H
#define CANVAS_H

#include <QGLWidget>
//#include "3dengine.h"

#include "ui_control.h"
//#include "control.h"

#include "RayEngine.hpp"

#define WINDOW_PX 800
#define DISPLAY_WIDTH 400
#define U_HITBOX 8

class controlData;

class Canvas : public QGLWidget
{
	Q_OBJECT

	int coolParameter;

	public:

	Canvas(QWidget * parent);
	~Canvas();
	rayEngine engine;
	int pxMult;
	bool shift_down;
    bool tool_drag;
	bool u_drag;
    QPoint drag_start;
    QPoint last_drag;
//	point *moving;
	int uXOffset, uYOffset;
	int selected; //when polygons are being transformed, they are selected, and their id is stored here.
	float uStart, uEnd, uLen;
	int editU;
	//window stuff
	virtual void initializeGL();
	virtual void resizeGL(int w, int h);
	virtual void paintGL();
	controlData* ctrl;

	//mouse events
	virtual void mouseMoveEvent ( QMouseEvent * e );
	virtual void mousePressEvent ( QMouseEvent * e );
	virtual void mouseReleaseEvent ( QMouseEvent * e );
	virtual void mouseDoubleClickEvent ( QMouseEvent * e );
	virtual void wheelEvent ( QWheelEvent * e );
	virtual void keyPressEvent( QKeyEvent * e );
	virtual void keyReleaseEvent( QKeyEvent * e );
	//virtual void notify( QObject *o, QEvent *e );

	public slots: //here's where Qt deviates from standard C++.
	void setCoolParameter(int p) { coolParameter = p; updateGL(); }

};




#endif
