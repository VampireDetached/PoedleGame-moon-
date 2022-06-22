#include "widget.h"
#include "QWidget"
#include "ui_widget.h"
#include "QPushButton"
#include "QLabel"
#include "QDialog"
#include "QMessageBox"
#include "QPixmap"
#include "QTextEdit"
#include "QFont"
#include "QDebug"
#include "QtGui"
#include "QByteArray"
#include "stdio.h"
#include "ctime"
#include "QTextStream"
#include "QByteArray"
#include "fstream"
#include "QVector"
#include "QTextCodec"
#include <iostream>
#include <fstream>

int t=-1;
int totaltime=0;
int poemnum=182;
char in[5];
int ch=0;
const char * fake;
QString answer;
QString canswer;
QString ttime;
QString input;
QString filename=":/pic/substitute.txt";
QString tobecheck=":/pic/moonpoems.txt";
QString cinput;
QString s1="You still have 5 chances left !";
QString s2="You still have 4 chances left !";
QString s3="You still have 3 chances left !";
QString s4="You still have 2 chances left !";
QString s5="You still have 1 chances left !";
QString s6="You have no chance left !";
QVector<QString>checkwords(200);

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setWindowTitle("Poedle");
    this->setFixedSize(700,1200);
    //控件对象的定义与调整
    QFont ft1;
    ft1.setPointSize(14);
    ft1.setFamily("STHeiti");
    QFont ft2;
    ft2.setPointSize(28);
    ft2.setFamily("STHeiti");
    QPushButton * btn1=new QPushButton("Start",this);
    btn1->setFont(ft1);
    btn1->setFixedSize(200,50);
    btn1->move(250,700);
    QPushButton * btn11=new QPushButton("",this);
    btn11->resize(0,0);
    QPushButton * btn2=new QPushButton("Rules",this);
    btn2->setFont(ft1);
    btn2->setFixedSize(200,50);
    btn2->move(250,800);
    QPushButton * btn3=new QPushButton("Quit",this);
    btn3->setFont(ft1);
    btn3->setFixedSize(200,50);
    btn3->move(250,900);
    QLabel * label1=new QLabel("",this);
    QPixmap pic1;
    pic1.load(":/pic/title.png");
    label1->setPixmap(pic1);
    label1->setFixedSize(800,600);
    label1->setIndent(60);
    QLabel * label2=new QLabel("Presented by 刘子张",this);
    label2->setFixedSize(300,50);
    label2->move(240,600);
    QWidget * nw=new QWidget;
    nw->setFixedSize(550,550);
    nw->setWindowTitle("Input");
    QLabel * nwlabel=new QLabel("",nw);
    nwlabel->setFixedSize(500,100);
    nwlabel->move(25,0);
    nwlabel->setText("You still have 6 chances left !");
    nwlabel->setFont(ft1);
    nwlabel->setIndent(15);
    QTextEdit * ne=new QTextEdit(nw);
    ne->setFixedSize(500,200);
    ne->setFontPointSize(64);
    ne->move(25,100);
    QPushButton * nwbtn=new QPushButton("Submit",nw);
    nwbtn->setFont(ft1);
    nwbtn->setFixedSize(200,100);
    nwbtn->move(175,330);
    QWidget * sw=new QWidget;
    sw->setWindowTitle("Results");
    sw->setFixedSize(465,1200);
    ttime=QString::number(totaltime,10);
    QString temp1="You have played ";
    temp1.append(ttime);
    temp1.append(" games.");
    QLabel * timelabel=new QLabel("",sw);
    timelabel->setFixedSize(465,100);
    timelabel->move(0,1060);
    timelabel->setText(temp1);
    timelabel->setIndent(100);
    QLabel * slabel[60]={
        new QLabel("",sw),new QLabel("",sw),new QLabel("",sw),new QLabel("",sw),
        new QLabel("",sw),new QLabel("",sw),new QLabel("",sw),new QLabel("",sw),
        new QLabel("",sw),new QLabel("",sw),new QLabel("",sw),new QLabel("",sw),
        new QLabel("",sw),new QLabel("",sw),new QLabel("",sw),new QLabel("",sw),
        new QLabel("",sw),new QLabel("",sw),new QLabel("",sw),new QLabel("",sw),
        new QLabel("",sw),new QLabel("",sw),new QLabel("",sw),new QLabel("",sw),
        new QLabel("",sw),new QLabel("",sw),new QLabel("",sw),new QLabel("",sw),
        new QLabel("",sw),new QLabel("",sw),new QLabel("",sw),new QLabel("",sw),
        new QLabel("",sw),new QLabel("",sw),new QLabel("",sw),new QLabel("",sw),
        new QLabel("",sw),new QLabel("",sw),new QLabel("",sw),new QLabel("",sw),
        new QLabel("",sw),new QLabel("",sw),new QLabel("",sw),new QLabel("",sw),
        new QLabel("",sw),new QLabel("",sw),new QLabel("",sw),new QLabel("",sw),
        new QLabel("",sw),new QLabel("",sw),new QLabel("",sw),new QLabel("",sw),
        new QLabel("",sw),new QLabel("",sw),new QLabel("",sw),new QLabel("",sw),
        new QLabel("",sw),new QLabel("",sw),new QLabel("",sw),new QLabel("",sw)
    };
    for (int i=0;i<12;i++)
    {
        for (int j=0;j<5;j++)
        {
            slabel[5*i+j]->setFixedSize(75,75);
            slabel[5*i+j]->move(25+85*j,25+85*i);
            slabel[5*i+j]->setStyleSheet(QString("background-color:")+"lightgrey");
        }
    }

    //初始化答案
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    changeanswer(":/pic/substitute.txt");

    //关联信号与槽
    connect(btn1,&QPushButton::clicked,nw,[=](){
        nw->show();
    });

    connect(btn2,&QPushButton::clicked,[=](){
        QMessageBox::information(this,"游戏规则","1.游戏中，你都要通过六次猜测找到一个五个字组成的含有“月”字的诗句。\n2.每次你输入答案之后，你都会得到十个色块作为提示。\n3.色块的上面一行中，灰色色块表示你填入的字没有在这句诗里出现；黄色色块表示这个字在这句诗中出现了，但是位置不正确；绿色方块表示这个字出现在这句诗的正确位置。\n色块的下面一行中，红色表示你填入的字词性是错误的，蓝色表示你填入的字词性是正确的。\n4.当你猜出答案或者是用完六次机会时，你会得到一张色块图来记录你的猜词经历。");
    });

    connect(btn3,&QPushButton::clicked,[=](){
        this->close();
    });

    connect(nwbtn,&QPushButton::clicked,this,[=](){
        int tr=0;
        input=ne->toPlainText();
        ne->clear();
        if (input.length()==5)
        {
            int checkpoint=0;
            QFile file;
            file.setFileName(":/pic/substitute.txt");
            if (file.open(QIODevice::ReadOnly|QIODevice::Text))
            {
                //检测填入的五个字是否在诗句库中
                QString tan;
                QTextStream fin(&file);

                for (int i=0;i<166;i++)
                {
                    fin.device()->seek(15*i);
                    QString check=fin.read(5);
                    if(check==input)
                    {
                        checkpoint=1;
                        file.close();
                        tr=i;
                        break;
                    }

                }
            }
            if (checkpoint==0)
            {QMessageBox::warning(nw,"Warning","你输入的词不是含有月的五个字的诗句");}
            else
            {
                QFile cfile;
                cfile.setFileName(":/pic/moonpoems.txt");
                if (cfile.open(QIODevice::ReadOnly|QIODevice::Text))
                {
                    QTextStream cfin(&cfile);
                    cfin.device()->seek(15*tr);
                    cinput=cfin.read(5);
                    cfile.close();
                }
                t++;
                int right=0;
                for (int i=0;i<5;i++)
                {
                    if ((10*t+i<60)&&(10*t+i>=0))
                    {

                      //对填入的诗句每个字进行判断
                        slabel[10*t+i]->setFont(ft2);
                        slabel[10*t+i]->setAlignment(Qt::AlignVCenter);
                        slabel[10*t+i]->setAlignment(Qt::AlignHCenter);
                        for (int j=0;j<5;j++)
                        {
                            if(input[i]==answer[j])
                            slabel[10*t+i]->setStyleSheet(QString("background-color:")+"yellow");
                        }
                        if (input[i]==answer[i])
                        {
                            slabel[10*t+i]->setStyleSheet(QString("background-color:")+"green");
                            right++;
                        }
                    }


                    if ((10*t+5+i<60)&&(10*t+5+i>=0))
                    {

                      //对填入的文字的词性进行判断
                        slabel[10*t+5+i]->setFont(ft2);
                        slabel[10*t+5+i]->setAlignment(Qt::AlignVCenter);
                        slabel[10*t+5+i]->setAlignment(Qt::AlignHCenter);
                        if (cinput[i]==canswer[i])
                        {
                            slabel[10*t+5+i]->setStyleSheet(QString("background-color:")+"deepskyblue");
                        }
                        else
                        {
                            slabel[10*t+5+i]->setStyleSheet(QString("background-color:")+"red");
                        }
                    }
                }

                for (int i=0;i<5;i++)
                {
                    if ((10*t+i<60)&&(10*t+i>=0))
                    {
                        slabel[10*t+i]->setText(input.at(i));
                        slabel[10*t+i]->setFont(ft2);
                        slabel[10*t+5+i]->setText(cinput.at(i));
                        slabel[10*t+5+i]->setFont(ft2);
                    }
                }
                nw->close();
                sw->show();
                ne->setPlainText("");
                if ((t<5)&&(right!=5))
                nw->show();
                if (right==5)
                {

                   //显示答案
                    QMessageBox::information(nw,"You find the answer!",answer);
                    connect(nwbtn,&QPushButton::clicked,nw,[=](){nw->close();});
                    btn11->setText("Results");
                    btn11->setFont(ft1);
                    btn11->setFixedSize(200,50);
                    btn11->move(250,800);
                    btn2->move(250,900);
                    btn3->move(250,1000);
                    connect(btn11,&QPushButton::clicked,sw,[=](){sw->show();});
                    t=-1;
                    totaltime++;
                    ttime=QString::number(totaltime,10);
                    QString temp2="You have played ";
                    temp2.append(ttime);
                    temp2.append(" games.");
                    timelabel->setText(temp2);
                    nwlabel->setText("You still have 6 chances left !");
                    ne->setText("");

                    for (int i=0;i<60;i++)
                    slabel[i]->setText("");
                    sw->show();
                    QMessageBox::information(sw,"Your result picture","This is your result and will remake after you close it.");
                    for (int i=0;i<60;i++)
                    slabel[i]->setStyleSheet(QString("background-color:")+"lightgrey");
                    sw->close();
                    changeanswer(":/pic/substitute.txt");
                    ch++;
                    right=0;
                }
                else
                {
                    switch(t)
                    {
                        case 0:nwlabel->setText(s1);
                        break;
                        case 1:nwlabel->setText(s2);
                        break;
                        case 2:nwlabel->setText(s3);
                        break;
                        case 3:nwlabel->setText(s4);
                        break;
                        case 4:nwlabel->setText(s5);
                        break;
                        case 5:nwlabel->setText(s6);
                        break;
                    }
                }
                if ((t==5)&&(right!=5))
                {

                    //显示答案
                    QMessageBox::information(nw,"Answer that you failed to find!",answer);
                    btn11->setText("Results");
                    btn11->setFont(ft1);
                    btn11->setFixedSize(200,50);
                    btn11->move(250,800);
                    btn2->move(250,900);
                    btn3->move(250,1000);
                    connect(btn11,&QPushButton::clicked,nw,[=](){sw->show();});
                    t=-1;
                    totaltime++;
                    ttime=QString::number(totaltime,10);
                    QString temp2="You have played ";
                    temp2.append(ttime);
                    temp2.append(" games.");
                    timelabel->setText(temp2);
                    nwlabel->setText("You still have 6 chances left !");
                    ne->setText("");
                    for (int i=0;i<60;i++)
                    slabel[i]->setText("");
                    sw->show();
                    QMessageBox::information(sw,"Your result picture","This is your result and will remake after you close this dialog. To start a new game, click 'OK' and then click start");
                    for (int i=0;i<60;i++)
                    slabel[i]->setStyleSheet(QString("background-color:")+"grey");
                    sw->close();
                    changeanswer(filename);
                }
            }


         }
        else
        {
            QMessageBox::warning(nw,"Warning","你输入的词不是含有五个字母的诗句");
        }
    });


}

void Widget::changeanswer(QString f)
{
    //取随机数
    srand(unsigned(time(0)));
    int cho=rand()%poemnum;

    //随机取答案诗句
    QFile file;
    file.setFileName(f);
    if (file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        QString tan;
        QTextStream fin(&file);
        fin.device()->seek(15*cho);
        answer=fin.read(5);
        file.close();
    }

    //找到答案诗句对应的词性
    QFile cfile;
    cfile.setFileName(tobecheck);
    if(cfile.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        QTextStream cfin(&cfile);
        cfin.device()->seek(15*cho);
        canswer=cfin.read(5);
        cfile.close();
    }
}

Widget::~Widget()
{
    delete ui;
}
