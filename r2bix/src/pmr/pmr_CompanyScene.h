#pragma once

#include <memory>

#include "node/r2node_SceneNode.h"

namespace r2base
{
	using NodeUp = std::unique_ptr<class Node>;

	class Director;
}

namespace pmr
{
	class CompanyScene : public r2node::Scene
	{
	private:
		CompanyScene( r2base::Director& director );

	public:
		static r2base::NodeUp Create( r2base::Director& director );

	public:
		void Update() override;
	};
}