#include <mutex>
#include <memory>

#include "../../GameObject.h"
#include "AbstractEvent.h"
#include "../../Camera.h"

#ifdef SFML
	#include "SFMLEvent.h"
	
#endif // SFML

	void AbstractEvent::WindowEvent(component::Camera* camera)
	{
		CoreWindowEvent(camera);
	}

