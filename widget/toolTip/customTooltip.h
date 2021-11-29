#ifndef CUSTOMTOOLTIP_H
#define CUSTOMTOOLTIP_H

#include <QDialog>

class QPlainTextEdit;
class CustomToolTip : public QDialog
{
public:
    CustomToolTip();
    ~CustomToolTip();

    static void popup(QPoint pos, const QString &text);

    static void calQPlainTextEditAutoTxtHeight(QPlainTextEdit* pTxtEdit, int &height);

protected:
    bool eventFilter(QObject *obj, QEvent *e);

private:
    void setText(const QString &text);

private:
    QPlainTextEdit *m_pTxtEdit;
};

#endif // CUSTOMTOOLTIP_H
