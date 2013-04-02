/****************************************************************************
** Meta object code from reading C++ file 'RemoteThumbnailView.hpp'
**
** Created: Thu 21. Feb 22:35:21 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/RemoteThumbnailView.hpp"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'RemoteThumbnailView.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_RemoteThumbnailView[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       2,   49, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: signature, parameters, type, tag, flags
      21,   20,   20,   20, 0x05,
      44,   40,   20,   20, 0x05,
      64,   20,   20,   20, 0x05,

 // slots: signature, parameters, type, tag, flags
      81,   20,   20,   20, 0x0a,
      97,   20,   20,   20, 0x0a,
     114,  112,   20,   20, 0x0a,

 // methods: signature, parameters, type, tag, flags
     147,   20,   20,   20, 0x02,

 // properties: name, type, flags
      40,  159, 0x0a495103,
     173,  167, 0x87495001,

 // properties: notify_signal_id
       1,
       2,

       0        // eod
};

static const char qt_meta_stringdata_RemoteThumbnailView[] = {
    "RemoteThumbnailView\0\0imageUnavailable()\0"
    "url\0urlChanged(QString)\0loadingChanged()\0"
    "onImageLoaded()\0onUrlChanged()\0,\0"
    "dowloadProgressed(qint64,qint64)\0"
    "loadImage()\0QString\0float\0loading\0"
};

void RemoteThumbnailView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        RemoteThumbnailView *_t = static_cast<RemoteThumbnailView *>(_o);
        switch (_id) {
        case 0: _t->imageUnavailable(); break;
        case 1: _t->urlChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->loadingChanged(); break;
        case 3: _t->onImageLoaded(); break;
        case 4: _t->onUrlChanged(); break;
        case 5: _t->dowloadProgressed((*reinterpret_cast< qint64(*)>(_a[1])),(*reinterpret_cast< qint64(*)>(_a[2]))); break;
        case 6: _t->loadImage(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData RemoteThumbnailView::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject RemoteThumbnailView::staticMetaObject = {
    { &CustomControl::staticMetaObject, qt_meta_stringdata_RemoteThumbnailView,
      qt_meta_data_RemoteThumbnailView, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &RemoteThumbnailView::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *RemoteThumbnailView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *RemoteThumbnailView::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_RemoteThumbnailView))
        return static_cast<void*>(const_cast< RemoteThumbnailView*>(this));
    return CustomControl::qt_metacast(_clname);
}

int RemoteThumbnailView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = CustomControl::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
#ifndef QT_NO_PROPERTIES
      else if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QString*>(_v) = URL(); break;
        case 1: *reinterpret_cast< float*>(_v) = loading(); break;
        }
        _id -= 2;
    } else if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: setUrl(*reinterpret_cast< QString*>(_v)); break;
        }
        _id -= 2;
    } else if (_c == QMetaObject::ResetProperty) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 2;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void RemoteThumbnailView::imageUnavailable()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void RemoteThumbnailView::urlChanged(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void RemoteThumbnailView::loadingChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}
QT_END_MOC_NAMESPACE
