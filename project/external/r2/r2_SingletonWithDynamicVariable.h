#pragma once

#include "r2_Assert.h"
#include "r2_NoneCopyable.h"

namespace r2
{
	template<typename T>
	class SingletonWithDynamicVariable : private NoneCopyable
	{
	public:
		using ValueT = T;

	protected:
		SingletonWithDynamicVariable()
		{
			R2ASSERT( nullptr == mpInstance, "" );

			//
			// 값 1은 그저 값이 필요하기 때문에 사용되는 것이다.
			// 캐스팅을 통해 1이 각 타입에 맞는 주소 값으로 변환된다.
			//
			// 다중 상속의 경우 첫번째 상속 class를 제외하고 형변환 하면 포인터 간에 offset 이 존재한다.
			// 단일 상속인지, 다중 상속인지 판별이 불가능 하므로 항상 offset 계산을 한다.
			//
			const long long offset = ( (long long)( ValueT* )1 ) - ( (long long)( SingletonWithDynamicVariable<ValueT>* )( ValueT* )1 );
			mpInstance = static_cast<ValueT*>( this + offset );
		}

		~SingletonWithDynamicVariable()
		{
			mpInstance = nullptr;
		}

	public:
		static ValueT* GetInstance()
		{
			R2ASSERT( nullptr != mpInstance, "" );
			return mpInstance;
		}

	private:
		static ValueT* mpInstance;
	};

	template<typename T>
	T* SingletonWithDynamicVariable<T>::mpInstance = 0;
}