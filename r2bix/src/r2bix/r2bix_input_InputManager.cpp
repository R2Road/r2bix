#include "r2bix_input_InputManager.h"

#include <numeric>

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

			//
			// Mouse Cursor Update
			// > UpdateCursor 함수가 true 를 반환하면 이후 호출은 더미 Cursor값을 준다.
			//
			{
				if( mMachineInputCollector.IsMouseMoved() )
				{
					bool bKeepGoing = true;
					int i = 0;
					for( r2bix_input::Listener4Mouse* l : mListenerContainer4Mouse )
					{
						if( !l->IsActivated() )
						{
							l->UpdateCursor( CursorPoint{ std::numeric_limits<int>::min(), std::numeric_limits<int>::min() } );
							continue;
						}

						if( bKeepGoing )
						{
							if( l->UpdateCursor( mMachineInputCollector.GetCursorPoint() ) )
							{
								bKeepGoing = false;
							}
						}
						else
						{
							l->UpdateCursor( CursorPoint{ std::numeric_limits<int>::min(), std::numeric_limits<int>::min() } );
						}

						++i;
					}
				}
			}

			//
			// Mouse Key Update
			//
			auto target_listener = *mListenerContainer4Mouse.begin();
			{
				int i = 0;
				for( const r2bix_input::ObservationKey o : target_listener->GetObservationKeyContainer() )
				{
					target_listener->UpdateKey( i, mMachineInputCollector.HasInput( o.key_code ) );

					++i;
				}
			}
		}
		if( !mListenerContainer4Keyboard.empty() )
		{
			auto target_listener = *mListenerContainer4Keyboard.begin();

			//
			// Keyboard Key Update
			//
			int i = 0;
			for( const r2bix_input::ObservationKey o : target_listener->GetObservationKeyContainer() )
			{
				target_listener->UpdateKey( i, mMachineInputCollector.HasInput( o.key_code ) );

				++i;
			}
		}
	}



	void InputManager::ClearListener()
	{
		mListenerContainer4Mouse.clear();
		mListenerContainer4Keyboard.clear();
	}

	void InputManager::AddListener( r2bix_input::Listener4Mouse* const listener )
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
		mMachineInputCollector.AddObservationKeys( listener->GetObservationKeyContainer() );
	}
	void InputManager::RemoveListener( r2bix_input::Listener4Mouse* const listener )
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
		mMachineInputCollector.RemoveObservationKeys( listener->GetObservationKeyContainer() );
	}

	void InputManager::AddListener( r2bix_input::Listener4Keyboard* const listener )
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
		mMachineInputCollector.AddObservationKeys( listener->GetObservationKeyContainer() );
	}
	void InputManager::RemoveListener( r2bix_input::Listener4Keyboard* const listener )
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
		mMachineInputCollector.RemoveObservationKeys( listener->GetObservationKeyContainer() );
	}
}