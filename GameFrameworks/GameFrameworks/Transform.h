#ifndef __MELTSHINE_TRANSFORM_H__
#define __MELTSHINE_TRANSFORM_H__
#include <d3dx9.h>
#include "Component.h"
namespace meltshine
{
	class Transform : public Component
	{
	protected:
		Transform();
	public:
		virtual ~Transform();

		// ComponentÀ»(¸¦) ÅëÇØ »ó¼ÓµÊ
		virtual bool Init(std::shared_ptr<Core> core) override;
		virtual void OnEnter() override;
		virtual void OnExit() override;
		virtual void Update(const float& dt) override;
		virtual void LateUpdate() override;
		virtual void PreRender() override;
		virtual void Render() override;
		virtual void PostRender() override;
		virtual void RenderImage() override;

		// ¸â¹öº¯¼ö (Getter)
		D3DXVECTOR3 GetPosition() const { return _position; };
		D3DXVECTOR3 GetRotation() const { return _rotation; };
		D3DXVECTOR3 GetScale() const { _scale; };
		D3DXMATRIX  GetTransformMatrix() const { _transform; };

		// ¸â¹öº¯¼ö (Setter)
		void SetPosition(D3DXVECTOR3 pos) { _position = pos; };
		void SetPositionX(float x) { _position.x = x; };
		void SetPositionY(float y) { _position.y = y; };
		void SetPositionZ(float z) { _position.z = z; };
		void SetPositionXYZ(float x, float y, float z) { _position = { x,y,z }; };
		void SetRotation(D3DXVECTOR3 rot) { _rotation = rot; };
		void SetRotationYaw(float angle) { _rotation.y = angle; };
		void SetRotationPitch(float angle) { _rotation.x = angle; };
		void SetRotationRoll(float angle) { _rotation.z = angle; };
		void SetRotationYawPitchRoll(float yaw, float pitch, float roll) { _rotation = { pitch, yaw, roll }; };
		void SetScale(D3DXVECTOR3 scale) { _scale = scale; };
		void SetScaleX(float x) { _scale.x = x; };
		void SetScaleY(float y) { _scale.y = y; };
		void SetScaleZ(float z) { _scale.z = z; };
		void SetScaleXYZ(float x, float y, float z) { _scale = { x,y,z }; };

		// Translate
		void Translate(float x, float y, float z) { _position += {x, y, z}; };
		void Translate(D3DXVECTOR3 translation) { _position += translation; };
		
		// Rotate
		void Rotate(D3DXVECTOR3 rotation) { _rotation += rotation; };
		void Rotate(float x, float y, float z) { _rotation += {x, y, z}; };

	protected:
		D3DXVECTOR3	_position;
		D3DXVECTOR3	_rotation;
		D3DXVECTOR3	_scale;
		D3DXMATRIX  _transform;
		LPDIRECT3DDEVICE9 _d3d_device;

		friend class ObjectManager;
	};

}
#endif // !__MELTSHINE_TRANSFORM_H__