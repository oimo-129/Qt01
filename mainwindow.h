#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "xlsx.h"//表格操作
#include <QDebug>
#include <QFont>//字体
#include <QTime>//时间
#include <QTimer>//时间
#include <QSerialPort>
#include <QSerialPortInfo>
//鼠标特效
#include <QMovie>
#include <QLabel>
#include <QMouseEvent>
#include <QLine>
#include <QtCharts>
#define SIZE 34

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    friend class MyButton_1;
public:
    QString time_china1;//北京时间:年-月-日-时-周
    QString time_china2;//北京时间:年-月-日-时
    QString time_china3;//北京时间:时
    //图表与线条
    QChart* chart;
    QValueAxis *axisx;
    QValueAxis *axisy;

    QLineSeries *seriesigbt1;
    QLineSeries *seriesigbt2;
    QLineSeries *seriestop;
    QLineSeries *seriesbottom;

    void initchart();  //初始化图
    void putline(QLineSeries *series);  //添加线
    void showchart(int xrange, int yrangestart, int yrangeend);  //显示图

    int tmin;  //温度最小值
    int tmax;  //温度最大值

    int xlength;  //数据量

    int min(int a[], int n);
    int max(int a[], int n);



    //协议
    int length; //从机长度
    int length1;//主机长度
    QString str;//从机协议字符串
    QString str1;//主机协议字符串
    quint8 treaty[SIZE]={0};//从机协议缓冲区
    quint8 treaty1[SIZE]={0};//主机协议缓冲区

    //临界资源
    int source;
    //从机信息
    //从机协议
    int flag0;//检测到从机头码标志位
    int head;//头码
    int tail;//尾码
    int data_size0;//从机数据长度

    //主机信息
    //主机协议
    int flag_zhu;//检测到主机头码标志位
    int head1;//头码
    int tail1;//尾码
    int data_size1;//主机数据长度

    //从机显示
    QString TIGBT;
    QString RIGBT;
    QString work_phase;
    QString mode;
    float work_time;
    QString Top_hit_state;
    QString margin_hit_state;
    QString R_triangle_hit_state;
    QString Bottom_hit_state;
    QString fanya;

    //主机显示
    QString type;
    QString top;
    QString RI;//(int)
    QString BI;//(int)
    QString T;//(int)
    QString B;
    QString R;
    QString state;
    QString C;

    //定时器
    QTimer *timer;//初始化一个定时器，用于显示当前日期
    QTimer *timer1;//初始化一个定时器，用于计算工作时间

    //从机协议xlsx
    int j;//记录第j个表格；
    QString filename;
    int flag1;//文件创建标志位
    QXlsx::Document xlsx;//文件
    int row;//存入文件行

    //主机协议xlsx
    int k;//记录第k个表格；
    QString filename1;
    int flag2;//文件创建标志位
    QXlsx::Document xlsx1;//文件
    int row1;//存入文件行


public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QSerialPort *serialPort;

    //初始化参数
    void InitParam();
    //初始化串口号
    void InitPort();
    void readToHex();
    bool solve(int num);//处理从机协议
    bool solve1(int num);//处理主机协议
protected:
    //重写绘图事件（背景、窗口圆角）
    void paintEvent(QPaintEvent *);

    //鼠标双击事件
    void mouseDoubleClickEvent(QMouseEvent *event);
public slots:
    //时间槽函数
    void timerUpdata(void);
    void showParameter();
   // void fun();
private slots:

    void on_start_test_released();
    void on_end_test_released();

    //void on_groupBox_clicked();

    void on_actionSearch_triggered();
    void on_actionOpen_triggered();
    void on_data_button_2_activated(int index);
};

#endif // MAINWINDOW_H
