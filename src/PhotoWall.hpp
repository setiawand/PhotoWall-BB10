// Navigation pane project template
#ifndef PhotoWall_HPP_
#define PhotoWall_HPP_

#include <QObject>
#include <bb/cascades/QmlDocument>
#include "photomodel.h"

namespace bb { namespace cascades { class Application; }}

using namespace bb::cascades;

/*!
 * @brief Application pane object
 *
 *Use this object to create and init app UI, to create context objects, to register the new meta types etc.
 */
class PhotoWall : public QObject
{
    Q_OBJECT
public:
    PhotoWall(bb::cascades::Application *app);
    virtual ~PhotoWall();
    Q_INVOKABLE
    void refresh(QString tag);
private:
    void createPhotoList();
    PhotoModel *mModel;
    QmlDocument *qml;
};

#endif /* PhotoWall_HPP_ */
