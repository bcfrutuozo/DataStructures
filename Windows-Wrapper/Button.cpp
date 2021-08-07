#include "Button.h"

// Singleton WndClass
Button::ButtonClass Button::ButtonClass::m_ButtonClass;

// Window class declarations
Button::ButtonClass::ButtonClass() noexcept
	:
	m_Instance(GetModuleHandle(nullptr))
{
	WNDCLASSEX wc = { 0 };
	wc.cbSize = sizeof(wc);
	wc.style = CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = HandleMessageSetup;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = GetInstance();
	wc.hCursor = nullptr;
	wc.hbrBackground = nullptr;
	wc.lpszMenuName = nullptr;
	wc.lpszClassName = GetName();
	RegisterClassEx(&wc);
}

Button::ButtonClass::~ButtonClass()
{
	UnregisterClass(m_ClassName, GetInstance());
}

const char* Button::ButtonClass::GetName() noexcept
{
	return m_ClassName;
}

HINSTANCE Button::ButtonClass::GetInstance() noexcept
{
	return m_ButtonClass.m_Instance;
}

void Button::OnPaint_Impl(HWND hwnd) noexcept
{
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(hwnd, &ps);
	RECT rc;
	GetClientRect(hwnd, &rc);

	//Create pen for button border
	HPEN pen;

	if (IsClicking())
	{
		pen = CreatePen(PS_INSIDEFRAME, FlatAppearance.BorderSize, RGB(FlatAppearance.BorderColor.GetR(), FlatAppearance.BorderColor.GetG(), FlatAppearance.BorderColor.GetB()));
		m_Brush = CreateSolidBrush(RGB(FlatAppearance.MouseDownBackColor.GetR(), FlatAppearance.MouseDownBackColor.GetG(), FlatAppearance.MouseDownBackColor.GetB()));
	}
	else if (IsMouseOver())
	{
		pen = CreatePen(PS_INSIDEFRAME, FlatAppearance.BorderSize, RGB(FlatAppearance.BorderColor.GetR(), FlatAppearance.BorderColor.GetG(), FlatAppearance.BorderColor.GetB()));
		m_Brush = CreateSolidBrush(RGB(FlatAppearance.MouseOverBackColor.GetR(), FlatAppearance.MouseOverBackColor.GetG(), FlatAppearance.MouseOverBackColor.GetB()));
	}
	else
	{
		pen = CreatePen(PS_INSIDEFRAME, FlatAppearance.BorderSize, RGB(FlatAppearance.BorderColor.GetR(), FlatAppearance.BorderColor.GetG(), FlatAppearance.BorderColor.GetB()));
		m_Brush = CreateSolidBrush(RGB(m_BackgroundColor.GetR(), m_BackgroundColor.GetG(), m_BackgroundColor.GetB()));
	}

	//Select our brush into hDC
	HGDIOBJ old_pen = SelectObject(hdc, pen);
	HGDIOBJ old_brush = SelectObject(hdc, m_Brush);

	// GOING TO THINK A WAY OF IMPLEMENT NORMAL AND ROUNDED BORDER BUTTON

	//If you want rounded button, then use this, otherwise use FillRect().

	//RoundRect(hdc, rc.left, rc.top, rc.right, rc.bottom, 10, 10);
	Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);
	//FillRect(hdc, &rc, m_Brush);

	//Clean up
	SelectObject(hdc, old_pen);
	SelectObject(hdc, old_brush);
	DeleteObject(pen);

	SetBkMode(hdc, TRANSPARENT);
	SetTextColor(hdc, m_ForeColor.ToRGB());
	DrawText(hdc, GetText().c_str(), -1, &rc, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	EndPaint(hwnd, &ps);
	// NEED TO IMPLEMENT A LARGE GRAPHICS CLASS TO HANDLE EVENTARGS TO THE USER.
	// IT'S PROBABLY GOING TO BE ONE OF THE LAST STEPS
	//Dispatch("OnPaint", new PaintEventArgs());
}

Button::Button(Control* parent, const std::string& name, int width, int height, int x, int y)
	:
	WinControl(parent, name, width, height, x, y)
{
	Initialize();
}

Button::~Button()
{

}

void Button::Initialize() noexcept
{
	// Create window and get its handle
	Handle = CreateWindow(
		ButtonClass::GetName(),																				// Class name
		Text.c_str(),																						// Window title
		WS_CHILD | WS_VISIBLE | WS_TABSTOP,																	// Style values
		Location.X,																							// X position
		Location.Y,																							// Y position
		Size.Width,																							// Width
		Size.Height,																						// Height
		static_cast<HWND>(Parent->Handle.ToPointer()),														// Parent handle
		NULL,						                														// Menu handle
		ButtonClass::GetInstance(),																			// Module instance handle
		this																								// Pointer to the button instance to work along with HandleMessageSetup function.
	);

	if (Handle.IsNull())
	{
		throw CTL_LAST_EXCEPT();
	}
}

void Button::Disable() noexcept
{

}

void Button::Enable() noexcept
{

}

void Button::Hide()
{
	if (IsShown())
	{
		IsVisible = false;
		ShowWindow(static_cast<HWND>(Handle.ToPointer()), SW_HIDE);
	}
}

void Button::Show()
{
	if (!IsShown())
	{
		IsVisible = true;
		ShowWindow(static_cast<HWND>(Handle.ToPointer()), SW_SHOWDEFAULT);
	}
}