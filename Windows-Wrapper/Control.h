#pragma once

#include "Base.h"
#include "Common.h"
#include "IHandle.h"
#include "Size.h"
#include "Event.h"

class Window;

class Control : public IHandle, public Base
{
	friend class Menu;
	friend class MenuRadioItem;

protected:

	std::string Text;
	Size Size;
	Point Location;
	Control* Parent;
	std::vector<std::shared_ptr<Control>> Controls;
	EventDispatcher Events;

	Control();
	Control(Control* parent, const std::string& text);
	Control(Control* parent, const std::string& text, int width, int height, int x, int y);
	Control(const std::string& text);
	Control(const std::string& text, int width, int height, int x, int y);
	Control(Control&& other) = default;
	Control& operator=(const Control&) = default;
	Control& operator=(Control&&) = default;
	virtual ~Control();

	virtual void Bind() noexcept = 0;

	template<typename T, typename... Args>
	T& Create(Args... a)
	{
		auto obj = std::make_shared<T>(a...);
		Controls.push_back(obj);
		obj->Bind();
		return dynamic_cast<T&>(*Controls.back());
	}

	virtual void Dispatch(const std::string& event)
	{
		Events.Dispatch(event, this);
	}

public:

	void OnClickSet(const std::function<void(Control*)>& callback)
	{
		Events.Register(new Event<Control*>("OnClick", callback));
	}

	void OnClick()
	{
		Events.Dispatch("OnClick");
	}

	const std::string& GetText() const noexcept;
};