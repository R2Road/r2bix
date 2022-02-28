#include "pch.h"
#include "r2component_TransformComponent.h"

namespace r2component
{
	r2base::ComponentUp TransformComponent::Create( r2base::Node& owner_node )
	{
		std::unique_ptr<TransformComponent> ret( new ( std::nothrow ) TransformComponent( owner_node ) );
		if( !ret || !ret->Init() )
		{
			ret.reset();
		}

		return ret;
	}
}