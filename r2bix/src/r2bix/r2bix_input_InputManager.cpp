#include "r2bix_input_InputManager.h"

#include "r2_Assert.h"

#include "r2bix_input_Listener4Keyboard.h"
#include "r2bix_input_Listener4Mouse.h"

namespace r2bix_input
{
	InputManager::InputManager( const short offset_x, const short offset_y ) :
		  mMachineInputCollector( offset_x, offset_y )
		, mListenerContainer4Mouse()
		, mListenerContainer4Keyboard()
	{}

	void InputManager::Update()
	{
		//
		// 입력 수집
		//
		mMachineInputCollector.Collect();

		//
		// 업데이트
		//
		if( !mListenerContainer4Mouse.empty() )
		{
			auto target_listener = *mListenerContainer4Mouse.begin();

			//
			// Mouse Cursor Update
			//
			target_listener->UpdateCursor( mMachineInputCollector.GetCursorPoint() );

			//
			// Mouse Key Update
			//
			{
				int i = 0;
				for( const r2bix_input::KeyCodeTypeT k : target_listener->GetObservationKeys() )
				{
					if( mMachineInputCollector.HasInput( k ) )
					{
						target_listener->UpdateKey( i, true );
					}
					else
					{
						target_listener->UpdateKey( i, false );
					}

					++i;
				}
			}
		}
		if( !mListenerContainer4Keyboard.empty() )
		{
			//
			// Keyboard Key Update
			//
			( *mListenerContainer4Keyboard.begin() )->Update(mMachineInputCollector.GetObservationKeyStates());
		}
	}



	void InputManager::AddListener4Mouse( r2bix_input::Listener4Mouse* const listener )
	{
		//
		// 반복 등록 확인
		//
		{
			auto target_itr = std::find( mListenerContainer4Mouse.begin(), mListenerContainer4Mouse.end(), listener );
			if( target_itr != mListenerContainer4Mouse.end() )
			{
				R2ASSERT( false, "이미 등록된 M리스너의 등록을 요청한다." );
				return;
			}
		}

		//
		// Add
		//
		{
			auto pivot_itr = std::find_if( mListenerContainer4Mouse.begin(), mListenerContainer4Mouse.end(), [listener]( const r2bix_input::Listener4Mouse* const l ){
				if( l->GetOrder() <= listener->GetOrder() )
				{
					return true;
				}

				return false;
			} );

			if( mListenerContainer4Mouse.end() == pivot_itr )
			{
				mListenerContainer4Mouse.push_back( listener );
			}
			else
			{
				mListenerContainer4Mouse.insert( pivot_itr, listener );
			}
		}

		//
		// Regist Key
		//
		mMachineInputCollector.AddObservationKeys( listener->GetObservationKeys() );
	}
	void InputManager::RemoveListener4Mouse( r2bix_input::Listener4Mouse* const listener )
	{
		if( nullptr == listener )
		{
			R2ASSERT( false, "삭제 요청된 M리스너가 nullptr 이다." );
			return;
		}

		if( mListenerContainer4Mouse.empty() )
		{
			R2ASSERT( false, "등록된 M리스너가 없는데 삭제를 요청한다." );
			return;
		}

		//
		// Remove
		//
		{
			auto target_itr = std::find( mListenerContainer4Mouse.begin(), mListenerContainer4Mouse.end(), listener );
			if( target_itr == mListenerContainer4Mouse.end() )
			{
				R2ASSERT( false, "등록된적 없는 M리스너의 삭제를 요청한다." );
				return;
			}

			mListenerContainer4Mouse.erase( target_itr );
		}

		//
		// Unregist Key
		//
		mMachineInputCollector.RemoveObservationKeys( listener->GetObservationKeys() );
	}

	void InputManager::AddListener4Keyboard( r2bix_input::Listener4Keyboard* const listener )
	{
		//
		// 반복 등록 확인
		//
		{
			auto target_itr = std::find( mListenerContainer4Keyboard.begin(), mListenerContainer4Keyboard.end(), listener );
			if( target_itr != mListenerContainer4Keyboard.end() )
			{
				R2ASSERT( false, "이미 등록된 K리스너의 등록을 요청한다." );
				return;
			}
		}		

		//
		// Add
		//
		{
			auto pivot_itr = std::find_if( mListenerContainer4Keyboard.begin(), mListenerContainer4Keyboard.end(), [listener]( const r2bix_input::Listener4Keyboard* const l ){
				if( l->GetOrder() <= listener->GetOrder() )
				{
					return true;
				}

				return false;
			} );

			if( mListenerContainer4Keyboard.end() == pivot_itr )
			{
				mListenerContainer4Keyboard.push_back( listener );
			}
			else
			{
				mListenerContainer4Keyboard.insert( pivot_itr, listener );
			}
		}

		//
		// Regist Key
		//
		mMachineInputCollector.AddObservationKeys( listener->GetObservationKeys() );
	}
	void InputManager::RemoveListener4Keyboard( r2bix_input::Listener4Keyboard* const listener )
	{
		if( nullptr == listener )
		{
			R2ASSERT( false, "삭제 요청된 K리스너가 nullptr 이다." );
			return;
		}

		if( mListenerContainer4Keyboard.empty() )
		{
			R2ASSERT( false, "등록된 K리스너가 없는데 삭제를 요청한다." );
			return;
		}

		//
		// Remove
		//
		{
			auto target_itr = std::find( mListenerContainer4Keyboard.begin(), mListenerContainer4Keyboard.end(), listener );
			if( target_itr == mListenerContainer4Keyboard.end() )
			{
				R2ASSERT( false, "등록된적 없는 K리스너의 삭제를 요청한다." );
				return;
			}

			mListenerContainer4Keyboard.erase( target_itr );
		}

		//
		// Unregist Key
		//
		mMachineInputCollector.RemoveObservationKeys( listener->GetObservationKeys() );
	}
}