#include "r2bix_component_TransformComponent.h"

#include "r2bix_Director.h"

#include "r2bix_node_Node.h"

namespace r2bix_component
{
	TransformComponent::TransformComponent( r2bix::Director& director, r2bix_node::Node& owner_node ) : r2bix_component::Component<TransformComponent>( director, owner_node )
		, mPosition()
		, mZOrder( 0 )
		, mPivotPoint( 0.5f, 0.5f )
		, mSignal4PivotChanged()
	{}

	r2::PointInt TransformComponent::GetWorldPosition() const
	{
		r2::PointInt world_position;
		r2bix_node::Node* current_node = &GetOwnerNode();

		do
		{

			world_position += current_node->mTransformComponent->GetPosition();

			current_node = current_node->GetParentNode();

		} while( current_node );

		return world_position;
	}
	r2::PointInt TransformComponent::GetScreenPosition() const
	{
		const r2::Point<short> screen_offset = GetOwnerNode().GetDirector().GetScreenOffset();
		r2::PointInt screen_position = GetWorldPosition();

		screen_position.SetX( screen_position.GetX() + screen_offset.GetX() );
		screen_position.SetY( screen_position.GetY() + screen_offset.GetY() );

		return screen_position;
	}
}