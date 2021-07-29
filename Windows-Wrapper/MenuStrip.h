#pragma once

#include "MenuRoot.h"
#include "IHidable.h"

class Window;

class MenuStrip : public MenuRoot, public IHidable
{
	friend class Window;

public:

	MenuStrip(Control* parent);
	virtual ~MenuStrip() = default;

	void Hide() noexcept override;
	void Show() noexcept override;
};