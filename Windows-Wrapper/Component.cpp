#include "Component.h"
#include "IContainer.h"

inline bool Component::CanRaiseEvents()
{
	return true;
}

void Component::Dispose(bool disposing) noexcept
{
	if (disposing)
	{
		if (m_Site != nullptr && m_Site->GetContainer() != nullptr)
		{
			m_Site->GetContainer()->Remove(this);
		}

		Events.Dispatch("OnDispose", &ArgsDisposed);
	}
}

Component::Component()
	:
	IsDisposed(false)
{

}

Component::~Component()
{
	Dispose(false);
	// GarbageCollector?? Too much to dream for now
}

bool Component::IsDesignMode()
{
	return m_Site == nullptr ? false : m_Site->IsDesignMode();
}

ISite* Component::GetSite()
{
	return m_Site;
}

void Component::SetSite(ISite* const site)
{
	if (site == nullptr)
	{
		return ;
	}

	m_Site = site;
}

void Component::Dispose()
{
	Dispose(true);
}

const std::string Component::ToString() const noexcept
{
	return m_Site == nullptr ?
		GetType().ToString() :
		std::string(m_Site->GetName() + " [" + GetType().ToString() + "]");
}

IContainer* Component::GetContainer() const noexcept
{
	return m_Site == nullptr ? nullptr : m_Site->GetContainer();
}