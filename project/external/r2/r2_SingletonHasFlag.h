#pragma once

#include "r2_Assert.h"
#include "r2_NoneCopyable.h"

namespace r2
{
	template<typename T>
	class SingletonHasFlag : private NoneCopyable
	{
	protected:
		SingletonHasFlag()
		{
			R2ASSERT( false == mbLive, "" );
			mbLive = true;
		}

		~SingletonHasFlag()
		{
			mbLive = false;
		}

	private:
		static bool mbLive;
	};

	template<typename T>
	bool SingletonHasFlag<T>::mbLive = 0;
}