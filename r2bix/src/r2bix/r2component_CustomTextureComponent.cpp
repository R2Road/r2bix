#include "r2component_CustomTextureComponent.h"

#include "r2base_DebugConfig.h"
#include "r2base_Node.h"
#include "r2component_TransformComponent.h"
#include "r2render_Camera.h"

namespace r2component
{
	CustomTextureComponent::CustomTextureComponent( r2base::Node& owner_node ) : r2base::Component<CustomTextureComponent>( owner_node )
		, mTexture( 1, 1, ' ')
	{}
}