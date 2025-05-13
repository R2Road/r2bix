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
			// �� 1�� ���� ���� �ʿ��ϱ� ������ ���Ǵ� ���̴�.
			// ĳ������ ���� 1�� �� Ÿ�Կ� �´� �ּ� ������ ��ȯ�ȴ�.
			//
			// ���� ����� ��� ù��° ��� class�� �����ϰ� ����ȯ �ϸ� ������ ���� offset �� �����Ѵ�.
			// ���� �������, ���� ������� �Ǻ��� �Ұ��� �ϹǷ� �׻� offset ����� �Ѵ�.
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