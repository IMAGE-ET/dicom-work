#include "login_window.h"
#include <QtCore>
#include <cstdlib>
LoginWindow::~LoginWindow()
{
	
}
LoginWindow::LoginWindow(QWidget *parent):QDialog(parent)
{
	username = new QLineEdit();
	username->setPlaceholderText("USERNAME");
	password = new QLineEdit();
	password->setEchoMode(QLineEdit::Password);
	password->setPlaceholderText("PASSWORD");
	okButton = new QPushButton("OK");
	cancelButton = new QPushButton("Cancel");
	QGridLayout *mainDialog = new QGridLayout;
	QLabel *name_label = new QLabel("username: ");
	QLabel *passwd_label = new QLabel("password: ");
	mainDialog->addWidget(name_label, 0, 0 );
	mainDialog->addWidget(username, 0, 1);
	mainDialog->addWidget(passwd_label, 1, 0);
	mainDialog->addWidget(password, 1, 1);
	mainDialog->addWidget(okButton, 4, 2);
	mainDialog->addWidget(cancelButton, 4, 3);
	qDebug() << parent;
	setLayout(mainDialog);
	connect(this->okButton, SIGNAL(clicked()), this, SLOT(ok_data()));
	connect(this->cancelButton, SIGNAL(clicked()), this, SLOT(cancel_data()));
}

void LoginWindow::ok_data()
{
	user = username->displayText();
	passwd = password->text();
	this->close();
}
void LoginWindow::cancel_data() 
{
	user="";
	passwd="";
	exit(1);
}
QString LoginWindow::get_username() 
{
	return user;
}
QString LoginWindow::get_password()
{
	return passwd;
}
