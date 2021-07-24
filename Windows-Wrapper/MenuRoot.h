#pragma once

#include "Menu.h"

class MenuLeaf;
class MenuItem;

class MenuRoot : public Menu
{
protected:

	MenuRoot(Control* parent, unsigned int subitemIndex, int section);
	MenuRoot(Control* parent, const std::string& text, unsigned int subitemIndex, int section);
	virtual ~MenuRoot() = default;

public:

	MenuLeaf& AddMenu(const std::string& text);
	MenuItem& AddItem(const std::string& text, const std::string& iconPath = {});

	void Bind() noexcept override;
};

