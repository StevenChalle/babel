#include "Gui.hpp"

Gui::Gui(int &ac, char **av) : mAp(0), mWin(0)
{
    if (QApplication::startingUp())
    {
	mAp = new QApplication(ac, av);
    }
    mWin = new MainWindow();
}

Gui::~Gui()
{
    delete mWin;
    if (mAp)
	delete mAp;
}

void Gui::contactStatus(const std::string &name, int status)
{
    mWin->contactStatus(name, status);
}

void Gui::update()
{
    if (mAp)
    {
	mAp->sendPostedEvents();
	mAp->processEvents();
    }
}

void Gui::setCallback(IGuiCallBack *cb)
{
    mWin->setCallback(cb);
    mCb = cb;
}

void Gui::notice(const std::string &msg)
{
    mWin->statusBar()->showMessage(QString::fromStdString(msg));
}
