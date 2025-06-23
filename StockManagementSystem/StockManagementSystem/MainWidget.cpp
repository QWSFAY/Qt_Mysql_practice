#include "MainWidget.h"
#include "FuzzyTextWidget.h"
MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
{
	this->setWindowTitle("库存管理系统");
	this->setWindowIcon(QIcon(":/MainWidget/images/double.png"));
	this->setWindowFlags(windowFlags()&~Qt::WindowMaximizeButtonHint);
	// 父对象设置objectName
	//this->setObjectName("parentWidget");
	//this->setStyleSheet(
	//	"#parentWidget {background-color:rgba(28,238,214,255); }"  // 仅对父对象生效
	//);

	this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowMinMaxButtonsHint);

	setAttribute(Qt::WA_TranslucentBackground);  //设置窗口背景透明
	setWindowFlags(Qt::FramelessWindowHint | Qt::WindowMinMaxButtonsHint);  //去掉窗口边框
	this->setObjectName("parentWidget");
	this->setStyleSheet(
	"#parentWidget {background-color:rgba(28,238,214,255);border-radius:30px; }"  // 仅对父对象生效
);
	//this->setStyleSheet("QWidget{background-color:#FFFFFF;  \
 //       border-top-left-radius:15px;   \
 //       border-bottom-right-radius:15px; \
 //       }");

	// 设置窗口大小
	this->setFixedSize(1450, 1000);
	// 连接数据库
	ConnectMysqlDBFunc();

	vlay = new QVBoxLayout(this);

	hlay = new QHBoxLayout(this);
	lab = new QLabel();
	lab->setText("根据商品编号:");
	lab->setStyleSheet("color:rgba(85,85,255,255); font-weight:bold;");
	edit_id = new QLineEdit;
	edit_id->setPlaceholderText("请输入商品id");
	edit_id->setObjectName("edit_id");
	btnsearch = new QPushButton;
	btnsearch->setText("数据查询");
	btnsearch->setIcon(QIcon(":/MainWidget/images/select.png"));
	btnsearch->setStyleSheet("background-color:rgba(85,170,0,255);color:rgba(255,255,255,255);");
	btnsearch->setObjectName("btnsearch");
	QSpacerItem* spacer = new QSpacerItem(500, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);
	hlay->addItem(spacer);  // 添加到布局
	hlay->addWidget(lab);
	hlay->addWidget(edit_id);
	hlay->addWidget(btnsearch);
	hlay->setAlignment(Qt::AlignRight);
	id_wid = new QWidget(this);
	id_wid->setLayout(hlay);
	id_wid->setFixedHeight( 60);
	//id_wid->setStyleSheet("background-color:red");

	btnhlay = new QHBoxLayout(this);
	btn_add = new QPushButton;
	btn_add->setText("新增商品");
	btn_add->setObjectName("btn_add");
	btn_add->setIcon(QIcon(":/MainWidget/images/update.png"));
	btn_delete = new QPushButton;
	btn_delete->setText("删除商品");
	btn_delete->setObjectName("btn_delete");
	btn_delete->setIcon(QIcon(":/MainWidget/images/delete.png"));
	btn_in = new QPushButton;
	btn_in->setText("商品入库");
	btn_in->setObjectName("btn_in");
	btn_in->setIcon(QIcon(":/MainWidget/images/input.png"));
	btn_out = new QPushButton;
	btn_out->setText("数据出库");
	btn_out->setObjectName("btn_out");
	btn_out->setIcon(QIcon(":/MainWidget/images/output.png"));
	btn_dataout = new QPushButton;
	btn_dataout->setText("导出数据");
	btn_dataout->setObjectName("btn_dataout");
	btn_dataout->setIcon(QIcon(":/MainWidget/images/open.png"));

	btnhlay->addWidget(btn_add);
	btnhlay->addWidget(btn_delete);
	btnhlay->addWidget(btn_in);
	btnhlay->addWidget(btn_out);
	btnhlay->addWidget(btn_dataout);

	QSpacerItem* spacer2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
	btnhlay->addItem(spacer2);  // 添加到布局
	btn_wid = new QWidget;
	btn_wid->setLayout(btnhlay);
	btn_wid->setStyleSheet("QPushButton{background-color:rgba(85,170,0,255);color:rgba(255,255,255,255);}");
	btn_wid->setFixedHeight(60);

	exc_wid = new QWidget(this);
	exc_wid->setStyleSheet("border :2px solid black;background-color:rgba(255,245,213,255)");
	TableWidgetListDataFunc();
	excLayout = new QVBoxLayout(exc_wid);
	excLayout->addWidget(tab_list);  // 将表格添加到 exc_wid
	excLayout->setContentsMargins(0, 0, 0, 0); // 去除默认边距
	exc_wid->setLayout(excLayout);

	QWidget* title_wid = new QWidget(this);

	title_wid->setFixedSize(1450, 35);
	QPushButton *btn_clo = new QPushButton;
	btn_clo->setIcon(QIcon(":/MainWidget/images/delete.png"));
	btn_clo->setFixedSize(35, 35);
	QHBoxLayout* title_layout = new QHBoxLayout(title_wid);
	QSpacerItem* spacer3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
	title_layout->addItem(spacer3);  // 添加到布局
	
	QLabel* title_lab = new QLabel(this);
	title_lab->setText("基于Qt与Mysql实现的库存管理系统");
	title_lab->setStyleSheet("color:rgba(85,85,255,255); font-weight:bold; font-size: 30px;}");
	title_layout->addWidget(title_lab);

	QSpacerItem* spacer5 = new QSpacerItem(450,  QSizePolicy::Fixed);
	title_layout->addItem(spacer5);  // 添加到布局
	title_layout->addWidget(btn_clo);
	QSpacerItem* spacer4 = new QSpacerItem(40, QSizePolicy::Fixed);
	title_layout->addItem(spacer4);  // 添加到布局
	title_layout->setAlignment(Qt::AlignRight);
	title_wid->setContentsMargins(0, 0, 0, 0); // 去除默认边距
	title_layout->setContentsMargins(0, 0, 0, 0); // 去除默认边距
	title_layout->setSpacing(0); // 去除布局间距

	title_wid->setLayout(title_layout);

	vlay->addWidget(title_wid);
	vlay->addWidget(id_wid);
	vlay->addWidget(btn_wid);
	vlay->addWidget(exc_wid);

	connect(btnsearch, &QPushButton::clicked, this, &MainWidget::on_btnsearch_clicked);
	connect(btn_add, &QPushButton::clicked, this, &MainWidget::on_btn_add_clicked);
	connect(btn_delete, &QPushButton::clicked, this, &MainWidget::on_btn_delete_clicked);
	connect(btn_in, &QPushButton::clicked, this, &MainWidget::on_btn_in_clicked);
	connect(btn_out, &QPushButton::clicked, this, &MainWidget::on_btn_out_clicked);
	connect(btn_dataout, &QPushButton::clicked, this, &MainWidget::on_btn_dataout_clicked);
	connect(btn_clo, &QPushButton::clicked, this, &MainWidget::on_btn_clo_clicked);
}

