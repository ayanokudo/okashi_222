//=============================================================================
//
// collision�w�b�_ [collision.h]
// Author : ���V ����
//
//=============================================================================

//��d�C���N���[�h�h�~
#ifndef _COLLISON_H_
#define _COLLISON_H_

//*****************************
// �C���N���[�h
//*****************************
#include "main.h"
#include "model.h"

//*****************************
// �N���X��`
//*****************************

// �����蔻��N���X
class CCollision : public CModel
{
public:
	typedef enum
	{
		COLLISIONTYPE_BOX = 0,
		COLLISIONTYPE_SPHERE,
		COLLISIONTYPE_MAX,
	}COLLISIONTYPE;
	//�����o�֐�
	CCollision();
	~CCollision();
	static CCollision *CreateSphere(D3DXVECTOR3 pos, float fRadius);
	static bool CollisionSphere(CCollision*pCollision1, CCollision*pCollision2);
	static CCollision *CreateBox(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	static bool CollisionBox(CCollision*pCollision1, CCollision*pCollision2);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	void CreateMesh(void);
	// �����o�ϐ�
	LPD3DXMESH m_pMeshModel;	//���b�V�����ւ̃|�C���^
	LPD3DXBUFFER m_pBuffMatModel;	//�}�e���A�����ւ̃|�C���^
	DWORD m_nNumMatModel;	//�}�e���A�����̐�
	COLLISIONTYPE m_type;  // �R���W�����̃^�C�v
	float m_fRadius;
	D3DXVECTOR3 m_size;
};

#endif