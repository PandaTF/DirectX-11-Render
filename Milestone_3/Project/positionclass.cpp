////////////////////////////////////////////////////////////////////////////////
// Filename: positionclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "positionclass.h"

PositionClass::PositionClass()
{
	m_frameTime = 0.0f;

	m_rotationX = 30.0f;
	m_rotationY = 0.0f;
	m_rotationZ = 0.0f;

	m_positionX = 0.0f;
	m_positionY = 15.0f;
	m_positionZ = -20.0f;

	m_leftTurnSpeed = 0.0f;
	m_rightTurnSpeed = 0.0f;
	m_forwardSpeed = 0.0f;
	m_backSpeed = 0.0f;
	m_upSpeed = 0.0f;
	m_downSpeed = 0.0f;
	m_lookUpSpeed = 0.0f;
	m_lookDownSpeed = 0.0f;
}

PositionClass::PositionClass(const PositionClass& other)
{
}


PositionClass::~PositionClass()
{
}

void PositionClass::SetFrameTime(float time)
{
	m_frameTime = time;
	return;
}

void PositionClass::SetPosition(D3DXVECTOR3 position)
{
	m_positionX = position.x;
	m_positionY = position.y;
	m_positionZ = position.z;
	return;
}

void PositionClass::SetRotation(D3DXVECTOR3 rotation)
{
	m_rotationX = rotation.x;
	m_rotationY = rotation.y;
	m_rotationZ = rotation.z;
	return;
}

void PositionClass::GetRotation(D3DXVECTOR3 &rotation)
{
	rotation.x = m_rotationX;
	rotation.y = m_rotationY;
	rotation.z = m_rotationZ;
	return;
}

void PositionClass::GetPosition(D3DXVECTOR3 &position)
{
	position.x = m_positionX;
	position.y = m_positionY;
	position.z = m_positionZ;
	return;
}

void PositionClass::TurnLeft(bool keydown)
{
	// If the key is pressed increase the speed at which the camera turns left.  If not slow down the turn speed.
	if (keydown)
	{
		m_leftTurnSpeed += m_frameTime * 0.01f;

		if (m_leftTurnSpeed > (m_frameTime * 0.15f))
		{
			m_leftTurnSpeed = m_frameTime * 0.15f;
		}
	}
	else
	{
		m_leftTurnSpeed -= m_frameTime * 0.005f;

		if (m_leftTurnSpeed < 0.0f)
		{
			m_leftTurnSpeed = 0.0f;
		}
	}

	// Update the rotation using the turning speed.
	m_rotationY -= m_leftTurnSpeed;
	if (m_rotationY < 0.0f)
	{
		m_rotationY += 360.0f;
	}

	return;
}

void PositionClass::TurnRight(bool keydown)
{
	// If the key is pressed increase the speed at which the camera turns right.  If not slow down the turn speed.
	if (keydown)
	{
		m_rightTurnSpeed += m_frameTime * 0.01f;

		if (m_rightTurnSpeed > (m_frameTime * 0.15f))
		{
			m_rightTurnSpeed = m_frameTime * 0.15f;
		}
	}
	else
	{
		m_rightTurnSpeed -= m_frameTime * 0.005f;

		if (m_rightTurnSpeed < 0.0f)
		{
			m_rightTurnSpeed = 0.0f;
		}
	}

	// Update the rotation using the turning speed.
	m_rotationY += m_rightTurnSpeed;
	if (m_rotationY > 360.0f)
	{
		m_rotationY -= 360.0f;
	}

	return;
}