MainWidget::~MainWidget()
{
}

void MainWidget::ConnectMysqlDBFunc()
{
	QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
	db.setHostName("127.0.0.1");
	db.setPort(3306);
	db.setDatabaseName("stockmsdb");//ODBC配置名称
	db.setPassword("YOUR PASSWORD");

	bool bok = db.open();
	if (bok)
	{
		//QMessageBox::information(this, "连接成功", "连接到数据库成功");
	}
	else
	{
		QMessageBox::critical(this, "连接失败", "连接到数据库失败: " + db.lastError().text());
		qDebug() << "Database connection error: " << db.lastError().text();
	}
}

void MainWidget::TableWidgetListDataFunc()
{
	tab_list = new QTableWidget(this);
	InitTableWidgetFunc();
}

void MainWidget::on_btnsearch_clicked()
{
	if (!edit_id->text().isEmpty())
	{
		tab_list->clearContents(); // 清除表格内容
	}
	else// 如果没有输入商品编号，则显示所有商品信息
	{
		InitTableWidgetFunc();
	}
	
	QSqlQuery sqlquery;
	QString strid = "StockId=";
	strid = strid + edit_id->text();
	//测试
	//QMessageBox::information(this, "测试", "查询的商品编号是：" + strid);
	QString str = QString("SELECT * FROM commoditydatatable WHERE %1").arg(strid);
	sqlquery.exec(str);

	int i = 0;
	while (sqlquery.next())
	{
		// 将数据库里面的数据表读取出来转换成对应的字符串,赋给对应字符串变量
		QString strId = sqlquery.value(0).toString();
		QString strName = sqlquery.value(1).toString();
		QString strAmoumt = sqlquery.value(2).toString();
		QString strUnitPrice = sqlquery.value(3).toString();
		QString strSupplier = sqlquery.value(4).toString();
		QString strDirector = sqlquery.value(5).toString();
		QString strWareHouseTime = sqlquery.value(6).toString();
		QString strDeliveryTime = sqlquery.value(7).toString();
		QString strRemarks = sqlquery.value(8).toString();
		// 将字符串显示到表格控件当中
		tab_list->setItem(i, 0, new QTableWidgetItem(strId));
		tab_list->setItem(i, 1, new QTableWidgetItem(strName));
		tab_list->setItem(i, 2, new QTableWidgetItem(strAmoumt));
		tab_list->setItem(i, 3, new QTableWidgetItem(strUnitPrice));
		tab_list->setItem(i, 4, new QTableWidgetItem(strSupplier));
		tab_list->setItem(i, 5, new QTableWidgetItem(strDirector));
		tab_list->setItem(i, 6, new QTableWidgetItem(strWareHouseTime));
		tab_list->setItem(i, 7, new QTableWidgetItem(strDeliveryTime));
		tab_list->setItem(i, 8, new QTableWidgetItem(strRemarks));
	}
}
#include "addcommodity.h"
void MainWidget::on_btn_add_clicked()
{
	addcommodity* addwid = new addcommodity();
	addwid->show();
}

