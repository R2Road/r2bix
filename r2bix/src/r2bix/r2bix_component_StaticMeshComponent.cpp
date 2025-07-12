#include "r2bix_component_StaticMeshComponent.h"

namespace r2bix_component
{
	StaticMeshComponent::StaticMeshComponent( r2bix::Director& director, r2bix_node::Node& owner_node ) : r2bix_component::Component<StaticMeshComponent>( director, owner_node )
		, mVertices()
	{}



	void StaticMeshComponent::SetVertices( const std::initializer_list<VertexT>& vertices )
	{
		mVertices = vertices;
	}
}