/****************************************************************************
** Meta object code from reading C++ file 'application.h'
**
** Created: Sat Nov 3 21:39:24 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../MS-Analyser/Base/application.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'application.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Application[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      19,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      13,   12,   12,   12, 0x0a,
      28,   12,   12,   12, 0x0a,
      46,   12,   12,   12, 0x0a,
      66,   12,   12,   12, 0x0a,
      80,   12,   12,   12, 0x0a,
      97,   12,   12,   12, 0x0a,
     121,   12,   12,   12, 0x0a,
     156,   12,   12,   12, 0x0a,
     193,  191,   12,   12, 0x0a,
     233,   12,   12,   12, 0x0a,
     259,   12,   12,   12, 0x0a,
     274,   12,   12,   12, 0x0a,
     285,   12,   12,   12, 0x0a,
     296,   12,   12,   12, 0x0a,
     317,  191,   12,   12, 0x0a,
     342,   12,   12,   12, 0x0a,
     356,   12,   12,   12, 0x0a,
     373,   12,   12,   12, 0x0a,
     393,   12,   12,   12, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Application[] = {
    "Application\0\0pk_load_file()\0"
    "pk_load_replica()\0pk_super_spectrum()\0"
    "pk_analyzer()\0pk_buttons(bool)\0"
    "pk_context_menu(QPoint)\0"
    "pk_panel_changed(QListWidgetItem*)\0"
    "pk_panel_clicked(QListWidgetItem*)\0,\0"
    "pk_panel_clicked(QListWidgetItem*,bool)\0"
    "pk_panel_clicked_reflex()\0pk_edit_info()\0"
    "pk_clean()\0pk_merge()\0pk_panel_item_edit()\0"
    "setPlotInterval(int,int)\0infoChanged()\0"
    "modeChanged(int)\0plotPeakWeigth(int)\0"
    "peaklist_infotab_changed(int)\0"
};

void Application::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Application *_t = static_cast<Application *>(_o);
        switch (_id) {
        case 0: _t->pk_load_file(); break;
        case 1: _t->pk_load_replica(); break;
        case 2: _t->pk_super_spectrum(); break;
        case 3: _t->pk_analyzer(); break;
        case 4: _t->pk_buttons((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: _t->pk_context_menu((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 6: _t->pk_panel_changed((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 7: _t->pk_panel_clicked((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 8: _t->pk_panel_clicked((*reinterpret_cast< QListWidgetItem*(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 9: _t->pk_panel_clicked_reflex(); break;
        case 10: _t->pk_edit_info(); break;
        case 11: _t->pk_clean(); break;
        case 12: _t->pk_merge(); break;
        case 13: _t->pk_panel_item_edit(); break;
        case 14: _t->setPlotInterval((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 15: _t->infoChanged(); break;
        case 16: _t->modeChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 17: _t->plotPeakWeigth((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 18: _t->peaklist_infotab_changed((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData Application::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Application::staticMetaObject = {
    { &MainWindow::staticMetaObject, qt_meta_stringdata_Application,
      qt_meta_data_Application, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Application::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Application::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Application::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Application))
        return static_cast<void*>(const_cast< Application*>(this));
    return MainWindow::qt_metacast(_clname);
}

int Application::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = MainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 19)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 19;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
