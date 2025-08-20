#pragma once

#include "r2_assert.hpp"
#include "r2_none_copyable.hpp"

namespace r2
{
	template<typename T>
	class SingletonWithStaticMethod : private NoneCopyable
	{
	public:
		using MyT = T;

	protected:
		SingletonWithStaticMethod()
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