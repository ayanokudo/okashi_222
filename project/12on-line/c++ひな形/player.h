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
// �O���錾
//*****************************
class CCollision;

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
	static CPlayer *Create(D3DXVECTOR3 pos,int nPlayerNum);
	static HRESULT Load(void);
	static void Unload(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	void MoveKeyboard(void);
	void MoveController(void);
	void Direction(void);
	void Attack(void);

	// �����o�ϐ�
	static LPD3DXMESH m_pMeshModel;	//���b�V�����ւ̃|�C���^
	static LPD3DXBUFFER m_pBuffMatModel;	//�}�e���A�����ւ̃|�C���^
	static DWORD m_nNumMatModel;	//�}�e���A�����̐�
	static LPDIRECT3DTEXTURE9 m_apTexture; // �e�N�X�`��
	D3DXVECTOR3 m_move;        // �ړ���
	D3DXVECTOR3 m_moveDest;    // �ړ��ʂ̖ڕW�l
	float m_fRotYDist;         // �v���C���[�̌����Ă�������̖ڕW�l
	int m_nPlayerNum;          // �v���C���[�ԍ�
	CCollision*m_pCollision;    // �R���W�����N���X�̃|�C���^
};

#endif