#pragma once


#ifdef  SFML
class SFMLEvent;
typedef SFMLEvent InstanciableEvent;
#endif //  SFML


namespace resource
{
	class GameObject;
}

namespace component
{
	class Camera;
}

class AbstractEvent abstract
{
public:
	virtual ~AbstractEvent() = default;

	void WindowEvent(component::Camera* camera);
	
	AbstractEvent* CreateInstance();

protected:
	AbstractEvent() = default;

	virtual void CoreWindowEvent(component::Camera* camera) = 0;


private:
	

};

