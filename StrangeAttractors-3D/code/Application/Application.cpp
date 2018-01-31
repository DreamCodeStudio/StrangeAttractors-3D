#include "Application.h"

Application::Application()
{
	/* Create window, scene manager, and video driver */
	_Device = irr::createDevice(irr::video::EDT_DIRECT3D9, irr::core::dimension2d<irr::u32>(1920, 1080), 16U, false, false, true, 0);
	_Driver = _Device->getVideoDriver();
	_SceneManager = _Device->getSceneManager();

	/* Create camera */
	_Camera = _SceneManager->addCameraSceneNodeMaya(0, -1500, 200, 1500, -1, 100, true);
	_Camera->setTarget(irr::core::vector3df(0, 0, 0));

	/* Create Attractors */
	_Attractors.push_back(new Attractor(_SceneManager, irr::core::vector3df(0, 0, 50)));
	_Attractors.push_back(new Attractor(_SceneManager, irr::core::vector3df(35.35f, 0, -35.35f)));
	_Attractors.push_back(new Attractor(_SceneManager, irr::core::vector3df(-35.35f, 0, -35.35f)));
	_Attractors.push_back(new Attractor(_SceneManager, irr::core::vector3df(0, 50, 0)));

	/* Create Jumper */
	_Jumper = new Jumper(_SceneManager, _Attractors);
}

void Application::Run()
{
	/* Main loop */
	while (_Device->run())
	{
		_Driver->beginScene(true, true, irr::video::SColor(100, 100, 100, 100));

		/* Draw all objects */
		_SceneManager->drawAll();

		_Driver->endScene();		
		_Jumper->Jump();
		
	}
}

bool Application::IsOpen()
{
	return _Device->run();
}