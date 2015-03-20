#ifndef LOGIN_WINDOW_H
#define LOGIN_WINDOW_H
#include <QDialog>
#include <QPushButton>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QString>
#include <QLabel>
class LoginWindow : public QDialog {
	Q_OBJECT
public:
	explicit LoginWindow(QWidget *parent=0);
	virtual ~LoginWindow();
	QString get_username();
	QString get_password();
private slots:
	void ok_data();
	void cancel_data();
private:
	QLineEdit *username;
	QLineEdit *password;
	QPushButton *okButton;
	QPushButton *cancelButton;
	//username and password
	QString user;
	QString passwd;
};

#endif
