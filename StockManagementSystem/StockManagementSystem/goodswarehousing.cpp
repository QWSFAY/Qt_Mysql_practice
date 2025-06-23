#include "goodswarehousing.h"

goodswarehousing::goodswarehousing(QWidget* parent)
	: QWidget(parent)
{
	// 父对象设置objectName
	this->setObjectName("addWidget");
	this->setStyleSheet(
		"#addWidget {background-color:rgba(28,238,214,255); }"  // 仅对父对象生效
	);
	this->setWindowTitle("商品入库");
	this->setWindowIcon(QIcon(":/MainWidget/images/input.png"));
	this->setWindowFlags(windowFlags() & ~Qt::WindowMaximizeButtonHint);
	this->setFixedSize(500,100);

	QLabel* lab_id = new QLabel("商品编号:");
	QLabel* lab_name = new QLabel("商品数目:");


	comboBox_Id = new QComboBox;
	edit_nub = new QLineEdit;

	QHBoxLayout* Hlay_id = new QHBoxLayout;
	Hlay_id->addWidget(lab_id);
	Hlay_id->addWidget(comboBox_Id);
	Hlay_id->addWidget(lab_name);
	Hlay_id->addWidget(edit_nub);

	QVBoxLayout* vlay = new QVBoxLayout(this);
	vlay->addLayout(Hlay_id);

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

	connect(btn_add, &QPushButton::clicked, this, &goodswarehousing::on_btn_add_clicked);
	connect(btn_cancel, &QPushButton::clicked, this, &goodswarehousing::on_btn_cancel_clicked);

	wid->setFixedSize(500, 100);

	InitComboBoxFunc();

}


goodswarehousing::~goodswarehousing()
{
}
void goodswarehousing::on_btn_add_clicked()
{
	// 获取Combo Box控件里面的值
	QString StrCBId =comboBox_Id->currentText();


	// 判断商品入库的数量是否为空
	if (edit_nub->text().isEmpty())
	{
		QMessageBox::critical(this, "提示", "商品入库的数量不能为空，请重新检查？");
		edit_nub->setFocus();
		return;
	}

	// 设计SQL查询语句条件
	// SQL查询 SELECT * FROM commoditydatatable where StockId=1001

	QSqlQuery sqlquery;
	QString strid = "StockId=";
	strid += StrCBId;

	QString str = QString("SELECT * FROM commoditydatatable where %1").arg(strid);
	sqlquery.exec(str);
	// QMessageBox::critical(this,"提示",str);

	// 获取数据表中的商品编号对应的数量
	int i = 0;
	QString strAmount;
	while (sqlquery.next())
	{
		strAmount = sqlquery.value(2).toString();
		// QMessageBox::information(this,"提示",strAmount);
	}


	// 将输入数量+数量表当中的数量
	int inputamount = edit_nub->text().toInt(); // 用户输入数量
	int tableamount = strAmount.toUInt(); // 数据表里面的数量转换为整型
	int isum = inputamount + tableamount; // 实现相加

	// int 转换QString
	QString strresult = QString::number(isum);

	// 更新数据表中数量字段的值
	QString strdb = QString("update commoditydatatable set stockamount=%1 where %2").arg(strresult).arg(strid);

	if (sqlquery.exec(strdb))
	{
		QMessageBox::information(this, "提示", "入库成功！");
		close();
	}
	else
	{
		QMessageBox::critical(this, "提示", "对不起，商品入库失败，请重新检查？");
	}
}
void goodswarehousing::on_btn_cancel_clicked()
{
	close();
}
void goodswarehousing::InitComboBoxFunc() // 初始化Combo box控件
{
	int i = 0;
	QSqlQuery sqlQuery;
	sqlQuery.exec("SELECT * FROM commoditydatatable");

	QString StrId;

	while (sqlQuery.next())
	{
		StrId = sqlQuery.value(0).toString();
		comboBox_Id->insertItem(i, StrId);
		i++;
	}

}
