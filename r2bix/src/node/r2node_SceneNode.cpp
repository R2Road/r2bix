#include "pch.h"
#include "r2node_SceneNode.h"

#include "base/r2base_Director.h"
#include "component/r2component_TransformComponent.h"

namespace r2node
{
	SceneNode::SceneNode( r2base::Director& director ) : r2base::Node( director )
		, mCamera( { 53, 26 }, director.GetBufferWidth() )
		, mRenderTarget( director.GetBufferWidth().GetWidth(), director.GetBufferWidth().GetHeight(), '@' )
	{}

	void SceneNode::Update( const float delta_time )
	{
		r2base::Node::Update( delta_time );
	}

	void SceneNode::Render()
	{
		mRenderTarget.FillAll( '@' );

		r2base::Node::Render( &mCamera, &mRenderTarget, mTransformComponent->GetPosition() );

		mDirector.Write2BackBuffer( &mRenderTarget );
	}
}