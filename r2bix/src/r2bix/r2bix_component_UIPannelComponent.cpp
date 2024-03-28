#include "r2bix_component_UIPannelComponent.h"

#include "r2_Assert.h"

#include "r2bix_Director.h"

#include "r2bix_component_UIControlComponent.h"
#include "r2bix_ui_UIInputListener.h"

namespace r2bix_component
{
	UIPannelComponent::UIPannelComponent( r2bix_node::Node& owner_node ) : r2bix_component::Component<UIPannelComponent>( owner_node )
		, mListener4Mouse()
		, mUIInputListenerContainer()

		, mUIControlComponent( nullptr )
	{}



	bool UIPannelComponent::InitProcess()
	{
		mListener4Mouse.SetCallback4CursorMoved( [this]( const r2bix_input::CursorPoint cursor_point )->bool
		{
			mUIControlComponent->OnCursorResponse( cursor_point );

			switch( mUIControlComponent->GetState() )
			{
			case r2bix_ui::eCursorStatus::CursorLeave:
			case r2bix_ui::eCursorStatus::CursorOver:
			case r2bix_ui::eCursorStatus::CursorMove:
				OnCursorResponse( cursor_point );
				break;
			}

			//
			// Input Manager���� ��ȿ�� Listener ó���� �ߴ��ϰ� �Ѵ�.
			//
			return (
					r2bix_ui::eCursorStatus::CursorOver == mUIControlComponent->GetState()
				||	r2bix_ui::eCursorStatus::CursorMove == mUIControlComponent->GetState()
			);
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
			if( !mUIControlComponent->OnKeyResponse( key_index, key_status ) )
			{
				return false;
			}

			OnKeyResponse( key_index, key_status );

			//
			// Input Manager���� ��ȿ�� Listener ó���� �ߴ��ϰ� �Ѵ�.
			//
			return true;
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
	void UIPannelComponent::OnKeyResponse( const int key_index, const r2bix_input::eKeyStatus key_status )
	{
		for( auto l : mUIInputListenerContainer )
		{
			if( l->OnKeyResponse( key_index, key_status ) )
			{
				break;
			}
		}
	}
}