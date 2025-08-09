#pragma once

#include "r2_Assert.h"
#include "r2_NoneCopyable.h"

namespace r2
{
	template<typename T>
	class SingletonWithStaticFunction : private NoneCopyable
	{
	public:
		using MyT = T;

	protected:
		SingletonWithStaticFunction()
		{
			//
			// 이 생성자는 GetInstance() 에서 단 한 번 불려야 한다.
			//

			static bool blocked = false;

			R2ASSERT( false == blocked, "" );

			blocked = true;
		}

	public:
		static MyT& GetInstance()
		{
			static MyT instance;
			return instance;
		}
	};
}