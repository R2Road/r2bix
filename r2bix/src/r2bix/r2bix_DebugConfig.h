#pragma once

#include "r2_SingletonWithStaticVariable.h"

namespace r2bix
{
	class DebugConfig : public r2::SingletonWithStaticVariable<DebugConfig>
	{
	public:
		struct LabelConfig
		{
			bool bShowPositionPivot = true;
		};



	public:
		const LabelConfig& GetLabelConfig() const
		{
			return mLabelConfig;
		}



	private:
		LabelConfig mLabelConfig;
	};
}