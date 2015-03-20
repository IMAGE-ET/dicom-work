#include <QApplication>
#include <QMainWindow>
#include <QtCore>
#include "oiu_gui.h"
#include "login_window.h"
int main (int argc, char *argv[])
{
	QApplication app(argc, argv);
	// create login window
	LoginWindow Lwindow;
	Lwindow.exec();
	QByteArray user_array = Lwindow.get_username().toLocal8Bit(); //get username and password
	QByteArray passwd_array = Lwindow.get_password().toLocal8Bit();
	char *user = user_array.data(); //convert username and password from QByteArray to char*
	char *passwd = passwd_array.data();
	OIU_Main_Window mainwindow(user, passwd); // create main window and check login info
	mainwindow.show();
	mainwindow.setGeometry(400,300,50 , 100); //set decoration on screen
	mainwindow.setWindowTitle(mainwindow.window_title);
	return app.exec();
}

