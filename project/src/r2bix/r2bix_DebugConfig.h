#pragma once

#include "r2_SingletonWithStaticFunction.h"

namespace r2bix
{
	class DebugConfig : public r2::SingletonWithStaticFunction<DebugConfig>
	{
	public:
		struct RenderConfig
		{
			bool bShowPositionPivot = true;
		};



		//
		//
		//
		void SetRenderConfig( const RenderConfig& label_config )
		{
			mLabelConfig = label_config;
		}
		const RenderConfig& GetRenderConfig() const
		{
			return mLabelConfig;
		}



	private:
		RenderConfig mLabelConfig;
	};
}