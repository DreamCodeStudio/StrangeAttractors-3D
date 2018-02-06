#include "GUI.h"

GUI::GUI(irr::scene::ISceneManager *SceneManager, Jumper *Jumper)
{
	/* Safe pointer to jumper object */
	_Jumper = Jumper;

	/* Create GUI elements */
	_GUIEnv = SceneManager->getGUIEnvironment();
	_GUIEnv->getSkin()->setFont(_GUIEnv->getFont("Data\\Font\\rpgfont.xml"));

	_GUIEnv->addStaticText(irr::core::stringw("Jump distance").c_str(), irr::core::rect<irr::s32>(10, 10, 300, 30), false, true, 0, -1, false);
	_Distance = _GUIEnv->addScrollBar(true, irr::core::rect<irr::s32>(120, 10, 420, 30), 0, -1);
	_Distance->setMin(1);
	_Distance->setMax(99);
	_Distance->setPos(50);

	_Start = _GUIEnv->addButton(irr::core::rect<irr::s32>(10, 40, 100, 70), 0, -1, irr::core::stringw("Start").c_str(), 0);
	_Stop = _GUIEnv->addButton(irr::core::rect<irr::s32>(110, 40, 200, 70), 0, -1, irr::core::stringw("Stop").c_str(), 0);
	_Reset = _GUIEnv->addButton(irr::core::rect<irr::s32>(210, 40, 300, 70), 0, -1, irr::core::stringw("Reset").c_str(), 0);
	_Create = _GUIEnv->addButton(irr::core::rect<irr::s32>(310, 40, 400, 70), 0, -1, irr::core::stringw("Create").c_str(), 0);
	_Delete = _GUIEnv->addButton(irr::core::rect<irr::s32>(410, 40, 500, 70), 0, -1, irr::core::stringw("Delete").c_str(), 0);

	_PressedDelete = false;
	_PressedCreate = false;
}

void GUI::Update()
{
	/* Check if buttons are pressed */
	if (_Start->isPressed())
	{
		_Started = true;
	}
	if (_Stop->isPressed())
	{
		_Started = false;
	}
	if (_Reset->isPressed())
	{
		_Jumper->Reset();
		_Started = false;
	}
	if (_Delete->isPressed())
	{
		_PressedDelete = true;
		while (GetAsyncKeyState(VK_LBUTTON));
	}
	if (_Create->isPressed())
	{
		_PressedCreate = true;
		while (GetAsyncKeyState(VK_LBUTTON));
	}

	_Jumper->SetJumpDistance(static_cast<float>(_Distance->getPos() / 100.0f));
}

void GUI::Render()
{
	_GUIEnv->drawAll();
}

bool GUI::IsStarted()
{
	return _Started;
}

bool GUI::CreatePressed()
{
	if (_PressedCreate == true)
	{
		_PressedCreate = false;
		return true;
	}

	return false;
}
bool GUI::DeletePressed()
{
	if (_PressedDelete == true)
	{
		_PressedDelete = false;
		return true;
	}

	return false;
}