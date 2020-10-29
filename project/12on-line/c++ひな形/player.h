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

//*****************************
// �O���錾
//*****************************
class CCollision;
class CAnimation;

//*****************************
// �}�N����`
//*****************************

//*****************************
// �N���X��`
//*****************************

// �p�[�e�B�N���N���X
class CPlayer : public CModelHierarchy
{
public:
	typedef enum
	{
		ANIM_WAIT = 0,
		ANIM_WALK,
		ANIM_VOICE,
		ANIM_PUNCH,
		ANIM_DASH,
		ANIM_MAX
	}ANIMATION;

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
	void AnimationFalse(void);

	// �����o�ϐ�
	static CModel::Model m_model[MAX_PARTS_NUM];
	static int m_nNumModel;
	static char m_chAnimPath[ANIM_MAX][64]; // �A�j���[�V�����e�L�X�g�̃p�X�i�[�p
	D3DXVECTOR3 m_move;           // �ړ���
	D3DXVECTOR3 m_moveDest;       // �ړ��ʂ̖ڕW�l
	float m_fRotYDist;            // �v���C���[�̌����Ă�������̖ڕW�l
	int m_nPlayerNum;             // �v���C���[�ԍ�
	CCollision*m_pCollision;      // �R���W�����N���X�̃|�C���^
	CAnimation*m_pWalkAnim;       // �����A�j���[�V����
	CAnimation*m_pAnim[ANIM_MAX]; // �A�j���[�V�����|�C���^
};

#endif