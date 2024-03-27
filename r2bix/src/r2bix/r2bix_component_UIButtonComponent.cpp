#include "r2bix_component_UIButtonComponent.h"

#include "r2bix_Director.h"

#include "r2bix_component_UIPannelComponent.h"

namespace r2bix_component
{
	UIButtonComponent::UIButtonComponent( r2bix_node::Node& owner_node ) : r2bix_component::Component<UIButtonComponent>( owner_node )
		, mUIPannelComponent( nullptr )
		, mUIInputListener()

		, mCursorState( r2bix_ui::eCursorStatus::None )

		, mCallback4CursorStatusChanged()
		, mCallback4KeyStatusChanged()
	{
		mUIInputListener.SetCallback4CursorResponse( [this]( const r2bix_input::CursorPoint cursor_point )->bool
		{
			const r2::RectInt r( mOwnerNode.mTransformComponent->GetWorldPosition(), r2::SizeInt( GetWidth() - 1, GetHeight() - 1 ) );


			switch( mCursorState )
			{
			case r2bix_ui::eCursorStatus::None:
				if( r.IsIn( cursor_point ) )
				{
					mCursorState = r2bix_ui::eCursorStatus::CursorOver;

					if( mCallback4CursorStatusChanged )
					{
						mCallback4CursorStatusChanged( mCursorState );
					}

					//OnCursorResponse( mCursorState );
				}
				break;

			case r2bix_ui::eCursorStatus::CursorOver:
			case r2bix_ui::eCursorStatus::CursorMove:
				if( r.IsIn( cursor_point ) )
				{
					//
					// Input Manager 에서 커서가 이동했을 때 Callback을 호출하므로 커서 위치가 변했는지 확인 안해도 된다.
					//

					mCursorState = r2bix_ui::eCursorStatus::CursorMove;

					if( mCallback4CursorStatusChanged )
					{
						mCallback4CursorStatusChanged( mCursorState );
					}

					//OnCursorResponse( mCursorState );
				}
				else
				{
					mCursorState = r2bix_ui::eCursorStatus::CursorLeave;

					if( mCallback4CursorStatusChanged )
					{
						mCallback4CursorStatusChanged( mCursorState );
					}

					//OnCursorResponse( mCursorState );
				}
				break;

			case r2bix_ui::eCursorStatus::CursorLeave:
				mCursorState = r2bix_ui::eCursorStatus::None;
				break;
			}

			return ( r2bix_ui::eCursorStatus::CursorOver == mCursorState || r2bix_ui::eCursorStatus::CursorMove == mCursorState );
		} );
	}



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

		//
		// Regist UI Input Listener
		//
		if( mUIPannelComponent )
		{
			mUIPannelComponent->AddListener( &mUIInputListener );
		}
	}
	void UIButtonComponent::ExitProcess()
	{
		//
		// Unregist UI Input Listener
		//
		if( mUIPannelComponent )
		{
			mUIPannelComponent->RemoveListener( &mUIInputListener );
		}
	}



	void UIButtonComponent::SetCallback4CursorResponse( const Callback4CursorStatusChangedT& callback )
	{
		mCallback4CursorStatusChanged = callback;
	}
	void UIButtonComponent::SetCallback4KeyResponse( const Callback4KeyStatusChangedT& callback )
	{
		mCallback4KeyStatusChanged = callback;
	}

	void UIButtonComponent::AddObservationKey( const r2bix_input::eKeyCode key_code )
	{
		mUIInputListener.AddObservationKey( key_code );
	}
}