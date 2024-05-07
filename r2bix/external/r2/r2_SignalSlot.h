//
// # Version Rule
// - 1.0.0 : ��� ����
// - 0.1.0 : ����ڰ� �ڵ带 �ٲ� ������ ��ȭ
// - 0.0.1 : ������ ��ȭ
//
// # Last Update		: 2024.05.07 PM.04.59
// # Version			: 1.0.1
//

//
// # Signal
//  1. Slot( callback ) List ����
//  2. Signal �� ���ŵ� �� Slot�� ������ ���� ����� �Ѵ�.
//

//
// # Slot
//  1. callback ����
//  2. Slot �� ���ŵ� �� Signal�� ���� ������ ��û�Ѵ�.
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
		Slot() : mSignal( nullptr ), mCallback( []( ARGS_T ... ) { return RETURN_T(); } )
		{}

		explicit Slot( const CallbackT& call_back ) : mSignal( nullptr ), mCallback(call_back) {}
		~Slot()
		{
			R2ASSERT( nullptr == mSignal, "Slot : Hey Call Disconnect()" );
		}

		template<typename OWNER_T>
		explicit Slot( OWNER_T* o, RETURN_T( OWNER_T::* c )( ARGS_T ... ) ) : mSignal( nullptr ), mCallback(
			[o, c]( ARGS_T ... args )
			{
				return ( o->*c )( args ... );
			}
		) {}


	private:
		// none copy
		Slot( const Slot& ) = delete;
		Slot( Slot&& ) = delete;
		Slot& operator=( const Slot& ) = delete;
		Slot& operator=( Slot&& ) = delete;


	private:
		void Connect( SignalT* const signal )
		{
			mSignal = signal;
		}
	public:
		void Disconnect()
		{
			if( nullptr == mSignal )
			{
				return;
			}

			mSignal->Disconnect( this );

			// mSignal �� �ʱ�ȭ�� Signal::Disconnect �ȿ��� ���ش�.
		}


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


		RETURN_T Do( ARGS_T ... args )
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


		ConstIteratorT begin() const
		{
			return mSlotList.cbegin();
		}
		ConstIteratorT end() const
		{
			return mSlotList.cend();
		}


		void Connect( SlotT* const slot )
		{
			if( mSlotList.end() != get( slot ) )
			{
				return;
			}

			slot->Connect( this );
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