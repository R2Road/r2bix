#include "r2bix_component_UIPannelComponent.h"

#include "r2_Assert.h"

#include "r2bix_Director.h"

#include "r2bix_component_CustomTextureComponent.h"
#include "r2bix_component_TextureRenderComponent.h"

#include "r2bix_ui_UIInputListener.h"

#include "r2bix_node_Node.h"

namespace r2bix_component
{
	UIPannelComponent::UIPannelComponent( r2bix_node::Node& owner_node ) : r2bix_component::Component<UIPannelComponent>( owner_node )
		, mListener4Mouse()
		, mCursorResponseCallback()
		, mCallback4KeyResponse()

		, mCursorState( r2bix_ui::eCursorStatus::None )
		, mKeyStatus( r2bix_ui::eKeyStatus::None)

		, mUIInputListenerContainer()
	{}



	bool UIPannelComponent::InitProcess()
	{
		mListener4Mouse.SetCallback4CursorMoved( [this]( const r2bix_input::CursorPoint cursor_point )->bool
		{
			const r2::RectInt r( mOwnerNode.mTransformComponent->GetWorldPosition(), r2::SizeInt( GetWidth() - 1, GetHeight() - 1 ) );

			switch( mCursorState )
			{
			case r2bix_ui::eCursorStatus::None:
			case r2bix_ui::eCursorStatus::CursorLeave:
				if( r.IsIn( cursor_point ) )
				{
					mCursorState = r2bix_ui::eCursorStatus::CursorOver;

					if( mCursorResponseCallback )
					{
						mCursorResponseCallback( mCursorState );
					}

					OnCursorResponse( cursor_point );
				}
				break;

			case r2bix_ui::eCursorStatus::CursorOver:
			case r2bix_ui::eCursorStatus::CursorMove:
				if( r.IsIn( cursor_point ) )
				{
					//
					// Input Manager ���� Ŀ���� �̵����� �� Callback�� ȣ���ϹǷ� Ŀ�� ��ġ�� ���ߴ��� Ȯ�� ���ص� �ȴ�.
					//

					mCursorState = r2bix_ui::eCursorStatus::CursorMove;

					if( mCursorResponseCallback )
					{
						mCursorResponseCallback( mCursorState );
					}

					OnCursorResponse( cursor_point );
				}
				else
				{
					mCursorState = r2bix_ui::eCursorStatus::CursorLeave;

					if( mCursorResponseCallback )
					{
						mCursorResponseCallback( mCursorState );
					}

					OnCursorResponse( r2bix_input::CursorPoint{ std::numeric_limits<int>::min(), std::numeric_limits<int>::min() } );
				}
				break;
			}

			return ( r2bix_ui::eCursorStatus::CursorOver == mCursorState || r2bix_ui::eCursorStatus::CursorMove == mCursorState );
		} );

		//
		// UIInputListener�� ���缭 ���/��� ó���� �ϸ� �ʹ� ����������.
		// �ϴ� ��� �ִ°ɷ� ����.
		//
		mListener4Mouse.AddObservationKey( r2bix_input::eKeyCode::VK_LBUTTON );
		mListener4Mouse.AddObservationKey( r2bix_input::eKeyCode::VK_MBUTTON );
		mListener4Mouse.AddObservationKey( r2bix_input::eKeyCode::VK_RBUTTON );
		mListener4Mouse.SetCallback4KeyStatusChanged( [this]( const int key_index, const r2bix_input::eKeyStatus key_status )->bool
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

	void UIPannelComponent::ActivateProcess()
	{
		GetOwnerNode().GetDirector().GetInputManager().AddListener( &mListener4Mouse );
	}
	void UIPannelComponent::DeactivateProcess()
	{
		GetOwnerNode().GetDirector().GetInputManager().RemoveListener( &mListener4Mouse );
	}



	void UIPannelComponent::AddListener( r2bix_ui::UIInputListener* const listener )
	{
		//
		// �ݺ� ��� Ȯ��
		//
		{
			auto target_itr = std::find( mUIInputListenerContainer.begin(), mUIInputListenerContainer.end(), listener );
			if( target_itr != mUIInputListenerContainer.end() )
			{
				R2ASSERT( false, "�̹� ��ϵ� �������� ����� ��û�Ѵ�." );
				return;
			}
		}

		//
		// Add
		//
		{
			auto pivot_itr = std::find_if( mUIInputListenerContainer.begin(), mUIInputListenerContainer.end(), [listener]( const r2bix_ui::UIInputListener* const l ){
				if( l->GetOrder() <= listener->GetOrder() )
				{
					return true;
				}

				return false;
			} );

			if( mUIInputListenerContainer.end() == pivot_itr )
			{
				mUIInputListenerContainer.push_back( listener );
			}
			else
			{
				mUIInputListenerContainer.insert( pivot_itr, listener );
			}

			mListener4Mouse;
		}
	}
	void UIPannelComponent::RemoveListener( r2bix_ui::UIInputListener* const listener )
	{
		if( nullptr == listener )
		{
			R2ASSERT( false, "���� ��û�� �����ʰ� nullptr �̴�." );
			return;
		}

		if( mUIInputListenerContainer.empty() )
		{
			R2ASSERT( false, "��ϵ� �����ʰ� ���µ� ������ ��û�Ѵ�." );
			return;
		}

		//
		// Remove
		//
		{
			auto target_itr = std::find( mUIInputListenerContainer.begin(), mUIInputListenerContainer.end(), listener );
			if( target_itr == mUIInputListenerContainer.end() )
			{
				R2ASSERT( false, "��ϵ��� ���� �������� ������ ��û�Ѵ�." );
				return;
			}

			mUIInputListenerContainer.erase( target_itr );
		}
	}
	void UIPannelComponent::OnCursorResponse( const r2bix_input::CursorPoint cursor_point )
	{
		for( auto l : mUIInputListenerContainer )
		{
			if( l->OnCursorResponse( cursor_point ) )
			{
				break;
			}
		}
	}
}