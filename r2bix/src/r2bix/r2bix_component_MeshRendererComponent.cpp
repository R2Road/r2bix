#include "r2bix_component_MeshRendererComponent.h"

namespace r2bix_component
{
	MeshRendererComponent::MeshRendererComponent( r2bix::Director& director, r2bix_node::Node& owner_node ) : r2bix_component::Component<MeshRendererComponent>( director, owner_node )
		, mStaticMeshComponent( nullptr )
	{}

	void MeshRendererComponent::Render( const r2bix_render::Camera* const /*camera*/, r2bix_render::iRenderTarget* const /*render_target*/, r2::PointInt /*offset*/ )
	{
		// Do Something
	}
}