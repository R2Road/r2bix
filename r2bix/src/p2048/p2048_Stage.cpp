#include "pch.h"
#include "p2048_Stage.h"

namespace p2048
{
	Stage::Stage( const uint32_t width, const uint32_t height ) :
		mGridIndexConverter( width, height )
		, mContainer( width * height, -1 )
	{}
}