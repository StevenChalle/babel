#ifndef CALLWINDOW_HPP
#define CALLWINDOW_HPP

#include <QDialog>
#include "ui_CallWindow.h"

class CallWindow : public QDialog
{
	Q_OBJECT

    public:
	explicit CallWindow(QWidget *parent = 0);
	~CallWindow();

	void	setPort(int port);

    signals:
	void	callBtnPress(const std::string &ip, int port);

    private slots:
	void	on_CallBtn_clicked();

    private:
	Ui::CallWindow *ui;
};

#endif // CALLWINDOW_HPP
