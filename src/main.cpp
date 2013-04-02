// Navigation pane project template
#include "PhotoWall.hpp"
#include "RemoteThumbnailView.hpp"
#include "RemoteImageView.hpp"

#include <bb/cascades/Application>
#include <bb/data/DataSource>

#include <QLocale>
#include <QTranslator>
#include <Qt/qdeclarativedebug.h>

using namespace bb::cascades;

void messageLogger(QtMsgType type, const char *msg) {
	fprintf(stdout, "%s\n", msg);
	fflush(stdout);
}

Q_DECL_EXPORT int main(int argc, char **argv) {
	// this is where the server is started etc
	Application app(argc, argv);

	qInstallMsgHandler(messageLogger);

	bb::data::DataSource::registerQmlTypes();
	qmlRegisterType<RemoteThumbnailView>("remote.thumbnail", 1, 0,
			"RemoteThumbnailView");
	qmlRegisterType<RemoteImageView>("remote.image", 1, 0, "RemoteImageView");

	// localization support
	QTranslator translator;
	QString locale_string = QLocale().name();
	QString filename = QString("PhotoWall_%1").arg(locale_string);
	if (translator.load(filename, "app/native/qm")) {
		app.installTranslator(&translator);
	}

	// create the application pane object to init UI etc.
	new PhotoWall(&app);

	// we complete the transaction started in the app constructor and start the client event loop here
	return Application::exec();
	// when loop is exited the Application deletes the scene which deletes all its children (per qt rules for children)
}
