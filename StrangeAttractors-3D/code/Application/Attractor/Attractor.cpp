#include "Attractor.h"

Attractor::Attractor(irr::IrrlichtDevice *Device, irr::scene::ISceneManager *SceneManager, irr::core::vector3df Position)
{
	/* Save pointer to irrlicht device */
	_Device = Device;
	_Manager = SceneManager;

	/* Create Attractor and add sphere to the scene manager */
	_Attractor = SceneManager->addSphereSceneNode(2.0f, 32, 0, -1, Position, irr::core::vector3df(0, 0, 0), irr::core::vector3df(1, 1, 1));
	_Attractor->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	_Attractor->setMaterialTexture(0, SceneManager->getVideoDriver()->getTexture("Data\\Red.png"));

	_ArrowY = SceneManager->addAnimatedMeshSceneNode(SceneManager->getMesh("Data\\Arrow.obj"), 0, -1, _Attractor->getAbsolutePosition(), irr::core::vector3df(0, 0, 0), irr::core::vector3df(1, 3, 1));
	_ArrowY->setPosition(irr::core::vector3df(_Attractor->getAbsolutePosition().X, _Attractor->getAbsolutePosition().Y - _ArrowY->getTransformedBoundingBox().getExtent().Y / 3, _Attractor->getAbsolutePosition().Z));
	_ArrowY->setVisible(false);

	_ArrowX = SceneManager->addAnimatedMeshSceneNode(SceneManager->getMesh("Data\\Arrow.obj"), 0, -1, _Attractor->getAbsolutePosition(), irr::core::vector3df(0, 0, 90), irr::core::vector3df(1, 3, 1));
	_ArrowX->setPosition(irr::core::vector3df(_Attractor->getAbsolutePosition().X + _ArrowX->getTransformedBoundingBox().getExtent().X / 3, _Attractor->getAbsolutePosition().Y, _Attractor->getAbsolutePosition().Z));
	_ArrowX->setVisible(false);

	_ArrowZ = SceneManager->addAnimatedMeshSceneNode(SceneManager->getMesh("Data\\Arrow.obj"), 0, -1, _Attractor->getAbsolutePosition(), irr::core::vector3df(90, 0, 0), irr::core::vector3df(1, 3, 1));
	_ArrowZ->setPosition(irr::core::vector3df(_Attractor->getAbsolutePosition().X, _Attractor->getAbsolutePosition().Y, _Attractor->getAbsolutePosition().Z - _ArrowZ->getTransformedBoundingBox().getExtent().Z / 3));
	_ArrowZ->setVisible(false);



	_CurrentMovement = -1;

	_IsSelected = false;
	_Clicked = MOUSE_UP;
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
	if (GetAsyncKeyState(VK_LBUTTON) && _Clicked == MOUSE_UP)
	{
		_Clicked = MOUSE_CLICK;
	}
	if (!GetAsyncKeyState(VK_LBUTTON))
	{
		_Clicked = MOUSE_UP;
	}

	/* Move Attractor according to the RayFromScreenCoordinates. While you move the mouse this ray moves too */
	/* Move away or to the camera is moving the object along the ray. Just add to the current position of the object the direction vector multiplied with e.g. 0.1 */
	/* For the movement to the side you need an orthogonal vector. You get this by a scalar multiplication with the direction vector. The result is zero */
	if (_Clicked == MOUSE_CLICK && _IsSelected == true)
	{
		if (_ArrowY->getTransformedBoundingBox().intersectsWithLine(_Manager->getSceneCollisionManager()->getRayFromScreenCoordinates(_Device->getCursorControl()->getPosition(), _Manager->getActiveCamera())))
		{
			_CurrentMovement = VERTICAL;
			_ArrowX->setVisible(false);
			_ArrowZ->setVisible(false);

			_Clicked = MOUSE_HOLD;
		}

		if (_ArrowX->getTransformedBoundingBox().intersectsWithLine(_Manager->getSceneCollisionManager()->getRayFromScreenCoordinates(_Device->getCursorControl()->getPosition(), _Manager->getActiveCamera())))
		{
			_CurrentMovement = HORIZONTAL;
			_ArrowY->setVisible(false);
			_ArrowZ->setVisible(false);

			_Clicked = MOUSE_HOLD;
		}

		if (_ArrowZ->getTransformedBoundingBox().intersectsWithLine(_Manager->getSceneCollisionManager()->getRayFromScreenCoordinates(_Device->getCursorControl()->getPosition(), _Manager->getActiveCamera())))
		{
			_CurrentMovement = DEPTH;
			_ArrowY->setVisible(false);
			_ArrowX->setVisible(false);

			_Clicked = MOUSE_HOLD;
		}
	}

	/* If the left mouse button is pressed and the attractor is selected */
	if (_Clicked == MOUSE_CLICK)
	{
		if ((_Attractor->getTransformedBoundingBox().intersectsWithLine(_Manager->getSceneCollisionManager()->getRayFromScreenCoordinates(_Device->getCursorControl()->getPosition(), _Manager->getActiveCamera())) ||
			_ArrowY->getTransformedBoundingBox().intersectsWithLine(_Manager->getSceneCollisionManager()->getRayFromScreenCoordinates(_Device->getCursorControl()->getPosition(), _Manager->getActiveCamera())) || 
			_ArrowX->getTransformedBoundingBox().intersectsWithLine(_Manager->getSceneCollisionManager()->getRayFromScreenCoordinates(_Device->getCursorControl()->getPosition(), _Manager->getActiveCamera()))) &&
			_IsSelected == false)
		{		
			_IsSelected = true;
			_ArrowY->setVisible(true);
			_ArrowX->setVisible(true);
			_ArrowZ->setVisible(true);

			_Attractor->setMaterialTexture(0, _Manager->getVideoDriver()->getTexture("Data\\Selected.png"));
		
			_Clicked = MOUSE_HOLD;
		}
		else
		{
			if (_Device->getCursorControl()->getPosition().Y < 100) //Maybe the user did not want to unselect the button. He just wanted to press a button on the GUI
			{
				return;
			}

			_IsSelected = false;
			_ArrowY->setVisible(false);
			_ArrowX->setVisible(false);
			_ArrowZ->setVisible(false);
			_CurrentMovement = -1;

			_Attractor->setMaterialTexture(0, _Manager->getVideoDriver()->getTexture("Data\\Red.png"));

			_Clicked = MOUSE_HOLD;
		}
	}

	if (_IsSelected)
	{
		switch (_CurrentMovement)
		{
			case VERTICAL: {
				irr::core::line3df Line = _Manager->getSceneCollisionManager()->getRayFromScreenCoordinates(_Device->getCursorControl()->getPosition(), _Manager->getActiveCamera());

				irr::core::vector3df NewPosition = Line.getClosestPoint(_Attractor->getAbsolutePosition());

				_Attractor->setPosition(irr::core::vector3df(_Attractor->getAbsolutePosition().X, NewPosition.Y, _Attractor->getAbsolutePosition().Z));

				_ArrowY->setPosition(irr::core::vector3df(_Attractor->getAbsolutePosition().X, _Attractor->getAbsolutePosition().Y - _ArrowY->getTransformedBoundingBox().getExtent().Y / 3, _Attractor->getAbsolutePosition().Z));
				_ArrowX->setPosition(irr::core::vector3df(_Attractor->getAbsolutePosition().X + _ArrowX->getTransformedBoundingBox().getExtent().X / 3, _Attractor->getAbsolutePosition().Y, _Attractor->getAbsolutePosition().Z));
				_ArrowZ->setPosition(irr::core::vector3df(_Attractor->getAbsolutePosition().X, _Attractor->getAbsolutePosition().Y, _Attractor->getAbsolutePosition().Z - _ArrowZ->getTransformedBoundingBox().getExtent().Z / 3));
			}
						   break;
			case HORIZONTAL: {
				irr::core::line3df Line = _Manager->getSceneCollisionManager()->getRayFromScreenCoordinates(_Device->getCursorControl()->getPosition(), _Manager->getActiveCamera());

				irr::core::vector3df NewPosition = Line.getClosestPoint(_Attractor->getAbsolutePosition());

				_Attractor->setPosition(irr::core::vector3df(NewPosition.X, _Attractor->getAbsolutePosition().Y, _Attractor->getAbsolutePosition().Z));

				_ArrowY->setPosition(irr::core::vector3df(_Attractor->getAbsolutePosition().X, _Attractor->getAbsolutePosition().Y - _ArrowY->getTransformedBoundingBox().getExtent().Y / 3, _Attractor->getAbsolutePosition().Z));
				_ArrowX->setPosition(irr::core::vector3df(_Attractor->getAbsolutePosition().X + _ArrowX->getTransformedBoundingBox().getExtent().X / 3, _Attractor->getAbsolutePosition().Y, _Attractor->getAbsolutePosition().Z));
				_ArrowZ->setPosition(irr::core::vector3df(_Attractor->getAbsolutePosition().X, _Attractor->getAbsolutePosition().Y, _Attractor->getAbsolutePosition().Z - _ArrowZ->getTransformedBoundingBox().getExtent().Z / 3));
			}
							 break;
			case DEPTH: {
				irr::core::line3df Line = _Manager->getSceneCollisionManager()->getRayFromScreenCoordinates(_Device->getCursorControl()->getPosition(), _Manager->getActiveCamera());

				irr::core::vector3df NewPosition = Line.getClosestPoint(_Attractor->getAbsolutePosition());

				_Attractor->setPosition(irr::core::vector3df(_Attractor->getAbsolutePosition().X, _Attractor->getAbsolutePosition().Y, NewPosition.Z));

				_ArrowY->setPosition(irr::core::vector3df(_Attractor->getAbsolutePosition().X, _Attractor->getAbsolutePosition().Y - _ArrowY->getTransformedBoundingBox().getExtent().Y / 3, _Attractor->getAbsolutePosition().Z));
				_ArrowX->setPosition(irr::core::vector3df(_Attractor->getAbsolutePosition().X + _ArrowX->getTransformedBoundingBox().getExtent().X / 3, _Attractor->getAbsolutePosition().Y, _Attractor->getAbsolutePosition().Z));
				_ArrowZ->setPosition(irr::core::vector3df(_Attractor->getAbsolutePosition().X, _Attractor->getAbsolutePosition().Y, _Attractor->getAbsolutePosition().Z - _ArrowZ->getTransformedBoundingBox().getExtent().Z / 3));
			}
						break;
		}
	}
}
bool Attractor::IsSelected()
{
	return _IsSelected;
}

void Attractor::Delete()
{
	_Attractor->remove();
	_ArrowX->remove();
	_ArrowY->remove();
	_ArrowZ->remove();
}