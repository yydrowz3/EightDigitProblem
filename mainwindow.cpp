#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->resetButton, &QPushButton::clicked, [=](){  //重置按钮
        ui->start0->clear();
        ui->start1->clear();
        ui->start2->clear();
        ui->start3->clear();
        ui->start4->clear();
        ui->start5->clear();
        ui->start6->clear();
        ui->start7->clear();
        ui->start8->clear();
        ui->end0->clear();
        ui->end1->clear();
        ui->end2->clear();
        ui->end3->clear();
        ui->end4->clear();
        ui->end5->clear();
        ui->end6->clear();
        ui->end7->clear();
        ui->end8->clear();
        ui->output0->setText("-");
        ui->output1->setText("-");
        ui->output2->setText("-");
        ui->output3->setText("-");
        ui->output4->setText("-");
        ui->output5->setText("-");
        ui->output6->setText("-");
        ui->output7->setText("-");
        ui->output8->setText("-");
        ui->searchTimeCnt->setText("-");
        ui->costStepCnt->setText("-");
    });

    connect(ui->startButton, &QPushButton::clicked, [=](){  //开始按钮
        fillArray();    //将输入框中的数据填入数组
        if(!validCheck())   //判断输入的内容是否合理
            QMessageBox::warning(this, "错误", "请按正确形式输入数字0-8(0代表空格)");
        else
        {
            eightDigit *Problem = new eightDigit();
            Problem->init(this->startState, this->endState);    //初始化
            if(!Problem->inversionJudge())  //通过逆序数判断是否有解
                QMessageBox::information(this, "提示", "该种情况无解(起始状态与目标状态逆序数奇偶性不同)");
            else
            {
                if(ui->algorithmSelect->currentIndex() == 0)    //通过选择框中的内容使用对应的算法
                    Problem->AStarSearch();
                else if(ui->algorithmSelect->currentIndex() == 1)
                    Problem->BFSSearch();
                printResult(Problem);
            }

            delete Problem;
        }
    });


}


int MainWindow::numberConvert(QString str)  //将输入框的字符转换为数字
{
    int value = 0;
    string temp = str.toStdString();
    for(auto ch : temp)
    {
        if(ch < '0' || ch > '9')
            return -1;
        else
            value = value * 10 + ch - '0';
    }

    return value;
}

void MainWindow::fillArray()    //数组填充
{
    this->startState[0] = numberConvert(ui->start0->text());
    this->startState[1] = numberConvert(ui->start1->text());
    this->startState[2] = numberConvert(ui->start2->text());
    this->startState[3] = numberConvert(ui->start3->text());
    this->startState[4] = numberConvert(ui->start4->text());
    this->startState[5] = numberConvert(ui->start5->text());
    this->startState[6] = numberConvert(ui->start6->text());
    this->startState[7] = numberConvert(ui->start7->text());
    this->startState[8] = numberConvert(ui->start8->text());

    this->endState[0] = numberConvert(ui->end0->text());
    this->endState[1] = numberConvert(ui->end1->text());
    this->endState[2] = numberConvert(ui->end2->text());
    this->endState[3] = numberConvert(ui->end3->text());
    this->endState[4] = numberConvert(ui->end4->text());
    this->endState[5] = numberConvert(ui->end5->text());
    this->endState[6] = numberConvert(ui->end6->text());
    this->endState[7] = numberConvert(ui->end7->text());
    this->endState[8] = numberConvert(ui->end8->text());
}


bool MainWindow::validCheck()   //检查数组来判断输入的内容是否有误
{
    int hashTableStart[LIMIT] = {0};
    for(int i = 0; i < LIMIT; i++)
    {
        if(startState[i] < 0 || startState[i] > 8)
            return false;
        hashTableStart[startState[i]]++;
    }
    for(int i = 0; i < LIMIT; i++)
        if(hashTableStart[i] != 1)
            return false;

    int hashTableEnd[LIMIT] = {0};
    for(int i = 0; i < LIMIT; i++)
    {
        if(endState[i] < 0 || endState[i] > 8)
            return false;
        hashTableEnd[endState[i]]++;
    }
    for(int i = 0; i < LIMIT; i++)
        if(hashTableEnd[i] != 1)
            return false;

    return true;
}

void MainWindow::printResult(eightDigit *P) //结果输出
{
    ui->searchTimeCnt->setText(QString::number(P->searchedTimeCount));  //输出搜索次数
    ui->costStepCnt->setText(QString::number(P->Path.size() - 1));  //输出结果步数
    bool flag = true;
    connect(ui->startButton, &QPushButton::clicked, [&flag](bool)mutable{flag = false;});
    connect(ui->resetButton, &QPushButton::clicked, [&flag](bool)mutable{flag = false;});
    while(!P->Path.empty())
    {
        Node temp = P->Path.top();
        ui->output0->setText(QString::number(temp.state[0]));
        ui->output1->setText(QString::number(temp.state[1]));
        ui->output2->setText(QString::number(temp.state[2]));
        ui->output3->setText(QString::number(temp.state[3]));
        ui->output4->setText(QString::number(temp.state[4]));
        ui->output5->setText(QString::number(temp.state[5]));
        ui->output6->setText(QString::number(temp.state[6]));
        ui->output7->setText(QString::number(temp.state[7]));
        ui->output8->setText(QString::number(temp.state[8]));

        QTime reachTime = QTime::currentTime().addMSecs(1000);  //设置延迟,便于结果的演示
        while(QTime::currentTime() < reachTime)
        {
            if(flag == false)
                break;
            QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
        }
        P->Path.pop();
        if(flag == false)
            break;
    }

}



MainWindow::~MainWindow()
{
    delete ui;
}


