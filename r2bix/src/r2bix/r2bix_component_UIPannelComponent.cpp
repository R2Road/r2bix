#include "r2bix_component_UIPannelComponent.h"

#include "r2bix_component_CustomTextureComponent.h"
#include "r2bix_component_TextureRenderComponent.h"

namespace r2bix_component
{
	UIPannelComponent::UIPannelComponent( r2bix_node::Node& owner_node ) : r2bix_component::Component<UIPannelComponent>( owner_node )
		, mCustomTextureComponent( nullptr )
		, mTextureRenderComponent( nullptr )
	{}



	int UIPannelComponent::GetWidth() const
	{
		return mCustomTextureComponent->GetTexture()->GetWidth();
	}
	int UIPannelComponent::GetHeight() const
	{
		return mCustomTextureComponent->GetTexture()->GetHeight();
	}



	void UIPannelComponent::SetSize( const uint32_t width, const uint32_t height, const char fill_char )
	{
		if( mCustomTextureComponent )
		{
			mCustomTextureComponent->GetTexture()->Reset( width, height, fill_char );
		}

		if( mTextureRenderComponent )
		{
			mTextureRenderComponent->ResetVisibleRect();
		}
	}
	void UIPannelComponent::SetSize( const uint32_t width, const uint32_t height )
	{
		SetSize( width, height, '#' );
	}
}