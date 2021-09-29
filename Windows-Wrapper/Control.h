#pragma once

#include "WinAPI.h"
#include "Color.h"
#include "Point.h"
#include "Size.h"
#include "Padding.h"
#include "EventHandler.h"
#include "KeyEventHandler.h"
#include "KeyPressEventHandler.h"
#include "MouseEventHandler.h"
#include "KeyEventArgs.h"
#include "MouseEventArgs.h"
#include "KeyPressEventArgs.h"
#include "CancelEventArgs.h"
#include "OnClosedEventArgs.h"
#include "OnClosingEventArgs.h"
#include "ControlException.h"

#include <list>
#include <memory>
#include <functional>

class Control : public WinAPI
{
	friend class Window;
	friend class Button;
	friend class ToolStrip;
	friend class TextBox;
	friend class ListBox;

private:

	// Tabulation fields
	int m_TabIndex;
	static int m_IncrementalTabIndex;
	std::string Name;

	// Variable to check if control is tab selected
	bool m_IsTabSelected;

	bool m_IsVisible;

	void OnFocusEnter_Impl(HWND hwnd, HWND hwndOldFocus) override;
	void OnFocusLeave_Impl(HWND hwnd, HWND hwndNewFocus) override;
	void OnKeyDown_Impl(HWND hwnd, unsigned int vk, int cRepeat, unsigned int flags) override;
	void OnMouseLeftDown_Impl(HWND hwnd, int x, int y, unsigned int keyFlags) override;
	void OnNextDialogControl_Impl(HWND hwnd, HWND hwndSetFocus, bool fNext) override;

	EventHandler* OnActivate;
	EventHandler* OnClick;
	EventHandler* OnDeactivate;
	EventHandler* OnGotFocus;
	EventHandler* OnLostFocus;
	KeyEventHandler* OnKeyDown;
	KeyPressEventHandler* OnKeyPress;
	KeyEventHandler* OnKeyUp;
	MouseEventHandler* OnMouseClick;
	MouseEventHandler* OnMouseDown;
	EventHandler* OnMouseEnter;
	EventHandler* OnMouseHover;
	EventHandler* OnMouseLeave;
	MouseEventHandler* OnMouseLeftDoubleClick;
	MouseEventHandler* OnMouseMove;
	MouseEventHandler* OnMouseRightDoubleClick;
	MouseEventHandler* OnMouseUp;
	MouseEventHandler* OnMouseWheel;
	EventHandler* OnVisibleChanged;

protected:

	Point m_Location;
	Control* Parent;
	std::string Text;
	Size m_Size;
	Color m_ForeColor;
	Color m_BackgroundColor;
	Padding m_Margin;
	Padding m_Padding;
	Font m_Font;
	unsigned int m_MinSize;

	// Forces the implementation and call on individual childs because each WinApi control
	// has it own creation method.
	// ALL DERIVED CLASSES MUST CALL THIS METHOD ON ITS CONSTRUCTOR
	virtual void Initialize() = 0;

	template<typename T, typename... Args>
	T* Create(Args... a)
	{
		T* item = new T(a...);
		Controls.push_back(item);
		return item;
	}

	Control() noexcept;
	Control(Control* parent, const std::string& text) noexcept;
	Control(Control* parent, const std::string& text, int width, int height, int x, int y) noexcept;
	Control(const std::string& text) noexcept;
	Control(const std::string& text, int width, int height, int x, int y) noexcept;
	Control(const Control&) = default;														// Copy constructor
	Control(Control&&) = default;															// Move constructor
	Control& operator=(const Control&) = default;											// Copy assignment constructor
	Control& operator=(Control&&) = default;												// Move assignment constructor

public:

	std::list<Control*> Controls;

	virtual ~Control() noexcept(false);																		// Destructor

	void Dispose() override;

	void OnActivateSet(const std::function<void(Object*, EventArgs*)>& callback) noexcept;
	void OnClickSet(const std::function<void(Object*, EventArgs*)>& callback) noexcept;
	void OnDeactivateSet(const std::function<void(Object*, EventArgs*)>& callback) noexcept;
	void OnGotFocusSet(const std::function<void(Object*, EventArgs*)>& callback) noexcept;
	void OnLostFocusSet(const std::function<void(Object*, EventArgs*)>& callback) noexcept;
	void OnKeyDownSet(const std::function<void(Object*, KeyEventArgs*) >& callback) noexcept;
	void OnKeyPressSet(const std::function<void(Object*, KeyPressEventArgs*) >& callback) noexcept;
	void OnKeyUpSet(const std::function<void(Object*, KeyEventArgs*) >& callback) noexcept;
	void OnMouseClickSet(const std::function<void(Object*, MouseEventArgs*)>& callback) noexcept;
	void OnMouseDownSet(const std::function<void(Object*, MouseEventArgs*)>& callback) noexcept;
	void OnMouseEnterSet(const std::function<void(Object*, EventArgs*)>& callback) noexcept;
	void OnMouseHoverSet(const std::function<void(Object*, EventArgs*)>& callback) noexcept;
	void OnMouseLeaveSet(const std::function<void(Object*, EventArgs*)>& callback) noexcept;
	void OnMouseLeftDoubleClickSet(const std::function<void(Object*, MouseEventArgs*)>& callback) noexcept;
	void OnMouseMoveSet(const std::function<void(Object*, MouseEventArgs*)>& callback) noexcept;
	void OnMouseRightDoubleClickSet(const std::function<void(Object*, MouseEventArgs*)>& callback) noexcept;
	void OnMouseUpSet(const std::function<void(Object*, MouseEventArgs*)>& callback) noexcept;
	void OnMouseWheelSet(const std::function<void(Object*, MouseEventArgs*)>& callback) noexcept;
	void OnVisibleChangedSet(const std::function<void(Object*, EventArgs*)>& callback) noexcept;

	bool HasChildren() const noexcept;
	Size CalculateSizeByFont() noexcept;
	bool IsEnabled() const noexcept override;
	Window* GetWindow() noexcept;
	Size GetSize() const noexcept;
	void Resize(Size s) noexcept;
	void Resize(int width, int height) noexcept;
	Padding GetMargin() const noexcept;
	Control* GetByTabIndex(const int& index) noexcept;
	Color GetForeColor() const noexcept;
	void SetForeColor(const Color& color) noexcept;
	Color GetBackgroundColor() const noexcept;
	void SetBackgroundColor(const Color& color) noexcept;
	const std::string& GetText() const noexcept;
	void SetText(const std::string& text) noexcept;
	Control* GetPreviousControl() noexcept;
	Control* GetNextControl() noexcept;
	Control* GetById(unsigned int id) noexcept;
	Control* GetByHandle(const IntPtr p) noexcept;
	int GetTabIndex() const noexcept;
	void SetTabIndex(const int& index) noexcept;
	Font GetFont() const noexcept;
	void SetFont(Font font) noexcept;
	Point GetLocation() const noexcept;
	void SetLocation(Point p) noexcept;
	void SetLocation(int x, int y) noexcept;
	bool IsShown() const noexcept;
	virtual void Hide();
	virtual void Show();
};