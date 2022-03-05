#include "pch.h"
#include "r2node_SceneNode.h"

#include "base/r2base_Director.h"

namespace r2node
{
	SceneNode::SceneNode( r2base::Director& director ) : r2base::Node( director )
		, mCamera( { 55, 26 }, { 111, 54 } )
		, mRenderTarget( 111, 54, '@' )
	{}

	void SceneNode::Update()
	{
	}

	void SceneNode::Render()
	{
		mRenderTarget.FillAll( '@' );

		r2base::Node::Render( &mCamera, &mRenderTarget );

		mDirector.Write2BackBuffer( &mRenderTarget );
	}
}