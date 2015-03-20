#include "oiu_gui.h"
#include "oiu_config.h"
OIU_Main_Window::~OIU_Main_Window()
{
}
OIU_Main_Window ::OIU_Main_Window(char *user, char *passwd)
{
	//load config file
	oiu_config_t config={0};
	int index; //index of user in configuration file
	index = oiu_config(user, passwd, &config);
	//end load config
	btgroup = new QButtonGroup;
	number_of_riu=config.users[index].allow_roles[0]->n_allow_nodes;
	number_of_grp=config.users[index].allow_roles[0]->n_allow_grps;
	button_array = new bool [number_of_riu+number_of_grp];
	//button_array is the array stored all information about what button has been clicked
	for (int i=0;i<number_of_riu+number_of_grp;i++) {
		button_array[i]=false;
	}
	int total_riu_and_grp;
	if (number_of_grp>0) {
		total_riu_and_grp=number_of_riu+number_of_grp;
	} else {
		total_riu_and_grp = number_of_riu;
	}
	// display welcome user in label
	QString s = config.users[index].name;
	s = "Welcome, " + s;
	window_title=s;
	//username = new QLabel(s);
	//end of display username
	
	riu_name = new MyQLabel[total_riu_and_grp];
	tx_button = new MyQPushButton[total_riu_and_grp];
	rx_button = new MyQPushButton[total_riu_and_grp];
	progressBar = new MyQProgressBar[total_riu_and_grp];
	MyQGridLayout *sub_layout = new MyQGridLayout[total_riu_and_grp];

	QHBoxLayout *top_layout = new QHBoxLayout();
	QPushButton *but2 = new QPushButton("Logs");
	QPushButton *but3 = new QPushButton("Change\nPassword");
	QPushButton *but4 = new QPushButton("Volume");
	QPushButton *but5 = new QPushButton("PTT");
	
	but2->setMaximumWidth(60);
	but2->setMaximumHeight(50);
	but2->setMinimumWidth(60);
	but2->setMinimumHeight(50);
	but2->setStyleSheet("QPushButton{color: #333; border: 2px solid #555;border-radius: 11px;padding: 5px;background: qradialgradient(cx: 0.3, cy: -0.4i,fx:0.3, fy: -0.4, radius: 1.35, stop:0 #fff,stop:1 #888);min-width:80px}" "QPushButton:hover{background: qradialgradient(cx: 0.3, cy: -0.4, fx: 0.3, fy: -0.4, radius: 1.35, stop: 0 #fff, stop: 1 #bbb);}" "QPushButton:pressed{background: qradialgradient(cx: 0.4, cy: -0.1, fx: 0.4, fy: -0.1, radius: 1.35, stop: 0 #fff, stop: 1 #ddd);}");
	but3->setMaximumWidth(60);
	but3->setMaximumHeight(50);
	but3->setMinimumWidth(60);
	but3->setMinimumHeight(50);

	but3->setStyleSheet("QPushButton{color: #333; border: 2px solid #555;border-radius: 11px;padding: 5px;background: qradialgradient(cx: 0.3, cy: -0.4i,fx:0.3, fy: -0.4, radius: 1.35, stop:0 #fff,stop:1 #888);min-width:80px}" "QPushButton:hover{background: qradialgradient(cx: 0.3, cy: -0.4, fx: 0.3, fy: -0.4, radius: 1.35, stop: 0 #fff, stop: 1 #bbb);}" "QPushButton:pressed{background: qradialgradient(cx: 0.4, cy: -0.1, fx: 0.4, fy: -0.1, radius: 1.35, stop: 0 #fff, stop: 1 #ddd);}");
	but4->setMaximumWidth(60);
	but4->setMaximumHeight(50);
	but4->setMinimumWidth(60);
	but4->setMinimumHeight(50);

	but4->setStyleSheet("QPushButton{color: #333; border: 2px solid #555;border-radius: 11px;padding: 5px;background: qradialgradient(cx: 0.3, cy: -0.4i,fx:0.3, fy: -0.4, radius: 1.35, stop:0 #fff,stop:1 #888);min-width:80px}" "QPushButton:hover{background: qradialgradient(cx: 0.3, cy: -0.4, fx: 0.3, fy: -0.4, radius: 1.35, stop: 0 #fff, stop: 1 #bbb);}" "QPushButton:pressed{background: qradialgradient(cx: 0.4, cy: -0.1, fx: 0.4, fy: -0.1, radius: 1.35, stop: 0 #fff, stop: 1 #ddd);}");
	but5->setMaximumWidth(60);
	but5->setMaximumHeight(50);
	but5->setMinimumWidth(60);
	but5->setMinimumHeight(50);
	
	but5->setStyleSheet("QPushButton{color: #333; border: 2px solid #555;border-radius: 11px;padding: 5px;background: qradialgradient(cx: 0.3, cy: -0.4i,fx:0.3, fy: -0.4, radius: 1.35, stop:0 #fff,stop:1 #888);min-width:80px}" "QPushButton:hover{background: qradialgradient(cx: 0.3, cy: -0.4, fx: 0.3, fy: -0.4, radius: 1.35, stop: 0 #fff, stop: 1 #bbb);}" "QPushButton:pressed{background: qradialgradient(cx: 0.4, cy: -0.1, fx: 0.4, fy: -0.1, radius: 1.35, stop: 0 #fff, stop: 1 #ddd);}");
	but5->setAutoRepeat(true);
	date_time_label = new QLabel("starting...");
	//get date time and display in mainwindow
	date_time_label->setMaximumWidth(180);
	date_time_label->setMaximumHeight(50);
	date_time_label->setMinimumWidth(180);
	date_time_label->setMinimumHeight(50);
	//end get date time

	//top_layout->addWidget(username);
	top_layout->addWidget(but2);
	top_layout->addWidget(but3);
	top_layout->addWidget(but4);
	top_layout->addWidget(but5);
	top_layout->addWidget(date_time_label);
	//top_layout->setSpacing(15);	
	QString str="tx_";
	//create new array button and related field
	bool flag=false; // apply for for loop below only, maybe remove
	int count=0; //apply for for loop below only, maybe remove
	for (int i=0;i<total_riu_and_grp;i++) {
		QString temp_string_name;	
		if (flag == false) {
			temp_string_name=config.users[index].allow_roles[0]->allow_nodes[i]->name;
			temp_string_name = temp_string_name + "\n"+ QString::number(config.users[index].allow_roles[0]->allow_nodes[i]->freq[0]);
		} else if (flag==true && number_of_grp >0) {
			temp_string_name=config.users[index].allow_roles[0]->allow_grps[count]->name;
			temp_string_name = "<Grp> \n " + temp_string_name; 
			count++;
		}
		riu_name[i] = new QLabel(temp_string_name);
		riu_name[i]->setMaximumWidth(80);	
		riu_name[i]->setStyleSheet("border: none");
		//chage to frequence if require
		str="tx__" + QString::number(i);
		tx_button[i] = new QPushButton(str);
		tx_button[i]->setMinimumWidth(60);
		tx_button[i]->setMinimumHeight(60);
		tx_button[i]->setMaximumWidth(60);
		tx_button[i]->setMaximumHeight(60);
		//tx_button[i]->setAutoRepeat(true);

		tx_button[i]->setStyleSheet("QPushButton{color: #333; border: 2px solid #555;border-radius: 11px;padding: 5px;background: qradialgradient(cx: 0.3, cy: -0.4i,fx:0.3, fy: -0.4, radius: 1.35, stop:0 #fff,stop:1 #888);min-width:80px}" "QPushButton:hover{background: qradialgradient(cx: 0.3, cy: -0.4, fx: 0.3, fy: -0.4, radius: 1.35, stop: 0 #fff, stop: 1 #bbb);}" "QPushButton:pressed{background: qradialgradient(cx: 0.4, cy: -0.1, fx: 0.4, fy: -0.1, radius: 1.35, stop: 0 #fff, stop: 1 #ddd);}");
		btgroup->addButton(tx_button[i],i);
	
		//change to frequence if require
		str="rx__" + QString::number(i);
		rx_button[i] = new QPushButton(str);
		rx_button[i]->setMinimumWidth(60);
		rx_button[i]->setMinimumHeight(30);
		rx_button[i]->setMaximumWidth(60);
		rx_button[i]->setMaximumHeight(30);
		rx_button[i]->setStyleSheet("border: none");

		progressBar[i] = new QProgressBar;
		progressBar[i]->setMaximum(100);
		progressBar[i]->setMinimum(0);
		progressBar[i]->setValue(0);
		progressBar[i]->setTextVisible(false);
		progressBar[i]->setMaximumWidth(100);
		progressBar[i]->setStyleSheet("border: none");
		if (i==number_of_riu-1) {
			flag = true;
		}
	}
		
	QGridLayout *container = new QGridLayout;
	//add new widget to layout
	//note: mainWindow class has default layout, so you can not setLayout() directly, use CentralWidget
	int i=0;
	int j=0,k=0;
	for (i = 0;i<total_riu_and_grp;i++) {
		sub_layout[i] = new QGridLayout;
		sub_layout[i]->addWidget(riu_name[i],0,0,2,1);
		sub_layout[i]->addWidget(tx_button[i],0,1,2,1);
		sub_layout[i]->addWidget(rx_button[i],0,2);
		sub_layout[i]->addWidget(progressBar[i],1,2);
		if (i%5==0) {
			j++;	
			k=0;
		}
		QWidget *temp_widget = new QWidget;
		temp_widget->setLayout(sub_layout[i]);
		temp_widget->setStyleSheet("border: 1px solid grey");
		temp_widget->setMaximumWidth(320);
		temp_widget->setMinimumWidth(320);
		temp_widget->setMaximumHeight(70);
		temp_widget->setMinimumHeight(70);
		container->addWidget(temp_widget,k,j);
		container->setSpacing(10);
		container->setMargin(10);
		k++;
	}
	QGridLayout *main_layout = new QGridLayout;
	main_layout->setSpacing(10);
	main_layout->setMargin(10);
	//convert top layout to QWidget
	QWidget *temp_widget = new QWidget;
	temp_widget->setLayout(top_layout);
	temp_widget->setMaximumWidth(800);
	temp_widget->setMaximumHeight(90);
	//end convert top layout to widget

	main_layout->addWidget(temp_widget, 0, 0, 1, 2);
	main_layout->addLayout(container, 1, 0,1,1);
	QWidget *widget;
	widget = new QWidget;
	widget->setLayout(main_layout);
	//widget->setStyleSheet("background-color: black");
	widget->setMaximumSize(800,480);
	setCentralWidget(widget);
	
	QTimer *timer = new QTimer(); //timer for countdown
	connect (timer, SIGNAL(timeout()), this, SLOT(update_date_time_label()));
	//connect signal
	//connect(btgroup, SIGNAL(buttonPressed(QAbstractButton*)), this, SLOT(on_tx_button_pressed(QAbstractButton*)));
	connect(btgroup, SIGNAL(buttonReleased(QAbstractButton*)), this, SLOT(on_tx_button_released(QAbstractButton*)));
	connect(btgroup, SIGNAL(buttonClicked(QAbstractButton*)), this, SLOT(on_tx_button_clicked(QAbstractButton*)));
	//connect(add_new_riu_button, SIGNAL(clicked()), this, SLOT(on_add_new_riu_button_clicked()));
	connect(but5, SIGNAL(pressed()),this,SLOT(on_ptt_pressed()));
	connect(but5, SIGNAL(released()),this,SLOT(on_ptt_released()));
	timer->start(1000); //start countdown, after that, the clock will be updated
}

