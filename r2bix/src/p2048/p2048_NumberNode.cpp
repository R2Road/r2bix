#include "p2048_NumberNode.h"

#include <numeric>

#include "r2bix/r2bix_Director.h"
#include "r2bix/r2bix_component_CustomTextureComponent.h"
#include "r2bix/r2bix_component_LabelSComponent.h"
#include "r2bix/r2bix_component_TextureRenderComponent.h"
#include "r2bix/r2bix_node_CustomTextureNode.h"
#include "r2bix/r2bix_node_LabelSNode.h"
#include "r2bix/r2bix_node_PivotNode.h"
#include "r2bix/r2bix_node_SpriteNode.h"

#include "p2048_Config.h"
#include "p2048_NumberComponent.h"
#include "p2048table_TextureTable.h"

namespace p2048
{
	r2bix_node::NodeUp NumberNode::Create( r2bix::Director& director )
	{
		auto ret( r2bix_node::Node::Create( director ) );
		if( ret )
		{
			auto number_component = ret->AddComponent<p2048::NumberComponent>();

			//
			// Frame
			//
			{
				auto node = ret->AddChild<r2bix_node::CustomTextureNode>( std::numeric_limits<int>::min() );
				node->GetComponent<r2bix_component::CustomTextureComponent>()->GetTexture()->Reset( 8u, 3u, ' ' );
				node->GetComponent<r2bix_component::TextureRenderComponent>()->SetTexture(
					node->GetComponent<r2bix_component::CustomTextureComponent>()->GetTexture()
				);

				number_component->SetCustomTextureComponent( node->GetComponent<r2bix_component::CustomTextureComponent>() );
			}

			//
			// Label
			//
			{
				auto node = ret->AddChild<r2bix_node::LabelSNode>();
				node->GetComponent<r2bix_component::TextureRenderComponent>()->SetPivotPoint( 1.f, 0.f );
				node->GetComponent<r2bix_component::TransformComponent>()->SetPosition( 2, 0 );
				node->GetComponent<r2bix_component::LabelSComponent>()->SetColor( r2base::eForegroundColor::FG_White | r2base::eBackgroundColor::BG_Black );

				number_component->SetLabelComponent( node->GetComponent<r2bix_component::LabelSComponent>() );
			}

			//
			// Debug
			//
			if( p2048::Config::GetNodeConfig().pivot )
			{
				ret->AddChild<r2bix_node::PivotNode>( std::numeric_limits<int>::max() );
			}
		}

		return ret;
	}
}