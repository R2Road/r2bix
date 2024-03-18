#include "r2bix_input_InputManager.h"

#include "r2_Assert.h"

#include "r2bix_input_Listener4Keyboard.h"
#include "r2bix_input_Listener4Mouse.h"

namespace r2bix_input
{
	InputManager::InputManager( const short offset_x, const short offset_y ) :
		  mMachineInputCollector( offset_x, offset_y )
		, mKeyboardListener()
		, mMouseListener()
	{}

	void InputManager::Update()
	{
		//
		// 입력 수집
		//
		mMachineInputCollector.Collect();

		//
		// 키 상태 업데이트
		//
		if( !mMouseListener.empty() )
		{
			( *mMouseListener.begin() )->Update(mMachineInputCollector.GetObservationKeyStates(), mMachineInputCollector.GetCursorPoint());
		}
		if( !mKeyboardListener.empty() )
		{
			( *mKeyboardListener.begin() )->Update(mMachineInputCollector.GetObservationKeyStates());
		}
	}



	void InputManager::AddMouseListener( r2bix_input::Listener4Mouse* const listener )
	{
		//
		// 반복 등록 확인
		//
		{
			auto target_itr = std::find( mMouseListener.begin(), mMouseListener.end(), listener );
			if( target_itr != mMouseListener.end() )
			{
				R2ASSERT( false, "이미 등록된 M리스너의 등록을 요청한다." );
				return;
			}
		}

		//
		// Add
		//
		{
			auto pivot_itr = std::find_if( mMouseListener.begin(), mMouseListener.end(), [listener]( const r2bix_input::Listener4Mouse* const l ){
				if( l->GetOrder() <= listener->GetOrder() )
				{
					return true;
				}

				return false;
			} );

			if( mMouseListener.end() == pivot_itr )
			{
				mMouseListener.insert( pivot_itr, listener );
			}
			else
			{
				mMouseListener.push_back( listener );
			}
		}

		//
		// Regist Key
		//
		mMachineInputCollector.AddObservationKeys( listener->GetObservationKeys() );
	}
	void InputManager::RemoveMouseListener( r2bix_input::Listener4Mouse* const listener )
	{
		if( nullptr == listener )
		{
			R2ASSERT( false, "삭제 요청된 M리스너가 nullptr 이다." );
			return;
		}

		if( mMouseListener.empty() )
		{
			R2ASSERT( false, "등록된 M리스너가 없는데 삭제를 요청한다." );
			return;
		}

		//
		// Remove
		//
		{
			auto target_itr = std::find( mMouseListener.begin(), mMouseListener.end(), listener );
			if( target_itr == mMouseListener.end() )
			{
				R2ASSERT( false, "등록된적 없는 M리스너의 삭제를 요청한다." );
				return;
			}

			mMouseListener.erase( target_itr );
		}

		//
		// Unregist Key
		//
		mMachineInputCollector.RemoveObservationKeys( listener->GetObservationKeys() );
	}

	void InputManager::AddKeyboardListener( r2bix_input::Listener4Keyboard* const listener )
	{
		//
		// 반복 등록 확인
		//
		{
			auto target_itr = std::find( mKeyboardListener.begin(), mKeyboardListener.end(), listener );
			if( target_itr != mKeyboardListener.end() )
			{
				R2ASSERT( false, "이미 등록된 K리스너의 등록을 요청한다." );
				return;
			}
		}		

		//
		// Add
		//
		{
			auto pivot_itr = std::find_if( mKeyboardListener.begin(), mKeyboardListener.end(), [listener]( const r2bix_input::Listener4Keyboard* const l ){
				if( l->GetOrder() <= listener->GetOrder() )
				{
					return true;
				}

				return false;
			} );

			if( mKeyboardListener.end() == pivot_itr )
			{
				mKeyboardListener.insert( pivot_itr, listener );
			}
			else
			{
				mKeyboardListener.push_back( listener );
			}
		}

		//
		// Regist Key
		//
		mMachineInputCollector.AddObservationKeys( listener->GetObservationKeys() );
	}
	void InputManager::RemoveKeyboardListener( r2bix_input::Listener4Keyboard* const listener )
	{
		if( nullptr == listener )
		{
			R2ASSERT( false, "삭제 요청된 K리스너가 nullptr 이다." );
			return;
		}

		if( mKeyboardListener.empty() )
		{
			R2ASSERT( false, "등록된 K리스너가 없는데 삭제를 요청한다." );
			return;
		}

		//
		// Remove
		//
		{
			auto target_itr = std::find( mKeyboardListener.begin(), mKeyboardListener.end(), listener );
			if( target_itr == mKeyboardListener.end() )
			{
				R2ASSERT( false, "등록된적 없는 K리스너의 삭제를 요청한다." );
				return;
			}

			mKeyboardListener.erase( target_itr );
		}

		//
		// Unregist Key
		//
		mMachineInputCollector.RemoveObservationKeys( listener->GetObservationKeys() );
	}
}