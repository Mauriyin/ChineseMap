#include "prov_wind.h"
#include "ui_prov_wind.h"
#include <QMessageBox>

prov_wind::prov_wind(QWidget *parent) :
    QWidget(parent),

    ui(new Ui::prov_wind)
{
    if (Load())
        {
            ui->setupUi(this);
            int item = ui->ComboBox->currentIndex();
            ui->label_1->setText("Province:"+QString::fromLocal8Bit(G->Adjlist[item].prov_name));
            ui->label_2->setText("Capital"+QString::fromLocal8Bit(G->Adjlist[item].capt_name));
            ui->label_3->setText("Poplulation"+QString("%1").arg(G->Adjlist[item].popu));
            ui->label_4->setText("Telephone Code"+QString::fromLocal8Bit(G->Adjlist[item].tel_num));
        }
    else
    {
        QMessageBox::in0formation(this,tr("Error"),tr("Unable to load resource file."));
    }
}

prov_wind::~prov_wind()
{
    delete ui;
}
