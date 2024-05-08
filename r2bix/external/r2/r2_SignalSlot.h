//
// # Version Rule
// - 1.0.0 : 사용 가능
// - 0.1.0 : 사용자가 코드를 바꿀 정도의 변화
// - 0.0.1 : 자잘한 변화
//
// # Last Update		: 2024.05.07 PM.04.59
// # Version			: 1.0.1
//

//
// # Signal
//  1. Slot( callback ) List 관리
//  2. Signal 이 제거될 때 Slot과 연결을 해제 해줘야 한다.
//

//
// # Slot
//  1. callback 보관
//  2. Slot 이 제거될 때 Signal에 연결 해제를 요청한다.
//

#pragma once

#include <functional>

#include "r2_Assert.h"

namespace r2
{
	template<typename RETURN_T, typename ... ARGS_T>
	class Signal;



	template<typename RETURN_T, typename ... ARGS_T>
	class Slot
	{
	public:
		friend class Signal<RETURN_T, ARGS_T ...>;

		using SignalT = Signal<RETURN_T, ARGS_T ...>;
		using CallbackT = std::function<RETURN_T( ARGS_T ... )>;


	public:
		Slot() : mSignal( nullptr ), mCallback()
		{
			ClearCallback();
		}
		explicit Slot( const CallbackT& call_back ) : mSignal( nullptr ), mCallback( call_back )
		{}
		template<typename OWNER_T>
		explicit Slot( OWNER_T* o, RETURN_T( OWNER_T::* c )( ARGS_T ... ) ) : mSignal( nullptr ), mCallback(
			[o, c]( ARGS_T ... args )
			{
				return ( o->*c )( args ... );
			} )
		{}

		~Slot()
		{
			R2ASSERT( nullptr == mSignal, "Slot : Hey Call Disconnect()" );
		}


		//
		// None Copy
		//
	private:
		Slot( const Slot& ) = delete;
		Slot( Slot&& ) = delete;
		Slot& operator=( const Slot& ) = delete;
		Slot& operator=( Slot&& ) = delete;


		//
		// Disconnect
		//  > mSignal의 할당, 초기화는 Signal::Disconnect 안에서 해준다.
		//
	public:
		void Disconnect()
		{
			if( nullptr == mSignal )
			{
				return;
			}

			mSignal->Disconnect( this );
		}


		//
		// Callback
		//
		void SetCallback( const CallbackT call_back )
		{
			mCallback = call_back;
		}
		template<typename OWNER_T>
		void SetCallback( OWNER_T* o, RETURN_T( OWNER_T::* c )( ARGS_T ... ) )
		{
			mCallback = [o, c]( ARGS_T ... args )
			{
				return ( o->*c )( args ... );
			};
		}

		void ClearCallback()
		{
			mCallback = []( ARGS_T ... ) { return RETURN_T(); };
		}


		//
		//
		//
		inline RETURN_T Do( ARGS_T ... args )
		{
			return mCallback( args ... );
		}


	private:
		SignalT* mSignal;
		CallbackT mCallback;
	};



	template<typename RETURN_T, typename ... ARGS_T>
	class Signal
	{
	public:
		using SlotT = Slot<RETURN_T, ARGS_T ...>;
		using ContainerT = std::list<SlotT*>;
		using IteratorT = typename ContainerT::iterator;
		using ConstIteratorT = typename ContainerT::const_iterator;


		Signal() : mSlotList()
		{}
		~Signal()
		{
			DisconnectAll();
		}


		//
		// Iteration
		//
		ConstIteratorT begin() const
		{
			return mSlotList.cbegin();
		}
		ConstIteratorT end() const
		{
			return mSlotList.cend();
		}


		//
		// Connection
		//
		void Connect( SlotT* const slot )
		{
			if( mSlotList.end() != get( slot ) )
			{
				return;
			}

			slot->mSignal = this;
			mSlotList.push_back( slot );
		}
		void Disconnect( SlotT* const slot )
		{
			IteratorT itor = get( slot );
			if( mSlotList.end() == itor )
			{
				return;
			}

			( *itor )->mSignal = nullptr;
			mSlotList.erase( itor );
		}
		void DisconnectAll()
		{
			for( auto& slot : mSlotList )
			{
				slot->mSignal = nullptr;
			}
			mSlotList.clear();
		}
	private:
		IteratorT get( const SlotT* const slot )
		{
			for( auto cur = mSlotList.begin(), end = mSlotList.end(); end != cur; ++cur )
			{
				if( slot == *cur )
				{
					return cur;
				}
			}

			return mSlotList.end();
		}


	public:
		void Emit( ARGS_T ... args )
		{
			for( auto& slot : mSlotList )
			{
				slot->mCallback( args... );
			}
		}


		std::size_t Count() const
		{
			return mSlotList.size();
		}


	private:
		ContainerT mSlotList;
	};
}