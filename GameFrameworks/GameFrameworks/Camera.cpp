#include "Camera.h"

#include "Core.h"
#include "GameObject.h"
#include "Renderer.h"
#include "Scene.h"
#include "SceneController.h"
#include "Transform.h"

namespace meltshine
{
	Camera::Camera()
		: _aspect_ratio()
		, _cam_type(PERSPECTIVE)
		, _changed_value_of_projection(false)
		, _clear_color(0xFF0000FF)
		, _clear_flags(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL)
		, _depth(0)
		, _fov_angle(D3DXToRadian(45))
		, _far_z(1000.f)
		, _near_z(0.1f)
		, _vp()
		, _render_texture(nullptr)
		, _surface_of_backbuffer(nullptr)
		, _surface_of_render_texture(nullptr)
		, _masking_tags(0)
	{
		_vp.X = 0;
		_vp.Y = 0;
		_vp.Width = 0;
		_vp.Height = 0;
		_vp.MinZ = 0.0f;
		_vp.MaxZ = 1.0f;
	}

	Camera::~Camera()
	{
	}

	bool Camera::Init(std::shared_ptr<Core> core)
	{
		if (core == nullptr)
		{
			return false;
		}

		_renderer = core->GetRenderer();

		core->GetWinSize((int&)_vp.Width, (int&)_vp.Height);
		_aspect_ratio = (float)_vp.Width / _vp.Height;

		return true;
	}

	void Camera::OnEnter()
	{
		auto owner = GetOwner();
		_transform = owner->GetTransform();
		_scene = owner->GetSceneController()->GetCurrentScene();

		// 투영 변환 행렬 계산
		CalculateProjectionMatrix();

		// Scene에 등록
		auto scene = GetScene();
		scene->_cameras.emplace_back(std::static_pointer_cast<Camera>(shared_from_this()));
		_depth = (int)scene->_cameras.size() - 1;
		scene->_dirty_cameras = true;
	}

	void Camera::OnExit()
	{
		auto scene = GetScene();
		if (scene == nullptr)
		{
			return;
		}

		// Scene에서 제거
		auto& cameras = scene->_cameras;
		auto it = cameras.begin();
		auto end = cameras.end();
		for (; it != end; ++it)
		{
			if ((*it).get() == this)
			{
				cameras.erase(it);
				return;
			}
		}
	}

	void Camera::Update(const float& dt)
	{
	}

	void Camera::LateUpdate()
	{
		auto current_transform_matrix = _transform.lock()->GetTransformMatrix();
		// 카메라 컴포넌트를 소유한 게임 오브젝트가 움직였다면
		// 뷰 변환 행렬을 다시 계산합니다.
		if (_previous_transform_matrix != current_transform_matrix)
		{
			D3DXVECTOR3 eye, at, up;
			D3DXVec3TransformNormal(&eye, &_eye, &current_transform_matrix);
			D3DXVec3TransformCoord(&at, &_at, &current_transform_matrix);
			D3DXVec3TransformCoord(&up, &_up, &current_transform_matrix);
			D3DXMatrixLookAtLH(&_look_at, &eye, &at, &up);
			_previous_transform_matrix = current_transform_matrix;
		}

		if (_changed_value_of_projection)
		{
			CalculateProjectionMatrix();
			_changed_value_of_projection = false;
		}
	}

	void Camera::PreRender()
	{
		if (GetScene()->GetVisitingCamera().get() != this)
		{
			return;
		}

		auto renderer = GetRenderer();
		if (HasRenderTexture())
		{
			renderer->GetRenderTarget(0, &_surface_of_backbuffer);
			renderer->SetRenderTarget(0, _surface_of_render_texture);
		}

		renderer->Clear(_clear_color, _clear_flags);
		renderer->BeginScene();
		renderer->SetTransform(D3DTS_VIEW, &_look_at);
		renderer->SetTransform(D3DTS_PROJECTION, &_projection);
	}

	void Camera::Render()
	{
	}

	void Camera::PostRender()
	{
		if (GetScene()->GetVisitingCamera().get() != this)
		{
			return;
		}

		auto renderer = GetRenderer();
		renderer->EndScene();
		if (HasRenderTexture())
		{
			renderer->SetRenderTarget(0, _surface_of_backbuffer);
		}
	}

	void Camera::RenderImage()
	{
	}

	void Camera::SetCameraType(CameraType type)
	{
		if (_cam_type == type)
		{
			return;
		}
		_cam_type = type;
		CalculateProjectionMatrix();
	}

	void Camera::SetDepth(int depth)
	{
		if (_depth == depth)
		{
			return;
		}
		_depth = depth;
		
		GetScene()->_dirty_cameras = true;
	}

	void Camera::SetViewport(D3DVIEWPORT9 vp)
	{
		_vp = vp;
		if (_vp.Width != vp.Width ||
			_vp.Height != vp.Height)
		{
			_aspect_ratio = (float)_vp.Width / _vp.Height;
			_changed_value_of_projection = true;
		}
	}

	void Camera::SetViewportSize(UINT w, UINT h)
	{
		if (_vp.Width == w && _vp.Height == h)
		{
			return;
		}
		_vp.Width = w;
		_vp.Height = h;
		_aspect_ratio = (float)_vp.Width / _vp.Height;
		_changed_value_of_projection = true;
	}

	void Camera::SetFovAngle(float fov_angle)
	{
		if (_fov_angle == fov_angle)
		{
			return;
		}
		_fov_angle = fov_angle;
		_changed_value_of_projection = true;
	}

	void Camera::SetAspectRatio(float aspect_ratio)
	{
		if (_aspect_ratio == aspect_ratio)
		{
			return;
		}

		_aspect_ratio = aspect_ratio;
		_changed_value_of_projection = true;
	}

	void Camera::SetRenderTexture(LPDIRECT3DTEXTURE9 tex)
	{
		if (_render_texture == tex)
		{
			return;
		}
		if (tex != nullptr)
		{
			tex->GetSurfaceLevel(0, &_surface_of_render_texture);
		}
		else
		{
			_surface_of_render_texture = nullptr;
		}
		_render_texture = tex;
	}

	void Camera::CalculateProjectionMatrix()
	{
		switch (_cam_type)
		{
		case PERSPECTIVE:
			D3DXMatrixPerspectiveFovLH(&_projection, _fov_angle, _aspect_ratio, _near_z, _far_z);
			break;
		case ORTHOGRAPHIC:
			D3DXMatrixOrthoLH(&_projection, (float)_vp.Width, (float)_vp.Height, _near_z, _far_z);
			break;
		default:
			break;
		}
	}

}