/****************************************************************************
** Meta object code from reading C++ file 'Canvas.h'
**
** Created: Mon Mar 19 23:52:24 2007
**      by: The Qt Meta Object Compiler version 59 (Qt 4.2.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Canvas.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Canvas.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.2.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

static const uint qt_meta_data_Canvas[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      10,    8,    7,    7, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Canvas[] = {
    "Canvas\0\0p\0setCoolParameter(int)\0"
};

const QMetaObject Canvas::staticMetaObject = {
    { &QGLWidget::staticMetaObject, qt_meta_stringdata_Canvas,
      qt_meta_data_Canvas, 0 }
};

const QMetaObject *Canvas::metaObject() const
{
    return &staticMetaObject;
}

void *Canvas::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Canvas))
	return static_cast<void*>(const_cast< Canvas*>(this));
    return QGLWidget::qt_metacast(_clname);
}

int Canvas::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGLWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: setCoolParameter((*reinterpret_cast< int(*)>(_a[1]))); break;
        }
        _id -= 1;
    }
    return _id;
}