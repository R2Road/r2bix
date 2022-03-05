#include "pch.h"
#include "r2node_SceneNode.h"

#include "base/r2base_Director.h"

namespace r2node
{
	SceneNode::SceneNode( r2base::Director& director ) : r2base::Node( director )
		, mCamera( { 53, 26 }, { 107, 53 } )
		, mRenderTarget( 107, 53, '@' )
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