#pragma once
#include"IMemory.h"
#include"eMeshType.h"
#include"Vertices.h"
namespace Mydx
{
	struct Mesh : IMemory
	{
		virtual bool Generate() override;
		virtual void Release() override;

		Mesh(eMeshType meshType, eVertexType vertexType);
		Mesh(const Mesh& rhs);
		~Mesh();

		inline ID3D11Buffer** const GetVertexBufferAddressOf() { return mVertexBuffer.GetAddressOf(); }
		inline ID3D11Buffer** const GetIndexBufferAddressOf() { return mIndexBuffer.GetAddressOf(); }

		friend class PrimitiveGenerator;

	private:

		ComPtr<ID3D11Buffer> mVertexBuffer;
		ComPtr<ID3D11Buffer> mIndexBuffer;

		unsigned int mVertexCount = 0;
		unsigned int mIndexCount = 0;

		eMeshType mMeshType;
		eVertexType mVertexType;

	};
}