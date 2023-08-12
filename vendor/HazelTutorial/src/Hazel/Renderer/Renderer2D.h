#pragma once

#include "Hazel/Renderer/OrthographicCamera.h"

#include "Hazel/Renderer/Texture.h"

#include "Hazel/Renderer/Camera.h"

namespace Hazel
{

	class Renderer2D
	{
	//MODED
	public:
		static constexpr std::array<glm::vec2, 4> DEFAULT_TEX_COORDS = 
		{ 
			glm::vec2{ 0.0f, 0.0f },
			glm::vec2{ 1.0f, 0.0f },
			glm::vec2{ 1.0f, 1.0f },
			glm::vec2{ 0.0f, 1.0f } 
		};
	//MODED
	public:
		static void Init();
		static void Shutdown();

		static void BeginScene(const Camera& camera, const glm::mat4& transform);
		static void BeginScene(const OrthographicCamera& camera); // TODO: Remove
		static void EndScene();
		static void Flush();

		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);
		//MODED (added textureLimits)
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, Ref<Texture2D> texture, const std::array<glm::vec2, 4>& textureCoords = DEFAULT_TEX_COORDS, float tilingFactor = 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f));
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, Ref<Texture2D> texture, const std::array<glm::vec2, 4>& textureCoords = DEFAULT_TEX_COORDS, float tilingFactor = 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f));
		//MODED (added textureLimits)

		static void DrawQuad(const glm::mat4& transform, const glm::vec4& color);
		//MODED (added textureLimits)
		static void DrawQuad(const glm::mat4& transform, const Ref<Texture2D>& texture, const std::array<glm::vec2, 4>& textureCoords = DEFAULT_TEX_COORDS, float tilingFactor = 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f));
		//MODED (added textureLimits)

		static void DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec4& color);
		static void DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const glm::vec4& color);
		//MODED (added textureLimits)
		static void DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, Ref<Texture2D> texture, const std::array<glm::vec2, 4>& textureCoords = DEFAULT_TEX_COORDS, float tilingFactor = 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f));
		static void DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, Ref<Texture2D> texture, const std::array<glm::vec2, 4>& textureCoords = DEFAULT_TEX_COORDS, float tilingFactor = 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f));
		//MODED (added textureLimits)

		// Stats
		struct Statistics
		{
			uint32_t DrawCalls = 0;
			uint32_t QuadCount = 0;

			uint32_t GetTotalVertexCount() const { return QuadCount * 4; }
			uint32_t GetTotalIndexCount() const { return QuadCount * 6; }
		};
		static void ResetStats();
		static Statistics GetStats();
	private:
		static void StartBatch();
		static void NextBatch();
		//MODED
	public:
		enum class QuadCenter : uint32_t
		{
			Center = 0, LeftBottom, RightBottom, RightTop, LeftTop
		};
		static QuadCenter GetQuadCenter() { return s_CurrentQuadCenter; }
		static void SetQuadCenter(QuadCenter quadCenter);
	private:
		static QuadCenter s_CurrentQuadCenter;
		//MODED
	};

}