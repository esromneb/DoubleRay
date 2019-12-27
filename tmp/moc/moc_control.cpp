/****************************************************************************
** Meta object code from reading C++ file 'control.h'
**
** Created: Mon Mar 19 23:52:26 2007
**      by: The Qt Meta Object Compiler version 59 (Qt 4.2.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../control.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'control.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.2.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

static const uint qt_meta_data_controlData[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
      29,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      49,   13,   12,   12, 0x0a,
     105,   12,   12,   12, 0x0a,
     120,   12,   12,   12, 0x0a,
     134,   12,   12,   12, 0x0a,
     147,   12,   12,   12, 0x0a,
     166,  162,   12,   12, 0x0a,
     184,  162,   12,   12, 0x0a,
     202,  162,   12,   12, 0x0a,
     221,  162,   12,   12, 0x0a,
     240,  162,   12,   12, 0x0a,
     266,  162,   12,   12, 0x0a,
     289,  162,   12,   12, 0x0a,
     312,  162,   12,   12, 0x0a,
     335,  162,   12,   12, 0x0a,
     358,  162,   12,   12, 0x0a,
     381,  162,   12,   12, 0x0a,
     404,  162,   12,   12, 0x0a,
     428,  162,   12,   12, 0x0a,
     452,  162,   12,   12, 0x0a,
     477,  162,   12,   12, 0x0a,
     497,  162,   12,   12, 0x0a,
     517,  162,   12,   12, 0x0a,
     541,  537,   12,   12, 0x0a,
     556,  537,   12,   12, 0x0a,
     571,  537,   12,   12, 0x0a,
     586,  537,   12,   12, 0x0a,
     601,  162,   12,   12, 0x0a,
     620,  162,   12,   12, 0x0a,
     642,  162,   12,   12, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_controlData[] = {
    "controlData\0\0sphere,objectNum,nIN,kd,ka,kr,ks,kt\0"
    "load_object(bool,vec3,int,vec3,float,float,float,float)\0"
    "load_initial()\0trace_click()\0exit_click()\0"
    "reload_click()\0txt\0c_change(QString)\0"
    "n_change(QString)\0il_change(QString)\0"
    "ia_change(QString)\0lightEdit_change(QString)\0"
    "lightx_change(QString)\0lighty_change(QString)\0"
    "lightz_change(QString)\0lightR_change(QString)\0"
    "lightG_change(QString)\0lightB_change(QString)\0"
    "camerao_change(QString)\0camerad_change(QString)\0"
    "cameraup_change(QString)\0iaR_change(QString)\0"
    "iaG_change(QString)\0iaB_change(QString)\0"
    "val\0ka_change(int)\0kr_change(int)\0"
    "ks_change(int)\0kt_change(int)\0"
    "kd_change(QString)\0depth_change(QString)\0"
    "resolution_change(QString)\0"
};

const QMetaObject controlData::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_controlData,
      qt_meta_data_controlData, 0 }
};

const QMetaObject *controlData::metaObject() const
{
    return &staticMetaObject;
}

void *controlData::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_controlData))
	return static_cast<void*>(const_cast< controlData*>(this));
    if (!strcmp(_clname, "Ui::control"))
	return static_cast< Ui::control*>(const_cast< controlData*>(this));
    return QWidget::qt_metacast(_clname);
}

int controlData::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: load_object((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< vec3(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< vec3(*)>(_a[4])),(*reinterpret_cast< float(*)>(_a[5])),(*reinterpret_cast< float(*)>(_a[6])),(*reinterpret_cast< float(*)>(_a[7])),(*reinterpret_cast< float(*)>(_a[8]))); break;
        case 1: load_initial(); break;
        case 2: trace_click(); break;
        case 3: exit_click(); break;
        case 4: reload_click(); break;
        case 5: c_change((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 6: n_change((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 7: il_change((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 8: ia_change((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 9: lightEdit_change((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 10: lightx_change((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 11: lighty_change((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 12: lightz_change((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 13: lightR_change((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 14: lightG_change((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 15: lightB_change((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 16: camerao_change((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 17: camerad_change((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 18: cameraup_change((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 19: iaR_change((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 20: iaG_change((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 21: iaB_change((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 22: ka_change((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 23: kr_change((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 24: ks_change((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 25: kt_change((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 26: kd_change((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 27: depth_change((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 28: resolution_change((*reinterpret_cast< QString(*)>(_a[1]))); break;
        }
        _id -= 29;
    }
    return _id;
}
