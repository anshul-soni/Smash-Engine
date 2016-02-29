#pragma once

namespace SmashEngine
{
	class Manifold;

	class CollisionSignal
	{
	public:
		CollisionSignal(Manifold* contactData);
		Manifold* GetContactData()const;
	private:
		Manifold* contactData;

	};
}