#pragma once

#include "base/r2base_Component.h"
#include "base/r2base_ComponentStaticID.h"

namespace p2048mini
{
	class GameComponent : public r2base::Component
	{
	private:
		GameComponent( r2base::Node& owner_node );

	public:
		int GetStaticID() const override { return r2base::ComponentStaticID<GameComponent>::Get(); }
		static std::unique_ptr<GameComponent> Create( r2base::Node& owner_node );
	};
}