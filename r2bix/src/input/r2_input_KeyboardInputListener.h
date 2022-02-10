#pragma once

#include <vector>

#include "r2_input_Constant.h"

namespace r2_input
{
	class KeyboardInputListener
	{
	public:
		enum class eKeyStatus
		{
			Push,
			Pressed,
			Release,
		};

		KeyboardInputListener();

		//
		// Getter
		//
		bool IsPushed( const std::size_t key_index ) const
		{
			return ( eKeyStatus::Push == mKeyStatusContainer[key_index] );
		}

		//
		//
		//
		void Update();

		std::vector<KeyCodeTypeT> mObservationKeyList;
		std::vector<bool> mKeyFlags;
		std::vector<eKeyStatus> mKeyStatusContainer;
	};
}