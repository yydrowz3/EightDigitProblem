#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QTime>
#include "eightdigit.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    int startState[LIMIT] = {0}, endState[LIMIT] = {0}; //保存输入的状态

    int numberConvert(QString str); //将输入框中的内容转换为数字
    void fillArray();   //将转换的数字保存到类中的数组中
    bool validCheck();  //检查输入是否合理
    void printResult(eightDigit *P);    //输出结果

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
