#ifndef GUI_HH
#define GUI_HH

#include "IGui.hpp"
#include "QtCore"
#include "QApplication"
#include "MainWindow.hpp"

class Gui : public IGui
{
    public:
	Gui(int &ac, char **av);
	~Gui();

	void	contactStatus(const std::string &name, int status);
	void	update();
	void	setCallback(IGuiCallBack *cb);
	void	notice(const std::string &);
    private:
	QApplication	*mAp;
	MainWindow	*mWin;
	IGuiCallBack	*mCb;
};

#endif // GUI_HH
