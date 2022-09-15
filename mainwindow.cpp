/*对于Qt进行整改，以从机为模板*/
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFont>//字体
#include <QTime>//时间
#include <QTimer>//时间
#include <qdatetime.h>//日期
#include <QMovie>//加入动图
#include <QPainter>
#include <QPaintEvent>
#include "xlsx.h"//表格操作
#include <QDebug>
#include <QByteArray>
#include <QMessageBox>//对话框
#include <QBitmap>
#include <QFile>

//添加状态栏的功能
#include "findxlsx.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //menu优化
    ui->menu->setAttribute(Qt::WA_TranslucentBackground); //Menu背景透明
    ui->menu->setWindowFlags(ui->menu->windowFlags()  | Qt::FramelessWindowHint | Qt::NoDropShadowWindowHint);
    ui->menu_E->setAttribute(Qt::WA_TranslucentBackground); //Menu背景透明
    ui->menu_E->setWindowFlags(ui->menu->windowFlags()  | Qt::FramelessWindowHint | Qt::NoDropShadowWindowHint);
    ui->menu_H->setAttribute(Qt::WA_TranslucentBackground); //Menu背景透明
    ui->menu_H->setWindowFlags(ui->menu->windowFlags()  | Qt::FramelessWindowHint | Qt::NoDropShadowWindowHint);
    ui->menu_T->setAttribute(Qt::WA_TranslucentBackground); //Menu背景透明
    ui->menu_T->setWindowFlags(ui->menu->windowFlags()  | Qt::FramelessWindowHint | Qt::NoDropShadowWindowHint);

    initchart();
    seriesigbt1 = new QLineSeries();
    seriesigbt2 = new QLineSeries();
    seriestop = new QLineSeries();
    seriesbottom = new QLineSeries();
    seriesigbt1->setName("IGBT1");
    seriesigbt2->setName("IGBT2");
    seriestop->setName("顶部");
    seriesbottom->setName("底部");
    putline(seriesigbt1);
    putline(seriesigbt2);
    putline(seriestop);
    putline(seriesbottom);



    InitPort();
    //设置时间
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(timerUpdata()));
    timer->start(1000);
    //this->ui->toolBar->addAction("查询");
    //this->ui->toolBar->addAction("故障");
    //this->ui->toolBar->addAction("绘图");
    this->ui->end_test->setEnabled(false);//初始化停止测试按钮，不能使用
    this->ui->start_test->setEnabled(true);//初始化开始测试按钮，能使用
//connect(this->ui->toolBar->addAction("查询"),SIGNAL(triggered()),this,SLOT(fun()));
   InitParam();
}

