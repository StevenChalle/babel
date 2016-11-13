#include "ConnectionWindow.hpp"

ConnectionWindow::ConnectionWindow(QWidget *parent) : QDialog(parent)
{
    ui.setupUi(this);
}

void ConnectionWindow::on_CancelBtn_clicked()
{
    hide();
}

void ConnectionWindow::on_ConnectBtn_clicked()
{
    emit connectClick(ui.IpInput->text().toStdString(), ui.PortInput->text().toInt(), ui.UserInput->text().toStdString(), ui.PassInput->text().toStdString());
    hide();
}

void ConnectionWindow::on_RegisterBtn_clicked()
{
    emit registerClick(ui.IpInput->text().toStdString(), ui.PortInput->text().toInt(), ui.UserInput->text().toStdString(), ui.PassInput->text().toStdString());
    accept();
    hide();
}

void ConnectionWindow::reject()
{
    hide();
}
