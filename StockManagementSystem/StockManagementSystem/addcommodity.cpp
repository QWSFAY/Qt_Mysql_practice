#include "addcommodity.h"

addcommodity::addcommodity(QWidget* parent)
	: QWidget(parent)
{
	// 父对象设置objectName
	this->setObjectName("addWidget");
	this->setStyleSheet(
		"#addWidget {background-color:rgba(28,238,214,255); }"  // 仅对父对象生效
	);
	this->setWindowTitle("新增商品");
	this->setWindowIcon(QIcon(":/MainWidget/images/update.png"));
	this->setWindowFlags(windowFlags() & ~Qt::WindowMaximizeButtonHint);
	this->setFixedSize(500, 600);

	QLabel* lab_id = new QLabel("商品编号:");
	QLabel* lab_name = new QLabel("商品名称:");
	QLabel* lab_nub = new QLabel("商品数量:");
	QLabel* lab_price = new QLabel("商品单价:");
	QLabel* lab_supplier = new QLabel("供应商家:");
	QLabel* lab_director = new QLabel("负责主管:");
	QLabel* lab_remark = new QLabel("备注:");

	 edit_id = new QLineEdit;
	 edit_name = new QLineEdit;
	 edit_nub = new QLineEdit;
	 edit_price = new QLineEdit;
	 edit_supplier = new QLineEdit;
	 edit_director = new QLineEdit;
	 edit_remark = new QTextEdit;

	QHBoxLayout* Hlay_id = new QHBoxLayout;	
	Hlay_id->addWidget(lab_id);
	Hlay_id->addWidget(edit_id);

	QHBoxLayout* Hlay_name = new QHBoxLayout;
	Hlay_name->addWidget(lab_name);
	Hlay_name->addWidget(edit_name);
	QHBoxLayout* Hlay_nub = new QHBoxLayout;
	Hlay_nub->addWidget(lab_nub);
	Hlay_nub->addWidget(edit_nub);
	QHBoxLayout* Hlay_price = new QHBoxLayout;
	Hlay_price->addWidget(lab_price);
	Hlay_price->addWidget(edit_price);
	QHBoxLayout* Hlay_supplier = new QHBoxLayout;
	Hlay_supplier->addWidget(lab_supplier);
	Hlay_supplier->addWidget(edit_supplier);
	QHBoxLayout* Hlay_director = new QHBoxLayout;
	Hlay_director->addWidget(lab_director);
	Hlay_director->addWidget(edit_director);
	QHBoxLayout* Hlay_remark = new QHBoxLayout;
	Hlay_remark->addWidget(lab_remark);
	Hlay_remark->addWidget(edit_remark);

	QVBoxLayout* vlay = new QVBoxLayout(this);
	vlay->addLayout(Hlay_id);
	vlay->addLayout(Hlay_name);
	vlay->addLayout(Hlay_nub);
	vlay->addLayout(Hlay_price);
	vlay->addLayout(Hlay_supplier);
	vlay->addLayout(Hlay_director);
	vlay->addLayout(Hlay_remark);
	
	QHBoxLayout* btnlay = new QHBoxLayout;
	QPushButton* btn_add = new QPushButton("添加商品");
	btn_add->setObjectName("btn_add");
	QPushButton* btn_cancel = new QPushButton("取消添加");
	btn_cancel->setObjectName("btn_cancel");
	btnlay->addWidget(btn_add);
	btnlay->addWidget(btn_cancel);

	vlay->addLayout(btnlay);

	QWidget* wid = new QWidget(this);
	wid->setLayout(vlay);

	connect(btn_add, &QPushButton::clicked, this, &addcommodity::on_btn_add_clicked);
	connect(btn_cancel, &QPushButton::clicked, this, &addcommodity::on_btn_cancel_clicked);
	
	wid->setFixedSize(500, 600);
}


