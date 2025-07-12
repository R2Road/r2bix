//
// # ����
//  - 3D ������ ������ ������ ���� Static Mesh�� �׸���.
//

#pragma once

#include "r2bix_component_Component.h"

namespace r2bix_component
{
	class StaticMeshComponent;

	class MeshRendererComponent : public r2bix_component::Component<MeshRendererComponent>
	{
	public:
		MeshRendererComponent( r2bix::Director& director, r2bix_node::Node& owner_node );



		//
		// Override
		//
		void Render( const r2bix_render::Camera* const camera, r2bix_render::iRenderTarget* const render_target, r2::PointInt offset ) override;



		//
		//
		//
		void SetStaticMesh( StaticMeshComponent* const static_mesh_component )
		{
			mStaticMeshComponent = static_mesh_component;
		}
		StaticMeshComponent* GetStaticMesh() const
		{
			return mStaticMeshComponent;
		}



	private:
		StaticMeshComponent* mStaticMeshComponent;
	};
}