#include "Transform.h"

#include "GameObject.h"
#include "Core.h"
#include "Direct3D.h"

namespace meltshine
{
	Transform::Transform()
		: _position(0, 0, 0)
		, _rotation(0, 0, 0)
		, _scale(1, 1, 1)
		, _transform()
		, _d3d_device(nullptr)
	{
	}


	Transform::~Transform()
	{
	}

	bool Transform::Init(std::shared_ptr<Core> core)
	{
		if (core == nullptr)
		{
			return false;
		}

		_d3d_device = core->GetDirect3D()->GetDevice();
		if (_d3d_device == nullptr)
		{
			return false;
		}

		return true;
	}

	void Transform::OnEnter()
	{
	}

	void Transform::OnExit()
	{
	}

	void Transform::Update(const float& dt)
	{
	}

	void Transform::LateUpdate()
	{
		D3DXQUATERNION q;
		D3DXQuaternionRotationYawPitchRoll(&q, _rotation.y, _rotation.x, _rotation.z);
		D3DXMatrixTransformation(&_transform,
			nullptr,
			nullptr,
			&_scale,
			&_position,
			&q,
			&_position);

		auto parent = GetOwner()->GetParent();
		if (parent != nullptr)
		{
			_transform *= parent->GetTransform()->_transform;
		}
	}

	void Transform::PreRender()
	{
	}

	void Transform::Render()
	{
	}

	void Transform::PostRender()
	{
	}

	void Transform::RenderImage()
	{
	}

}