#ifndef ADD_RIU_H
#define ADD_RIU_H
#include <QDialog>
#include <QPushButton>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QLabel>
class Add_RIU : public QDialog {
	Q_OBJECT
public:
	explicit Add_RIU(QWidget *parent=0);
	virtual ~Add_RIU();
signals:
	void emit_data_to_main_window(QString riu_name, QString riu_ip, int riu_port);
private slots:
	void get_data();
private:
	QLineEdit *riu_name;
	QLineEdit *riu_ip;
	QLineEdit *riu_port;
	QPushButton *okButton;
	QPushButton *cancelButton;
};

#endif
