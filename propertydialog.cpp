#include "propertydialog.h"
#include "ui_propertydialog.h"
#include <QValidator>

PropertyDialog::PropertyDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PropertyDialog)
{
    ui->setupUi(this);
    //只允许输入数字
    //1-100整数
    QIntValidator *intValidator = new QIntValidator(this);
    intValidator->setRange(1, 20);
    ui->lineEdit->setValidator(intValidator);
    intValidator->setRange(1, 15);
    ui->rowEdit->setValidator(intValidator);
    intValidator->setRange(100, 1000);
    ui->speedEdit->setValidator(intValidator);//没有用

}

PropertyDialog::~PropertyDialog()
{
    delete ui;
}

int PropertyDialog::getLineNum()
{
    QString str = ui->lineEdit->text();
    bool ok;
    return str.toInt(&ok);
}

int PropertyDialog::getRowNum()
{
    QString str = ui->rowEdit->text();
    bool ok;
    return str.toInt(&ok);
}

int PropertyDialog::getSpeedNum()
{
    QString str = ui->speedEdit->text();
    bool ok;
    return str.toInt(&ok);
}

void PropertyDialog::on_pushButton_2_clicked()
{
    close();
    reject();
}


void PropertyDialog::on_pushButton_clicked()
{
    //父亲获得儿子信息只需要.或->即可
    close();
    accept();
}



