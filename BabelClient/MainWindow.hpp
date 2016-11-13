#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include "QCloseEvent"
#include "QtWidgets/QMainWindow"
#include "QInputDialog"
#include "QStandardItemModel"
#include "ui_MainWindow.h"
#include "IGuiCallBack.hpp"
#include "ConnectionWindow.hpp"
#include "ContactLabel.hpp"
#include "CallWindow.hpp"

#include "QIcon"
#include "QStyledItemDelegate"

class MainWindow : public QMainWindow
{
	Q_OBJECT
    public:
	explicit MainWindow(QWidget *parent = 0);

	void	contactStatus(const std::string &name, int status);
	void	setCallback(IGuiCallBack *cb);
	void	closeEvent(QCloseEvent *event);

    private slots:
	void	on_ConnectBtn_clicked();
	void	on_AddContactBtn_clicked();

	void	on_CallBtn_clicked();
	void	on_DeleteBtn_clicked();

	void	on_DirectCallBtn_clicked();

	void	directConnect(const std::string &ip, int port);
	void	directConnectStop();

	void	connectClick(const std::string &ip, uint16_t port, const std::string &name, const std::string &pass);
	void	registerClick(const std::string &ip, uint16_t port, const std::string &name, const std::string &pass);

    private:
	IGuiCallBack	    *mCb;
	ConnectionWindow    mConWin;
	Ui::MainWindow	    ui;
	QStandardItemModel  mModel;
	ContactLabel	    mDelegate;
	QIcon		    mConnectedIco;
	QIcon		    mDeconnectedIco;
	CallWindow	    mCallWin;
};

#endif // MAINWINDOW_HPP
