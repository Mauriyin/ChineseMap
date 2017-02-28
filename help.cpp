#include "help.h"
#include "ui_help.h"

help::help(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::help)
{
    ui->setupUi(this);
    this->setWindowTitle("Help");
    str = tr("This program is a simple analysis on Chinese map.\n");
    str += tr("It has 4 functions as the following.\n");
    str += tr("Search the map: Find information of all 32 areas except HK and Macau.\n");
    str += tr("Fill the map: Fill the map while extinguishing neighboring areas in different colors.\n");
    str += tr("Link the map: Linking the major cities with the shortest distance in total.\n");
    str += tr("Restore: Show a blank map.\n");
    ui->label->setText(str);
}

help::~help()
{
    delete ui;
}
