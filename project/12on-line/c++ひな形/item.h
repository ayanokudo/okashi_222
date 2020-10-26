//=============================================================================
//
// item�w�b�_ [item.h]
// Author : ����@�r�H
//
//=============================================================================

//��d�C���N���[�h�h�~
#ifndef _ITEM_H_
#define _ITEM_H_

//*****************************
// �C���N���[�h
//*****************************
#include "main.h"
#include "model.h"

//*****************************
// �O���錾
//*****************************
class CCollision;

//*****************************
// �N���X��`
//*****************************

// �p�[�e�B�N���N���X
class CItem : public CModel
{
public:

	//�����o�֐�
	CItem();
	~CItem();
	static CItem *Create(D3DXVECTOR3 pos);
	static HRESULT Load(void);
	static void Unload(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	void Direction(void);
	void Attack(void);

	// �����o�ϐ�
	static LPD3DXMESH m_pMeshModel;	//���b�V�����ւ̃|�C���^
	static LPD3DXBUFFER m_pBuffMatModel;	//�}�e���A�����ւ̃|�C���^
	static DWORD m_nNumMatModel;	//�}�e���A�����̐�
	static LPDIRECT3DTEXTURE9 m_apTexture; // �e�N�X�`��
	CCollision*m_pCollision;    // �R���W�����N���X�̃|�C���^
};

#endif