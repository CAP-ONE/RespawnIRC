/****************************************************************************
** Meta object code from reading C++ file 'showTopicMessages.hpp'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../respawnIrc/showTopicMessages.hpp"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'showTopicMessages.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_showTopicMessagesClass_t {
    QByteArrayData data[29];
    char stringdata0[431];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_showTopicMessagesClass_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_showTopicMessagesClass_t qt_meta_stringdata_showTopicMessagesClass = {
    {
QT_MOC_LITERAL(0, 0, 22), // "showTopicMessagesClass"
QT_MOC_LITERAL(1, 23, 16), // "quoteThisMessage"
QT_MOC_LITERAL(2, 40, 0), // ""
QT_MOC_LITERAL(3, 41, 14), // "messageToQuote"
QT_MOC_LITERAL(4, 56, 14), // "addToBlacklist"
QT_MOC_LITERAL(5, 71, 17), // "pseudoToBlacklist"
QT_MOC_LITERAL(6, 89, 15), // "editThisMessage"
QT_MOC_LITERAL(7, 105, 15), // "idOfMessageEdit"
QT_MOC_LITERAL(8, 121, 16), // "newMessageStatus"
QT_MOC_LITERAL(9, 138, 20), // "newNumberOfConnected"
QT_MOC_LITERAL(10, 159, 11), // "setEditInfo"
QT_MOC_LITERAL(11, 171, 11), // "messageEdit"
QT_MOC_LITERAL(12, 183, 10), // "infoToSend"
QT_MOC_LITERAL(13, 194, 11), // "cpatchaLink"
QT_MOC_LITERAL(14, 206, 20), // "newMessagesAvailable"
QT_MOC_LITERAL(15, 227, 15), // "newNameForTopic"
QT_MOC_LITERAL(16, 243, 7), // "newName"
QT_MOC_LITERAL(17, 251, 11), // "linkClicked"
QT_MOC_LITERAL(18, 263, 4), // "link"
QT_MOC_LITERAL(19, 268, 11), // "getEditInfo"
QT_MOC_LITERAL(20, 280, 17), // "idOfMessageToEdit"
QT_MOC_LITERAL(21, 298, 12), // "getQuoteInfo"
QT_MOC_LITERAL(22, 311, 17), // "idOfMessageQuoted"
QT_MOC_LITERAL(23, 329, 11), // "getMessages"
QT_MOC_LITERAL(24, 341, 19), // "loadFirstPageFinish"
QT_MOC_LITERAL(25, 361, 20), // "loadSecondPageFinish"
QT_MOC_LITERAL(26, 382, 15), // "analyzeEditInfo"
QT_MOC_LITERAL(27, 398, 16), // "analyzeQuoteInfo"
QT_MOC_LITERAL(28, 415, 15) // "analyzeMessages"

    },
    "showTopicMessagesClass\0quoteThisMessage\0"
    "\0messageToQuote\0addToBlacklist\0"
    "pseudoToBlacklist\0editThisMessage\0"
    "idOfMessageEdit\0newMessageStatus\0"
    "newNumberOfConnected\0setEditInfo\0"
    "messageEdit\0infoToSend\0cpatchaLink\0"
    "newMessagesAvailable\0newNameForTopic\0"
    "newName\0linkClicked\0link\0getEditInfo\0"
    "idOfMessageToEdit\0getQuoteInfo\0"
    "idOfMessageQuoted\0getMessages\0"
    "loadFirstPageFinish\0loadSecondPageFinish\0"
    "analyzeEditInfo\0analyzeQuoteInfo\0"
    "analyzeMessages"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_showTopicMessagesClass[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      18,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       8,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,  104,    2, 0x06 /* Public */,
       4,    1,  107,    2, 0x06 /* Public */,
       6,    1,  110,    2, 0x06 /* Public */,
       8,    0,  113,    2, 0x06 /* Public */,
       9,    0,  114,    2, 0x06 /* Public */,
      10,    4,  115,    2, 0x06 /* Public */,
      14,    0,  124,    2, 0x06 /* Public */,
      15,    1,  125,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      17,    1,  128,    2, 0x0a /* Public */,
      19,    1,  131,    2, 0x0a /* Public */,
      19,    0,  134,    2, 0x2a /* Public | MethodCloned */,
      21,    1,  135,    2, 0x0a /* Public */,
      23,    0,  138,    2, 0x0a /* Public */,
      24,    0,  139,    2, 0x0a /* Public */,
      25,    0,  140,    2, 0x0a /* Public */,
      26,    0,  141,    2, 0x0a /* Public */,
      27,    0,  142,    2, 0x0a /* Public */,
      28,    0,  143,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::QString, QMetaType::QString, QMetaType::QString,    7,   11,   12,   13,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   16,

 // slots: parameters
    QMetaType::Void, QMetaType::QUrl,   18,
    QMetaType::Bool, QMetaType::Int,   20,
    QMetaType::Bool,
    QMetaType::Void, QMetaType::QString,   22,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void showTopicMessagesClass::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        showTopicMessagesClass *_t = static_cast<showTopicMessagesClass *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->quoteThisMessage((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->addToBlacklist((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->editThisMessage((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->newMessageStatus(); break;
        case 4: _t->newNumberOfConnected(); break;
        case 5: _t->setEditInfo((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4]))); break;
        case 6: _t->newMessagesAvailable(); break;
        case 7: _t->newNameForTopic((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 8: _t->linkClicked((*reinterpret_cast< const QUrl(*)>(_a[1]))); break;
        case 9: { bool _r = _t->getEditInfo((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 10: { bool _r = _t->getEditInfo();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 11: _t->getQuoteInfo((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 12: _t->getMessages(); break;
        case 13: _t->loadFirstPageFinish(); break;
        case 14: _t->loadSecondPageFinish(); break;
        case 15: _t->analyzeEditInfo(); break;
        case 16: _t->analyzeQuoteInfo(); break;
        case 17: _t->analyzeMessages(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (showTopicMessagesClass::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&showTopicMessagesClass::quoteThisMessage)) {
                *result = 0;
            }
        }
        {
            typedef void (showTopicMessagesClass::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&showTopicMessagesClass::addToBlacklist)) {
                *result = 1;
            }
        }
        {
            typedef void (showTopicMessagesClass::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&showTopicMessagesClass::editThisMessage)) {
                *result = 2;
            }
        }
        {
            typedef void (showTopicMessagesClass::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&showTopicMessagesClass::newMessageStatus)) {
                *result = 3;
            }
        }
        {
            typedef void (showTopicMessagesClass::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&showTopicMessagesClass::newNumberOfConnected)) {
                *result = 4;
            }
        }
        {
            typedef void (showTopicMessagesClass::*_t)(int , QString , QString , QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&showTopicMessagesClass::setEditInfo)) {
                *result = 5;
            }
        }
        {
            typedef void (showTopicMessagesClass::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&showTopicMessagesClass::newMessagesAvailable)) {
                *result = 6;
            }
        }
        {
            typedef void (showTopicMessagesClass::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&showTopicMessagesClass::newNameForTopic)) {
                *result = 7;
            }
        }
    }
}

const QMetaObject showTopicMessagesClass::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_showTopicMessagesClass.data,
      qt_meta_data_showTopicMessagesClass,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *showTopicMessagesClass::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *showTopicMessagesClass::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_showTopicMessagesClass.stringdata0))
        return static_cast<void*>(const_cast< showTopicMessagesClass*>(this));
    return QWidget::qt_metacast(_clname);
}

int showTopicMessagesClass::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 18)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 18;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 18)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 18;
    }
    return _id;
}

// SIGNAL 0
void showTopicMessagesClass::quoteThisMessage(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void showTopicMessagesClass::addToBlacklist(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void showTopicMessagesClass::editThisMessage(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void showTopicMessagesClass::newMessageStatus()
{
    QMetaObject::activate(this, &staticMetaObject, 3, Q_NULLPTR);
}

// SIGNAL 4
void showTopicMessagesClass::newNumberOfConnected()
{
    QMetaObject::activate(this, &staticMetaObject, 4, Q_NULLPTR);
}

// SIGNAL 5
void showTopicMessagesClass::setEditInfo(int _t1, QString _t2, QString _t3, QString _t4)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void showTopicMessagesClass::newMessagesAvailable()
{
    QMetaObject::activate(this, &staticMetaObject, 6, Q_NULLPTR);
}

// SIGNAL 7
void showTopicMessagesClass::newNameForTopic(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}
QT_END_MOC_NAMESPACE
