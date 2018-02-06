#include "Application.h"

Application::Application()
{
	/* Create window, scene manager, and video driver */
	_Device = irr::createDevice(irr::video::EDT_DIRECT3D9, irr::core::dimension2d<irr::u32>(1920, 1080), 16U, false, false, false, 0);
	_Driver = _Device->getVideoDriver();
	_SceneManager = _Device->getSceneManager();

	/* Create camera */
	_FrozenCamera = _SceneManager->addCameraSceneNode();
	_Camera = _SceneManager->addCameraSceneNodeMaya(0, -1500, 200, 1500, -1, 100, true);
	_Camera->setTarget(irr::core::vector3df(0, 0, 0));

	/* Create Attractors */
	_Attractors.push_back(new Attractor(_Device, _SceneManager, irr::core::vector3df(0, 0, 50)));
	_Attractors.push_back(new Attractor(_Device, _SceneManager, irr::core::vector3df(35.35f, 0, -35.35f)));
	_Attractors.push_back(new Attractor(_Device, _SceneManager, irr::core::vector3df(-35.35f, 0, -35.35f)));
	_Attractors.push_back(new Attractor(_Device, _SceneManager, irr::core::vector3df(0, 50, 0)));

	/* Create Jumper */
	_Jumper = new Jumper(_SceneManager, _Attractors);

	/* Create GUI */
	_GUI = new GUI(_SceneManager, _Jumper);
}

void Application::Run()
{
	/* Main loop */
	while (_Device->run())
	{
		_Driver->beginScene(true, true, irr::video::SColor(100, 100, 100, 100));

		/* Draw all objects */
		_SceneManager->drawAll();

		/* Update and render GUI */
		_GUI->Update(); 
		_GUI->Render();

		/* Update all Attractors */
		bool IsSelected = false;
		for (unsigned int c = 0; c < _Attractors.size(); c++)
		{
			_Attractors[c]->Update();
			if (_Attractors[c]->IsSelected())
			{
				IsSelected = true;
			}

		}

		if (IsSelected)
		{
			_FrozenCamera->setPosition(_Camera->getPosition());
			_FrozenCamera->setTarget(irr::core::vector3df(0, 0, 0));

			_SceneManager->setActiveCamera(_FrozenCamera);
		}
		else
		{
			_SceneManager->setActiveCamera(_Camera);
		}


		/* Jump to attractor */
		if (_GUI->IsStarted())
		{
			_Jumper->Jump();
		}

	
		_Driver->endScene();				
	}
}

bool Application::IsOpen()
{
	return _Device->run();
}
