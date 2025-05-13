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
		CaseIterationData( ConstIteratorT itr_begin, ConstIteratorT itr_end, ConstIteratorT itr_current ) :
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
