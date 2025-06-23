#pragma once

#include <QtWidgets/QWidget>
#ifdef WIN64 
#pragma execution_character_set("utf-8")  
#endif
//操作数据库相关头文件
#include<QsqlDataBase>
#include<QsqlQuery>
#include<QsqlError>
#include <QMessageBox>
#include<QtDebug>
#include <QtGui/QIcon>
#include <qlabel.h>
#include<qpushbutton.h>
#include<QBoxLayout>
#include <qlineedit.h>
#include <qtablewidget.h>
#include<QPainter>
class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget(QWidget *parent = nullptr);
    ~MainWidget();

private:
	QTableWidget* tab_list;
public:
    void ConnectMysqlDBFunc();
	void InitTableWidgetFunc();
    void TableWidgetListDataFunc();
	void on_btnsearch_clicked();
	void on_btn_add_clicked();
	void on_btn_delete_clicked();
	void on_btn_in_clicked();
	void on_btn_out_clicked();
	void on_btn_dataout_clicked();
	void on_btn_clo_clicked();
private:
	void mousePressEvent(QMouseEvent* event) override;
private:
	void paintEvent(QPaintEvent*) override;

private:
	QLabel* lab;
	QPushButton* btnsearch;
	QPushButton* btn_add;
	QPushButton* btn_delete;
	QPushButton* btn_in;
	QPushButton* btn_out;
	QPushButton* btn_dataout;

	QLineEdit* edit_id;
	QLineEdit* edit_name;
	QLineEdit* edit_type;
	QLineEdit* edit_price;
	QLineEdit* edit_num;
	QLineEdit* edit_date;
	QLineEdit* edit_supplier;
	QLineEdit* edit_remark;
	QWidget* id_wid;
	QWidget* btn_wid;
	QWidget* exc_wid;
	QVBoxLayout* vlay;
	QHBoxLayout* hlay;
	QHBoxLayout* btnhlay;
	QHBoxLayout* id_hlay;
	QHBoxLayout* edit_hlay;
	QHBoxLayout* btn_edit_hlay;
	QVBoxLayout* excLayout;
};
