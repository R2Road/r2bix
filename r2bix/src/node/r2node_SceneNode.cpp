#include "pch.h"
#include "r2node_SceneNode.h"

#include "base/r2base_Director.h"
#include "component/r2component_TransformComponent.h"

namespace r2node
{
	SceneNode::SceneNode( r2base::Director& director ) : r2base::Node( director )
		, mCamera( { director.GetScreenBufferSize().GetWidth() / 2, director.GetScreenBufferSize().GetHeight() / 2 }, director.GetScreenBufferSize() )
		, mRenderTarget( director.GetScreenBufferSize().GetWidth(), director.GetScreenBufferSize().GetHeight(), '@' )
	{}

	void SceneNode::Render()
	{
		mRenderTarget.FillAll( ' ' );

		r2base::Node::Render( &mCamera, &mRenderTarget, mTransformComponent->GetPosition() );

		mDirector.Write2BackBuffer( &mRenderTarget );
	}
}