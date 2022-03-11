#include "pch.h"
#include "r2component_LabelComponent.h"

namespace r2component
{
	LabelComponent::LabelComponent( r2base::Node& owner_node ) : r2base::Component( owner_node )
		, mTexture( " " )
		, mTextureRenderComponent( nullptr )
	{}

	std::unique_ptr<LabelComponent> LabelComponent::Create( r2base::Node& owner_node )
	{
		std::unique_ptr<LabelComponent> ret( new ( std::nothrow ) LabelComponent( owner_node ) );
		if( !ret || !ret->Init() )
		{
			ret.reset();
		}

		return ret;
	}

	void LabelComponent::SetString( const std::string_view str )
	{
		if( mText == str )
		{
			return;
		}

		mText = str;
		mTexture.Reset( str );
	}
}