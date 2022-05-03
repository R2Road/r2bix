#include "pch.h"
#include "p2048mini_GameComponent.h"

namespace p2048mini
{
	GameComponent::GameComponent( r2base::Node& owner_node ) : r2base::Component( owner_node )
	{}

	std::unique_ptr<GameComponent> GameComponent::Create( r2base::Node& owner_node )
	{
		std::unique_ptr<GameComponent> ret( new ( std::nothrow ) GameComponent( owner_node ) );
		if( !ret || !ret->Init() )
		{
			ret.reset();
		}

		return ret;
	}
}