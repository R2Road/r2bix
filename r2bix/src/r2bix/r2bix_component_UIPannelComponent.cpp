#include "r2bix_component_UIPannelComponent.h"

#include "r2_Assert.h"

#include "r2bix_Director.h"

#include "r2bix_component_UIControlComponent.h"

namespace r2bix_component
{
	UIPannelComponent::UIPannelComponent( r2bix_node::Node& owner_node ) : r2bix_component::Component<UIPannelComponent>( owner_node )
		, mListener4Mouse()
		, mMyUIControlComponent( nullptr )
		, mUIControlComponentContainer()
	{}



	bool UIPannelComponent::InitProcess()
	{
		mListener4Mouse.SetCallback4CursorMoved( [this]( const r2bix_input::CursorPoint cursor_point )->bool
		{
			//
			// UIControlComponent �� ����� Ȱ���� ��ȿ ������ Ȯ�� �Ѵ�.
			//
			mMyUIControlComponent->OnCursorResponse( cursor_point );

			//
			// ��ϵ� UIControlComponent ó��
			//
			switch( mMyUIControlComponent->GetState() )
			{
			case r2bix_ui::eCursorStatus::CursorLeave:
				OnCursorResponse( r2bix_input::CursorPoint( std::numeric_limits<int>::min(), std::numeric_limits<int>::min() ) );
				break;

			case r2bix_ui::eCursorStatus::CursorOver:
			case r2bix_ui::eCursorStatus::CursorMove:
				OnCursorResponse( cursor_point );
				break;
			}

			//
			// ���� PannelComponent�� ��ȿ�� ó���� �Ϸ��ߴٸ�
			// Input Manager���� �ٸ� PannelComponent�� ó���� ���� �ʰ� �Ѵ�.
			//
			return (
				r2bix_ui::eCursorStatus::CursorOver == mMyUIControlComponent->GetState()
				|| r2bix_ui::eCursorStatus::CursorMove == mMyUIControlComponent->GetState()
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
			if( !mMyUIControlComponent->OnKeyResponse( key_index, key_status ) )
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



	void UIPannelComponent::SetMyUIControlComponent( UIControlComponent* const ui_control_component )
	{
		mMyUIControlComponent = ui_control_component;

		if( mMyUIControlComponent )
		{
			mMyUIControlComponent->SetCallback4KeyResponse( []( int, r2bix_ui::eKeyStatus )->bool { return true; } );
		}
	}



	int UIPannelComponent::GetWidth() const
	{
		return mMyUIControlComponent->GetWidth();
	}
	int UIPannelComponent::GetHeight() const
	{
		return mMyUIControlComponent->GetHeight();
	}
	void UIPannelComponent::SetSize( const uint32_t width, const uint32_t height )
	{
		mMyUIControlComponent->SetSize( width, height );
	}



	void UIPannelComponent::AddUIControl( r2bix_component::UIControlComponent* const control )
	{
		//
		// �ݺ� ��� Ȯ��
		//
		{
			auto target_itr = std::find( mUIControlComponentContainer.begin(), mUIControlComponentContainer.end(), control );
			if( target_itr != mUIControlComponentContainer.end() )
			{
				R2ASSERT( false, "�̹� ��ϵ� �������� ����� ��û�Ѵ�." );
				return;
			}
		}

		//
		// Add
		//
		{
			auto pivot_itr = std::find_if( mUIControlComponentContainer.begin(), mUIControlComponentContainer.end(), [control]( const r2bix_component::UIControlComponent* const c ){
				if( c->GetOrder() <= control->GetOrder() )
				{
					return true;
				}

				return false;
			} );

			if( mUIControlComponentContainer.end() == pivot_itr )
			{
				mUIControlComponentContainer.push_back( control );
			}
			else
			{
				mUIControlComponentContainer.insert( pivot_itr, control );
			}

			mListener4Mouse;
		}
	}
	void UIPannelComponent::RemoveUIControl( r2bix_component::UIControlComponent* const control )
	{
		if( nullptr == control )
		{
			R2ASSERT( false, "���� ��û�� �����ʰ� nullptr �̴�." );
			return;
		}

		if( mUIControlComponentContainer.empty() )
		{
			R2ASSERT( false, "��ϵ� �����ʰ� ���µ� ������ ��û�Ѵ�." );
			return;
		}

		//
		// Remove
		//
		{
			auto target_itr = std::find( mUIControlComponentContainer.begin(), mUIControlComponentContainer.end(), control );
			if( target_itr == mUIControlComponentContainer.end() )
			{
				R2ASSERT( false, "��ϵ��� ���� �������� ������ ��û�Ѵ�." );
				return;
			}

			mUIControlComponentContainer.erase( target_itr );
		}
	}
	void UIPannelComponent::OnCursorResponse( const r2bix_input::CursorPoint cursor_point )
	{
		for( auto l : mUIControlComponentContainer )
		{
			if( l->OnCursorResponse( cursor_point ) )
			{
				break;
			}
		}
	}
	void UIPannelComponent::OnKeyResponse( const int key_index, const r2bix_input::eKeyStatus key_status )
	{
		for( auto l : mUIControlComponentContainer )
		{
			if( l->OnKeyResponse( key_index, key_status ) )
			{
				break;
			}
		}
	}
}