#ifndef __MELTSHINE_CAMERA_H__
#define __MELTSHINE_CAMERA_H__
#include <d3dx9.h>
#include "Component.h"
namespace meltshine
{
	enum CameraType
	{
		PERSPECTIVE,
		ORTHOGRAPHIC
	};

	class Scene;
	class Transform;
	class Renderer;
	class Camera : public Component
	{
	protected:
		Camera();
	public:
		virtual ~Camera();

		// Component¿ª(∏¶) ≈Î«ÿ ªÛº”µ 
		virtual bool Init(std::shared_ptr<Core> core) override;
		virtual void OnEnter() override;
		virtual void OnExit() override;
		virtual void Update(const float& dt) override;
		virtual void LateUpdate() override;
		virtual void PreRender() override;
		virtual void Render() override;
		virtual void PostRender() override;
		virtual void RenderImage() override;

		// Getter
		bool IsPerspective() const { return _cam_type == PERSPECTIVE; };
		bool IsOrthographic() const { return _cam_type == ORTHOGRAPHIC; };
		DWORD GetClearFlags() const { return _clear_flags; };
		D3DCOLOR GetClearColor() const { return _clear_color; };
		D3DVIEWPORT9 GetViewport() const { return _vp; };
		D3DXVECTOR3 GetEye() const { return _eye; };
		D3DXVECTOR3 GetUp() const { return _up; };
		D3DXVECTOR3 GetAt() const { return _at; };
		float GetFovAngle() const { return _fov_angle; };
		float GetAspectRatio() const { return _aspect_ratio; };
		int GetDepth() const { return _depth; };
		int	GetMaskingTags() const { return _masking_tags; };

		// Setter
		void SetCameraType(CameraType type);
		void SetDepth(int depth);
		void SetViewport(D3DVIEWPORT9 vp);
		void SetViewportSize(UINT w, UINT h);
		void SetFovAngle(float fov_angle);
		void SetAspectRatio(float aspect_ratio);
		void SetClearFlags(DWORD d3dclear_flag) { _clear_flags = d3dclear_flag; };
		void SetClearColor(D3DCOLOR color) { _clear_color = color; };
		void SetEyeUpAt(D3DXVECTOR3 eye, D3DXVECTOR3 up, D3DXVECTOR3 at) { _eye = eye; _up = up; _at = at; };
		void SetEye(D3DXVECTOR3 eye) { _eye = eye; };
		void SetUp(D3DXVECTOR3 up) { _up = up; };
		void SetAt(D3DXVECTOR3 at) { _at = at; };
		void SetMaskingTags(int masking_tags) { _masking_tags = masking_tags; };

		// Owner
		std::shared_ptr<Scene> GetScene() const { return _scene.lock(); };
		std::shared_ptr<Transform> GetTrasform() const { return _transform.lock(); };
		std::shared_ptr<Renderer> GetRenderer() const { return _renderer.lock(); };

		// RenderTexture
		LPDIRECT3DTEXTURE9 GetRenderTexture() const { return _render_texture; };
		bool HasRenderTexture() const { return _render_texture != nullptr; };
		void SetRenderTexture(LPDIRECT3DTEXTURE9 tex);

	protected:
		CameraType _cam_type;
		DWORD _clear_flags;
		D3DCOLOR _clear_color;
		
		D3DXMATRIX _previous_transform_matrix;

		D3DVIEWPORT9 _vp;
		D3DXVECTOR3 _eye;
		D3DXVECTOR3 _up;
		D3DXVECTOR3 _at;
		D3DXMATRIX _look_at;

		float _fov_angle;	// field of view
		float _aspect_ratio;
		float _near_z;
		float _far_z;
		D3DXMATRIX _projection;

		int _depth;
		bool _changed_value_of_projection;
		int _masking_tags;

		std::weak_ptr<Scene> _scene;
		std::weak_ptr<Transform> _transform;
		std::weak_ptr<Renderer> _renderer;

		// ∑ª¥ı ≈ÿΩ∫√ƒ(∑ª¥ı≈∏∞Ÿ)
		LPDIRECT3DTEXTURE9 _render_texture;
		LPDIRECT3DSURFACE9 _surface_of_render_texture;
		LPDIRECT3DSURFACE9 _surface_of_backbuffer;

		void CalculateProjectionMatrix();

		friend class ObjectManager;
	};
}
#endif // !__MELTSHINE_CAMERA_H__
