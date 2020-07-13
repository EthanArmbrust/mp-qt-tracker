#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "primehook.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


public slots:
    void update_data();
    void onRetryClicked();

private:
    Ui::MainWindow *ui;
    PrimeHook *ph;
    void setGridImage(int i, int j, QString res);
};
#endif // MAINWINDOW_H
