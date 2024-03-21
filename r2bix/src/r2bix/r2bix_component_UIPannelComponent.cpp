#include "r2bix_component_UIPannelComponent.h"

#include "r2bix_Director.h"

#include "r2bix_component_CustomTextureComponent.h"
#include "r2bix_component_TextureRenderComponent.h"

#include "r2bix_node_Node.h"

namespace r2bix_component
{
	UIPannelComponent::UIPannelComponent( r2bix_node::Node& owner_node ) : r2bix_component::Component<UIPannelComponent>( owner_node )
		, mListener4Mouse()
		, mMouseOverCallback()
		, mMouseMoveCallback()
		, mMouseLeaveCallback()
		, mState( eState::None )
	{
		mListener4Mouse.SetCallback4CursorMoved( [this]( const r2bix_input::CursorPoint cursor_point )->bool
		{
			const r2::RectInt r( mOwnerNode.mTransformComponent->GetPosition(), r2::SizeInt( GetWidth() - 1, GetHeight() - 1 ) );


			switch( mState )
			{
			case eState::None:
				if( r.IsIn( cursor_point ) )
				{
					mState = eState::MouseOver;

					if( mMouseOverCallback )
					{
						mMouseOverCallback();
					}
				}
				break;

			case eState::MouseOver:
			case eState::MouseMove:
				if( r.IsIn( cursor_point ) )
				{
					//
					// Input Manager 에서 커서가 이동했을 때 Callback을 호출하므로 커서 위치가 변했는지 확인 안해도 된다.
					//

					mState = eState::MouseMove;

					if( mMouseMoveCallback )
					{
						mMouseMoveCallback();
					}
				}
				else
				{
					mState = eState::MouseLeave;

					if( mMouseLeaveCallback )
					{
						mMouseLeaveCallback();
					}
				}
				break;

			case eState::MouseLeave:
				mState = eState::None;
				break;
			}

			return ( eState::MouseOver == mState );
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
}