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
#include "model_hierarchy.h"

//*****************************
// �O���錾
//*****************************
class CCollision;
class CMotion;

//*****************************
// �N���X��`
//*****************************

// �p�[�e�B�N���N���X
class CEnemy : public CModelHierarchy
{
public:
	typedef enum
	{
		WALK = 0,	  // ����
		MOTION_MAX
	}MOTION;

	typedef enum
	{
		ENEMY_CARRIER = 0,		//���َq�^��ł�G
		ENEMY_ESCORT,			//BOSS����Ă�G
		ENEMY_MAX,
	}ENEMY;

	//�����o�֐�
	CEnemy();
	~CEnemy();
	static CEnemy *Create(D3DXVECTOR3 pos, ENEMY type);
	static HRESULT Load(void);
	static void Unload(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Hit(int nDamage);
	CCollision *GetCollision(void) { return m_pCollision; }
private:
	//�e�G�L�����̓����̏���
	void RangeDecisionCarrier(void);
	void RangeDecisionEscort(void);
	void MotionCarrier(void);
	void MotionEscort(void);
	void Move(void);
	void Direction(void);

	// �����o�ϐ�
	// �����o�ϐ�
	static CModel::Model m_model[ENEMY_MAX][MAX_PARTS_NUM]; // ���f�����
	static int m_nNumModel;                      // ���f����
	static char m_achAnimPath[MOTION_MAX][64];   // �A�j���[�V�����e�L�X�g�̃p�X�i�[�p

	//static LPD3DXMESH m_pMeshModel[ENEMY_MAX];	//���b�V�����ւ̃|�C���^
	//static LPD3DXBUFFER m_pBuffMatModel[ENEMY_MAX];	//�}�e���A�����ւ̃|�C���^
	//static DWORD m_nNumMatModel[ENEMY_MAX];	//�}�e���A�����̐�
	//static LPDIRECT3DTEXTURE9 m_apTexture[ENEMY_MAX]; // �e�N�X�`��
	D3DXVECTOR3 m_move;        // �ړ���
	D3DXVECTOR3 m_moveDest;
	CCollision *m_pCollision;    // �����蔻��
	CCollision *m_pRadiusColision;
	ENEMY m_type;
	int m_nLife;
	bool m_bRd;
	float m_fRotYDist;
	int m_nCount;
	int m_nCntAttack;
	int m_nCountMotion;
	int m_nCountRand;
	CMotion*m_pMotion[MOTION_MAX];  // �A�j���[�V�����|�C���^
};

#endif