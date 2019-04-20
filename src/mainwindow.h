#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "page.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pb_view_clicked();

    void on_pb_open_clicked();

private:
    Ui::MainWindow *ui;
    Page m_pg;
};

#endif // MAINWINDOW_H
