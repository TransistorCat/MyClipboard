#ifndef CUSTOMTIMEPANEL_H
#define CUSTOMTIMEPANEL_H

#include "qdatetime.h"
#include <QDialog>

namespace Ui {
class CustomTimePanel;
}

class CustomTimePanel : public QDialog
{
    Q_OBJECT

public:
    explicit CustomTimePanel(QWidget *parent = nullptr);
    QDate GetStartDate();
    QDate GetEndData();
    ~CustomTimePanel();

private slots:
    void on_buttonBox_rejected();


    void on_buttonBox_accepted();
signals:
    // void confirmation(const QDate &start, const QDate &end);
private:
    Ui::CustomTimePanel *ui;
    QDate startDate;
    QDate endDate;
};

#endif // CUSTOMTIMEPANEL_H
