#include "r2bix_component_CustomTextureComponent.h"

namespace r2bix_component
{
	CustomTextureComponent::CustomTextureComponent( r2bix_node::Node& owner_node ) : r2bix_component::Component<CustomTextureComponent>( owner_node )
		, mTexture( 1, 1, ' ')
	{}
}