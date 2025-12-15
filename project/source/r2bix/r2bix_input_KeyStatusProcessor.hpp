#pragma once

#include <array>

#include "r2bix_input_KeyStatus.hpp"

namespace r2bix_input
{
	class MachineInputCollector;

	class KeyStatusProcessor
	{
	public:
		using KeyCodeT = r2bix_input::KeyCodeTypeT;

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
		eKeyStep GetStep( const KeyCodeT key_code ) const
		{
			return mContainer[key_code].GetStep();
		}
		bool GetChanged( const KeyCodeT key_code ) const
		{
			return mContainer[key_code].GetChanged();
		}
		bool IsPushed( const KeyCodeT key_code ) const
		{
			return ( eKeyStep::Push == mContainer[key_code].GetStep() );
		}
		bool IsRelease( const KeyCodeT key_code ) const
		{
			return ( eKeyStep::Release == mContainer[key_code].GetStep() );
		}
		bool HasInput( const KeyCodeT key_code ) const
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