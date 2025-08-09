#include "r2bix_component_CustomTextureComponent.h"

namespace r2bix_component
{
	CustomTextureComponent::CustomTextureComponent( r2bix::Director& director, r2bix_node::Node& owner_node ) : r2bix_component::Component<CustomTextureComponent>( director, owner_node )
		, mTexture( 1, 1, ' ')
	{}
}