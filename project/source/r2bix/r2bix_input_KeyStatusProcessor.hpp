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

		struct KeyStatusInfo
		{
			r2bix_input::eKeyStatus status = r2bix_input::eKeyStatus::None;
			bool changed = false;
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
			return mContainer[key_code].status;
		}
		bool IsPushed( const r2bix_input::eKeyCode key_code ) const
		{
			return ( eKeyStatus::Push == mContainer[key_code].status );
		}
		bool IsRelease( const r2bix_input::eKeyCode key_code ) const
		{
			return ( eKeyStatus::Release == mContainer[key_code].status );
		}
		bool HasInput( const r2bix_input::eKeyCode key_code ) const
		{
			return ( eKeyStatus::None < mContainer[key_code].status );
		}


		//
		//
		//
		void Update( const MachineInputCollector& machine_input_collector );


	private:
		ContainerT mContainer;
	};
}