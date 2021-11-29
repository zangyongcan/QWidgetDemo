#include "toolTip.h"
#include "ui_toolTip.h"
#include "customTooltip.h"
#include <QCoreApplication>
#include <QFile>
#include <QSettings>
#include <qdebug.h>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget),
    m_IniPath(QCoreApplication::applicationDirPath() + "/toolTip.ini")
{
    ui->setupUi(this);

    QFile qFile(m_IniPath);
    if (!qFile.exists()) {
        if (!qFile.open(QIODevice::ReadWrite)) {
            qCritical() << "file.open failed!";
        }
        qFile.close();
    } else {
        QSettings setting(m_IniPath, QSettings::IniFormat);
        ui->pTxtEditInputTestData->setPlainText(setting.value("all/1").toString());
    }
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_rBtnSystemToolTip_clicked()
{
    m_bSystem = true;

    ui->label->setToolTip(ui->pTxtEditInputTestData->toPlainText());
    ui->lineEdit->setToolTip(ui->pTxtEditInputTestData->toPlainText());
    ui->textEdit->setToolTip(ui->pTxtEditInputTestData->toPlainText());
    ui->plainTextEdit->setToolTip(ui->pTxtEditInputTestData->toPlainText());
}

void Widget::on_rBtnCustomToolTip_clicked()
{
    m_bSystem = false;
    CustomToolTip::popup(QCursor::pos(), ui->pTxtEditInputTestData->toPlainText());
}

void Widget::on_btnSave_clicked()
{
    QSettings setting(m_IniPath, QSettings::IniFormat);
    setting.beginGroup("all");
    setting.setValue(ui->spinBox->text(),
                     ui->pTxtEditInputTestData->toPlainText());
    setting.endGroup();
}

void Widget::on_btnDel_clicked()
{
    QSettings setting(m_IniPath, QSettings::IniFormat);
    setting.remove(QString::asprintf("all/%1").arg(ui->spinBox->text()));
}

void Widget::on_spinBox_valueChanged(int arg1)
{
    QSettings setting(m_IniPath, QSettings::IniFormat);
    ui->pTxtEditInputTestData->setPlainText(setting.value(QString::asprintf("all/%1").arg(arg1)).toString());
    m_lastIndex = arg1;
}

void Widget::on_tabWidget_currentChanged(int index)
{
    if (index == 1) {
        ui->label->setText(ui->pTxtEditInputTestData->toPlainText());
        ui->lineEdit->setText(ui->pTxtEditInputTestData->toPlainText());
        ui->textEdit->setPlainText(ui->pTxtEditInputTestData->toPlainText());
        ui->plainTextEdit->setPlainText(ui->pTxtEditInputTestData->toPlainText());
        if (m_bSystem) {
            ui->label->setToolTip(ui->pTxtEditInputTestData->toPlainText());
            ui->lineEdit->setToolTip(ui->pTxtEditInputTestData->toPlainText());
            ui->textEdit->setToolTip(ui->pTxtEditInputTestData->toPlainText());
            ui->plainTextEdit->setToolTip(ui->pTxtEditInputTestData->toPlainText());
        } else {
            CustomToolTip::popup(QCursor::pos(), ui->pTxtEditInputTestData->toPlainText());
        }
    }
}
