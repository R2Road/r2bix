#include "r2bix_component_UIButtonComponent.h"

#include "r2bix_Director.h"

#include "r2bix_component_CustomTextureComponent.h"
#include "r2bix_component_TextureRenderComponent.h"
#include "r2bix_component_UIPannelComponent.h"

namespace r2bix_component
{
	UIButtonComponent::UIButtonComponent( r2bix_node::Node& owner_node ) : r2bix_component::Component<UIButtonComponent>( owner_node )
		, mCustomTextureComponent( nullptr )
		, mTextureRenderComponent( nullptr )
		, mUIPannelComponent( nullptr )
	{}



	void UIButtonComponent::EnterProcess()
	{
		r2bix_node::Node* parent_node = GetOwnerNode().GetParentNode();

		//
		// Find UIPannelComponent
		//
		while( parent_node )
		{
			mUIPannelComponent = parent_node->GetComponent<UIPannelComponent>();
			if( mUIPannelComponent )
			{
				break;
			}

			parent_node = parent_node->GetParentNode();
		}

		if( mUIPannelComponent )
		{
			//
			// Regist UI Input Listener
			//
		}
	}
	void UIButtonComponent::ExitProcess()
	{
		if( mUIPannelComponent )
		{
			//
			// Unregist UI Input Listener
			//
		}
	}



	int UIButtonComponent::GetWidth() const
	{
		return mCustomTextureComponent->GetTexture()->GetWidth();
	}
	int UIButtonComponent::GetHeight() const
	{
		return mCustomTextureComponent->GetTexture()->GetHeight();
	}



	void UIButtonComponent::SetSize( const uint32_t width, const uint32_t height, const char fill )
	{
		if( mCustomTextureComponent )
		{
			mCustomTextureComponent->GetTexture()->Reset( width, height, fill );
		}

		if( mTextureRenderComponent )
		{
			mTextureRenderComponent->ResetVisibleRect();
		}
	}
}