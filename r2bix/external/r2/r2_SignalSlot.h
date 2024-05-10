//
// # Version Rule
// - 1.0.0 : ��� ����
// - 0.1.0 : ����ڰ� �ڵ带 �ٲ� ������ ��ȭ
// - 0.0.1 : ������ ��ȭ
//
// # Last Update		: 2024.05.10 PM.03.30
// # Version			: 1.0.2
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
#include <list>

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
		//  > mSignal�� �Ҵ�, �ʱ�ȭ�� Signal::Disconnect �ȿ��� ���ش�.
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
		using SizeT = typename ContainerT::size_type;



		Signal() : mSlotList(), mbEmit( false ), mDefarredConnectContainer(), mDefarredDisconnectContainer()
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
	public:
		void Connect( SlotT* const slot )
		{
			if( mbEmit )
			{
				mDefarredConnectContainer.push_back( slot );
			}
			else
			{
				connectProcess( slot );
			}
		}
	private:
		void connectProcess( SlotT* const slot )
		{
			if( mSlotList.end() != get( slot ) )
			{
				return;
			}

			slot->mSignal = this;
			mSlotList.push_back( slot );
		}

	public:
		void Disconnect( SlotT* const slot )
		{
			if( mbEmit )
			{
				mDefarredDisconnectContainer.push_back( slot );
			}
			else
			{
				disconnectProcess( slot );
			}
		}
	private:
		void disconnectProcess( SlotT* const slot )
		{
			IteratorT itor = get( slot );
			if( mSlotList.end() == itor )
			{
				return;
			}

			( *itor )->mSignal = nullptr;
			mSlotList.erase( itor );
		}
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
		void DisconnectAll()
		{
			for( auto& slot : mSlotList )
			{
				slot->mSignal = nullptr;
			}
			mSlotList.clear();
		}



		void Emit( ARGS_T ... args )
		{
			mbEmit = true;

			for( auto& slot : mSlotList )
			{
				slot->mCallback( args... );
			}

			mbEmit = false;

			//
			// Defarred Connection
			//
			for( const auto slot : mDefarredConnectContainer )
			{
				connectProcess( slot );
			}
			for( const auto slot : mDefarredDisconnectContainer )
			{
				disconnectProcess( slot );
			}
		}



		SizeT Count() const
		{
			return mSlotList.size();
		}



	private:
		ContainerT mSlotList;

		bool mbEmit;
		ContainerT mDefarredConnectContainer;
		ContainerT mDefarredDisconnectContainer;
	};
}