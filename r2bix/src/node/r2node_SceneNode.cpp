#include "pch.h"
#include "r2node_SceneNode.h"

#include "base/r2base_Director.h"

namespace r2node
{
	SceneNode::SceneNode( r2base::Director& director ) : r2base::Node( director )
		, mCamera( { 25, 25 }, { 50, 50 } )
		, mRenderTarget( 50, 50, '@' )
	{}

	void SceneNode::Update()
	{
	}

	void SceneNode::Render()
	{
		r2base::Node::Render( &mCamera, &mRenderTarget );
	}
}