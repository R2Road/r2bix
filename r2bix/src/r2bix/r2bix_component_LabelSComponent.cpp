#include "r2bix_component_LabelSComponent.h"

#include "r2bix_component_CustomTextureComponent.h"
#include "r2bix_component_TextureRenderComponent.h"

namespace r2bix_component
{
	LabelSComponent::LabelSComponent( r2bix::Director& director, r2bix_node::Node& owner_node ) : r2bix_component::Component<LabelSComponent>( director, owner_node )
		, mCustomTextureComponent( nullptr )
		, mTextureRenderComponent( nullptr )
		, mColorValue( r2bix::eForegroundColor::FG_White | r2bix::eBackgroundColor::BG_Black )
	{}

	void LabelSComponent::SetString( const std::string_view str )
	{
		if( mText == str )
		{
			return;
		}

		mText = str;

		if( mCustomTextureComponent )
		{
			mCustomTextureComponent->GetTexture()->Reset( static_cast<uint32_t>( str.size() ), str, mColorValue );
		}

		if( mTextureRenderComponent )
		{
			mTextureRenderComponent->ResetVisibleRect();
		}
	}
	void LabelSComponent::SetColor( const r2bix::ColorValue color_value )
	{
		if( color_value == mColorValue )
		{
			return;
		}

		mColorValue = color_value;

		if( mCustomTextureComponent )
		{
			mCustomTextureComponent->GetTexture()->FillColorAll( mColorValue );
		}
	}
	void LabelSComponent::Set( const std::string_view str, const r2bix::ColorValue color_value )
	{
		if( mText == str && color_value == mColorValue )
		{
			return;
		}

		mText = str;
		mColorValue = color_value;

		if( mCustomTextureComponent )
		{
			mCustomTextureComponent->GetTexture()->Reset( static_cast< uint32_t >( str.size() ), str, mColorValue );
		}

		if( mTextureRenderComponent )
		{
			mTextureRenderComponent->ResetVisibleRect();
		}
	}
}