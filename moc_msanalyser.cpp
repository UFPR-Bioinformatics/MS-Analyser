/****************************************************************************
** Meta object code from reading C++ file 'msanalyser.h'
**
** Created: Tue Apr 23 10:20:28 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../MS-Analyser/MS-Analyser/msanalyser.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'msanalyser.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MSAnalyser[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x0a,
      26,   11,   11,   11, 0x0a,
      41,   39,   11,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_MSAnalyser[] = {
    "MSAnalyser\0\0loadReplica()\0loadSingle()\0"
    ",\0selectionChanged(int,int)\0"
};

void MSAnalyser::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MSAnalyser *_t = static_cast<MSAnalyser *>(_o);
        switch (_id) {
        case 0: _t->loadReplica(); break;
        case 1: _t->loadSingle(); break;
        case 2: _t->selectionChanged((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData MSAnalyser::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MSAnalyser::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_MSAnalyser,
      qt_meta_data_MSAnalyser, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MSAnalyser::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MSAnalyser::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MSAnalyser::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MSAnalyser))
        return static_cast<void*>(const_cast< MSAnalyser*>(this));
    return QWidget::qt_metacast(_clname);
}

int MSAnalyser::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
