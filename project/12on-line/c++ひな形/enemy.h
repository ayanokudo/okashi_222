//=============================================================================
//
// enemy�w�b�_ [enemy.h]
// Author : ���� �r�H
//
//=============================================================================

//��d�C���N���[�h�h�~
#ifndef _ENEMY_H_
#define _ENEMY_H_

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
class CEnemy : public CModel
{
public:
	typedef enum
	{
		ENEMY_CARRIER,		//���َq�^��ł�G
		ENEMY_ESCORT,		//BOSS����Ă�G
		ENEMY_RARE,			//���A�L����
		ENEMY_MAX,
	}ENEMY;

	//�����o�֐�
	CEnemy();
	~CEnemy();
	static CEnemy *Create(D3DXVECTOR3 pos);
	static HRESULT Load(void);
	static void Unload(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	CCollision *GetCollision(void) { return m_pCollision; }
private:
	// �����o�ϐ�
	static LPD3DXMESH m_pMeshModel;	//���b�V�����ւ̃|�C���^
	static LPD3DXBUFFER m_pBuffMatModel;	//�}�e���A�����ւ̃|�C���^
	static DWORD m_nNumMatModel;	//�}�e���A�����̐�
	static LPDIRECT3DTEXTURE9 m_apTexture[ENEMY_MAX]; // �e�N�X�`��
	D3DXVECTOR3 m_move;        // �ړ���
	CCollision *m_pCollision;    // �����蔻��
};

#endif