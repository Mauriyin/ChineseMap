#ifndef PROV_INFO_H
#define PROV_INFO_H

#include <QWidget>
#include "stdlib.h"

namespace Ui {
class prov_info;
}

class prov_info : public QWidget
{
    Q_OBJECT

public:
    explicit prov_info(QWidget *parent = 0);
    ~prov_info();

private:
    Ui::prov_info *ui;

private slots:
    void on_OK_Button_clicked();

public:
    typedef int status;
    typedef struct PNode{             //省份信息节点结构
        int num;                      //节点序号
        char prov_name[30];           //省份名
        char capt_name[30];           //省会名
        char tel_num[6];              //电话区号
        float popu;                   //人口
        int location;                 //位置
    }PNode;
    int map[50][50];                  //邻接矩阵

    PNode prov[32];

    status Load(void)
   {
       FILE *fp;
       if(!(fp=fopen("graph_info_table.txt", "r")))
           exit(-1);
       int i;
       for(i=0; i<32; i++)
           fscanf(fp,"%d %s %s %f %s %d",&prov[i].num,prov[i].prov_name,prov[i].capt_name,&prov[i].popu,prov[i].tel_num,&prov[i].location );
       fclose(fp);
       return true;
   }

};


#endif // PROV_INFO_H
