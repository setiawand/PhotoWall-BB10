/* Copyright (c) 2012 Research In Motion Limited.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef _PHOTOMODEL_H_
#define _PHOTOMODEL_H_

#include <bb/cascades/GroupDataModel>
#include <bb/data/JsonDataAccess>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>


using namespace bb::data;

class PhotoModel: public bb::cascades::GroupDataModel {
	Q_OBJECT
	Q_PROPERTY(QString tag READ tag WRITE setTag
	            NOTIFY tagChanged)
public:
	PhotoModel(QObject *parent = 0);
	void setTag(QString tag);
	QString tag();
	signals:
	void tagChanged(QString tag);

private slots:
	void httpFinished();
	void onSslErrors(QNetworkReply * reply, const QList<QSslError> & errors);

private:
	void loadPhoto(QVariantList photoData);

	// The network parameters; used for accessing a file from the Internet
	QNetworkAccessManager mAccessManager;
	QNetworkReply *mReply;
	QNetworkRequest *qheader;

	// String constant for the address used to look up weather data
	static const QString mPhotoAdress;
	QString mTag;
};

#endif // ifndef _PHOTOMODEL_H_
