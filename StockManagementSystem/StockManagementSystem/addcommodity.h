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
#include<QTableWidget>
#ifdef WIN64 
#pragma execution_character_set("utf-8")  
#endif
class addcommodity :
    public QWidget
{
	Q_OBJECT
public:
    addcommodity(QWidget* parent = nullptr);
    ~addcommodity();
public:
	QLineEdit* edit_id ;
	QLineEdit* edit_name ;
	QLineEdit* edit_nub;
	QLineEdit* edit_price ;
	QLineEdit* edit_supplier;
	QLineEdit* edit_director;
	QTextEdit* edit_remark;

private slots:
	void on_btn_add_clicked();
	void on_btn_cancel_clicked();
	void InitTableWidgetFunc();
};

