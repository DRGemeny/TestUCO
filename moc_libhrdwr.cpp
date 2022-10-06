/****************************************************************************
** Meta object code from reading C++ file 'libhrdwr.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../ClientUCODN31/libhrdwr.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'libhrdwr.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_LibHrdwr_t {
    QByteArrayData data[10];
    char stringdata0[74];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_LibHrdwr_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_LibHrdwr_t qt_meta_stringdata_LibHrdwr = {
    {
QT_MOC_LITERAL(0, 0, 8), // "LibHrdwr"
QT_MOC_LITERAL(1, 9, 8), // "ErrorSig"
QT_MOC_LITERAL(2, 18, 0), // ""
QT_MOC_LITERAL(3, 19, 3), // "str"
QT_MOC_LITERAL(4, 23, 3), // "res"
QT_MOC_LITERAL(5, 27, 9), // "ErrorSig3"
QT_MOC_LITERAL(6, 37, 7), // "ShowMes"
QT_MOC_LITERAL(7, 45, 5), // "msg_t"
QT_MOC_LITERAL(8, 51, 6), // "outMsg"
QT_MOC_LITERAL(9, 58, 15) // "connectedServer"

    },
    "LibHrdwr\0ErrorSig\0\0str\0res\0ErrorSig3\0"
    "ShowMes\0msg_t\0outMsg\0connectedServer"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_LibHrdwr[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   39,    2, 0x06 /* Public */,
       1,    1,   44,    2, 0x06 /* Public */,
       5,    1,   47,    2, 0x06 /* Public */,
       6,    1,   50,    2, 0x06 /* Public */,
       9,    0,   53,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::Int,    3,    4,
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void,

       0        // eod
};

void LibHrdwr::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        LibHrdwr *_t = static_cast<LibHrdwr *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->ErrorSig((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->ErrorSig((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->ErrorSig3((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->ShowMes((*reinterpret_cast< msg_t(*)>(_a[1]))); break;
        case 4: _t->connectedServer(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (LibHrdwr::*)(QString , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&LibHrdwr::ErrorSig)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (LibHrdwr::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&LibHrdwr::ErrorSig)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (LibHrdwr::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&LibHrdwr::ErrorSig3)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (LibHrdwr::*)(msg_t );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&LibHrdwr::ShowMes)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (LibHrdwr::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&LibHrdwr::connectedServer)) {
                *result = 4;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject LibHrdwr::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_LibHrdwr.data,
      qt_meta_data_LibHrdwr,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *LibHrdwr::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *LibHrdwr::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_LibHrdwr.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int LibHrdwr::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void LibHrdwr::ErrorSig(QString _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void LibHrdwr::ErrorSig(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void LibHrdwr::ErrorSig3(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void LibHrdwr::ShowMes(msg_t _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void LibHrdwr::connectedServer()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
