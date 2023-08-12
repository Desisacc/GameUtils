#pragma once

#include <sstream>

#include "Hazel/Core/Base.h"
#include "Hazel/Events/Event.h"

namespace Hazel {

	struct WindowProps
	{
		std::string Title;
		uint32_t Width;
		uint32_t Height;

		WindowProps(const std::string& title = "Hazel Engine",
			uint32_t width = DEFAULT_WINDOW_WIDTH, 
			uint32_t height = DEFAULT_WINDOW_HEIGHT)
			: Title(title), Width(width), Height(height)
		{
		}

		//MODED
		static constexpr uint32_t DEFAULT_WINDOW_WIDTH = 960;
		static constexpr uint32_t DEFAULT_WINDOW_HEIGHT = 540;
		//MODED
	};

	// Interface representing a desktop system based Window
	class Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() = default;

		virtual void OnUpdate() = 0;

		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;

		// Window attributes
		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		virtual void* GetNativeWindow() const = 0;

		static Scope<Window> Create(const WindowProps& props = WindowProps());
	};

}