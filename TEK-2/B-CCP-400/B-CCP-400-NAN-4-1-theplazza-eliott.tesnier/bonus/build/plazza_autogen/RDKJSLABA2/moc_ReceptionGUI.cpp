/****************************************************************************
** Meta object code from reading C++ file 'ReceptionGUI.hpp'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.6.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/GUI/ReceptionGUI.hpp"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ReceptionGUI.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.6.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSReceptionGUIENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSReceptionGUIENDCLASS = QtMocHelpers::stringData(
    "ReceptionGUI",
    "onCommandEntered",
    "",
    "onStatusUpdate",
    "checkForOrderCompletions",
    "onCommandTextChanged",
    "showOrderCompleteNotification",
    "message"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSReceptionGUIENDCLASS_t {
    uint offsetsAndSizes[16];
    char stringdata0[13];
    char stringdata1[17];
    char stringdata2[1];
    char stringdata3[15];
    char stringdata4[25];
    char stringdata5[21];
    char stringdata6[30];
    char stringdata7[8];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSReceptionGUIENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSReceptionGUIENDCLASS_t qt_meta_stringdata_CLASSReceptionGUIENDCLASS = {
    {
        QT_MOC_LITERAL(0, 12),  // "ReceptionGUI"
        QT_MOC_LITERAL(13, 16),  // "onCommandEntered"
        QT_MOC_LITERAL(30, 0),  // ""
        QT_MOC_LITERAL(31, 14),  // "onStatusUpdate"
        QT_MOC_LITERAL(46, 24),  // "checkForOrderCompletions"
        QT_MOC_LITERAL(71, 20),  // "onCommandTextChanged"
        QT_MOC_LITERAL(92, 29),  // "showOrderCompleteNotification"
        QT_MOC_LITERAL(122, 7)   // "message"
    },
    "ReceptionGUI",
    "onCommandEntered",
    "",
    "onStatusUpdate",
    "checkForOrderCompletions",
    "onCommandTextChanged",
    "showOrderCompleteNotification",
    "message"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSReceptionGUIENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   44,    2, 0x08,    1 /* Private */,
       3,    0,   45,    2, 0x08,    2 /* Private */,
       4,    0,   46,    2, 0x08,    3 /* Private */,
       5,    0,   47,    2, 0x08,    4 /* Private */,
       6,    1,   48,    2, 0x08,    5 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    7,

       0        // eod
};

Q_CONSTINIT const QMetaObject ReceptionGUI::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_CLASSReceptionGUIENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSReceptionGUIENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSReceptionGUIENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<ReceptionGUI, std::true_type>,
        // method 'onCommandEntered'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onStatusUpdate'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'checkForOrderCompletions'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onCommandTextChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'showOrderCompleteNotification'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>
    >,
    nullptr
} };

void ReceptionGUI::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ReceptionGUI *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->onCommandEntered(); break;
        case 1: _t->onStatusUpdate(); break;
        case 2: _t->checkForOrderCompletions(); break;
        case 3: _t->onCommandTextChanged(); break;
        case 4: _t->showOrderCompleteNotification((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject *ReceptionGUI::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ReceptionGUI::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSReceptionGUIENDCLASS.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "IReceptionInterface"))
        return static_cast< IReceptionInterface*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int ReceptionGUI::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 5;
    }
    return _id;
}
QT_WARNING_POP
