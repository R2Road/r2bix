//
// # Version Rule
// - 1.0.0.0 : 사용 가능
// - 0.1.0.0 : 기능 추가/삭제
// - 0.0.1.0 : 기능 개선/변경
// - 0.0.0.1 : 자잘한 변화
//
// # Last Update		: 2025.05.22 PM.06.40
// # Version			: 1.1.1.0
//

#pragma once

#include <list>

namespace r2
{
	template<typename Value_T, typename Changes_T>
	class ValueAccumulator
	{
	public:
		using ValueT = Value_T;
		using ChangesT = Changes_T;

		using ContainerT = std::list<ChangesT>;

		using MyT = ValueAccumulator<ValueT, ChangesT>;



		ValueAccumulator() noexcept :
			  mTotal()
			, mContainer()
		{}

		//
		// None-Copy
		//
		ValueAccumulator( const ValueAccumulator& ) = delete;
		ValueAccumulator( ValueAccumulator&& ) = delete;
		ValueAccumulator& operator=( const ValueAccumulator& ) = delete;
		ValueAccumulator& operator=( ValueAccumulator&& ) = delete;

		//
		// Getter
		//
		const ValueT& Get() const noexcept
		{
			return mTotal;
		}
		const ContainerT& GetContainer() const noexcept
		{
			return mContainer;
		}

		//
		//
		//
		void Clear() noexcept
		{
			mTotal = {};
			mContainer.clear();
		}
		bool Add( const ChangesT& changes ) noexcept
		{
			for( const auto& i : mContainer )
			{
				if( i == changes )
				{
					return false;
				}
			}

			mContainer.push_back( changes );

			mTotal += ( changes );

			return true;
		}
		bool Remove( const ChangesT& changes )
		{
			auto cur = mContainer.begin();
			const auto end = mContainer.end();
			for( ; end != cur; ++cur )
			{
				if( *cur == changes )
				{
					break;
				}
			}

			if( end == cur )
			{
				return false;
			}

			mContainer.erase( cur );

			mTotal -= ( changes );

			return true;
		}

	private:
		ValueT mTotal;
		ContainerT mContainer;
	};
}
