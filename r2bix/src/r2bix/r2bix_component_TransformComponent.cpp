#include "r2bix_component_TransformComponent.h"

#include "r2bix_node_Node.h"

namespace r2bix_component
{
	TransformComponent::TransformComponent( r2bix_node::Node& owner_node ) : r2bix_component::Component<TransformComponent>( owner_node )
		, mPosition()
		, mZOrder( 0 )
	{}

	r2::PointInt TransformComponent::GetWorldPosition() const
	{
		r2::PointInt world_position = GetPosition();

		r2bix_node::Node* parent_node = GetOwnerNode().GetParentNode();

		//
		// Calculate World Position
		//
		while( parent_node )
		{
			world_position += parent_node->GetComponent<TransformComponent>()->GetPosition();

			parent_node = parent_node->GetParentNode();
		}

		return world_position;
	}
}