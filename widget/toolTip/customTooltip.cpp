#include "customTooltip.h"
#include <QPlainTextEdit>
#include <QHBoxLayout>
#include <QEvent>
#include <QDebug>

CustomToolTip::CustomToolTip()
{
    setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog | Qt::WindowStaysOnTopHint);
    setAttribute(Qt::WA_DeleteOnClose);

    m_pTxtEdit = new QPlainTextEdit(this);
    m_pTxtEdit->setFixedWidth(512);
    m_pTxtEdit->setReadOnly(true);
    QHBoxLayout *hLayout = new QHBoxLayout(this);
    hLayout->addWidget(m_pTxtEdit);
    hLayout->setContentsMargins(QMargins(3, 3, 3, 3));
    hLayout->setSpacing(0);
    setLayout(hLayout);

    this->installEventFilter(this);
    this->setStyleSheet("QDialog { background: #FFFFFFFF; border:1px; border-radius:12px };");
    m_pTxtEdit->setStyleSheet("QPlainTextEdit { background: #AABDF0FF; border:1px groove #DDBDF0FF; border-radius:10px };"
                              "QScrollBar:vertical { width: 0px; } ");
}

CustomToolTip::~CustomToolTip()
{

}

void CustomToolTip::popup(QPoint pos, const QString &text)
{
    CustomToolTip *t = new CustomToolTip();
    t->setText(text);
    t->setAttribute(Qt::WA_DeleteOnClose);
    t->show();
    t->move(pos);
}

void CustomToolTip::calQPlainTextEditAutoTxtHeight(QPlainTextEdit *pTxtEdit, int &height)
{
    int blockCount = pTxtEdit->blockCount();//有多少个块。就代表有多少个空行
    //计算字体的宽度
    int nSumWidth = pTxtEdit->fontMetrics().width(pTxtEdit->toPlainText());
    int nUiWidth = pTxtEdit->width() - 10;//10px：样式表中的圆弧半径
    int nHeight = pTxtEdit->fontMetrics().lineSpacing();//字体每一行的高度
    qDebug() << "pTxtEdit->toPlainText(): " << pTxtEdit->toPlainText();
    qDebug() << "nSumWidth: " << nSumWidth << ", nUiWidth: " << nUiWidth;
    //字体宽度/每一行的宽度为字体占据多少行
    int nRowCount = static_cast<int>(ceil(static_cast<float>(nSumWidth) / nUiWidth));
    //最终的行数为字体占据的行数+空行的行数（计算的可能不太正确，继续验证）
    nRowCount = nRowCount + blockCount;
    height = nHeight * nRowCount;
}

bool CustomToolTip::eventFilter(QObject *obj, QEvent *e)
{
    if (obj == this){
        if (QEvent::WindowDeactivate == e->type()){
            this->close();
            e->accept();
            return true;
        }
    }
    return QWidget::eventFilter(obj, e);
}

void CustomToolTip::setText(const QString &text)
{
    m_pTxtEdit->setPlainText(text);

    int nHeight = 1;
    CustomToolTip::calQPlainTextEditAutoTxtHeight(m_pTxtEdit, nHeight);
    m_pTxtEdit->setFixedHeight(nHeight);
}
