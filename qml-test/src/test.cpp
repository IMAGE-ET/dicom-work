#ifdef QT5
    #include <QGuiApplication>
    #include <QQuickView>
    #include <QQmlEngine>
#else
    #include <QApplication>
    #include <QDeclarativeView>
    #include <QDeclarativeEngine>
    typedef QApplication QGuiApplication;
    typedef QDeclarativeView QQuickView;
    #define QStringLiteral(str) QString::fromUtf8("" str "", sizeof(str) -1)
#endif
    #include "Gauge.h"
int main(int argc, char * argv[]) {
    QGuiApplication a(argc, argv);

    qmlRegisterType<Gauge>("Gauge", 1, 0, "Gauge");

    QQuickView view;
    view.setSource(QUrl::fromLocalFile(QStringLiteral("qml/main.qml")));
    view.setFlags(Qt::Desktop);
    view.setResizeMode(QQuickView::SizeViewToRootObject);
    //view.showFullScreen();
    view.show();

    QObject::connect(view.engine(), SIGNAL(quit()), &a, SLOT(quit()));
    view.setResizeMode(QQuickView::SizeRootObjectToView);
    return a.exec();
}
