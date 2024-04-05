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
			// UIControlComponent 의 기능을 활용해 유효 영역을 확인 한다.
			//
			mMyUIControlComponent->OnCursorResponse( cursor_point );

			//
			// 등록된 UIControlComponent 처리
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
			// 현재 PannelComponent가 유효한 처리를 완료했다면
			// Input Manager에서 다른 PannelComponent의 처리를 하지 않게 한다.
			//
			return (
				r2bix_ui::eCursorStatus::CursorOver == mMyUIControlComponent->GetState()
				|| r2bix_ui::eCursorStatus::CursorMove == mMyUIControlComponent->GetState()
				);
		} );

		//
		// UIInputListener에 맞춰서 등록/취소 처리를 하면 너무 복잡해진다.
		// 일단 우겨 넣는걸로 하자.
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
			// Input Manager에서 유효한 Listener 처리를 중단하게 한다.
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
		// 반복 등록 확인
		//
		{
			auto target_itr = std::find( mUIControlComponentContainer.begin(), mUIControlComponentContainer.end(), control );
			if( target_itr != mUIControlComponentContainer.end() )
			{
				R2ASSERT( false, "이미 등록된 리스너의 등록을 요청한다." );
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
			R2ASSERT( false, "삭제 요청된 리스너가 nullptr 이다." );
			return;
		}

		if( mUIControlComponentContainer.empty() )
		{
			R2ASSERT( false, "등록된 리스너가 없는데 삭제를 요청한다." );
			return;
		}

		//
		// Remove
		//
		{
			auto target_itr = std::find( mUIControlComponentContainer.begin(), mUIControlComponentContainer.end(), control );
			if( target_itr == mUIControlComponentContainer.end() )
			{
				R2ASSERT( false, "등록된적 없는 리스너의 삭제를 요청한다." );
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