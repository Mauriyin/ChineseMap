#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QImage>
#include <QPixmap>
#include <QBitmap>
#include <QIcon>
#include <QPoint>
#include <QVector>
#include <QDebug>
#include <QMessageBox>
#include <stdio.h>
#include <prov_info.h>
#include <help.h>
#include <QPainter>
#include <QPen>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void on_AboutButton_clicked();
    void on_QueryButton_clicked();
    void on_ColorButton_clicked();
    void on_NetButton_clicked();
    void on_HelpButton_clicked();
    void on_RestoreButton_clicked();

private:
    QImage  lableimage ;
    QImage  getTransImage(QImage image);
    QImage  LinkImage(QPaintEvent *, QImage image);

private:
    Ui::Widget *ui;

public:
    typedef int status;
    typedef struct edge
    {
        int fromvex,endvex;                 //边的起点和终点
        int length;                         //边的权值
    }edge;
    typedef struct ANode{                   //最小生成树辅助数组
        int from;                               //起始点
        int to;                                 //终止点
        int weight;                             //权值
        int flag;                               //标记
    }ANode;
    typedef struct QNode{
            QPoint data;
            struct QNode *next;
    }QNode,*QueuePtr;                  //像素点队列
    typedef struct{
            QueuePtr front;
            QueuePtr rear;
    }LinkQueue;                        //队列头尾指针

    QPoint pro[32];                   //省份像素点数组
    int map[32][32];                  //邻接矩阵
    char prov[32][30];                //省份名数组
    char prim_prov[32][30];           //最小生成树省份数组

    status InitQueue(LinkQueue &Q)
    {
        Q.front=(QueuePtr)malloc(sizeof(QNode));
        if(!Q.front) exit(-1);
        Q.front->next=NULL;
        Q.rear=Q.front;
        return true;
    }                                  //初始化队列

    status Enqueue(LinkQueue &Q,QPoint &e)
    {
        QNode *p;
        p=(QueuePtr)malloc(sizeof(QNode));
        if(!p)  exit(-1);
        p->data=e;
        p->next=NULL;
        Q.rear->next=p;
        Q.rear=p;
        return true;
    }                                  //元素进队

    QPoint Dequeue(LinkQueue &Q,QPoint &e)
    {
        QNode *p;
        p=Q.front->next;
        e=p->data;
        Q.front->next=p->next;
        if(Q.rear==p)
            Q.rear=Q.front;
        free(p);
        return e;
    }                                  //元素出队

    status QisEmpty(LinkQueue &Q)
    {
        if(Q.front==Q.rear)
            return true;
        else
            return false;
    }                                 //判断队列是否为空

    void graph_color(int map[][32],int color[],int m)
    {
        int k = 0;
        while(k >= 0)
        {
            color[k] = color[k] + 1;
            while(color[k] <= m)
                if (judge_color(map,color,k)) break;
                else color[k] = color[k] + 1;//搜索下一个颜色
            if(color[k] <= m && k == 32)	break;//求解完毕，输出解
            else if(color[k] <= m && k < 32)
                    k = k + 1;    //处理下一个顶点
            else
            {
                color[k] = 0;
                k = k - 1;//回溯
            }
        }
    }   //上色函数

    status judge_color(int map[][32],int color[],int k)
    {
        int i;
        for(i = 0; i < 32; i++)
            if(map[k][i] > 1 && color[i] == color[k])	return 0;
            return 1;
    }	//判断相邻省份色彩是否重复

    void prim_graph(int map[][32],edge T[])//
    {
        int j,k,m,v,min,max=10000;
        int d;
        edge e;
        for(j=1;j<32;j++)  //构造初始候选紫边集
        {
            T[j-1].fromvex=1;  //顶点1是第一个加入树中的红点
            T[j-1].endvex=j+1;
            T[j-1].length=map[0][j];
        }
        for(k=0;k<31;k++)//求第k条边
        {
            min=max;
            for(j=k;j<31;j++)//在候选紫边集中找出最短紫边
            {
                if(T[j].length < min && T[j].length > 1)
                {
                    min=T[j].length;
                    m=j;
                }//T[m]是当前最短紫边
            }
            e=T[m];T[m]=T[k];T[k]=e;//T[k]和T[m]交换后，T[k]是第k条红色树边
            v=T[k].endvex;//v是新红点
            for(j=k+1;j<31;j++)//调整候选紫边集
            {
                d=map[v-1][T[j].endvex-1];
                if((d<T[j].length && d > 1) || T[j].length <= 1)
                {
                    T[j].length=d;
                    T[j].fromvex=v;
                }
            }
        }
    }

    status LoadMap()
    {
        FILE *fp1,*fp2;
        if(!(fp1 = fopen("D:\\dot_info_table.txt", "r")))
            exit(-1);
        int i,j;
        for(i=0; i<=31; i++)
            fscanf(fp1,"%d %d",&(pro[i].rx()),&(pro[i].ry()));
        fclose(fp1);
        if(!(fp2 = fopen("D:\\map_info_table.txt", "r")))
            exit(-1);
        for(i=0; i<=31; i++)
        {
            for(j=0; j<=31; j++)
            {
                fscanf(fp2,"%d",&map[i][j]);
            }
        }
        fclose(fp2);
        return true;
    }   //读取省份像素以及邻接信息

};



#endif // WIDGET_H
