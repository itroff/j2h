#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QTextStream>
#include "page.h"

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

void MainWindow::on_pushButton_clicked()
{
   // QFileDialog dialog(this);
  //  dialog.setFileMode(QFileDialog::AnyFile);
   // dialog.show();
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                    "/home",
                                                    tr("JSON (*.json)"));

    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly)) {
  //      QMessageBox::information(0, "error", file.errorString());
    }

    QTextStream in(&file);
    QByteArray ar;
    while(!in.atEnd()) {
        QString line = in.readLine();
        ar +=line;
    }

    file.close();
    Page pg;
    QString page;
    try{
        page = pg.transform(ar);
    }
    catch(conv_error &err){
        ui->label->setText(err.msg());

    }
    QFile fileW("/home/itr/html.html" );
    if ( fileW.open(QIODevice::ReadWrite) )
    {
        QTextStream stream( &fileW );
        stream << page << endl;
    }
    fileW.close();

}
