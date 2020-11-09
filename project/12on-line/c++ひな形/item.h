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
	typedef enum
	{
		CANDY = 0,	// ���������
		KOBAN,		// �X�R�AUP
		LIFE,		// �̗͉�
		ITEM_MAX	
	}ITEM;

	//�����o�֐�
	CItem();
	~CItem();
	static CItem *Create(D3DXVECTOR3 pos, ITEM type);
	static HRESULT Load(void);
	static void Unload(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	void Direction(void);
	void CollisionItem(void);

	// �����o�ϐ�
	static LPD3DXMESH m_pMeshModel[ITEM_MAX];	//���b�V�����ւ̃|�C���^
	static LPD3DXBUFFER m_pBuffMatModel[ITEM_MAX];	//�}�e���A�����ւ̃|�C���^
	static DWORD m_nNumMatModel[ITEM_MAX];	//�}�e���A�����̐�
	static LPDIRECT3DTEXTURE9 m_apTexture; // �e�N�X�`��
	CCollision*m_pCollision;    // �R���W�����N���X�̃|�C���^
	ITEM m_type;				// �A�C�e���̎�ޏ��
	int m_nCandy;				// �L�����f�B�̐�
	float m_fRotYDist;
};

#endif