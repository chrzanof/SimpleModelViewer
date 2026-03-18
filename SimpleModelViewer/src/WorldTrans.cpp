#include "WorldTrans.h"

void WorldTrans::SetScale(float scale)
{
	this->m_Scale = Vector3f(scale, scale, scale);
}

void WorldTrans::SetScale(float x, float y, float z)
{
	this->m_Scale = Vector3f(x, y, z);
}

void WorldTrans::SetRotation(float x, float y, float z)
{
	this->m_Rotation = Vector3f(x, y, z);
}

void WorldTrans::SetPosition(float x, float y, float z)
{
	this->m_Position = Vector3f(x, y, z);
}

const Vector3f& WorldTrans::GetPosition() const
{
	return m_Position;
}

Matrix4x4_f WorldTrans::GetMatrix() const
{
	auto translation = Matrix4x4_f::Translation(
		Vector3f{ m_Position.x,m_Position.y, m_Position.z }
	);

	auto rotation = Matrix4x4_f::RotationXYZ(
		Vector3f{ m_Rotation.x, m_Rotation.y, m_Rotation.z }
	);

	auto scale = Matrix4x4_f::Scale(
		Vector3f{ m_Scale.x, m_Scale.y, m_Scale.z }
	);

	return translation * rotation * scale;
}
