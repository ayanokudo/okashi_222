//=============================================================================
//
// ���f������ [model.h]
// Author : �R�c�ˑ�
//
//=============================================================================
#ifndef _MODEL_H_
#define _MODEL_H_

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "scene.h"

//=============================================================================
//���f���N���X
//=============================================================================
class CModel : public CScene
{
public:
	//=========================================================================
	//�����o�֐��錾
	//=========================================================================
	CModel(OBJTYPE type);
	~CModel();

	static CModel *Create(D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);
	LPD3DXMESH GetMesh(void)const;


	void SetPos(const D3DXVECTOR3 pos);
	D3DXVECTOR3 GetPos(void)const;
	void SetRot(const D3DXVECTOR3 rot);
	D3DXVECTOR3 GetRot(void)const;
	void BindModel(LPD3DXMESH pMeshModel, LPD3DXBUFFER pBuffMatModel, DWORD nNumMatModel);
private:
	//=========================================================================
	//�����o�ϐ��錾
	//=========================================================================
	LPD3DXMESH m_pMeshModel;	//���b�V�����ւ̃|�C���^
	LPD3DXBUFFER m_pBuffMatModel;	//�}�e���A�����ւ̃|�C���^
	DWORD m_nNumMatModel;	//�}�e���A�����̐�
	D3DXVECTOR3 m_pos;	//�ʒu
	D3DXVECTOR3 m_rot;	//����
	D3DXMATRIX m_mtxWorldModel;	//���[���h�}�g���b�N�X
};
#endif 