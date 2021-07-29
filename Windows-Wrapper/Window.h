#pragma once

#include "Control.h"
#include "Color.h"
#include "Exception.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "MenuStrip.h"

#include <memory>
#include <vector>
#include <optional>
#include <string>

// Error exception helper macro
#define WND_EXCEPT( hr ) Window::HRException( __LINE__,__FILE__,(hr) )
#define WND_LAST_EXCEPT() Window::HRException( __LINE__,__FILE__,GetLastError() )

class Menu;

class Window : public Control, public IHidable
{
	friend class Menu;

private:

	bool m_IsCursorEnabled;
	bool m_IsMenuStripEnabled;
	std::unique_ptr<Keyboard> m_Keyboard;
	std::unique_ptr<Mouse> m_Mouse;
	std::vector<BYTE> m_RawBuffer;

	// Set default as white
	Color m_ForeColor = Color::White();

	// Singleton manages registration/cleanup of window class
	class WndClass
	{
	private:

		static constexpr const char* m_ClassName = "Window Class";
		static WndClass m_WndClass;
		HINSTANCE m_Instance;

		WndClass() noexcept;
		~WndClass() noexcept;
		WndClass(const WndClass&) = delete;
		WndClass& operator=(const WndClass&) = delete;

	public:

		static const char* GetName() noexcept;
		static HINSTANCE GetInstance() noexcept;
	};

	void EncloseCursor() const noexcept;
	static void FreeCursor() noexcept;
	static void HideCursor() noexcept;
	static void ShowCursor() noexcept;
	static LRESULT WINAPI HandleMessageSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
	static LRESULT WINAPI HandleMessageForwarder(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
	LRESULT WINAPI HandleMessage(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;

	// Events implementations
	void OnActivate_Impl(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
	void OnCommand_Impl(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
	void OnClose_Impl(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
	void OnClosing_Impl(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
	void OnClosed_Impl(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
	void OnFocusEnter_Impl(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
	void OnFocusLeave_Impl(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
	void OnKeyDown_Impl(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
	void OnKeyPressed_Impl(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
	void OnKeyUp_Impl(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
	void OnMouseMove_Impl(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
	void OnMouseLeftDown_Impl(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
	void OnMouseLeftUp_Impl(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
	void OnMouseRightDown_Impl(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
	void OnMouseRightUp_Impl(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
	void OnMouseLeftDoubleClick_Impl(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
	void OnMouseRightDoubleClick_Impl(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
	void OnMouseWheel_Impl(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
	void OnNotify_Impl(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
	void OnRawInput_Impl(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;

protected:

	void Initialize() noexcept override;

	virtual void OnCreate()
	{

	}

	virtual void OnActivation() const
	{
		if (m_IsCursorEnabled)
		{
			EncloseCursor();
			HideCursor();
		}
	};

	virtual void OnDeactivation() const
	{
		if (m_IsCursorEnabled)
		{
			FreeCursor();
			ShowCursor();
		}
	};

	virtual void OnClose() const {};

	virtual void OnClosed() const {};

	virtual void OnClosing() const {};

	virtual void OnDestroy() const {};

	virtual void OnFocusEnter() const {};

	virtual void OnFocusLeave() const {};

	virtual void OnKeyDown() const {};

	virtual void OnKeyPressed() const {};

	virtual void OnKeyUp() const {};

	virtual void OnMouseMove() const {};

	virtual void OnMouseLeftDown() const {};

	virtual void OnMouseLeftUp() const {};

	virtual void OnMouseRightDown() const {};

	virtual void OnMouseRightUp() const {};

	virtual void OnMouseLeftDoubleClick() const {};

	virtual void OnMouseRightDoubleClick() const {};

	virtual void OnMouseWheel() const {};

	virtual void OnNotify() const {};

	virtual void OnPaint() const {};

	virtual void OnResize() const {};

public:

	Window(const std::string& name, int width, int height);
	virtual ~Window();
	Window(const Window&) = delete;
	Window& operator=(const Window&) = delete;

	void Hide() override;
	void Show() override;

	// MenuStrip functions
	void ClearMenuStrip() noexcept;
	void UpdateMenuStrip() noexcept;
	MenuStrip& GetMenuStrip() noexcept;

	void SetText(const std::string& text);
	void EnableCursor() noexcept;
	void DisableCursor() noexcept;
	Color GetForeColor() noexcept;
	void SetForeColor(const Color& color) noexcept;
	bool IsCursorEnabled() const noexcept;
	Keyboard& GetKeyboard() noexcept;
	Mouse& GetMouse() noexcept;
	static const std::optional<int> ProcessMessages();

	// Window Exception
	class WindowException : public Exception
	{
	public:
		static const std::string& TranslateErrorCode(HRESULT hr) noexcept;
	};

	// HRException
	class HRException : public Exception
	{
	public:

		HRException(int line, const char* file, HRESULT hr) noexcept;

		const char* what() const noexcept override;
		const char* GetType() const noexcept;
		HRESULT GetErrorCode() const noexcept;
		const std::string& GetErrorDescription() const noexcept;

	private:

		HRESULT hr;
	};
};