/****************************************************************************
//	Usagi Engine, Copyright © Vitei, Inc. 2013
****************************************************************************/
#include "Engine/Common/Common.h"
#include "Engine/Memory/MemUtil.h"
#include "IGamepad.h"
#include "Gamepad.h"

namespace usg{

Gamepad::Gamepad()
	: m_pIGamepad(nullptr)
	, m_uCaps(0)
	, m_bConnected(false)
{
	MemClear(&m_deviceState, sizeof(m_deviceState));
	m_deviceState.leftHand.LoadIdentity();
	m_deviceState.rightHand.LoadIdentity();
}

Gamepad::~Gamepad()
{

}

bool Gamepad::GetButtonDown(uint32 uButtonShift, ButtonState eState) const
{
	uint32 uButtonMask = 1 << (uButtonShift - 1);

	switch(eState)
	{
	case BUTTON_STATE_PRESSED:
		{
			return ((m_deviceState.uButtonsDown&uButtonMask)!=0)&&((m_deviceState.uButtonsPrevDown&uButtonMask)==0);
		}
	case BUTTON_STATE_RELEASED:
		{
			return ((m_deviceState.uButtonsPrevDown&uButtonMask)!=0)&&((m_deviceState.uButtonsDown&uButtonMask)==0);
		}
	case BUTTON_STATE_HELD:
		{
			return ((m_deviceState.uButtonsDown&uButtonMask)!=0);
		}
	case BUTTON_STATE_CONTACT:
		{
		return ((m_deviceState.uButtonsContact&uButtonMask) != 0);
		}
	default:
		ASSERT(false);	// Unhandled state
	}
	return false;
}

float Gamepad::GetAxisValue(uint32 uAxis) const
{
	ASSERT(uAxis < _GamepadAxis_count);
	return m_deviceState.fAxisValues[uAxis];
}

void Gamepad::GetMatrix(Matrix4x4& out, GamepadHand eHand)
{
	if (eHand == GamepadHand::Left)
	{
		out = m_deviceState.leftHand;
	}

	out = m_deviceState.rightHand;
}

void Gamepad::Update(usg::GFXDevice* pDevice)
{
	if (m_pIGamepad)
	{
		m_pIGamepad->Update(pDevice, m_deviceState);
		m_bConnected = m_pIGamepad->IsConnected();

	}
	else
	{
		m_uCaps = 0;
	}
}

void Gamepad::ResetGyro()
{
	m_pIGamepad->ResetGyro();
}

void Gamepad::ResetGyroDirection()
{
	m_pIGamepad->ResetGyroDirection();
}


void Gamepad::BindHardware(IGamepad* pGamepad)
{
	m_pIGamepad = pGamepad;
	if (m_pIGamepad)
	{
		m_uCaps = m_pIGamepad->GetCaps();
		m_bConnected = m_pIGamepad->IsConnected();
	}
}

}
