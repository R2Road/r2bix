#pragma once

#include <array>

#include "r2bix_input_Constant.h"

namespace r2bix_input
{
	class MachineInputCollector;

	class KeyStatusProcessor
	{
	public:
		using KeyCodeT = r2bix_input::KeyCodeTypeT;

		class KeyStatusInfo
		{
		public:
			void Set( const r2bix_input::eKeyStatus status, const bool changed )
			{
				mInfo = static_cast<KeyStatusTypeT>( status ) | ( changed ? 0b10000000 : 0b00000000 );
			}

			inline r2bix_input::eKeyStatus GetStatus() const
			{
				return static_cast<r2bix_input::eKeyStatus>( mInfo & 0b00001111 );
			}
			inline bool GetChanged() const
			{
				return ( mInfo & 0b10000000 );
			}

		private:
			r2bix_input::KeyStatusTypeT mInfo = 0;
		};
		using ValueT = KeyStatusInfo;
		using ContainerT = std::array<ValueT, MAX_OBSERVATION_KEY_COUNT>;
		using ConstIteratorT = ContainerT::const_iterator;


		//
		//
		//
		KeyStatusProcessor();


		//
		//
		//
		ConstIteratorT begin() const
		{
			return mContainer.begin();
		}
		ConstIteratorT end() const
		{
			return mContainer.end();
		}


		//
		//
		//
		eKeyStatus GetStatus( const r2bix_input::eKeyCode key_code ) const
		{
			return mContainer[key_code].GetStatus();
		}
		bool GetChanged( const r2bix_input::eKeyCode key_code ) const
		{
			return mContainer[key_code].GetChanged();
		}
		bool IsPushed( const r2bix_input::eKeyCode key_code ) const
		{
			return ( eKeyStatus::Push == mContainer[key_code].GetStatus() );
		}
		bool IsRelease( const r2bix_input::eKeyCode key_code ) const
		{
			return ( eKeyStatus::Release == mContainer[key_code].GetStatus() );
		}
		bool HasInput( const r2bix_input::eKeyCode key_code ) const
		{
			return ( eKeyStatus::None < mContainer[key_code].GetStatus() );
		}


		//
		//
		//
		void Update( const MachineInputCollector& machine_input_collector );


	private:
		ContainerT mContainer;
	};
}