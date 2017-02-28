#include "widget.h"
#include "ui_widget.h"
#include <QMessageBox>
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    if(LoadMap())
    {
        ui->setupUi(this);
        this->setWindowTitle("Query System on Chinese map");
        //QObject::connect(ui->QueryButton,SIGNAL(clicked(bool)),this,SLOT(on_QueryButton_clicked()));
        QObject::connect(ui->ColorButton,SIGNAL(clicked(bool)),this,SLOT(on_ColorButton_clicked()));
        QObject::connect(ui->NetButton,SIGNAL(clicked(bool)),this,SLOT(on_NetButton_clicked()));
        QObject::connect(ui->RestoreButton,SIGNAL(clicked(bool)),this,SLOT(on_RestoreButton_clicked()));
        //connect(ui->HelpButton,SIGNAL(clicked(bool)),this,SLOT(on_HelpButton_clicked()));
        //connect(ui->AboutButton,SIGNAL(clicked(bool)),this,SLOT(on_AboutButton_clicked()));
        lableimage = QImage(":/new/icon/img.jpg") ;
        ui->label->setPixmap( QPixmap::fromImage( lableimage ).scaled(ui->label->size()) );
    }
    else
    {
        QMessageBox::information(this,tr("Error"),tr("Unable to load the data."));
    }
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_AboutButton_clicked()
{
    QMessageBox::information(this,tr("About"),tr("Copyright©Jeff Mei 2017\nMiss Shanghai Always."));
}

void Widget::on_RestoreButton_clicked()
{
    lableimage = QImage(":/new/icon/img.jpg") ;
    ui->label->setPixmap( QPixmap::fromImage( lableimage ).scaled(ui->label->size()) );
}

void Widget::on_HelpButton_clicked()
{
    help *widget = new help;
    widget->show();
}

void Widget::on_QueryButton_clicked()
{
    prov_info *widget = new prov_info;
    widget->show();
}

void Widget::on_ColorButton_clicked()
{
    QImage image = getTransImage(lableimage);
    ui->label->setPixmap( QPixmap::fromImage( image ).scaled(ui->label->size()) );
}

void Widget::on_NetButton_clicked()
{
        QImage image = LinkImage(NULL,lableimage);
        ui->label->setPixmap( QPixmap::fromImage ( image ).scaled(ui->label->size()) );
}

QImage Widget::getTransImage(QImage image)
{
    int i,j,red, green, blue;
    int color[32];
    QRgb map_color, ColorBox[4];
    QPoint point[4],pt;
    LinkQueue Q[32];
    for(i = 0; i < 32; i++) color[i] = 0;
    graph_color(map,color,4);
    ColorBox[0] = qRgb(0,205,0);
    ColorBox[1] = qRgb(205,0,0);
    ColorBox[2] = qRgb(0,0,205);
    ColorBox[3] = qRgb(255,215,0);
    for(i = 0; i < 32; i++)
    {
        switch(color[i])
        {
            case 1:
            {
                map_color = ColorBox[0];break;
            }
            case 2:
            {
                map_color = ColorBox[1];break;
            }
            case 3:
            {
                map_color = ColorBox[2];break;
            }
            case 4:
            {
                map_color = ColorBox[3];break;
            }
            default:
            {
                map_color = qRgb(255,255,255);break;
            }
        }
        InitQueue(Q[i]);
        Enqueue(Q[i],pro[i]);

        while(!QisEmpty(Q[i]))
        {
            Dequeue(Q[i],pt);
            red = qRed(image.pixel(pt.rx(),pt.ry()));
            green = qGreen(image.pixel(pt.rx(),pt.ry()));
            blue = qBlue(image.pixel(pt.rx(),pt.ry()));
            if(red>=200 && green>=200&& blue>=200 )
            {
                image.setPixel(pt, map_color);
                point[0].rx()=pt.rx()+1;
                point[0].ry()=pt.ry();
                point[1].rx()=pt.rx()-1;
                point[1].ry()=pt.ry();
                point[2].ry()=pt.ry()+1;
                point[2].rx()=pt.rx();
                point[3].ry()=pt.ry()-1;
                point[3].rx()=pt.rx();
                for(j=0;j<4;j++)
                {
                    red = qRed(image.pixel(point[j].rx(),point[j].ry()));
                    green = qGreen(image.pixel(point[j].rx(),point[j].ry()));
                    blue = qBlue(image.pixel(point[j].rx(),point[j].ry()));
                    if(red>=200 && green>=200&& blue>=200 )
                    {
                         Enqueue(Q[i],point[j]);
                    }
                }
            }
         }

    }
    return image;
}

QImage Widget::LinkImage(QPaintEvent *,QImage image)
{
    QPainter painter(&image);             // 创建QPainter一个对象
    QPen pen;
    int i;
    edge T[31];
    prim_graph(map,T);
    pen.setColor(Qt::red);           // 设置画笔为红色
    painter.setPen(pen);                // 设置画笔
    for(i = 0; i < 31; i++)
    {
        painter.drawLine(pro[T[i].fromvex-1].rx(),pro[T[i].fromvex-1].ry(),pro[T[i].endvex-1].rx(),pro[T[i].endvex-1].ry());
    }
    return image;
}
