//
// # 개요
//  - 기능 X
//  - 정점 저장소
//

#pragma once

#include <vector>

#include "r2_Vector3.h"

#include "r2bix_component_Component.h"

namespace r2bix_component
{
	class StaticMeshComponent : public r2bix_component::Component<StaticMeshComponent>
	{
	public:
		using VertexT = r2::Vector3;
		using VerticesT = std::vector<VertexT>;
		using VertexSizeT = typename VerticesT::size_type;

		StaticMeshComponent( r2bix::Director& director, r2bix_node::Node& owner_node );



		//
		//
		//
		const VerticesT& Get() const
		{
			return mVertices;
		}
		const VertexSizeT Size() const
		{
			return mVertices.size();
		}
		bool IsEmpty() const
		{
			return mVertices.empty();
		}

		//
		//
		//
		void SetVertices( const std::initializer_list<VertexT>& vertices );



	private:
		VerticesT mVertices;
	};
}