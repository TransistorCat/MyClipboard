#include "customtimepanel.h"
#include "ui_customtimepanel.h"

CustomTimePanel::CustomTimePanel(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::CustomTimePanel)
{
    ui->setupUi(this);
    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(on_buttonBox_accepted()));
    ui->dateEdit->setDate(QDate::currentDate());
        ui->dateEdit_2->setDate(QDate::currentDate());
}

QDate CustomTimePanel::GetStartDate()
{
    return startDate;
}

QDate CustomTimePanel::GetEndData()
{
    return endDate;
}

CustomTimePanel::~CustomTimePanel()
{
    delete ui;
}

void CustomTimePanel::on_buttonBox_rejected()
{
    qDebug()<<"rejected";
    this->hide();
}


void CustomTimePanel::on_buttonBox_accepted()
{
    startDate=ui->dateEdit->date();
    endDate=ui->dateEdit_2->date();
    qDebug()<<"accepted";
    // emit confirmation(startDate, endDate);
    this->close();
}

