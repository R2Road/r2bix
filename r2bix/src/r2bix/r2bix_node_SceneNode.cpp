#include "r2bix_node_SceneNode.h"

#include "r2bix_Director.h"
#include "r2bix_component_TransformComponent.h"

namespace r2bix_node
{
	SceneNode::SceneNode( r2bix::Director& director ) : r2bix_node::Node( director )
		, mCamera( { director.GetScreenBufferSize().GetWidth() / 2, director.GetScreenBufferSize().GetHeight() / 2 }, director.GetScreenBufferSize() )
		, mRenderTarget( director.GetScreenBufferSize().GetWidth(), director.GetScreenBufferSize().GetHeight(), '@' )
	{}

	SceneNodeUp SceneNode::Create( r2bix::Director& director )
	{
		SceneNodeUp ret( new ( std::nothrow ) SceneNode( director ) );
		if( !ret || !ret->Init() )
		{
			ret.reset();
		}

		return ret;
	}

	void SceneNode::Render()
	{
		mRenderTarget.FillCharacterAll( ' ' );
		mRenderTarget.FillColorAll( r2bix::DefaultColorValue );

		r2bix_node::Node::Render( &mCamera, &mRenderTarget, mTransformComponent->GetPosition() );

		mDirector.Write2BackBuffer( &mRenderTarget );
	}
}