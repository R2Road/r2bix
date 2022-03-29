#include "pch.h"
#include "r2node_CustomTextureNode.h"

#include <numeric>

#include "base/r2base_Director.h"
#include "component/r2component_CustomTextureComponent.h"
#include "component/r2component_TextureRenderComponent.h"
#include "node/r2node_PivotNode.h"

namespace r2node
{
	r2base::NodeUp CustomTextureNode::Create( r2base::Director& director )
	{
		auto ret( r2base::Node::Create( director ) );
		if( ret )
		{
			//
			//
			//
			{
				auto custome_texture_component = ret->AddComponent<r2component::CustomTextureComponent>();
				auto texture_render_component = ret->AddComponent<r2component::TextureRenderComponent>();

				texture_render_component->SetTexture( custome_texture_component->GetTexture() );
			}

			//
			// Debug
			//
			{
				ret->AddChild<r2node::PivotNode>( std::numeric_limits<int>::max() );
			}
		}

		return ret;
	}
}