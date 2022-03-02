#pragma once

#include <memory>

namespace r2node
{
	using SceneNodeUp = std::unique_ptr<class SceneNode>;
}

namespace r2base
{
	class Director
	{
	public:
		Director();

		void Setup( r2node::SceneNodeUp node );

		void Update();

		void RequestAbort() { mbAbort = true; }

	private:
		bool mbAbort;
		r2node::SceneNodeUp mSceneNode;
	};
}