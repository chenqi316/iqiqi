#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "iTunesHelper/ConnectHelper.h"
#include "QMessageBox"
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

int MainWindow::OnDeviceConnect(HANDLE device, void* user_data)
{
    int result = FALSE;
    int ret_code = 0;

    MainWindow* window = (MainWindow*)user_data;

    PROCESS_ERROR(device);
    PROCESS_ERROR(window);
    ret_code = ConnectHelper::DeviceOpen(device);
    PROCESS_ERROR(ret_code);

    DeviceProperty info;
    ConnectHelper::GetDeviceInformation(device, &info);

    {
        setlocale(LC_ALL,"chs");

        QString name = QString::fromWCharArray(info.Name);
        window->ui->label_name->setText(name);

        QString type = QString::fromWCharArray(info.ProductType);
        window->ui->label_type->setText(type);

        QString sn = QString::fromWCharArray(info.SerialNumber);
        window->ui->label_sn->setText(sn);

        QString uuid = QString::fromWCharArray(info.IdentifyNumber);
        window->ui->label_uuid->setText(uuid);
    }

    result = TRUE;
Exit0:
    return result;
}

int MainWindow::OnDeviceDisconnect(HANDLE device, void* user_data)
{
    MainWindow* window = (MainWindow*)user_data;
    PROCESS_ERROR(window);

    ConnectHelper::DeviceClose(device);

    window->ui->label_name->setText("等待连接");
    window->ui->label_type->setText("等待连接");
    window->ui->label_sn->setText("等待连接");
    window->ui->label_uuid->setText("等待连接");

Exit0:
    return 1;
}

int MainWindow::Init()
{
    int ret_code = 0;
    ret_code = ConnectHelper::InitAPI();
    PROCESS_ERROR(ret_code);

    ui->label_name->setText("等待连接");
    ui->label_type->setText("等待连接");
    ui->label_sn->setText("等待连接");
    ui->label_uuid->setText("等待连接");

    ConnectHelper::RegisterOnConnectListener(MainWindow::OnDeviceConnect, this);
    ConnectHelper::RegisterOnDisConnectListener(MainWindow::OnDeviceDisconnect, this);

    ConnectHelper::StartListen();

Exit0:
    return 1;
}



int MainWindow::Uninit()
{
    return 1;
}
