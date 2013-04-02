// Navigation pane project template
#include "PhotoWall.hpp"

#include <bb/cascades/Application>
#include <bb/cascades/NavigationPane>

using namespace bb::cascades;

PhotoWall::PhotoWall(bb::cascades::Application *app) :
		QObject(app) {

	qml = QmlDocument::create("asset:///main.qml").parent(this);
	qml->setContextProperty("app", this);
	createPhotoList();
	NavigationPane *root = qml->createRootObject<NavigationPane>();
	Application::instance()->setScene(root);
}

PhotoWall::~PhotoWall() {
	delete mModel;
}

void PhotoWall::createPhotoList() {
	mModel = new PhotoModel(this);
	qml->setContextProperty("_photoModel", mModel);
	mModel->setTag("Indonesia");
}

void PhotoWall::refresh(QString tag) {
	qDebug() << "Refreshing";
	mModel->setTag(tag);
}
