/*
 * RemoteImageView.hpp
 *
 *  Created on: 30 Okt 2012
 *      Author: aluialarid
 *      ReWrite: Deni Setiawan
 */

#ifndef REMOTEIMAGEVIEW_HPP_
#define REMOTEIMAGEVIEW_HPP_

#include <bb/cascades/Page>
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

class RemoteImageView: public Page {

Q_OBJECT

Q_PROPERTY(QString url READ URL WRITE setUrl NOTIFY urlChanged)

Q_PROPERTY (float loading READ loading NOTIFY loadingChanged)

public:
	RemoteImageView();
	~RemoteImageView();
	Container* mRootContainer;
	ImageView* imageView;
	ActivityIndicator* indicator;
	ScrollView* scrollView;
	Label* mTitle;

	Q_INVOKABLE
	void loadImage();
	void setUrl(QString url);
	QString URL();
	void setPageTitle(QString title);
	QString pageTitle();
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
	QString mUrl, mPageTitle;
	float mLoading;
	ProgressIndicator* progress;
};

#endif /* REMOTEIMAGEVIEW_HPP_ */
