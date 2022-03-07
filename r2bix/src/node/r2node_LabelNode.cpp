#include "pch.h"
#include "r2node_LabelNode.h"

#include "base/r2base_Director.h"
#include "component/r2component_TextRenderComponent.h"
#include "component/r2component_LabelComponent.h"

namespace r2node
{
	LabelNode::LabelNode( r2base::Director& director ) : r2base::Node( director )
		, mTextureRenderComponent( nullptr )
		, mLabelComponent( nullptr )
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
		if( !r2base::Node::Init() )
		{
			return false;
		}

		{
			auto component = r2component::TextureRenderComponent::Create( *this );
			mTextureRenderComponent = component.get();
			AddComponent( std::move( component ) );
		}

		{
			auto component = r2component::LabelComponent::Create( *this );
			component->mTextureRenderComponent = mTextureRenderComponent;
			mLabelComponent = component.get();
			AddComponent( std::move( component ) );
		}

		return true;
	}
	
	void LabelNode::SetRect( const int x, const int y, const int width, const int height )
	{
		mTextureRenderComponent->SetRect( x, y, width, height );
	}
	void LabelNode::SetString( const std::string_view str )
	{
		mLabelComponent->SetString( str );
	}
}