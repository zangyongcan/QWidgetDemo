#ifndef TOOLTIP_H
#define TOOLTIP_H

#include <QWidget>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void on_rBtnSystemToolTip_clicked();

    void on_rBtnCustomToolTip_clicked();

    void on_btnSave_clicked();

    void on_btnDel_clicked();

    void on_spinBox_valueChanged(int arg1);

    void on_tabWidget_currentChanged(int index);

private:
    Ui::Widget *ui;

    QString m_IniPath;
    bool m_bSystem = true;
    int m_lastIndex = 0;
};

#endif // TOOLTIP_H
