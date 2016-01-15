/****************************************************************************
** Meta object code from reading C++ file 'water.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../SluiceController/water.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'water.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Water_t {
    QByteArrayData data[8];
    char stringdata0[79];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Water_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Water_t qt_meta_stringdata_Water = {
    {
QT_MOC_LITERAL(0, 0, 5), // "Water"
QT_MOC_LITERAL(1, 6, 12), // "levelChanged"
QT_MOC_LITERAL(2, 19, 0), // ""
QT_MOC_LITERAL(3, 20, 11), // "WATER_LEVEL"
QT_MOC_LITERAL(4, 32, 12), // "currentLevel"
QT_MOC_LITERAL(5, 45, 6), // "update"
QT_MOC_LITERAL(6, 52, 13), // "StartUpdating"
QT_MOC_LITERAL(7, 66, 12) // "StopUpdating"

    },
    "Water\0levelChanged\0\0WATER_LEVEL\0"
    "currentLevel\0update\0StartUpdating\0"
    "StopUpdating"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Water[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   37,    2, 0x08 /* Private */,
       6,    0,   38,    2, 0x0a /* Public */,
       7,    0,   39,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Water::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Water *_t = static_cast<Water *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->levelChanged((*reinterpret_cast< WATER_LEVEL(*)>(_a[1]))); break;
        case 1: _t->update(); break;
        case 2: _t->StartUpdating(); break;
        case 3: _t->StopUpdating(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (Water::*_t)(WATER_LEVEL );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Water::levelChanged)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject Water::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Water.data,
      qt_meta_data_Water,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Water::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Water::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Water.stringdata0))
        return static_cast<void*>(const_cast< Water*>(this));
    return QObject::qt_metacast(_clname);
}

int Water::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void Water::levelChanged(WATER_LEVEL _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
