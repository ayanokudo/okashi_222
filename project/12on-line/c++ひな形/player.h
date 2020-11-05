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
#include "model_hierarchy.h"
#include "game.h"

//*****************************
// �O���錾
//*****************************
class CCollision;
class CMotion;
class CUi;

//*****************************
// �}�N����`
//*****************************
#define UI_PLAYER 3

//*****************************
// �N���X��`
//*****************************

// �p�[�e�B�N���N���X
class CPlayer : public CModelHierarchy
{
public:
	//�e�p�[�c�^�C�v����
	typedef enum
	{
		WAIT = 0, // �ҋ@
		WALK,	  // ����
		VOICE,	  // ����
		PUNCH,	  // �p���`
		DASH,	  // ����
		MOTION_MAX
	}MOTION;

	//�ړ��^�C�v����
	typedef enum
	{
		TYPE_WALK = 0,	//����
		TYPE_DASH,		//�_�b�V��
		TYPE_MAX
	}PLAYERTYPE;

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

	CCollision*GetCollision(void) { return m_pCollision; }
	D3DXVECTOR3 GetMove(void) { return m_move; }
	void GetMove(D3DXVECTOR3 move) { m_move = move; }
	
private:
	void MoveKeyboard(void);
	void MoveController(void);
	void Direction(void);
	void Attack(void);
	void Life(void);
	void MotionManager(void);
	void MotionFalse(void);
	void SetMotion(MOTION motionState);

	// �����o�ϐ�
	static CModel::Model m_model[MAX_PLAYER][MAX_PARTS_NUM]; // ���f�����
	static int m_nNumModel;                      // ���f����
	static char m_achAnimPath[MOTION_MAX][64];   // �A�j���[�V�����e�L�X�g�̃p�X�i�[�p

	D3DXVECTOR3 m_move;             // �ړ���
	D3DXVECTOR3 m_moveDest;         // �ړ��ʂ̖ڕW�l
	float m_fRotYDist;              // �v���C���[�̌����Ă�������̖ڕW�l
	int m_nPlayerNum;               // �v���C���[�ԍ�
	CCollision*m_pCollision;        // �R���W�����N���X�̃|�C���^
	CMotion*m_pMotion[MOTION_MAX];  // �A�j���[�V�����|�C���^
	int m_nLife;					// �v���C���[�̃��C�t
	MOTION m_motionState;           // ���݂̃��[�V�������
	int m_nSpeed;
	bool m_bAttack;                 // �U�����Ă��邩�̔���p
	CUi* m_pUi[UI_PLAYER];
};

#endif