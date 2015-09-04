#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <wtypes.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    static int OnDeviceConnect(HANDLE device, void* window);
    static int OnDeviceDisconnect(HANDLE device, void* window);

    int Init();
    int Uninit();
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
