#include "pch.h"
#include "r2node_LabelNode.h"

#include "base/r2base_Director.h"
#include "component/r2component_TextureRenderComponent.h"
#include "component/r2component_LabelComponent.h"

namespace r2node
{
	std::unique_ptr<r2base::Node> LabelNode::Create( r2base::Director& director )
	{
		auto ret( r2base::Node::Create( director ) );
		if( !ret )
		{
			r2component::TextureRenderComponent* texture_render_component = ret->AddComponent<r2component::TextureRenderComponent>();
			r2component::LabelComponent* label_component = ret->AddComponent<r2component::LabelComponent>();

			label_component->mTextureRenderComponent = texture_render_component;
			texture_render_component->SetTexture( label_component->GetTexture() );
		}

		return ret;
	}
}