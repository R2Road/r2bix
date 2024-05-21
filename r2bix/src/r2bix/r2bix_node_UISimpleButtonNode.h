//
// # 특별한 디자인이 요구되지 않는 단순한 버튼
//  > CustomTexture Component 를 View로 사용
//  > 색상 변경 만으로 버튼 상태에 대응
//

#pragma once

#include "r2bix_node_Node.h"

namespace r2bix
{
	class Director;
}

namespace r2bix_node
{
	class UISimpleButtonNode
	{
	private:
		UISimpleButtonNode() = delete;

	public:
		static r2bix_node::NodeUp Create( r2bix::Director& director );
	};
}