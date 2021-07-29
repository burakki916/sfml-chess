#include "Window.h"

Window::Window() {
	Setup("THE EPIC WINDOW", sf::Vector2u(640, 480));
}
Window::Window(const std::string& l_title, const sf::Vector2u& l_size)
{
	Setup(l_title, l_size);
}
Window::~Window() {
	Destroy();
}
void Window::Close(EventDetails* l_details)
{
	m_isDone = true; 
}
void Window::Setup(const std::string& l_title, const sf::Vector2u& l_size){
	m_FullScreenRes.x = sf::VideoMode::getDesktopMode().width; 
	m_FullScreenRes.y = sf::VideoMode::getDesktopMode().height;
	m_nonFSRes = l_size;
	m_windowSize = m_nonFSRes; 
	m_isFullScreen = false;
	m_windowTitle = l_title;
	m_isDone = false;
	m_isFocused = true; 
	m_eventManager.AddCallback("FullScreen_toggle", &Window::ToggleFullscreen, this); 
	m_eventManager.AddCallback("Window_close", &Window::Close, this); 
	Create(); 

}
void Window::Create() {
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	auto style = (m_isFullScreen ? sf::Style::Fullscreen : sf::Style::Default);
	m_window.create({ m_windowSize.x,m_windowSize.y,32 }, m_windowTitle, style, settings);

}
void Window::Destroy() {
	m_window.close();
}
void Window::Update(){
	sf::Event event;
	while (m_window.pollEvent(event)) {
		if (event.type == sf::Event::LostFocus) {
			m_isFocused = false; 
			m_eventManager.SetFocus(false);
		}
		else if (event.type == sf::Event::GainedFocus) {
			m_isFocused = true;
			m_eventManager.SetFocus(true);
		}
		m_eventManager.HandleEvent(event);
	}
	m_eventManager.Update(); 
}
void Window::ToggleFullscreen(EventDetails* l_details) {
	m_isFullScreen = !m_isFullScreen;
	if (m_isFullScreen) {
		m_windowSize = m_FullScreenRes;
	}
	else {
		m_windowSize = m_nonFSRes; 
	}
	Destroy();
	Create(); 
}
void Window::BeginDraw() { m_window.clear(sf::Color(30,30,30,255)); }
void Window::EndDraw() { m_window.display(); }

bool Window::IsDone() { return m_isDone; }
bool Window::IsFullScreen() { return m_isFullScreen; }
bool Window::IsFocused()
{
	return m_isFocused; 
}
sf::Vector2u* Window::GetWindowSize() { return &m_windowSize; }

void Window::Draw(sf::Drawable& l_drawable) {
	m_window.draw(l_drawable);
}

sf::RenderWindow* Window::GetRenderWindow()
{
	return &m_window; 
}

EventManager* Window::GetEventManager()
{
	return &m_eventManager;
}
