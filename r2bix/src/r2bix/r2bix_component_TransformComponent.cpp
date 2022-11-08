#include "r2bix_component_TransformComponent.h"

namespace r2bix_component
{
	TransformComponent::TransformComponent( r2bix_node::Node& owner_node ) : r2bix_component::Component<TransformComponent>( owner_node )
		, mPosition()
		, mZOrder( 0 )
	{}
}