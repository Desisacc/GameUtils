#pragma once

#include "Hazel/Renderer/VertexArray.h"

namespace Hazel
{

	class OpenGLVertexArray : public VertexArray
	{
	public:
		OpenGLVertexArray();
		virtual ~OpenGLVertexArray();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) override;
		virtual void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) override;

		inline virtual const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const { return m_VertexBuffers; }
		inline virtual const Ref<IndexBuffer>& GetIndexBuffer() const { return m_IndexBuffer; }

		//MODED
		inline virtual std::vector<Ref<VertexBuffer>>& GetVertexBuffers() { return m_VertexBuffers; }
		virtual void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer, uint32_t index) override;
		//MODED
	private:
		uint32_t m_RendererID;
		uint32_t m_VertexBufferIndex = 0;
		std::vector<Ref<VertexBuffer>> m_VertexBuffers;
		Ref<IndexBuffer> m_IndexBuffer;
	};

}