#ifndef CONNECTIONWINDOW_HH
#define CONNECTIONWINDOW_HH

#include <QDebug>
#include <QDialog>
#include "ui_ConnectionWindow.h"

class ConnectionWindow : public QDialog
{
	Q_OBJECT
    public:
	explicit ConnectionWindow(QWidget *parent = 0);

    signals:
	void	connectClick(const std::string &ip, uint16_t port, const std::string &name, const std::string &pass);
	void	registerClick(const std::string &ip, uint16_t port, const std::string &name, const std::string &pass);

    private slots:
	void on_CancelBtn_clicked();
	void on_ConnectBtn_clicked();
	void on_RegisterBtn_clicked();
	void reject();

    private:
	Ui::ConnectDialog ui;
};

#endif // CONNECTIONWINDOW_HH
