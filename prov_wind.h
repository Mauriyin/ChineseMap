#ifndef PROV_WIND_H
#define PROV_WIND_H

#include <QWidget>

namespace Ui {
class prov_wind;
}

class prov_wind : public QWidget
{
    Q_OBJECT

public:
    explicit prov_wind(QWidget *parent = 0);
    ~prov_wind();

private:
    Ui::prov_wind *ui;

public:
    typedef int status;
    typedef struct PNode{             //省份信息节点结构
        int num;                      //节点序号
        char prov_name[30];           //省份名
        char capt_name[30];           //省会名
        char tel_num[6];              //电话区号
        float popu;                   //人口
    }PNode;
    typedef struct Graph{              //图结构
        PNode Adjlist[50];			//省份节点数组
        int map[50][50];//邻接矩阵
        int vex_num ;                           //节点数量
    }Graph;

    Graph *G;

    status Load(void)
    {
        FILE *in;
        if((in = fopen("d:\\graph_info_table.txt","r")) == NULL)
             exit(-1);
        int i;
        for(i=0; i<31; i++)
            fscanf(in,"%d %s %s %s %f",&G->Adjlist[i].num,G->Adjlist[i].prov_name,G->Adjlist[i].capt_name,G->Adjlist[i].tel_num,&G->Adjlist[i].popu);
        fclose(in);
        return true;
    }

};

#endif // PROV_WIND_H
