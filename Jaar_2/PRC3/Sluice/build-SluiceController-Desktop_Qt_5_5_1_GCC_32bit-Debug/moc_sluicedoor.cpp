/****************************************************************************
** Meta object code from reading C++ file 'sluicedoor.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../SluiceController/sluicedoor.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'sluicedoor.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_SluiceDoor_t {
    QByteArrayData data[6];
    char stringdata0[69];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SluiceDoor_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SluiceDoor_t qt_meta_stringdata_SluiceDoor = {
    {
QT_MOC_LITERAL(0, 0, 10), // "SluiceDoor"
QT_MOC_LITERAL(1, 11, 13), // "StartUpdating"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 12), // "StopUpdating"
QT_MOC_LITERAL(4, 39, 17), // "waterLevelChanged"
QT_MOC_LITERAL(5, 57, 11) // "WATER_LEVEL"

    },
    "SluiceDoor\0StartUpdating\0\0StopUpdating\0"
    "waterLevelChanged\0WATER_LEVEL"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SluiceDoor[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   29,    2, 0x06 /* Public */,
       3,    0,   30,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    1,   31,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 5,    2,

       0        // eod
};

void SluiceDoor::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SluiceDoor *_t = static_cast<SluiceDoor *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->StartUpdating(); break;
        case 1: _t->StopUpdating(); break;
        case 2: _t->waterLevelChanged((*reinterpret_cast< WATER_LEVEL(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (SluiceDoor::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SluiceDoor::StartUpdating)) {
                *result = 0;
            }
        }
        {
            typedef void (SluiceDoor::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SluiceDoor::StopUpdating)) {
                *result = 1;
            }
        }
    }
}

const QMetaObject SluiceDoor::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_SluiceDoor.data,
      qt_meta_data_SluiceDoor,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *SluiceDoor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SluiceDoor::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_SluiceDoor.stringdata0))
        return static_cast<void*>(const_cast< SluiceDoor*>(this));
    return QObject::qt_metacast(_clname);
}

int SluiceDoor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void SluiceDoor::StartUpdating()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void SluiceDoor::StopUpdating()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
