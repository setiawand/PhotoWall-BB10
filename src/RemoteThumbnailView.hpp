/*
 * RemoteThumbnailView.hpp
 *
 *  Created on: 30 Okt 2012
 *      Author: aluialarid
 *      ReWrite: Deni Setiawan
 */

#ifndef REMOTETHUMBNAILVIEW_HPP_
#define REMOTETHUMBNAILVIEW_HPP_

#include <bb/cascades/CustomControl>
#include <bb/cascades/Container>
#include <bb/cascades/ImageView>
#include <bb/cascades/Container>
#include <bb/cascades/controls/activityindicator.h>
#include <bb/cascades/controls/scrollview.h>
#include <bb/cascades/controls/label.h>
#include <bb/cascades/controls/progressindicator.h>
#include <bb/cascades/ActionItem>

namespace bb {
namespace cascades {
class Container;
}
}
using namespace bb::cascades;

class RemoteThumbnailView: public CustomControl {

Q_OBJECT

Q_PROPERTY(QString url READ URL WRITE setUrl NOTIFY urlChanged)

Q_PROPERTY (float loading READ loading NOTIFY loadingChanged)

public:
	RemoteThumbnailView();
	~RemoteThumbnailView();
	ImageView* imageView;

	Q_INVOKABLE
	void loadImage();
	void setUrl(QString url);
	QString URL();
	double loading() const;

public slots:
	void onImageLoaded();
	void onUrlChanged();
	void dowloadProgressed(qint64, qint64);

signals:
	void imageUnavailable();
	void urlChanged(QString url);
	void loadingChanged();

private:
	QString mUrl;
	float mLoading;
	ProgressIndicator* progress;
	Container *mRootContainer;
};

#endif /* REMOTETHUMBNAILVIEW_HPP_ */
