/*
 * RemoteImageView.cpp
 *
 *  Created on: 30 Okt 2012
 *  	Author: aluialarid
 *      Rewrite: Deni Setiawan
 */

#include "RemoteImageView.hpp"
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

RemoteImageView::RemoteImageView() :
		Page() {
	scrollView = new ScrollView();
	ScrollViewProperties* scrollViewProp = scrollView->scrollViewProperties();
	scrollViewProp->setPinchToZoomEnabled(true);
	scrollViewProp->setMinContentScale(1.0);
	scrollViewProp->setMaxContentScale(5.0);
	scrollViewProp->setScrollMode(ScrollMode::Both);

	mRootContainer = new Container();
	mRootContainer->setLayout(new DockLayout);
	mRootContainer->setHorizontalAlignment(HorizontalAlignment::Fill);
	mRootContainer->setVerticalAlignment(VerticalAlignment::Fill);
	mRootContainer->setBackground(Color::fromARGB(0xff000000));
	imageView = new ImageView();
	imageView->setHorizontalAlignment(HorizontalAlignment::Fill);
	imageView->setVerticalAlignment(VerticalAlignment::Fill);
	imageView->setScalingMethod(bb::cascades::ScalingMethod::AspectFill);
	scrollView->setContent(imageView);

	indicator = new ActivityIndicator();
	indicator->setHorizontalAlignment(HorizontalAlignment::Center);
	indicator->setVerticalAlignment(VerticalAlignment::Center);
	indicator->setPreferredSize(400.0, 400.0);

	setPageTitle("Page 1");
	mTitle = Label::create("");
	mTitle->textStyle()->setFontWeight(FontWeight::Bold);
	mTitle->textStyle()->setColor(Color::Gray);
	mTitle->textStyle()->setFontSize(FontSize::Medium);

	Container* labelContainer = new Container();
	labelContainer->setRightPadding(30.0);
	labelContainer->setBottomPadding(30.0);
	labelContainer->setVerticalAlignment(VerticalAlignment::Bottom);
	labelContainer->setHorizontalAlignment(HorizontalAlignment::Left);

	progress = new ProgressIndicator();
	progress->setVerticalAlignment(VerticalAlignment::Bottom);
	progress->setHorizontalAlignment(HorizontalAlignment::Fill);
	progress->setValue(0.0);
	progress->setVisible(true);

//	labelContainer->add(mTitle);
	mRootContainer->add(scrollView);
	mRootContainer->add(indicator);
//	mRootContainer->add(labelContainer);
	mRootContainer->add(progress);
	setContent(mRootContainer);

	connect(this, SIGNAL(urlChanged(QString)), this, SLOT(onUrlChanged()));
}

RemoteImageView::~RemoteImageView() {
	delete progress;
	delete indicator;
	delete imageView;
	delete mRootContainer;
}

void RemoteImageView::loadImage() {
	progress->setValue(0.0);
	progress->setVisible(true);
	indicator->setVisible(true);
	indicator->start();
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

void RemoteImageView::onUrlChanged() {
	loadImage();
}

void RemoteImageView::onImageLoaded() {

	QNetworkReply* reply = qobject_cast<QNetworkReply*>(sender());

	if (reply->error() != QNetworkReply::NoError) {
		emit imageUnavailable();
		indicator->setVisible(false);
		indicator->stop();
		return;
	}
	Image image = Image(reply->readAll());
	imageView->setImage(image);
	mTitle->setText(mPageTitle);
	indicator->setVisible(false);
	indicator->stop();
}

void RemoteImageView::setUrl(QString url) {
	mUrl = url;
	emit urlChanged(mUrl);
}

QString RemoteImageView::URL() {
	return mUrl;
}

void RemoteImageView::setPageTitle(QString title) {
	mPageTitle = title;
}

QString RemoteImageView::pageTitle() {
	return mPageTitle;
}

void RemoteImageView::dowloadProgressed(qint64 bytes, qint64 total) {

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

double RemoteImageView::loading() const {
	return mLoading;
}

