#include "pch.h"
#include "r2render_Renderer.h"

#include <stdlib.h>

#include "r2render_iRenderable.h"

namespace r2render
{
	Renderer::Renderer() : mCamera( nullptr ), mContainer()
	{}

	void Renderer::Clear()
	{
		mCamera = nullptr;
		mContainer.clear();
	}
	void Renderer::Add( iRenderable* const renderable )
	{
		mContainer.push_back( renderable );
	}

	void Renderer::Draw()
	{
		system( "cls" );

		for( auto r : mContainer )
		{
			r->Render( mCamera, nullptr );
		}
	}
}