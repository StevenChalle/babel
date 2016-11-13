#ifndef IGUI_HPP
#define IGUI_HPP

#include <vector>
#include "ContactData.h"
#include "IGuiCallBack.hpp"

class IGui
{
    public:
	virtual ~IGui() {}
	virtual void	contactStatus(const std::string &name, int status) = 0;
	virtual void	update() = 0;
	virtual void	setCallback(IGuiCallBack *) = 0;
	virtual void	notice(const std::string &) = 0;
};

#endif // IGUI_HPP
