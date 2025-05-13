//
// # Version Rule
// - 1.0.0 : 사용 가능
// - 0.1.0 : 사용자가 코드를 바꿀 정도의 변화
// - 0.0.1 : 자잘한 변화
//
// # Last Update		: 2024.05.13 AM.08.53
// # Version			: 1.0.3
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
#include <list>

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
			Disconnect();
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
			if( nullptr == slot )
			{
				return;
			}

			if( mSlotList.end() != get( slot ) )
			{
				return;
			}

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
			slot->mSignal = this;
			mSlotList.push_back( slot );
		}

	public:
		void Disconnect( SlotT* const slot )
		{
			if( nullptr == slot )
			{
				return;
			}

			if( mSlotList.end() == get( slot ) )
			{
				return;
			}

			slot->mSignal = nullptr;

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
			mSlotList.remove( slot );
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