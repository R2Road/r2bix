#include "pch.h"
#include "r2node_PivotNode.h"

#include "base/r2base_Director.h"
#include "component/r2component_PivotComponent.h"
#include "component/r2component_TextureRenderComponent.h"

namespace r2node
{
	r2base::NodeUp PivotNode::Create( r2base::Director& director )
	{
		auto ret( r2base::Node::Create( director ) );
		if( ret )
		{
			r2component::TextureRenderComponent* texture_render_component = ret->AddComponent<r2component::TextureRenderComponent>();
			r2component::PivotComponent* pivot_component = ret->AddComponent<r2component::PivotComponent>();

			texture_render_component->SetTexture( pivot_component->GetTexture() );
		}

		return ret;
	}
}