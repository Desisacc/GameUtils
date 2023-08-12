#pragma once

#include <memory>
#include "Hazel/Renderer/Buffer.h"

namespace Hazel
{

	class VertexArray
	{
	public:
		virtual ~VertexArray() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) = 0;
		virtual void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) = 0;

		virtual const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const = 0;
		virtual const Ref<IndexBuffer>& GetIndexBuffer() const = 0;

		//MODED
		virtual std::vector<Ref<VertexBuffer>>& GetVertexBuffers() = 0;
		virtual void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer, uint32_t index) = 0;
		//MODED

		static Ref<VertexArray> Create();
	};

}