void MainWidget::on_btn_delete_clicked()
{
	// 1：首先：提醒用户是否确认删除此记录
	// 1：获取QMessageBox选择按钮：Yes 或 No
	int iClick = QMessageBox::warning(this, "警告", "警告：删除操作是根据商品编号进行删除，请确认是否安全？", QMessageBox::Yes | QMessageBox::No);

	// 2：判断用户是否单击Yes按钮
	if (iClick == QMessageBox::Yes)
	{
		// 3：获取当前选择行进行删除：商品记录数据
		int iRow = tab_list->currentRow();

		// 4：根据index（行，列）获取对应商品编号
		QString strValue = tab_list->model()->index(iRow, 0).data().toString();
		// QMessageBox::information(this,"测试","获取数据为:"+strValue);

		QSqlQuery result;
		QString strid = strValue;

		// 5：判断删除商品编号是否为空？？？
		if (strid == NULL)
		{
			QMessageBox::critical(this, "错误", "提示：请选择要删除商品编号，请重新检查？");
			return;
		}
		// 6：实现删除
		QString sqlquery = QString("delete from commoditydatatable where StockId = %1").arg(strid);
		if (result.exec(sqlquery))
		{
			// 删除提示
			QMessageBox::information(this, "提示", "删除商品记录成功！");

			// 清空表格控件数据
			tab_list->clear();

			// 设置表格控件标题（表头）
			tab_list->setHorizontalHeaderLabels(QStringList() << "编号" << "名称" << "数量" << "单价" << "供应商家" << "负责人" << "入库时间" << "出库时间" << "备注");

			// 调用函数将数据表中数据再次展示到表格控件当中
			InitTableWidgetFunc();
		}

	}
	else
	{
		return;
	}
}

void MainWidget::InitTableWidgetFunc()
{
	tab_list->setColumnCount(9);
	tab_list->setRowCount(200);
	tab_list->setStyleSheet("font-size:20px;color:red;");
	tab_list->setHorizontalHeaderLabels(QStringList() << "编号" << "名称" << "数量" << "单价" << "供应商" << "负责人" << "入库时间" << "出库时间" << "备注");
	tab_list->setColumnWidth(0, 80);
	tab_list->setColumnWidth(1, 150);
	tab_list->setColumnWidth(2, 80);
	tab_list->setColumnWidth(3, 80);
	tab_list->setColumnWidth(4, 100);
	tab_list->setColumnWidth(5, 80);
	tab_list->setColumnWidth(6, 280);
	tab_list->setColumnWidth(7, 280);
	tab_list->setColumnWidth(8, 180);
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
		tab_list->setItem(i, 0, new QTableWidgetItem(strId));
		tab_list->setItem(i, 1, new QTableWidgetItem(strName));
		tab_list->setItem(i, 2, new QTableWidgetItem(strAmoumt));
		tab_list->setItem(i, 3, new QTableWidgetItem(strUnitPrice));
		tab_list->setItem(i, 4, new QTableWidgetItem(strSupplier));
		tab_list->setItem(i, 5, new QTableWidgetItem(strDirector));
		tab_list->setItem(i, 6, new QTableWidgetItem(strWareHouseTime));
		tab_list->setItem(i, 7, new QTableWidgetItem(strDeliveryTime));
		tab_list->setItem(i, 8, new QTableWidgetItem(strRemarks));
		i++;
	}
	return;
}
#include "goodswarehousing.h"
void MainWidget::on_btn_in_clicked()
{
	goodswarehousing* inwid = new goodswarehousing();
	inwid->setWindowIcon(QIcon(":/MainWidget/images/input.png"));
	inwid->show();
}
#include"goodsdelivery.h"
void MainWidget::on_btn_out_clicked()
{
	goodsdelivery* outwid = new goodsdelivery();
	outwid->setWindowIcon(QIcon(":/MainWidget/images/output.png"));
	outwid->show();
}

