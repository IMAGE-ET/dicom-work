#include "add_riu.h"
#include <QtCore>
Add_RIU::~Add_RIU()
{
	
}
Add_RIU::Add_RIU(QWidget *parent):QDialog(parent)
{
	parent->setEnabled(false);
	this->setEnabled(true);
	riu_name = new QLineEdit();
	riu_name->setPlaceholderText("RIU NAME");
	riu_ip = new QLineEdit();
	riu_ip->setPlaceholderText("RIU IP Address");
	riu_port = new QLineEdit();
	riu_port->setPlaceholderText("RIU Port");
	okButton = new QPushButton("OK");
	cancelButton = new QPushButton("Cancel");
	QGridLayout *mainDialog = new QGridLayout;
	QLabel *riu_name_label = new QLabel("RIU NAME");
	QLabel *riu_ip_label = new QLabel("RIU IP");
	QLabel *riu_port_label = new QLabel("RIU PORT");
	mainDialog->addWidget(riu_name_label, 0, 0 );
	mainDialog->addWidget(riu_name, 0, 1);
	mainDialog->addWidget(riu_ip_label, 1, 0);
	mainDialog->addWidget(riu_ip, 1, 1);
	mainDialog->addWidget(riu_port_label, 2, 0);
	mainDialog->addWidget(riu_port, 2, 1);
	mainDialog->addWidget(okButton, 4, 2);
	mainDialog->addWidget(cancelButton, 4, 3);
	qDebug() << parent;
	setLayout(mainDialog);
	connect(this->okButton, SIGNAL(clicked()), this, SLOT(get_data()));
	connect (this->cancelButton, SIGNAL(clicked()), this, SLOT(close()));
}

void Add_RIU::get_data()
{
	QString name, ip;
	int port;
	name=riu_name->displayText();
	ip = riu_ip->displayText();
	port = (riu_port->displayText()).toInt();
	emit emit_data_to_main_window(name, ip, port);
	this->close();
}
