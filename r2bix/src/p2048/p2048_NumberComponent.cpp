#include "pch.h"
#include "p2048_NumberComponent.h"

namespace p2048
{
	NumberComponent::NumberComponent( r2base::Node& owner_node ) : r2base::Component( owner_node )
	{}

	std::unique_ptr<NumberComponent> NumberComponent::Create( r2base::Node& owner_node )
	{
		std::unique_ptr<NumberComponent> ret( new ( std::nothrow ) NumberComponent( owner_node ) );
		if( !ret || !ret->Init() )
		{
			ret.reset();
		}

		return ret;
	}
}