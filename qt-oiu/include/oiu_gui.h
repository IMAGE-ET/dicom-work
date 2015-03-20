#ifndef OIU_GUI_H
#define OIU_GUI_H
#include <QMainWindow> 
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QProgressBar>
#include <QButtonGroup>
#include <QAbstractButton>
#include <QGridLayout>
#include <QLabel>
#include <QApplication>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QWidget>
#include <QtGui>
#include <QGridLayout>
#include <cstdlib>
#include <QDate>
#include <QTime>
#include <QLinearGradient>

#include "add_riu.h"
typedef QLabel* MyQLabel;
typedef QPushButton* MyQPushButton;
typedef QProgressBar* MyQProgressBar;
typedef QHBoxLayout* MyQHBoxLayout;
typedef QVBoxLayout* MyQVBoxLayout;
typedef QGridLayout* MyQGridLayout;
class OIU_Main_Window:public QMainWindow {
	Q_OBJECT
public:
	explicit OIU_Main_Window (char *user, char *passwd);
	virtual ~OIU_Main_Window();
	QString window_title;
signals:

private slots:
	void on_tx_button_pressed(QAbstractButton *b);
	void on_tx_button_released(QAbstractButton *b);
	void on_tx_button_clicked(QAbstractButton *b);
	void on_add_new_riu_button_clicked();
	void add_new_riu_channel(QString name, QString ip, int port);
	void update_date_time_label();
	void on_ptt_pressed();
	void on_ptt_released();
private:
	QButtonGroup *btgroup;
	QLabel *username;
	QLabel *date_time_label;
	MyQLabel* riu_name;
	MyQPushButton* tx_button; //for riu only
	MyQPushButton* rx_button;
	bool *button_array;			// check if button was clicked
	MyQProgressBar* progressBar;
	int number_of_riu;
	int number_of_grp;
	QPushButton *add_new_riu_button;
	QPushButton *delete_riu_button;
};
#endif
