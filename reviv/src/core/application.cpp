#include"application.h"
#include"renderer/render_manager.h"
#include"physics/physics_manager.h"
#include"core/time.h"

Application* Application::s_Instance(nullptr);

Application::Application(const std::string& applicationName /* = "Reviv App" */ )
    : applicationName(applicationName)
{
    assert(s_Instance == nullptr); // ERROR: can't have more than 1 application

    s_Instance = this;
}

void Application::iOnEvent(Event* event)
{
    switch(event->m_Type)
    {
        case(EventType::EventTypeWindowClose):
            onEventWindowClose(event);
            break;
        case(EventType::EventTypeWindowResize):
            onEventWindowResize(event);
            break;
        default:
            assert(false); // ERROR: event type not recognized by Application class
    }
}

void Application::onEventWindowClose(Event* event)
{
    assert(event->m_Type == EventType::EventTypeWindowClose and event->getName() == "EventWindowClose");
    EventWindowClose* eventWindowClose = (EventWindowClose*)event;

    m_IsRunning = false;
}

void Application::onEventWindowResize(Event* event)
{
    assert(event->m_Type == EventType::EventTypeWindowResize and event->getName() == "EventWindowResize");
    EventWindowResize* eventWindowResize = (EventWindowResize*)event;
}

void Application::initEngine()
{
    window.init(true, false, 1600, 900, applicationName);              // window.init() must go before RenderManager::init()

    Input::disableCursor();        // For the first person 3d camera controller
    Input::useRawMouseMotion();

    PhysicsManager::init();
    RenderManager::init(window.m_Data);
}

void Application::run()
{
    m_IsRunning = true;

    initBeforeEngine();                 // game defined init funciton
    initEngine();                       // engine defined init function
    initAfterEngine();                  // game defined init funciton

    while(m_IsRunning)
    {
        onUpdate();                     // game defined onUpdate function

        Time::onUpdate();
        Input::onUpdate();
        PhysicsManager::onUpdate();
        RenderManager::onUpdate(window.m_Data);
        window.onUpdate();              // update the glfw window
    }

    RenderManager::shutdown();
    window.shutdown();
}

Window* Application::getWindow()
{
    return &window;
}
