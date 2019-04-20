#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QTextStream>
#include <QDesktopServices>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->pb_view->setDisabled(true);
    ui->plainTextEdit->setReadOnly(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

/**
 * @brief MainWindow::on_pb_view_clicked Сохранение результата в файл и открытие в системном браузере
 */
void MainWindow::on_pb_view_clicked()
{
    QString path = QDir::currentPath()+ "/html.html";
    QFile fileW(path);
    if ( fileW.open(QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text) )
    {
        QTextStream stream( &fileW );
        stream << m_pg.getText() << endl;
    }
    fileW.close();
    QDesktopServices::openUrl (path);
}

/**
 * @brief MainWindow::on_pb_open_clicked Выбор, открытие, передача в либу исходного json и отображение
 */
void MainWindow::on_pb_open_clicked()
{

    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                    QDir::currentPath(),
                                                    tr("JSON (*.json)"));

    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly)) {
        ui->plainTextEdit->setPlainText("Ошибка открытия файла");
        ui->pb_view->setDisabled(true);
        return;
    }

    QTextStream in(&file);
    QByteArray ar;
    while(!in.atEnd()) {
        QString line = in.readLine();
        ar +=line;
    }

    file.close();

    try{
        QString page = m_pg.transform(ar);
        ui->plainTextEdit->setPlainText(page);
        ui->pb_view->setDisabled(false);

    }
    // если произошла ошибка в процессе обработки - выводим ее
    catch(conv_error &err){
        ui->plainTextEdit->setPlainText(err.msg());
        ui->pb_view->setDisabled(true);

    }
}
