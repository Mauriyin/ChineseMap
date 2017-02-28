#include "prov_info.h"
#include "ui_prov_info.h"
#include <QMessageBox>
#include <string.h>
#include <stdio.h>

prov_info::prov_info(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::prov_info)
{
    if(Load())
    {
        ui->setupUi(this);
        this->setWindowTitle("Query");
        QObject::connect(ui->OKButton,SIGNAL(clicked(bool)),this,SLOT(on_OK_Button_clicked()));
    }
    else
        QMessageBox::information(this,tr("Error"),tr("Unable to load the data."));
}

prov_info::~prov_info()
{
    delete ui;
}

void prov_info::on_OK_Button_clicked()
{
    QString str;
    int item = ui->ComboBox->currentIndex();
    char a[10];
    sprintf(a,"%.2f",prov[item].popu);
    str += tr(prov[item].prov_name);
    str += tr("\n");
    str += tr("Capital: ");
    str += tr(prov[item].capt_name);
    str += tr("\n");
    str += tr("Population: ");
    str += tr(a);
    str += tr("million\n");
    str += tr("Code: ");
    str += tr(prov[item].tel_num);
    str += tr("\n");
    switch(prov[item].location)
    {
        case 0:{
            str += tr("Location: Northern China\n");break;
        }
        case 1:{
            str += tr("Location: Northeast China\n");break;
        }
        case 2:{
            str += tr("Location: Eastern China\n");break;
        }
        case 3:{
            str += tr("Location: Central China\n");break;
        }
        case 4:{
            str += tr("Location: Southern China\n");break;
        }
        case 5:{
            str += tr("Location: Southwest China\n");break;
        }
        case 6:{
            str += tr("Location: Western China\n");break;
        }
        case 7:{
            str += tr("Location: Under ROC control\n");break;
        }
    }
    QMessageBox::information(this, tr("Result"), str);
}
