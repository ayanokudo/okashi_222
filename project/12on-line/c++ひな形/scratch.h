//=============================================================================
//
// scratch�w�b�_ [scratch.h]
// Author : ���V ����
//
//=============================================================================

//��d�C���N���[�h�h�~
#ifndef _SCRATCH_H_
#define _SCRATCH_H_

//*****************************
// �C���N���[�h
//*****************************
#include "main.h"
#include "scene3d.h"

//*****************************
// �}�N����`
//*****************************
#define SCRATCH_SIZE_PLAYER 180   // �T�C�Y
#define SCRATCH_SIZE_ENEMY 100   // �T�C�Y
#define SCRATCH_COLLISION_SIZE_PLAYER 150


// �����蔻��̃T�C�Y
#define SCRATCH_COLLISION_SIZE_ENEMY 100   // �����蔻��̃T�C�Y
#define SCRATCH_HEIGHT 75 // �v���C���[��荂���ʒu�ɒu��
//*****************************
// �O���錾
//*****************************
class CCollision;

//*****************************
// �N���X��`
//*****************************

 
// �e�N���X
class CScratch : public CScene3d
{
public:
	typedef enum
	{
		SCRATCHUSER_PLAYER,
		SCRATCHUSER_ENEMY,
		SCRATCHUSER_BOSS,
		SCRATCHUSER_MAX,
	}SCRATCHUSER;

	//�����o�֐�
	CScratch();
	~CScratch();
	static CScratch *Create(const D3DXVECTOR3 pos, const float fAngle, const  SCRATCHUSER user, const int nPlayerNum);
	static HRESULT Load(void);
	static void Unload(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	void CollisionScratch(SCRATCHUSER user);
	void Animation(void);
	// �����o�ϐ�
	static LPDIRECT3DTEXTURE9 m_apTexture[SCRATCHUSER_MAX]; // �e�N�X�`��
	SCRATCHUSER m_user; // �o���b�g���[�U�[
	CCollision*m_pCollision;    // �R���W�����N���X�̃|�C���^
	int m_nPlayerNum;   // �ǂ̃v���C���[�̍U����
	int m_nCntAnim;     // �A�j���[�V�����J�E���g
	int m_nAnimX;       // �A�j���[�V����X��
	int m_nAnimY;       // �A�j���[�V����Y��
	bool m_bAttackEnemy;
	bool m_bAttackPlayer;
};

#endif