void PositionClass::GoForward(bool keydown)
{
	float radians;

	if (keydown)
	{
		m_forwardSpeed += m_frameTime * 0.001f;

		if (m_forwardSpeed > (m_frameTime * 0.03f))
		{
			m_forwardSpeed = m_frameTime * 0.03f;
		}
	}
	else
	{
		m_forwardSpeed -= m_frameTime * 0.0007f;

		if (m_forwardSpeed < 0.0f)
		{
			m_forwardSpeed = 0.0f;
		}
	}

	// Convert degrees to radians.
	radians = m_rotationY * 0.0174532925f;

	// Update the position.
	m_positionX += sinf(radians) * m_forwardSpeed;
	m_positionZ += cosf(radians) * m_forwardSpeed;

	return;
}

void PositionClass::GoBack(bool keydown)
{
	float radians;

	if (keydown)
	{
		m_backSpeed += m_frameTime * 0.001f;

		if (m_backSpeed > (m_frameTime * 0.03f))
		{
			m_backSpeed = m_frameTime * 0.03f;
		}
	}
	else
	{
		m_backSpeed -= m_frameTime * 0.0007f;

		if (m_backSpeed < 0.0f)
		{
			m_backSpeed = 0.0f;
		}
	}

	// Convert degrees to radians.
	radians = m_rotationY * 0.0174532925f;

	// Update the position.
	m_positionX -= sinf(radians) * m_backSpeed;
	m_positionZ -= cosf(radians) * m_backSpeed;

	return;
}

void PositionClass::GoUp(bool keydown)
{
	if (keydown)
	{
		m_upSpeed += m_frameTime * 0.003f;

		if (m_upSpeed > (m_frameTime * 0.03f))
		{
			m_upSpeed = m_frameTime * 0.03f;
		}
	}
	else
	{
		m_upSpeed -= m_frameTime * 0.002f;

		if (m_upSpeed < 0.0f)
		{
			m_upSpeed = 0.0f;
		}
	}

	// Update the height position.
	m_positionY += m_upSpeed;

	return;
}

void PositionClass::GoDown(bool keydown)
{
	if (keydown)
	{
		m_downSpeed += m_frameTime * 0.003f;

		if (m_downSpeed > (m_frameTime * 0.03f))
		{
			m_downSpeed = m_frameTime * 0.03f;
		}
	}
	else
	{
		m_downSpeed -= m_frameTime * 0.002f;

		if (m_downSpeed < 0.0f)
		{
			m_downSpeed = 0.0f;
		}
	}

	// Update the height position.
	m_positionY -= m_downSpeed;

	return;
}

void PositionClass::LookUpward(bool keydown)
{
	// Update the upward rotation speed movement based on the frame time and whether the user is holding the key down or not.
	if (keydown)
	{
		m_lookUpSpeed += m_frameTime * 0.01f;

		if (m_lookUpSpeed > (m_frameTime * 0.15f))
		{
			m_lookUpSpeed = m_frameTime * 0.15f;
		}
	}
	else
	{
		m_lookUpSpeed -= m_frameTime * 0.005f;

		if (m_lookUpSpeed < 0.0f)
		{
			m_lookUpSpeed = 0.0f;
		}
	}

	// Update the rotation.
	m_rotationX -= m_lookUpSpeed;

	// Keep the rotation maximum 90 degrees.
	if (m_rotationX > 90.0f)
	{
		m_rotationX = 90.0f;
	}

	return;
}


void PositionClass::LookDownward(bool keydown)
{
	// Update the downward rotation speed movement based on the frame time and whether the user is holding the key down or not.
	if (keydown)
	{
		m_lookDownSpeed += m_frameTime * 0.01f;

		if (m_lookDownSpeed > (m_frameTime * 0.15f))
		{
			m_lookDownSpeed = m_frameTime * 0.15f;
		}
	}
	else
	{
		m_lookDownSpeed -= m_frameTime * 0.005f;

		if (m_lookDownSpeed < 0.0f)
		{
			m_lookDownSpeed = 0.0f;
		}
	}

	// Update the rotation.
	m_rotationX += m_lookDownSpeed;

	// Keep the rotation maximum 90 degrees.
	if (m_rotationX < -90.0f)
	{
		m_rotationX = -90.0f;
	}

	return;
}