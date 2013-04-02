#include "photomodel.h"

#include <bb/data/XmlDataAccess>
#include <QtNetwork/QNetworkAccessManager>

using namespace bb::cascades;

const QString PhotoModel::mPhotoAdress =
		"http://api.flickr.com/services/feeds/photos_public.gne";

PhotoModel::PhotoModel(QObject *parent) :
		GroupDataModel(parent) {
	// Connect to the sslErrors signal to the onSslErrors() function. This will help us see what errors
	// we get when connecting to the address given by mMovieAdress.
	connect(&mAccessManager,
			SIGNAL(sslErrors ( QNetworkReply * , const QList<QSslError> & )),
			this,
			SLOT(onSslErrors ( QNetworkReply * , const QList<QSslError> & )));
}

void PhotoModel::httpFinished() {
	XmlDataAccess xda;
	QVariantList photoData;

	if (mReply->error() == QNetworkReply::NoError) {
		// Load the data using the reply QIODevice.
		photoData = xda.load(mReply, "/rss/channel/item").value<QVariantList>();
	} else {
		QString photoXml = "app/native/assets/models/photo.xml";

		photoData = xda.load(photoXml, "/rss/channel/item").value<QVariantList>();
		qDebug() << "ERROR RESULT";
		qDebug() << mReply->errorString();
	}

	if (xda.hasError()) {
		bb::data::DataAccessError error = xda.error();
		qDebug() << "XML loading error: " << error.errorType() << ": "
				<< error.errorMessage();
		return;
	}

	loadPhoto(photoData);

	// The reply is not needed now so we call deleteLater() function since we are in a slot.
	mReply->deleteLater();
}

void PhotoModel::loadPhoto(QVariantList photoData) {
	this->clear();
	setSortingKeys(QStringList() << "pubDate");
	insertList(photoData);
	setGrouping(ItemGrouping::None);
}

void PhotoModel::onSslErrors(QNetworkReply * reply,
		const QList<QSslError> & errors) {
// Ignore all SSL errors to be able to load from JSON file from the secure address.
// It might be a good idea to display an error message indicating that security may be compromised.
//
// The errors we get are:
// "SSL error: The issuer certificate of a locally looked up certificate could not be found"
// "SSL error: The root CA certificate is not trusted for this purpose"
// Seems to be a problem with how the server is set up and a known QT issue QTBUG-23625

	reply->ignoreSslErrors(errors);
}

void PhotoModel::setTag(QString tag) {
	// Remove all the old data.
	this->clear();

	// Set up a request for loading data from github, we encode the string so that
	// spaces and web-safe characters can be handled.
	QString encodedTag = QUrl(tag).toEncoded();
	QString path = mPhotoAdress + "?tags=" + encodedTag + "&format=rss2";
//	qDebug() << path;
	qheader = new QNetworkRequest(QUrl(path));
	mReply = mAccessManager.get(*qheader);

	// Connect to the reply finished signal to httpFinsihed() Slot function.
	connect(mReply, SIGNAL(finished()), this, SLOT(httpFinished()));

	mTag = tag;
	emit tagChanged(tag);
}

QString PhotoModel::tag() {
	return mTag;
}

