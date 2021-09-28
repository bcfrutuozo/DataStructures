#pragma once

#include "Control.h"

class ScrollableControl;

class ScrollBar : public Control
{
	friend class ScrollableControl;

protected:

	ScrollableControl* Owner;
	size_t Scrolling;
	size_t MaximumValue;

	int OnEraseBackground_Impl(HWND hwnd, HDC hdc) override;
	void OnPaint_Impl(HWND hwnd) override;

	ScrollBar(ScrollableControl* parent, int width, int height, int x, int y);

public:

	virtual ~ScrollBar();

	void Initialize() override;
	size_t GetScrolling() const noexcept;

	void SetMaximumValue(size_t maxValue) noexcept;
};