/*
 * RemoteThumbnailView.cpp
 *
 *  Created on: 30 Okt 2012
 *  	Author: aluialarid
 *      Rewrite: Deni Setiawan
 */

#include "RemoteThumbnailView.hpp"
#include <bb/cascades/Container>
#include <bb/cascades/ImageView>
#include <bb/cascades/ScalingMethod>
#include <bb/cascades/DockLayout>
#include <bb/cascades/controls/activityindicator.h>
#include <bb/cascades/controls/scrollview.h>
#include <bb/cascades/controls/page.h>
#include <bb/cascades/NavigationPaneProperties>
#include <bb/cascades/Color>

using namespace bb::cascades;

RemoteThumbnailView::RemoteThumbnailView() :
		CustomControl() {
	mRootContainer = new Container();
	mRootContainer->setLayout(new DockLayout);
	mRootContainer->setHorizontalAlignment(HorizontalAlignment::Fill);
	mRootContainer->setVerticalAlignment(VerticalAlignment::Fill);
	mRootContainer->setBackground(Color::fromARGB(0xff000000));
	imageView = new ImageView();
	imageView->setHorizontalAlignment(HorizontalAlignment::Fill);
	imageView->setVerticalAlignment(VerticalAlignment::Fill);
	imageView->setScalingMethod(bb::cascades::ScalingMethod::Fill);

	progress = new ProgressIndicator();
	progress->setVerticalAlignment(VerticalAlignment::Bottom);
	progress->setHorizontalAlignment(HorizontalAlignment::Fill);
	progress->setValue(0.0);
	progress->setVisible(true);

	mRootContainer->add(imageView);
	mRootContainer->add(progress);
	setRoot(mRootContainer);

	connect(this, SIGNAL(urlChanged(QString)), this, SLOT(onUrlChanged()));
}

RemoteThumbnailView::~RemoteThumbnailView() {
	delete progress;
	delete imageView;
	delete mRootContainer;
}

void RemoteThumbnailView::loadImage() {
	progress->setValue(0.0);
	progress->setVisible(true);
	QNetworkRequest request = QNetworkRequest();
	request.setUrl(QUrl(mUrl));

	QNetworkAccessManager* nam = new QNetworkAccessManager(this);
	QNetworkReply * reply = nam->get(request);
	bool result = connect(reply, SIGNAL(finished()), this,
			SLOT(onImageLoaded()));
	connect(reply, SIGNAL(downloadProgress(qint64, qint64)), this,
			SLOT(dowloadProgressed(qint64, qint64)));
	Q_ASSERT(result);
	Q_UNUSED(result);
}

void RemoteThumbnailView::onUrlChanged() {
	loadImage();
}

void RemoteThumbnailView::onImageLoaded() {

	QNetworkReply* reply = qobject_cast<QNetworkReply*>(sender());

	if (reply->error() != QNetworkReply::NoError) {
		emit imageUnavailable();
		return;
	}
	Image image = Image(reply->readAll());
	imageView->setImage(image);
}

void RemoteThumbnailView::setUrl(QString url) {
	mUrl = url;
	emit urlChanged(mUrl);
}

QString RemoteThumbnailView::URL() {
	return mUrl;
}

void RemoteThumbnailView::dowloadProgressed(qint64 bytes, qint64 total) {

	mLoading = double(bytes) / double(total);
	if (total == 0) {
		mLoading = 1;
	}

	progress->setValue(mLoading);

	if (mLoading == 1) {
		progress->setVisible(false);
	}

	emit loadingChanged();
}

double RemoteThumbnailView::loading() const {
	return mLoading;
}

