//=============================================================================
//
// bullet�w�b�_ [bullet.h]
// Author : ���V ����
//
//=============================================================================

//��d�C���N���[�h�h�~
#ifndef _BULLET_H_
#define _BULLET_H_

//*****************************
// �C���N���[�h
//*****************************
#include "main.h"
#include "scene3d.h"

//*****************************
// �}�N����`
//*****************************
#define BULLET_SPEED_PLAYER 25    // ���x(�v���C���[�̒e)
#define BULLET_SPEED_ENEMY 20     // ���x(�G�l�~�[�̒e)
#define BULLET_SIZE 100            // �T�C�Y

//*****************************
// �O���錾
//*****************************
class CCollision;

//*****************************
// �N���X��`
//*****************************

// �e�N���X
class CBullet : public CScene3d
{
public:
	typedef enum
	{
		BULLETUSER_PLAYER,
		BULLETUSER_ENEMY,
		BULLETUSER_MAX,
	}BULLETUSER;

	//�����o�֐�
	CBullet();
	~CBullet();
	static CBullet *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 move, const int nLife, const  BULLETUSER user);
	static HRESULT Load(void);
	static void Unload(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	
private:
	void CollisionBullet(BULLETUSER user);
	// �����o�ϐ�
	static LPDIRECT3DTEXTURE9 m_pTexture; // �e�N�X�`��
	D3DXVECTOR3 m_move; // �ړ���
	int m_nLife;        // ����
	BULLETUSER m_user; // �o���b�g���[�U�[
	CCollision*m_pCollision;    // �R���W�����N���X�̃|�C���^
};

#endif