// 导出数据
#include <QFileDialog>
#include <QAxObject>
#include <QDesktopServices>

// 该函数功能：导出表格控件数据，直接生成Excel文件保存
void MainWidget::on_btn_dataout_clicked()
{
	// 保存文件扩展名为：.xls
	QDateTime time;
	QString strTemp;

	// 1：获取当前系统当时作为文件名称进行保存
	time = QDateTime::currentDateTime();
	strTemp = time.toString("yyyy-MM-dd-hhmmss");
	// QMessageBox::information(this,"测试",strTemp);

	// 2：应用文件对话框来保存要导出文件名称(设置保存的文件名称)及数据信息
	QString strFileName = QFileDialog::getSaveFileName(this, tr("Excel Files"), QString("./%1%2.xls").arg(strTemp).arg("_kcgl"), tr("Excel Files(*.xls)"));
	// QMessageBox::information(this,"测试",strFileName);

	// 3：处理工作簿
	if (strFileName != NULL)
	{
		QAxObject* excel = new QAxObject;
		if (excel->setControl("Excel.Application"));
		{
			excel->dynamicCall("SetVisible (bool Visible)", false);
			excel->setProperty("DisplayAlerts", false);

			QAxObject* workbooks = excel->querySubObject("WorkBooks"); // 获得工作簿集合
			workbooks->dynamicCall("Add"); // 创建一个工作簿
			QAxObject* workbook = excel->querySubObject("ActiveWorkBook"); // 获得当前工作簿
			QAxObject* worksheet = workbook->querySubObject("Worksheets(int)", 1);
			QAxObject* cell;
			// 1：添加Excel文件表头数据
			for (int i = 1; i <= tab_list->columnCount(); i++)
			{
				cell = worksheet->querySubObject("Cells(int,int)", 1, i);
				cell->setProperty("RowHeight", 25);
				cell->dynamicCall("SetValue(const QString&)", tab_list->horizontalHeaderItem(i - 1)->data(0).toString());
			}
			// 2：将表格数据保存到Excel文件当中
			for (int j = 2; j <= tab_list->rowCount() + 1; j++)
			{
				for (int k = 1; k <= tab_list->columnCount(); k++)
				{
					cell = worksheet->querySubObject("Cells(int,int)", j, k);
					QTableWidgetItem* item = tab_list->item(j - 2, k - 1);
					if (item && cell) {
						cell->dynamicCall("SetValue(const QString&)", item->text() + "\t");
					}
				}
			}
			// 3：将刚才创建的Excel文件直接保存到指定的目录下
			workbook->dynamicCall("SaveAs(const QString&)", QDir::toNativeSeparators(strFileName)); // 保存到strFileName
			workbook->dynamicCall("Close()");
			excel->dynamicCall("Quit()");
			delete excel;
			excel = NULL;
		}
	}
}

void MainWidget::on_btn_clo_clicked()
{
	this->close();
}

#include <qt_windows.h>
void MainWidget::mousePressEvent(QMouseEvent* event)
{
	if (ReleaseCapture())
	{
		QWidget* pWindow = this->window();
		if (pWindow->isTopLevel())
		{
			SendMessage(HWND(pWindow->winId()), WM_SYSCOMMAND, SC_MOVE + HTCAPTION, 0);
		}
	}
}
void MainWidget::paintEvent(QPaintEvent*)
{
	QStyleOption opt;
	opt.init(this);
	QPainter p(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}