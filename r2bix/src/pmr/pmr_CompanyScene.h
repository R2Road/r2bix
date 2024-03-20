#pragma once

#include <memory>

#include "r2bix_node_Node.h"

namespace pmr
{
	class CompanyScene : public r2bix_node::Node
	{
	private:
		CompanyScene( r2bix::Director& director );

	public:
		static const char* const GetTitle() { return "Game : Mini Rogue( To do )"; }
		static r2bix_node::NodeUp Create( r2bix::Director& director );

	private:
		bool Init() override;
	public:
		void Update( const float delta_time ) override;
	};
}