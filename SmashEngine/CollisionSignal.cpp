#include "stdafx.h"
#include "CollisionSignal.h"

namespace SmashEngine
{
	CollisionSignal::CollisionSignal(Manifold* contactData) :
		contactData(contactData)
	{
	}

	Manifold* CollisionSignal::GetContactData() const
	{
		return contactData;
	}
}