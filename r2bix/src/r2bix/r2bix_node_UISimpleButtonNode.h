//
// # Ư���� �������� �䱸���� �ʴ� �ܼ��� ��ư
//  > CustomTexture Component �� View�� ���
//  > ���� ���� ������ ��ư ���¿� ����
//

#pragma once

#include "r2bix_node_Node.h"

namespace r2bix
{
	class Director;
}

namespace r2bix_node
{
	class UISimpleButtonNode : public r2bix_node::Node
	{
	private:
		UISimpleButtonNode() = delete;

	public:
		static r2bix_node::NodeUp Create( r2bix::Director& director );
	};
}