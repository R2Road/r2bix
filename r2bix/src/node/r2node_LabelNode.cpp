#include "pch.h"
#include "r2node_LabelNode.h"

#include "base/r2base_Director.h"
#include "component/r2component_TextRenderComponent.h"
#include "component/r2component_TransformComponent.h"

namespace r2node
{
	LabelNode::LabelNode( r2base::Director& director ) : r2base::Node( director )
		, mTransformComponent( nullptr )
		, mTextRenderComponent( nullptr )
	{}

	std::unique_ptr<LabelNode> LabelNode::Create( r2base::Director& director )
	{
		std::unique_ptr<LabelNode> ret( new ( std::nothrow ) LabelNode( director ) );
		if( !ret || !ret->Init() )
		{
			ret.reset();
		}

		return ret;
	}

	bool LabelNode::Init()
	{
		auto transform_component = r2component::TransformComponent::Create( *this );
		mTransformComponent = transform_component.get();
		AddComponent( std::move( transform_component ) );

		auto text_render_component = r2component::TextRenderComponent::Create( *this );
		text_render_component->mTransformComponent = mTransformComponent;
		mTextRenderComponent = text_render_component.get();
		AddComponent( std::move( text_render_component ) );

		return true;
	}
	
	void LabelNode::SetRect( const int x, const int y, const int width, const int height )
	{
		mTextRenderComponent->SetRect( x, y, width, height );
	}
	void LabelNode::SetString( const std::string_view str )
	{
		mTextRenderComponent->SetString( str );
	}
}