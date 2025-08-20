#pragma once

#include "r2_assert.hpp"
#include "r2_none_copyable.hpp"

namespace r2
{
	template<typename T>
	class SingletonWithFlag : private NoneCopyable
	{
	protected:
		SingletonWithFlag()
		{
			R2ASSERT( false == mbLive, "" );
			mbLive = true;
		}

		~SingletonWithFlag()
		{
			mbLive = false;
		}

	private:
		static bool mbLive;
	};

	template<typename T>
	bool SingletonWithFlag<T>::mbLive = 0;
}