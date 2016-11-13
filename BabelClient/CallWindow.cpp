#include "CallWindow.hpp"

CallWindow::CallWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CallWindow)
{
    ui->setupUi(this);
}

CallWindow::~CallWindow()
{
    delete ui;
}

void CallWindow::setPort(int port)
{
    ui->PortLabel->setText(QString::number(port));
}

void CallWindow::on_CallBtn_clicked()
{
    emit callBtnPress(ui->IpInput->text().toStdString(), ui->PortInput->text().toInt());
}
