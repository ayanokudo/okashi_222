//=============================================================================
//
// player�w�b�_ [player.h]
// Author : ���V ����
//
//=============================================================================

//��d�C���N���[�h�h�~
#ifndef _PLAYER_H_
#define _PLAYER_H_

//*****************************
// �C���N���[�h
//*****************************
#include "main.h"
#include "model.h"

//*****************************
// �N���X��`
//*****************************

// �p�[�e�B�N���N���X
class CPlayer : public CModel
{
public:

	//�����o�֐�
	CPlayer();
	~CPlayer();
	static CPlayer *Create(D3DXVECTOR3 pos);
	static HRESULT Load(void);
	static void Unload(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	void Move(void);
	void Attack(void);

	// �����o�ϐ�
	static LPD3DXMESH m_pMeshModel;	//���b�V�����ւ̃|�C���^
	static LPD3DXBUFFER m_pBuffMatModel;	//�}�e���A�����ւ̃|�C���^
	static DWORD m_nNumMatModel;	//�}�e���A�����̐�
	static LPDIRECT3DTEXTURE9 m_apTexture; // �e�N�X�`��
	D3DXVECTOR3 m_move;        // �ړ���
};

#endif