// generate signal streng
void OIU_Main_Window::on_tx_button_pressed(QAbstractButton *b)
{
	int bt_id=btgroup->id(b);
	progressBar[bt_id]->setValue(qrand()%101);
	if (bt_id < number_of_riu) {
		qDebug() << "You are pressing an RIU Button";
	} else {
		qDebug() << "You are pressing a Group Button";
	}
}
void OIU_Main_Window::on_tx_button_released(QAbstractButton *b)
{
	int bt_id=btgroup->id(b);
	progressBar[bt_id]->setValue(0);
}
void OIU_Main_Window::on_tx_button_clicked(QAbstractButton *b)
{
	if (button_array[btgroup->id(b)] == false) {
		button_array[btgroup->id(b)] = true;
		qDebug() << "false";
		b->setStyleSheet("QPushButton{color: #0000FF; border: 2px solid #555;border-radius: 11px;padding: 5px;background: qradialgradient(cx: 0, cy: 1,fx:1, fy: 1, radius: 1.35, stop:0 white ,stop:1 #056BFA);min-width:80px}"); 
	} else {
		button_array[btgroup->id(b)] = false;
		qDebug() << "true";
		tx_button[btgroup->id(b)]->setStyleSheet("QPushButton{color: #333; border: 2px solid #555;border-radius: 11px;padding: 5px;background: qradialgradient(cx: 0.3, cy: -0.4i,fx:0.3, fy: -0.4, radius: 1.35, stop:0 #fff,stop:1 #888);min-width:80px}" "QPushButton:hover{background: qradialgradient(cx: 0.3, cy: -0.4, fx: 0.3, fy: -0.4, radius: 1.35, stop: 0 #fff, stop: 1 #bbb);}" "QPushButton:pressed{background: qradialgradient(cx: 0.4, cy: -0.1, fx: 0.4, fy: -0.1, radius: 1.35, stop: 0 #fff, stop: 1 #ddd);}");
	}
}
void OIU_Main_Window::on_add_new_riu_button_clicked()
{
	Add_RIU *add_riu_dialog;
	add_riu_dialog = new Add_RIU(this);
	connect(add_riu_dialog, SIGNAL(emit_data_to_main_window(QString, QString, int)), this, SLOT(add_new_riu_channel(QString, QString, int)));
	add_riu_dialog->show();
	add_riu_dialog->exec();
	this->setEnabled(true);
}
void OIU_Main_Window::add_new_riu_channel(QString name, QString ip, int port)
{
	qDebug() << name;
	qDebug() << ip;
	qDebug() << port;
}
void OIU_Main_Window::update_date_time_label()
{
	QDate cd = QDate::currentDate();
	QTime ct = QTime::currentTime();
	date_time_label->setText(cd.toString()+"\n\n  "+ct.toString());
}

void OIU_Main_Window:: on_ptt_pressed()
{
	qDebug() << "PTT to ALL";
}

void OIU_Main_Window::on_ptt_released()
{
	qDebug() << "PTT to ALL";
}

