#include "MainWindow.hpp"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), mCb(0), mConWin(0), mConnectedIco(":/connected.png"), mDeconnectedIco(":/deconnected.png")
{
    ui.setupUi(this);
    connect(&mConWin, SIGNAL(connectClick(const std::string &, uint16_t, const std::string &, const std::string &)),
	    this, SLOT(connectClick(const std::string &, uint16_t, const std::string &, const std::string &)));
    connect(&mConWin, SIGNAL(registerClick(const std::string &, uint16_t, const std::string &, const std::string &)),
	    this, SLOT(registerClick(const std::string &, uint16_t, const std::string &, const std::string &)));
    connect(&mCallWin, SIGNAL(rejected()),
	    this, SLOT(directConnectStop()));
    connect(&mCallWin, SIGNAL(callBtnPress(const std::string &, int)),
	    this, SLOT(directConnect(const std::string &, int)));

    ui.ContactList->setItemDelegate(new QStyledItemDelegate);
    ui.ContactList->setModel(&mModel);
    show();
    mConWin.show();
}

void MainWindow::contactStatus(const std::string &name, int status)
{
    QStandardItem *item;
    QList <QStandardItem *> ret = mModel.findItems(QString::fromStdString(name));

    if (ret.size())
	item = ret.at(0);
    else
	item = new QStandardItem();
    if (status)
	item->setData(mConnectedIco, Qt::DecorationRole);
    else
	item->setData(mDeconnectedIco, Qt::DecorationRole);
    item->setData(QString::fromStdString(name), Qt::DisplayRole);
    if (!ret.size())
	mModel.appendRow(item);
}

void MainWindow::setCallback(IGuiCallBack *cb)
{
    mCb = cb;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (mCb)
	mCb->closeCallback();
    event->accept();
}

void MainWindow::on_ConnectBtn_clicked()
{
    mConWin.show();
}

void MainWindow::on_AddContactBtn_clicked()
{
    bool    ok;

    QString ret = QInputDialog::getText(this, "Add Contact", "Contact name", QLineEdit::Normal, QString(), &ok);

    if (ok && mCb)
	mCb->addContactCallback(ret.toStdString());
}

void MainWindow::on_CallBtn_clicked()
{
    if (mCb)
	mCb->callContactCallback(ui.ContactList->selectionModel()->currentIndex().data(Qt::DisplayRole).toString().toStdString());
}

void MainWindow::on_DeleteBtn_clicked()
{
    if (mCb)
	mCb->delContactCallback(ui.ContactList->selectionModel()->currentIndex().data(Qt::DisplayRole).toString().toStdString());
}

void MainWindow::on_DirectCallBtn_clicked()
{
    if (mCb)
    {
	mCallWin.setPort(mCb->openDirectCall());
	mCallWin.show();
    }
}

void MainWindow::directConnect(const std::string &ip, int port)
{
    if (mCb)
	mCb->startDirectCall(ip, port);
}

void MainWindow::directConnectStop()
{
    if (mCb)
	mCb->stopDirectCall();
}

void MainWindow::connectClick(const std::string &ip, uint16_t port, const std::string &name, const std::string &pass)
{
    if (mCb)
	mCb->connectCallback(ip, port, name, pass);
}

void MainWindow::registerClick(const std::string &ip, uint16_t port, const std::string &name, const std::string &pass)
{
    if (mCb)
	mCb->registerCallback(ip, port, name, pass);
}
