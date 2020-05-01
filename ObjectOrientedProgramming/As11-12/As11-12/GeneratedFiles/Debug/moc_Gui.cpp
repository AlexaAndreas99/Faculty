/****************************************************************************
** Meta object code from reading C++ file 'Gui.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Gui.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Gui.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Gui_t {
    QByteArrayData data[16];
    char stringdata0[157];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Gui_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Gui_t qt_meta_stringdata_Gui = {
    {
QT_MOC_LITERAL(0, 0, 3), // "Gui"
QT_MOC_LITERAL(1, 4, 21), // "connectSignalAndSlots"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 17), // "moveDogToAdoption"
QT_MOC_LITERAL(4, 45, 9), // "deleteDog"
QT_MOC_LITERAL(5, 55, 11), // "moveAllDogs"
QT_MOC_LITERAL(6, 67, 9), // "addNewDog"
QT_MOC_LITERAL(7, 77, 10), // "filterDogs"
QT_MOC_LITERAL(8, 88, 9), // "updateDog"
QT_MOC_LITERAL(9, 98, 4), // "next"
QT_MOC_LITERAL(10, 103, 4), // "open"
QT_MOC_LITERAL(11, 108, 12), // "openAdoption"
QT_MOC_LITERAL(12, 121, 14), // "iteratedFilter"
QT_MOC_LITERAL(13, 136, 4), // "undo"
QT_MOC_LITERAL(14, 141, 4), // "redo"
QT_MOC_LITERAL(15, 146, 10) // "new_window"

    },
    "Gui\0connectSignalAndSlots\0\0moveDogToAdoption\0"
    "deleteDog\0moveAllDogs\0addNewDog\0"
    "filterDogs\0updateDog\0next\0open\0"
    "openAdoption\0iteratedFilter\0undo\0redo\0"
    "new_window"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Gui[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   84,    2, 0x08 /* Private */,
       3,    0,   85,    2, 0x08 /* Private */,
       4,    0,   86,    2, 0x08 /* Private */,
       5,    0,   87,    2, 0x08 /* Private */,
       6,    0,   88,    2, 0x08 /* Private */,
       7,    0,   89,    2, 0x08 /* Private */,
       8,    0,   90,    2, 0x08 /* Private */,
       9,    0,   91,    2, 0x08 /* Private */,
      10,    0,   92,    2, 0x08 /* Private */,
      11,    0,   93,    2, 0x08 /* Private */,
      12,    0,   94,    2, 0x08 /* Private */,
      13,    0,   95,    2, 0x08 /* Private */,
      14,    0,   96,    2, 0x08 /* Private */,
      15,    0,   97,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Gui::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Gui *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->connectSignalAndSlots(); break;
        case 1: _t->moveDogToAdoption(); break;
        case 2: _t->deleteDog(); break;
        case 3: _t->moveAllDogs(); break;
        case 4: _t->addNewDog(); break;
        case 5: _t->filterDogs(); break;
        case 6: _t->updateDog(); break;
        case 7: _t->next(); break;
        case 8: _t->open(); break;
        case 9: _t->openAdoption(); break;
        case 10: _t->iteratedFilter(); break;
        case 11: _t->undo(); break;
        case 12: _t->redo(); break;
        case 13: _t->new_window(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject Gui::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_Gui.data,
    qt_meta_data_Gui,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Gui::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Gui::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Gui.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int Gui::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 14;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
