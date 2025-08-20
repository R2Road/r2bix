//
// # Version Rule
// - 1.0.0 : 사용 가능
// - 0.1.0 : 사용자가 코드를 바꿀 정도의 변화
// - 0.0.1 : 자잘한 변화
//
// # Last Update		: 2025.08.18 PM.07.20
// # Version			: 1.0.0
//

//
// # 개요
// 1. 지정한 begin ~ end 까지 순회 한다.
//

#pragma once

namespace r2
{
	template<typename Container_T>
	class CaseIterationData
	{
	public:
		using ConstIteratorT = typename Container_T::const_iterator;

		CaseIterationData() : mBegin(), mEnd(), mCurrent()
		{}
		explicit CaseIterationData( ConstIteratorT itr_begin, ConstIteratorT itr_end, ConstIteratorT itr_current ) :
			  mBegin( itr_begin )
			, mEnd( itr_end )
			, mCurrent( itr_current )
		{}

		//
		//
		//
		ConstIteratorT begin() const
		{
			return mBegin;
		}
		ConstIteratorT end() const
		{
			return mEnd;
		}
		ConstIteratorT current() const
		{
			return mCurrent;
		}

		//
		//
		//
		bool IsValid() const
		{
			return mCurrent != mEnd;
		}

		//
		//
		//
		void Restart()
		{
			mCurrent = mBegin;
		}
		bool MoveNext()
		{
			if( !IsValid() )
			{
				return false;
			}

			++mCurrent;

			return IsValid();
		}

	private:
		ConstIteratorT mBegin;
		ConstIteratorT mEnd;
		ConstIteratorT mCurrent;
	};
}
