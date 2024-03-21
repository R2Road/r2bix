#include "r2bix_component_UIPannelComponent.h"

#include "r2bix_Director.h"

#include "r2bix_component_CustomTextureComponent.h"
#include "r2bix_component_TextureRenderComponent.h"

#include "r2bix_node_Node.h"

namespace r2bix_component
{
	UIPannelComponent::UIPannelComponent( r2bix_node::Node& owner_node ) : r2bix_component::Component<UIPannelComponent>( owner_node )
		, mCustomTextureComponent( nullptr )
		, mTextureRenderComponent( nullptr )
		, mListener4Mouse()
		, mMouseOverCallback()
		, mMouseLeaveCallback()
		, mbMouseOver( false )
	{
		mListener4Mouse.SetCallback4CursorMoved( [this]( const r2bix_input::CursorPoint cursor_point )->bool
		{
			const r2::RectInt r( mOwnerNode.mTransformComponent->GetPosition(), r2::SizeInt( GetWidth() - 1, GetHeight() - 1 ) );

			mbMouseOver = r.IsIn( cursor_point );
			if( mbMouseOver )
			{
				if( mMouseOverCallback )
				{
					mMouseOverCallback();
				}

				//
				// Input Event 전파
				//
			}
			else
			{
				if( mMouseLeaveCallback )
				{
					mMouseLeaveCallback();
				}

				//
				// Input Event 전파
				//
			}

			return mbMouseOver;
		} );
	}



	void UIPannelComponent::ActivateProcess()
	{
		GetOwnerNode().GetDirector().GetInputManager().AddListener( &mListener4Mouse );
	}
	void UIPannelComponent::DeactivateProcess()
	{
		GetOwnerNode().GetDirector().GetInputManager().RemoveListener( &mListener4Mouse );
	}

	void UIPannelComponent::Update( const float delta_time )
	{

	}



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