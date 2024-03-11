#include "r2bix_component_UIButtonComponent.h"

#include "r2bix_component_CustomTextureComponent.h"
#include "r2bix_component_TextureRenderComponent.h"

namespace r2bix_component
{
	UIButtonComponent::UIButtonComponent( r2bix_node::Node& owner_node ) : r2bix_component::Component<UIButtonComponent>( owner_node )
		, mCustomTextureComponent( nullptr )
		, mTextureRenderComponent( nullptr )
	{}
}