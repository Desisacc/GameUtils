#include "MouseGame/MouseGameApp.h"

#include "GT/Utils/GlobalData.h"

#include "MouseGame/MouseGameObjects/GlobalMouseGameObjects.h"

namespace MouseGameLayer {

	/*void MouseGameApp::InitButtons()
	{
		{
			Button& buttonOne = m_Buttons.emplace_back();
			GT::SpriteSheet::InitializerForSpriteSheet buttonOneSpriteSheetData;
			buttonOneSpriteSheetData.Filepath = "assets/textures/EndButton.png";
			buttonOneSpriteSheetData.AnimationsInfo.emplace_back("Default", 0);
			
			buttonOne.Init({ 0.0f, 0.0f }, { 200.0f, 100.0f }, 0.0f, buttonOneSpriteSheetData, []()
			{
				HZ_INFO("Hi");
			});
		}

		{
			Button& buttonTwo = m_Buttons.emplace_back();
			GT::SpriteSheet::InitializerForSpriteSheet buttonTwoSpriteSheetData;
			buttonTwoSpriteSheetData.Filepath = "assets/textures/StartButton.png";
			buttonTwoSpriteSheetData.AnimationsInfo.emplace_back("Default", 0);

			buttonTwo.Init({ 0.0f, GT::GlobalData::GetMapHeight() - 100.0f }, { 200.0f, 100.0f }, 0.0f, buttonTwoSpriteSheetData, [this]()
			{
				//auto& testPositional = m_DragableObject.Get<GT::Component::Positional>();
				//testPositional.SetHorizontally(0.0f);
				//testPositional.SetVertically(0.0f);
			});
		}
	}*/

	/*class TestClass : public GT::Component::ElementInContainer<TestClass, GT::ObjectInSystemComponent>
	{
	public:
		TestClass() = default;

		TestClass(const TestClass& other) noexcept
		{
			ElementId::CopyIds(GetElementId(), other.GetElementId());

			Number = other.Number;
		}
		TestClass& operator=(const TestClass& other) noexcept
		{
			if (this != &other)
				return *this;

			ElementId::CopyIds(GetElementId(), other.GetElementId());

			Number = other.Number;

			return *this;
		}
		TestClass(TestClass&& other) noexcept
		{
			ElementId::MoveIds(GetElementId(), other.GetElementId());

			Number = other.Number;
			other.Number = 0;
		}
		TestClass& operator=(TestClass&& other) noexcept
		{
			ElementId::MoveIds(GetElementId(), other.GetElementId());

			Number = other.Number;
			other.Number = 0;
			return *this;
		}

		int Number = 0;
	};

	void Test()
	{
		std::vector<TestClass> vectorTest;
		
		auto& one = vectorTest.emplace_back();
		one.Get<GT::ObjectInSystemComponent>().InitObjectId(1);
		one.Number = 1;

		auto& two = vectorTest.emplace_back();
		two.Get<GT::ObjectInSystemComponent>().InitObjectId(2);
		two.Number = 2;
	}*/

	/*template<typename T>
	class BaseClass
	{
	protected:
		void dosmtg() 
		{ 
			HZ_TRACE("{0}", typeid(T).name());
		}
	};

	class DerivedClass : public BaseClass<int>, public BaseClass<float>
	{
	public:
		template<typename T>
		void caller()
		{
			// "this->" is optional but it might help to make it more clear
			this->BaseClass<T>::dosmtg();
		}
	};

	void Test()
	{
		DerivedClass derivedClass;
		derivedClass.caller<int>();
		derivedClass.caller<float>();
	}*/

	struct TestComponent
	{
		int DataOne = 10;
		float DataTwo = 20.0f;
	};
	struct TestComponent2
	{
		double DataThree = 30.0;
	};
	class TestClass : public GT::Component::GroupedLocalComponentVector<TestClass, TestComponent, TestComponent2>
	{
	public:
		/*TestClass() = default;
		~TestClass() = default;
		TestClass(const TestClass& other) noexcept
		{
			CopyComponents(other);
		}
		TestClass& operator=(const TestClass& other) noexcept
		{
			if (this != &other)
			{
				CopyComponents(other);
			}

			return *this;
		}
		TestClass(TestClass&& other) noexcept
		{
			MoveComponents(other);
		}
		TestClass& operator=(TestClass&& other) noexcept
		{
			MoveComponents(other);

			return *this;
		}*/
	};

	inline void Test()
	{
		TestClass myObject;
		auto& comp1 = myObject.Get<TestComponent>();
		auto& comp2 = myObject.Get<TestComponent2>();

		/*std::vector<TestClass> myVec;
		{
			myVec.emplace_back().Get<TestComponent>().DataOne = 10;
			myVec.emplace_back().Get<TestComponent>().DataOne = 20;
			myVec.emplace_back().Get<TestComponent>().DataOne = 30;
		}

		for (auto& e : myVec)
		{
			auto& comp = e.Get<TestComponent>();
			HZ_INFO("");
		}

		myVec.erase(myVec.begin() + 1);

		for (auto& e : myVec)
		{
			auto& comp = e.Get<TestComponent>();
			HZ_INFO("");
		}*/
	}

	void MouseGameApp::Init()
	{
		Test();

		Map::InitMap();
		Inventory::Init();
	}

	void MouseGameApp::Destruct()
	{
		GT::LoadingSystem<Room>::UnloadObjects();
		GT::LoadingSystem<Item>::UnloadObjects();
		GT::LoadingSystem<Interactable>::UnloadObjects();
		GT::LoadingSystem<GT::SpriteSheet>::UnloadObjects();
	}

	void MouseGameApp::OnUpdate(Hazel::Timestep ts)
	{
		GT::Component::GlobalComponentVector<GT::Component::ObjectRenderable>::UpdateComponentVector([ts](GT::Component::ObjectRenderable& objectRenderable) 
			{ objectRenderable.OnUpdate(ts); });

		Map::UpdateMap(ts);
		Inventory::OnUpdate(ts);
	}

	void MouseGameApp::OnRender()
	{
		Map::RenderMap();
		Inventory::OnRender();
	}

	void MouseGameApp::OnEvent(Hazel::Event& e)
	{
		Hazel::EventDispatcher dispatcher(e);
		dispatcher.Dispatch<Hazel::MouseButtonPressedEvent>(HZ_BIND_EVENT_FN(GT::BaseGameApp::OnMouseClickEvent));
	}

}