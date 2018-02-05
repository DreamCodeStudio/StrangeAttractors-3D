#include "Attractor.h"

Attractor::Attractor(irr::IrrlichtDevice *Device, irr::scene::ISceneManager *SceneManager, irr::core::vector3df Position)
{
	/* Save pointer to irrlicht device */
	_Device = Device;
	_Manager = SceneManager;

	/* Create Attractor and add sphere to the scene manager */
	_Attractor = SceneManager->addSphereSceneNode(2.0f, 32, 0, -1, Position);
	_Attractor->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	_Attractor->setMaterialTexture(0, SceneManager->getVideoDriver()->getTexture("Data\\Red.png"));
}

void Attractor::SetPosition(irr::core::vector3df NewPosition)
{
	_Attractor->setPosition(NewPosition);
}

irr::core::vector3df Attractor::GetPosition()
{
	return _Attractor->getPosition();
}

void Attractor::Update()
{
	/* Check if the mouse button is pressed */
	if (GetAsyncKeyState(VK_LBUTTON))
	{
		/* Get line from camera to 0, 0, 0 */
		irr::core::line3df line;
		line.start = _Manager->getActiveCamera()->getAbsolutePosition();
		line.end = irr::core::vector3df(0, 0, 0);

		/* Check if an attractor is within this line */
		if (_Attractor->getTransformedBoundingBox().intersectsWithLine(line) == true)
		{
			_Attractor->setMaterialTexture(0, _Manager->getVideoDriver()->getTexture("Data\\Selected.png"));
			_IsOnView = true;
		}
		else
		{
			_Attractor->setMaterialTexture(0, _Manager->getVideoDriver()->getTexture("Data\\Red.png"));
			_IsOnView = false;
		}		
	}

	if (_IsOnView == true)
	{
		if (GetAsyncKeyState(VK_RBUTTON))
		{
			switch (_IsSelected)
			{
				case true: {
					_IsSelected = false;
				}
				break;
				case false: {
					_IsSelected = true;
				}
			}

			while (GetAsyncKeyState(VK_RBUTTON));
		}
	}

	if (_IsSelected == true)
	{
		if (GetAsyncKeyState(VK_UP))
		{
			_Attractor->setPosition(irr::core::vector3df(_Attractor->getAbsolutePosition().X, _Attractor->getAbsolutePosition().Y + 1, _Attractor->getAbsolutePosition().Z));
		}
		if (GetAsyncKeyState(VK_DOWN))
		{
			_Attractor->setPosition(irr::core::vector3df(_Attractor->getAbsolutePosition().X, _Attractor->getAbsolutePosition().Y - 1, _Attractor->getAbsolutePosition().Z));
		}
	}

}