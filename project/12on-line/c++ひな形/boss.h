//=============================================================================
//
// boss�w�b�_ [boss.h]
// Author : ���� �r�H
//
//=============================================================================

//��d�C���N���[�h�h�~
#ifndef _BOSS_H_
#define _BOSS_H_

//*****************************
// �C���N���[�h
//*****************************
#include "main.h"
#include "model_hierarchy.h"
#include "player.h"

//*****************************
// �O���錾
//*****************************
class CCollision;
class CMotion;
class CUi;

//*****************************
// �N���X��`
//*****************************

// �p�[�e�B�N���N���X
class CBoss : public CModelHierarchy
{
public:

	// ���[�V������
	typedef enum
	{
		SPAWN = 0,  // �N���Ƃ�
		WALK,       // ����
		BREARH,     // �u���X
		SCRATCH,    // �Ђ�����
		TAIL,       // ������
		MOTION_MAX
	}MOTION;

	// �U����
	typedef enum
	{
		ATTACK_BREARH = 0,     // �u���X
		ATTACK_SCRATCH,        // �Ђ�����
		ATTACK_TAIL,           // ������
		ATTACK_MAX
	}ATTACK;

	//�{�X�̍U�����@�ƃX�^���̃^�C�v����
	typedef enum
	{
		TYPE_ATTACK_RANGE = 0,		// �͈͍U��
		TYPE_ATTACK_FAR,			// �������U��
		TYPE_ATTACK_PROXIMITY,		// �ߐڍU��
		TYPE_NUMB,					// ���
		TYPE_MAX
	}BOSS;

	//�����o�֐�
	CBoss();
	~CBoss();
	static CBoss *Create(D3DXVECTOR3 pos);
	static HRESULT Load(void);
	static void Unload(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Hit(int nDamage);
	CCollision *GetCollision(void) { return m_pCollision; }
	MOTION      GetMotion(void) { return m_motionState; }

private:
	//�e�G�L�����̓����̏���
	void Move(void);
	void ChangeTarget(int nNum = 0);
	void Direction(void);
    void Attack(void);

	void Brearh(void);
	void Scratch(void);
	void Tail(void);

	void MotionManager(void);
	void MotionFalse(void);
	void SetMotion(MOTION motionState);

	// �����o�ϐ�
	static CModel::Model m_model[MAX_PARTS_NUM]; // ���f�����
	static int m_nNumModel;                      // ���f����
	static char m_achAnimPath[MOTION_MAX][64];   // �A�j���[�V�����e�L�X�g�̃p�X�i�[�p

	// �����o�ϐ�
	//static LPD3DXMESH m_pMeshModel;	//���b�V�����ւ̃|�C���^
	//static LPD3DXBUFFER m_pBuffMatModel;	//�}�e���A�����ւ̃|�C���^
	//static DWORD m_nNumMatModel;	//�}�e���A�����̐�
	//static LPDIRECT3DTEXTURE9 m_apTexture; // �e�N�X�`��
	D3DXVECTOR3 m_move;        // �ړ���
	D3DXVECTOR3 m_moveDest;
	CCollision *m_pCollision;        // �����蔻��
	CCollision *m_pCollisionTail;    // �����ۂ̓����蔻��
	CCollision *m_pRadiusColision;
	int m_nLife;
	bool m_bRd;
	float m_fRotYDist;
	int m_nCount;
	int m_nCountMotion;
	int m_nCountRand;
	int m_nCntMove;                 // �ړ����̃J�E���g
	int m_nCntBullet;               // �e�����Ƃ��̃J�E���g
	int m_nTargetNum;               // �ǂ̃v���C���[���^�[�Q�b�g���Ă��邩
	bool m_bHitTail[MAX_PLAYER];    // �����ۂ����i�q�b�g���Ȃ��悤��
	CUi* m_pUi;

	CMotion*m_pMotion[MOTION_MAX];  // �A�j���[�V�����|�C���^
	MOTION m_motionState;           // ���[�V�����X�e�[�g
	bool m_bMotion;                 // �ړ����~�߂�n�̃��[�V��������p

};

#endif