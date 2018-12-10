#pragma once
////////////////////////////////////////////////////////////////////////////////
// Filename: positionclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _POSITIONCLASS_H_
#define _POSITIONCLASS_H_


//////////////
// INCLUDES //
//////////////
#include <math.h>
#include "d3dclass.h"

////////////////////////////////////////////////////////////////////////////////
// Class name: PositionClass
////////////////////////////////////////////////////////////////////////////////
class PositionClass
{
public:
	PositionClass();
	PositionClass(const PositionClass&);
	~PositionClass();

	void SetFrameTime(float);

	void SetPosition(D3DXVECTOR3);
	void SetRotation(D3DXVECTOR3);

	void GetRotation(D3DXVECTOR3&);
	void GetPosition(D3DXVECTOR3&);

	void TurnLeft(bool);
	void TurnRight(bool);
	void GoForward(bool);
	void GoBack(bool);
	void GoUp(bool);
	void GoDown(bool);
	void LookUpward(bool);
	void LookDownward(bool);

private:
	float m_frameTime;

	float m_rotationX, m_rotationY, m_rotationZ;
	float m_positionX, m_positionY, m_positionZ;

	float m_leftTurnSpeed, m_rightTurnSpeed, m_forwardSpeed, m_backSpeed, m_upSpeed, m_downSpeed;
	float m_lookUpSpeed, m_lookDownSpeed;
};

#endif