addcommodity::~addcommodity()
{
}
void addcommodity::on_btn_add_clicked()
{
	QSqlQuery sqlResult;
	QString strId,strName, strAmount,strUnitPrice, strSupplier, strDirector, strWareHouseTime, strDeliveryTime, strRemarks;
	strId = edit_id->text();
	strName = edit_name->text();
	strAmount = edit_nub->text();
	strUnitPrice = edit_price->text();
	strSupplier = edit_supplier->text();
	strDirector = edit_director->text();
	strWareHouseTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
	strDeliveryTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
	strRemarks = edit_remark->toPlainText();

	if (edit_id->text().isEmpty())
	{
		QMessageBox::critical(this, "Tips", "新增商品编号不能为空，请重新输入？");
		edit_id->setFocus();
		return;
	}
	QString sqlquery = QString("insert into commoditydatatable(StockId,StockName,StockAmount,StockUnitPrice,Supplier,Director,WareHousTime,DeliveryTime,Remarks) "
		"values('%1','%2','%3','%4','%5','%6','%7','%8','%9')")
		.arg(strId).arg(strName).arg(strAmount).arg(strUnitPrice).arg(strSupplier).arg(strDirector).arg(strWareHouseTime).arg(strDeliveryTime).arg(strRemarks);

	if (sqlResult.exec(sqlquery))
	{
		QMessageBox::information(this, "Tips", "恭喜你，商品记录插入成功!");
	}
	else
	{
		QMessageBox::critical(this, "Tips", "对不起商品记录插入失败，请重新检查？");
	}


}
void addcommodity::on_btn_cancel_clicked()
{
	close();
}
void addcommodity::InitTableWidgetFunc()
{
	QTableWidget* tab_tlist = new QTableWidget(this);
	tab_tlist->setColumnCount(9);
	tab_tlist->setRowCount(200);
	tab_tlist->setStyleSheet("font-size:20px;color:red;");
	tab_tlist->setHorizontalHeaderLabels(QStringList() << "编号" << "名称" << "数量" << "单价" << "供应商" << "负责人" << "入库时间" << "出库时间" << "备注");
	tab_tlist->setColumnWidth(0, 80);
	tab_tlist->setColumnWidth(1, 150);
	tab_tlist->setColumnWidth(2, 80);
	tab_tlist->setColumnWidth(3, 80);
	tab_tlist->setColumnWidth(4, 300);
	tab_tlist->setColumnWidth(5, 80);
	tab_tlist->setColumnWidth(6, 200);
	tab_tlist->setColumnWidth(7, 200);
	tab_tlist->setColumnWidth(8, 180);
	QSqlQuery tsqlquery;
	tsqlquery.exec("SELECT * FROM commoditydatatable");
	int i = 0;
	while (tsqlquery.next())
	{
		// 将数据库里面的数据表读取出来转换成对应的字符串,赋给对应字符串变量
		QString strId = tsqlquery.value(0).toString();
		QString strName = tsqlquery.value(1).toString();
		QString strAmoumt = tsqlquery.value(2).toString();
		QString strUnitPrice = tsqlquery.value(3).toString();
		QString strSupplier = tsqlquery.value(4).toString();
		QString strDirector = tsqlquery.value(5).toString();
		QString strWareHouseTime = tsqlquery.value(6).toString();
		QString strDeliveryTime = tsqlquery.value(7).toString();
		QString strRemarks = tsqlquery.value(8).toString();
		// 将字符串显示到表格控件当中
		tab_tlist->setItem(i, 0, new QTableWidgetItem(strId));
		tab_tlist->setItem(i, 1, new QTableWidgetItem(strName));
		tab_tlist->setItem(i, 2, new QTableWidgetItem(strAmoumt));
		tab_tlist->setItem(i, 3, new QTableWidgetItem(strUnitPrice));
		tab_tlist->setItem(i, 4, new QTableWidgetItem(strSupplier));
		tab_tlist->setItem(i, 5, new QTableWidgetItem(strDirector));
		tab_tlist->setItem(i, 6, new QTableWidgetItem(strWareHouseTime));
		tab_tlist->setItem(i, 7, new QTableWidgetItem(strDeliveryTime));
		tab_tlist->setItem(i, 8, new QTableWidgetItem(strRemarks));
		i++;
	}
	return;
}