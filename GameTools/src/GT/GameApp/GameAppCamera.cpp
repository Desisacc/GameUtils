#include "gtpch.h"
#include "GT/GameApp/GameAppCamera.h"

namespace GT {

	namespace DefaultCameras {

		void CameraFreeMove::OnUpdate(const CameraOnUpdateArguments& cameraOnUpdateArguments)
		{
			const auto& ts = cameraOnUpdateArguments.ts;

			const bool isKeyPressed_W = Hazel::Input::IsKeyPressed(Hazel::Key::W);
			const bool isKeyPressed_S = Hazel::Input::IsKeyPressed(Hazel::Key::S);
			const bool isKeyPressed_A = Hazel::Input::IsKeyPressed(Hazel::Key::A);
			const bool isKeyPressed_D = Hazel::Input::IsKeyPressed(Hazel::Key::D);

			const bool isKeyPressed_Shift = Hazel::Input::IsKeyPressed(Hazel::Key::LeftShift);

			m_Speed = isKeyPressed_Shift ? SLOW_SPEED : FAST_SPEED;
			const float& cameraSpeed = m_Speed;

			glm::vec3 cameraPosition = m_Camera.GetPosition();

			if (isKeyPressed_W && !isKeyPressed_S)
				cameraPosition.y += cameraSpeed * ts;
			else if (!isKeyPressed_W && isKeyPressed_S)
				cameraPosition.y -= cameraSpeed * ts;

			if (isKeyPressed_D && !isKeyPressed_A)
				cameraPosition.x += cameraSpeed * ts;
			else if (isKeyPressed_A && !isKeyPressed_D)
				cameraPosition.x -= cameraSpeed * ts;

			// Since setting a max value for a limit can result in a negative number, it is important to first check for 
			// the max value and then the min value 
			cameraPosition.x = std::min((float)GlobalData::GetMapWidth() - (float)GlobalData::GetWindowWidth(), cameraPosition.x);
			cameraPosition.x = std::max(0.0f, cameraPosition.x);

			cameraPosition.y = std::min((float)GlobalData::GetMapHeight() - (float)GlobalData::GetWindowHeight(), cameraPosition.y);
			cameraPosition.y = std::max(0.0f, cameraPosition.y);

			m_Camera.SetPosition(cameraPosition);
		}

		void CameraFocusedOnObject::OnUpdate(const CameraOnUpdateArguments& cameraOnUpdateArguments)
		{
			const auto& objectToFollowPosition = cameraOnUpdateArguments.ObjectToFollowPosition;
			const auto& objectToFollowSize = cameraOnUpdateArguments.ObjectToFollowSize;
			Vector3<float> cameraPosition = { 0.0f, 0.0f, 0.0f };

			// Moves so that player is in the middle of the screen in the x-axis and half a tile above the screen bottom
			cameraPosition.x = objectToFollowPosition.x - (float)GlobalData::GetWindowWidth() / 2.0f - objectToFollowSize.x / 2.0f;
			cameraPosition.y = objectToFollowPosition.y - objectToFollowSize.y / 2.0f;

			// Minimums and maximums for camera
			cameraPosition.x = std::max(cameraPosition.x, 0.0f);
			cameraPosition.x = std::min(cameraPosition.x, std::max(0.0f, (float)GlobalData::GetMapWidth() - (float)GlobalData::GetWindowWidth()));

			cameraPosition.y = std::max(cameraPosition.y, 0.0f);
			cameraPosition.y = std::min(cameraPosition.y, std::max(0.0f, (float)GlobalData::GetMapHeight() - (float)GlobalData::GetWindowHeight()));

			cameraPosition.z = objectToFollowPosition.z;

			m_Camera.SetPosition({ cameraPosition.x, cameraPosition.y, cameraPosition.z });
		}

	}

}