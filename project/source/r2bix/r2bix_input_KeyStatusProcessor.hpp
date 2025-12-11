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

		class KeyStatus
		{
		public:
			void Set( const r2bix_input::eKeyStep key_step, const bool changed )
			{
				mInfo = static_cast<KeyStepTypeT>( key_step ) | ( changed ? 0b10000000 : 0b00000000 );
			}

			inline r2bix_input::eKeyStep GetStep() const
			{
				return static_cast<r2bix_input::eKeyStep>( mInfo & 0b00001111 );
			}
			inline bool GetChanged() const
			{
				return ( mInfo & 0b10000000 );
			}

		private:
			r2bix_input::KeyStepTypeT mInfo = 0;
		};
		using ValueT = KeyStatus;
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
		eKeyStep GetStep( const r2bix_input::eKeyCode key_code ) const
		{
			return mContainer[key_code].GetStep();
		}
		bool GetChanged( const r2bix_input::eKeyCode key_code ) const
		{
			return mContainer[key_code].GetChanged();
		}
		bool IsPushed( const r2bix_input::eKeyCode key_code ) const
		{
			return ( eKeyStep::Push == mContainer[key_code].GetStep() );
		}
		bool IsRelease( const r2bix_input::eKeyCode key_code ) const
		{
			return ( eKeyStep::Release == mContainer[key_code].GetStep() );
		}
		bool HasInput( const r2bix_input::eKeyCode key_code ) const
		{
			return ( eKeyStep::None < mContainer[key_code].GetStep() );
		}


		//
		//
		//
		void Update( const MachineInputCollector& machine_input_collector );


	private:
		ContainerT mContainer;
	};
}