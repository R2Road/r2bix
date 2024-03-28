#include "r2bix_component_UIControlComponent.h"

#include "r2_Assert.h"

#include "r2bix_Director.h"

#include "r2bix_component_UIPannelComponent.h"

#include "r2bix_node_Node.h"

namespace r2bix_component
{
	UIControlComponent::UIControlComponent( r2bix_node::Node& owner_node ) : r2bix_component::Component<UIControlComponent>( owner_node )
		, mSize()

		, mCursorState( r2bix_ui::eCursorStatus::None )
		, mKeyStatus( r2bix_ui::eKeyStatus::None)

		, mCallback4CursorResponse()
		, mCallback4KeyResponse()

		, mUIInputListener()

		, mUIPannelComponent( nullptr )
	{}



	bool UIControlComponent::InitProcess()
	{
		mUIInputListener.SetCallback4CursorResponse( [this]( const r2bix_input::CursorPoint cursor_point )->bool
		{
			const r2::RectInt r( mOwnerNode.mTransformComponent->GetWorldPosition(), r2::SizeInt( GetWidth() - 1, GetHeight() - 1 ) );

			switch( mCursorState )
			{
			case r2bix_ui::eCursorStatus::None:
			case r2bix_ui::eCursorStatus::CursorLeave:
				if( r.IsIn( cursor_point ) )
				{
					mCursorState = r2bix_ui::eCursorStatus::CursorOver;

					if( mCallback4CursorResponse )
					{
						mCallback4CursorResponse( mCursorState );
					}
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

					if( mCallback4CursorResponse )
					{
						mCallback4CursorResponse( mCursorState );
					}
				}
				else
				{
					mCursorState = r2bix_ui::eCursorStatus::CursorLeave;

					if( mCallback4CursorResponse )
					{
						mCallback4CursorResponse( mCursorState );
					}
				}
				break;
			}

			return ( r2bix_ui::eCursorStatus::CursorOver == mCursorState || r2bix_ui::eCursorStatus::CursorMove == mCursorState );
		} );

		//
		// UIInputListener에 맞춰서 등록/취소 처리를 하면 너무 복잡해진다.
		// 일단 우겨 넣는걸로 하자.
		//
		mUIInputListener.AddObservationKey( r2bix_input::eKeyCode::VK_LBUTTON );
		mUIInputListener.AddObservationKey( r2bix_input::eKeyCode::VK_MBUTTON );
		mUIInputListener.AddObservationKey( r2bix_input::eKeyCode::VK_RBUTTON );
		mUIInputListener.SetCallback4KeyResponse( [this]( const int key_index, const r2bix_input::eKeyStatus key_status )->bool
		{
			switch( mCursorState )
			{
			case r2bix_ui::eCursorStatus::None:
			case r2bix_ui::eCursorStatus::CursorLeave:
				if( r2bix_ui::eKeyStatus::Push == mKeyStatus || r2bix_ui::eKeyStatus::Pressed == mKeyStatus )
				{
					mKeyStatus = r2bix_ui::eKeyStatus::Cancel;
				}
				else
				{
					mKeyStatus = r2bix_ui::eKeyStatus::None;
				}
				break;

			case r2bix_ui::eCursorStatus::CursorOver:
			case r2bix_ui::eCursorStatus::CursorMove:
				{
					switch( key_status )
					{
					case r2bix_input::eKeyStatus::None:
						mKeyStatus = r2bix_ui::eKeyStatus::None;
						break;
					case r2bix_input::eKeyStatus::Push:
						if( r2bix_ui::eKeyStatus::None == mKeyStatus || r2bix_ui::eKeyStatus::Release == mKeyStatus || r2bix_ui::eKeyStatus::Cancel == mKeyStatus )
						{
							mKeyStatus = r2bix_ui::eKeyStatus::Push;
						}
						break;
					case r2bix_input::eKeyStatus::Pressed:
						if( r2bix_ui::eKeyStatus::Push == mKeyStatus )
						{
							mKeyStatus = r2bix_ui::eKeyStatus::Pressed;
						}
						break;
					case r2bix_input::eKeyStatus::Release:
						if( r2bix_ui::eKeyStatus::Push == mKeyStatus || r2bix_ui::eKeyStatus::Pressed == mKeyStatus )
						{
							mKeyStatus = r2bix_ui::eKeyStatus::Release;
						}
						break;
					}
				}
				break;
			}

			if( r2bix_ui::eKeyStatus::None == mKeyStatus )
			{
				return false;
			}
			
			if( mCallback4KeyResponse )
			{
				return mCallback4KeyResponse( key_index, mKeyStatus );
			}

			return false;
		} );

		return true;
	}

	void UIControlComponent::EnterProcess()
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
	void UIControlComponent::ExitProcess()
	{
		//
		// Unregist UI Input Listener
		//
		if( mUIPannelComponent )
		{
			mUIPannelComponent->RemoveListener( &mUIInputListener );
		}
	}
}