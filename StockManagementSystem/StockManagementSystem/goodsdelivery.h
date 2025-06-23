#pragma once
#include <qwidget.h>
#include<QIcon>
#include <QPushButton>
#include <QBoxLayout>
#include <QLineEdit>
#include <QLabel>
#include<QTextedit>
#include<QSqlDatabase>
#include<QSqlQuery>
#include<QDateTime>
#include <QMessageBox>
#include<QComboBox>
#include<QTableWidget>

#ifdef WIN64 
#pragma execution_character_set("utf-8")  
#endif
class goodsdelivery :
	public QWidget
{
	Q_OBJECT
public:
	goodsdelivery(QWidget* parent = nullptr);
	~goodsdelivery();
public:
	QComboBox* comboBox_Id;
	QLineEdit* edit_nub;


private slots:
	void on_btn_add_clicked();
	void on_btn_cancel_clicked();
	void InitComboBoxFunc();

};