//初始化参数
void MainWindow::InitParam(){
    //临界资源
    source=0;

    //协议信息
    length=0;
    length1=0;
    str="";
    str1="";

    //从机协议标志位
    flag0=0;
    head=30;//0X1E
    tail=205;//0XCD
    data_size0=12;

    //主机协议标志位
    flag_zhu=0;
    head1=104;//0X68
    tail1=43;//0X2B
    data_size1=13;

    //从机初始化参数
    TIGBT="";
    RIGBT="";
    work_phase="NULL";
    mode="NULL";
    work_time=0;
    Top_hit_state="";
    margin_hit_state="";
    R_triangle_hit_state="";
    Bottom_hit_state="";
    fanya="";

    //从机文件标志位
    row=1;
    flag1=0;
    j=1;
    filename="";

    //主机文件标志位
    row1=1;
    flag2=0;
    k=1;
    filename1="";

    //从机初始化参数
    type="";
    top="";
    RI="";
    BI="";
    T="";
    B="";
    R="";
    state="";
    C="";
}
//初始化串口号
void MainWindow::InitPort()
{
    const auto infos = QSerialPortInfo::availablePorts();
    for(const QSerialPortInfo &info : infos)
    {
        QSerialPort serial;
        serial.setPort(info);
        if(serial.open(QIODevice::ReadWrite))
        {
            ui->chuankou_button->addItem(info.portName());
            serial.close();
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}


//查找功能的制作
//void MainWindow::fun(){
//    FindXlsx  *findxlsx=new FindXlsx;
//    findxlsx->show();
//}



//设置时间
void MainWindow::timerUpdata(){
    QFont font("黑体",15,1);
    QDateTime time = QDateTime::currentDateTime();
    time_china1 = time.toString("yyyy-MM-dd hh:mm:ss dddd");
    time_china2 = time.toString("yyyy-MM-dd hh:mm:ss");
    time_china3 = time.toString("hh:mm:ss");
    this->ui->label_2 ->setFont(font);
    this -> ui->label_2->setText(time_china1);
}

//重写绘图事件,设置背景图片
void MainWindow::paintEvent(QPaintEvent *){
    QPainter p(this);
    p.drawPixmap(rect(),QPixmap(":/new/prefix1/picture/bg3 (2).jpg"));
}


//计时工作时间
void MainWindow::showParameter(){
    work_time++;
    ui->work_time_label->setText(QString::number(work_time)+"s");
    ui->work_time_label_2->setText(QString::number(work_time)+"s");
    //求温度最值
    int temmin[5]={tmin, Bottom_hit_state.toInt(), Top_hit_state.toInt(), TIGBT.toInt(), RIGBT.toInt()};
    int temmax[5]={tmax, Bottom_hit_state.toInt(), Top_hit_state.toInt(), TIGBT.toInt(), RIGBT.toInt()};
    tmin=min(temmin, 5);
    tmax=max(temmax, 5);

    //添加点
    seriesigbt1->append(work_time, TIGBT.toInt());
    seriesigbt2->append(work_time, RIGBT.toInt());
    seriestop->append(work_time, Top_hit_state.toInt());
    seriesbottom->append(work_time, Bottom_hit_state.toInt());

}

void MainWindow::on_start_test_released()
{
    tmin=250;
    tmax=-20;
    xlength=0;
    seriesigbt1->clear();
    seriesigbt2->clear();
    seriestop->clear();
    seriesbottom->clear();

    //启动定时器
    timer1 = new QTimer(this);
    connect(timer1,SIGNAL(timeout()),this,SLOT(showParameter()));
    timer1->start(1000);
    //配置串口信息
    serialPort = new QSerialPort;

    serialPort->setPortName(ui->chuankou_button->currentText());

    if(serialPort->open(QIODevice::ReadWrite))
    {
        switch (ui->bote_button->currentIndex()) {
        case 0:
            serialPort->setBaudRate(QSerialPort::Baud2400);
            break;
        case 1:
            serialPort->setBaudRate(QSerialPort::Baud4800);
            break;
        default:
            break;
        }
        switch (ui->stop_button->currentIndex()) {
        case 0:
            serialPort->setStopBits(QSerialPort::OneStop);
            break;
        case 1:
            serialPort->setStopBits(QSerialPort::TwoStop);
            break;
        default:
            break;
        }

        switch (ui->data_button->currentIndex()) {
        case 0:
            serialPort->setDataBits(QSerialPort::Data5);
            break;
        case 1:
            serialPort->setDataBits(QSerialPort::Data6);
            break;
        case 2:
            serialPort->setDataBits(QSerialPort::Data7);
            break;
        case 3:
            serialPort->setDataBits(QSerialPort::Data8);
            break;
        default:
            break;
        }

        switch (ui->jiou_button->currentIndex()) {
        case 0:
            serialPort->setParity(QSerialPort::NoParity);
            break;
        case 1:
            serialPort->setParity(QSerialPort::OddParity);
            break;
        case 2:
            serialPort->setParity(QSerialPort::EvenParity);
            break;
        default:
            break;
        }
        connect(serialPort, &QSerialPort::readyRead, this, &MainWindow::readToHex);
        //控件操作
        this->ui->start_test->setEnabled(false);
        this->ui->end_test->setEnabled(true);

        ui->chuankou_button->setEnabled(false);
        ui->stop_button->setEnabled(false);
        ui->bote_button->setEnabled(false);
        ui->jiou_button->setEnabled(false);
        ui->data_button->setEnabled(false);
        ui->actionOpen->setEnabled(false);
    }
    else
    {
        QMessageBox::critical(this, tr("Error"), serialPort->errorString());
    }
}

void MainWindow::on_end_test_released()
{

    //关闭定时器
    timer1->stop();
    disconnect(timer1,SIGNAL(timeout()),this,SLOT(showParameter()));
    xlength=work_time;
    work_time=0;
    flag0=0;
    length=0;
    //控件操作
    this->ui->start_test->setEnabled(true);
    this->ui->end_test->setEnabled(false);

    ui->chuankou_button->setEnabled(true);
    ui->stop_button->setEnabled(true);
    ui->bote_button->setEnabled(true);
    ui->jiou_button->setEnabled(true);
    ui->data_button->setEnabled(true);
  ui->actionOpen->setEnabled(true);
    serialPort->clear();
    serialPort->close();
    serialPort->deleteLater();
    disconnect(serialPort, &QSerialPort::readyRead, this, &MainWindow::readToHex);
}

//读取十六进制，读取协议信息
void MainWindow::readToHex()
{
    int receBytes=0;
    QByteArray temp = serialPort->readAll();
    //auto isShow = ui->reDisplay->isChecked();         //接收显示
    receBytes += temp.size();
    QString redata = QString("received:%1").arg(QString::number(receBytes));
    //ui->sendlabel->setText(redata);
    QDataStream out(&temp,QIODevice::ReadOnly);    //将字节数组读入
    while(!out.atEnd())
    {
        quint8 outChar = 0;
        out>>outChar;   //每字节填充一次，直到结束
        //获取从机协议
        if(flag0==0){
            //head
            if(flag_zhu==0&&outChar==head){
                //qDebug()<<"outChar==104  "<<length;
                flag0=1;
                //write
                treaty[length++]=outChar;
            }
        }
        else if(flag0==1&&flag_zhu==0){
            //tail、length、solve
            treaty[length++]=outChar;
            if(outChar==tail&&length==16){
                flag0=0;
                solve(length);
                length=0;
            }
        }

        //获取主机协议
        if(flag_zhu==0){
            //head
            if(flag0==0&&outChar==head1){
                //qDebug()<<"outChar==104  "<<length;
                flag_zhu=1;
                //write
                treaty1[length1++]=outChar;
            }
        }
        else if(flag0==0&&flag_zhu==1){
            //tail、length、solve
            treaty1[length1++]=outChar;
            if(outChar==tail1&&length1==17){
                flag_zhu=0;
                solve1(length1);
                length1=0;
            }
        }

    }
}
//处理从机协议
bool MainWindow::solve(int length){
    //当row==1501时，重新建新文件
    if(row%1501==1){
        row=1;
        //将第一行写入文件
        QStringList list;
        list <<"北京时间"<<ui->TIGBT_label->text()<<ui->RIGBT_label->text()<<ui->work_phase->text()
             <<ui->mode_label->text()<<ui->work_time->text()<<ui->top_hit_state->text()
             <<ui->m_hit_state->text()<<ui->R_hit_state->text()<<ui->b_hit_state->text()
             <<ui->TTAD->text()<<ui->treaty_label_2->text();
        xlsx::writeRow(xlsx, list, row++, 1);
        filename="从机数据"+QString::number(j++)+".xlsx";
         qDebug()<<filename;
        xlsx.saveAs(filename);
    }
    if(length!=16)
        return false;

    //保存整体协议
    str="";
    for(int i=0;i<length;i++){
        str=str+QString("%1").arg(treaty[i]&0xFF,2,16,QLatin1Char('0'));
    }

    //反压、过流、浪涌
    quint8 temp01;
    temp01=treaty[6]&0X38;
    if(temp01==0){
        fanya="无";//反压
        R_triangle_hit_state="无";//过流
        work_phase="无";//浪涌
    }else if(temp01==8){
        fanya="无";//反压
        R_triangle_hit_state="无";//过流
        work_phase="有";//浪涌
    }else if(temp01==16){
        fanya="无";//反压
        R_triangle_hit_state="有";//过流
        work_phase="无";//浪涌
    }else if(temp01==24){
        fanya="无";//反压
        R_triangle_hit_state="有";//过流
        work_phase="有";//浪涌
    }else if(temp01==32){
        fanya="有";//反压
        R_triangle_hit_state="无";//过流
        work_phase="无";//浪涌
    }else if(temp01==40){
        fanya="有";//反压
        R_triangle_hit_state="无";//过流
        work_phase="有";//浪涌
    }else if(temp01==48){
        fanya="有";//反压
        R_triangle_hit_state="有";//过流
        work_phase="无";//浪涌
    }else if(temp01==56){
        fanya="有";//反压
        R_triangle_hit_state="有";//过流
        work_phase="有";//浪涌
    }

    //步骤0-5
    quint8 temp02;
    temp02=treaty[2]&0XE0;
    if(temp02==0)
        mode="步骤0";
    else if(temp02==32)
        mode="步骤1";
    else if(temp02==64)
        mode="步骤2";
    else if(temp02==96)
        mode="步骤3";
    else if(temp02==128)
        mode="步骤4";
    else if(temp02==160)
        mode="步骤5";
    else
        mode="NULL";
    //qDebug()<<mode;

    Bottom_hit_state=QString("%1").arg(treaty[8]);//底部温度
    Top_hit_state=QString("%1").arg(treaty[9]);//顶部温度
    TIGBT=QString("%1").arg(treaty[11]);//IGBT1温度
    RIGBT=QString("%1").arg(treaty[10]);//IGBT2温度

    //蜂鸣
    quint8 temp03;
    temp03=treaty[7]&0X03;
    if(temp03==0)
        margin_hit_state="无蜂鸣";
    else if(temp03==1)
         margin_hit_state="有蜂鸣";

    ui->treaty_1->setText(str);//协议

    ui->TIGBT_->setText(TIGBT);//IGBT1温度
    ui->RIGBT_->setText(RIGBT);//IGBT2温度
    ui->mode_->setText(mode);//工作步骤
    ui->top_hit_->setText(Top_hit_state);//顶部温度
    ui->b_hit_->setText(Bottom_hit_state);//底部温度

    ui->TTAD_label->setText(fanya);//反压
    ui->R_hit_->setText(R_triangle_hit_state);//过流
    ui->work_phase_label->setText(work_phase);//浪涌
    ui->m_hit_->setText(margin_hit_state);//蜂鸣

    //将获取para写入xlsx
    QStringList list;
    //QString("%1").arg(TTT)将float转QString
    list <<time_china3<<QString("%1").arg(TIGBT)<<QString("%1").arg(RIGBT)<<work_phase<<mode
         <<QString("%1").arg(work_time)<<Top_hit_state<<margin_hit_state
         <<R_triangle_hit_state<<Bottom_hit_state<<fanya<<str;
    xlsx::writeRow(xlsx, list, row++, 1);
    xlsx.saveAs(filename);
    return true;
}


//处理主机协议
bool MainWindow::solve1(int length1){

    if(row1%1501==1){
        row1=1;
        //将第一行写入文件
        QStringList list;
        list <<"北京时间"<<ui->work_time_2->text()<<ui->mode_label_2->text()<<ui->top_hit_state_2->text()
             <<ui->RIGBT_label_2->text()<<ui->TIGBT_label_2->text()<<ui->TTAD_2->text()
             <<ui->b_hit_state_2->text()<<ui->R_hit_state_2->text()<<ui->work_phase_2->text()
             <<ui->m_hit_state_2->text()<<"协议";
        xlsx::writeRow(xlsx1, list, row1++, 1);
        filename1="主机数据"+QString::number(k++)+".xlsx";
         qDebug()<<filename1;
        xlsx1.saveAs(filename1);
    }

    if(length1!=17)
        return false;

    //保存整体协议
    str1="";
    for(int i=0;i<length1;i++){
        str1=str1+QString("%1").arg(treaty1[i]&0xFF,2,16,QLatin1Char('0'));
    }
    ui->treaty_2->setText(str1);//1

    quint8 temp01;
    temp01=treaty1[2]&0X0F;
    if(temp01==0)
        state="待机";  //state
    else if(temp01==1)
        state="功能选择";
    else if(temp01==2)
        state="口感选择";
    else if(temp01==3)
        state="米种选择";
    else if(temp01==4)
        state="定时设置";
    else if(temp01==5)
        state="预约设置";
    else if(temp01==6)
        state="预约中";
    else if(temp01==7)
        state="烹饪中";
    else if(temp01==8)
        state="保温";
    else if(temp01==9)
        state="快测";
    else if(temp01==10)
        state="自检";
    else if(temp01==11)
        state="保护";
    else
        state="NULL";

    ui->state_1->setText(state);//2

    quint8 temp02;
    temp02=treaty1[3]&0X1F;
    if(temp02==1)
        type="标准煮";
    else if(temp02==2)
        type="精煮饭";
    else if(temp02==3)
        type="快煮饭";
    else if(temp02==4)
        type="煮粥";
    else if(temp02==5)
        type="稀饭";
    else if(temp02==6)
        type="煲汤";
    else if(temp02==7)
        type="热饭";
    else if(temp02==8)
        type="杂粮粥";
    else if(temp02==9)
        type="锅巴饭";
    else if(temp02==10)
        type="蒸煮";
    else if(temp02==11)
        type="蛋糕";
    else if(temp02==12)
        type="酸奶";
    else if(temp02==13)
        type="发芽饭";
    else if(temp02==14)
        type="婴儿粥";
    else if(temp02==15)
        type="煲仔饭";
    else if(temp02==16)
        type="杂粮饭";
    else if(temp02==17)
        type="快煮粥";
    else
        type="NULL";
    ui->type_1->setText(type);//3

    quint8 temp03;
    temp03=treaty1[10]&0X0F;
    if(temp03==15){
        top="加热";//top
        C="加热";//C
        R="加热";//R
        B="加热";//B
    }else if(temp03==14){
        top="加热";
        C="加热";
        R="加热";
        B="不加热";
    }else if(temp03==13){
        top="加热";
        C="加热";
        R="不加热";
        B="加热";
    }else if(temp03==12){
        top="加热";
        C="加热";
        R="不加热";
        B="不加热";
    }else if(temp03==11){
        top="加热";
        C="不加热";
        R="加热";
        B="加热";
    }else if(temp03==10){
        top="加热";
        C="不加热";
        R="加热";
        Bottom_hit_state="不加热";
    }else if(temp03==9){
        top="加热";
        C="不加热";
        R="不加热";
        B="加热";
    }else if(temp03==8){
        top="加热";
        C="不加热";
        R="不加热";
        B="不加热";
    }else if(temp03==7){
        top="不加热";
        C="加热";
        R="加热";
        B="加热";
    }else if(temp03==6){
        top="不加热";
        C="加热";
        R="加热";
        B="不加热";
    }else if(temp03==5){
        top="不加热";
        C="加热";
        R="不加热";
        B="加热";
    }else if(temp03==4){
        top="不加热";
        C="加热";
        R="不加热";
        B="不加热";
    }else if(temp03==3){
        top="不加热";
        C="不加热";
        R="加热";
        B="加热";
    }else if(temp03==2){
        top="不加热";
        C="不加热";
        R="加热";
        B="不加热";
    }else if(temp03==1){
        top="不加热";
        C="不加热";
        R="不加热";
        B="加热";
    }else if(temp03==0){
        top="不加热";
        C="不加热";
        R="不加热";
        B="不加热";
    }
    ui->top_1->setText(top); //top 4
    ui->C_1->setText(C);//C 5
    ui->R_1->setText(R);//R 6
    ui->B_1->setText(B);//B 7


    RI=QString("%1").arg(treaty1[14]&0xFF,2,16,QLatin1Char('0'));//RI
    BI=QString("%1").arg(treaty1[13]&0xFF,2,16,QLatin1Char('0'));//BI
    ui->BI_1->setText(BI);//8
    ui->RI_1->setText(RI);//9

    //写入表格
    //将获取para写入xlsx
    QStringList list;
    //QString("%1").arg(TTT)将float转QString
    list <<time_china3<<QString("%1").arg(work_time)<<type<<top<<RI
         <<BI<<T<<B
         <<R<<state<<C<<str1;
    xlsx::writeRow(xlsx1, list, row1++, 1);
    xlsx1.saveAs(filename1);
    return true;

}


//鼠标双击特效
void MainWindow::mouseDoubleClickEvent(QMouseEvent *event)
{

    //判断是否为鼠标左键双击
    if(event->button() == Qt::LeftButton)
    {
        QLabel * label = new QLabel(this);
        QMovie * movie = new QMovie(":/new/prefix1/picture/mouse_clicked.gif");//加载gif图片
        //设置label自动适应gif的大小
        label->setScaledContents(true);

        label->setMovie(movie);
        //这里为了调用move方便，进行resize，需要知道的是gif的大小本来也就是150*150
        label->resize(180,180);
        label->setStyleSheet("background-color:rgba(0,0,0,0);");
        //设置鼠标穿透
        label->setAttribute(Qt::WA_TransparentForMouseEvents, true);
        //让label的中心在当前鼠标双击位置
        label->move(event->pos().x()-label->width()/2,event->pos().y()-label->height()/2);
        //开始播放gif
        movie->start();

        label->show();

        //绑定QMovie的信号，判断gif播放次数
        connect(movie, &QMovie::frameChanged, [=](int frameNumber) {
            if (frameNumber == movie->frameCount() - 1)//gif播放次数为1，关闭标签
                label->close();
        });
    }
}


//查询功能的实现
void MainWindow::on_actionSearch_triggered()
{
    FindXlsx  *findxlsx=new FindXlsx;
    findxlsx->show();
}

//初始化图
void MainWindow::initchart(){
    axisx=new QValueAxis;
    axisy=new QValueAxis;
    axisx->setTitleText("时间/s");
    axisy->setTitleText("温度/°C");
    chart = new QChart();
    chart->addAxis(axisx, Qt::AlignBottom);
    chart->addAxis(axisy, Qt::AlignLeft);
    chart->setTitle("温度图");
}

//添加线
void MainWindow::putline(QLineSeries *series){
    chart->addSeries(series);
    series->attachAxis(axisx);
    series->attachAxis(axisy);
}

//显示图
void MainWindow::showchart(int xrange, int yrangestart, int yrangeend){
    axisx->setRange(0, xrange);
    if(yrangestart==yrangeend){
        yrangestart--;
        yrangeend++;
    }
    axisy->setRange(yrangestart, yrangeend);
    QWidget* widget=new QWidget;
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    QGridLayout* layout=new QGridLayout;
    layout->addWidget(chartView);
    widget->setLayout(layout);
    widget->resize(800, 600);
    widget->show();
}

int MainWindow::min(int a[], int n){
    int min=a[0];
    for (int i = 1; i < n; i++) {
        if(a[i] < min) min=a[i];
    }
    return min;
}

int MainWindow::max(int a[], int n){
    int max=a[0];
    for (int i = 1; i < n; i++) {
        if(a[i] > max) max=a[i];
    }
    return max;
}

void MainWindow::on_actionOpen_triggered()
{
    showchart(xlength, tmin, tmax);
}


void MainWindow::on_data_button_2_activated(int index)
{
    if(ui->data_button_2->font().toString()=="4013"){
        ui->bote_button->setFont("4028");
    }
}

