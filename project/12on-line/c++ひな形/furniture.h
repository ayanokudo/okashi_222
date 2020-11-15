//=============================================================================
//
// wall�w�b�_ [wall.h]
// Author : ����@�r�H
//
//=============================================================================

//��d�C���N���[�h�h�~
#ifndef _FURNITURE_H_
#define _FURNITURE_H_

//*****************************
//�C���N���[�h
//*****************************
#include "main.h"
#include "scene3d.h"
#include "model.h"

//*****************************
//�O���錾
//*****************************
class CPlayer;
class CCollision;

//*****************************
//�N���X��`
//*****************************
class CFurniture : public CModel
{
public:
	//���̃e�N�X�`���̎��
	typedef enum
	{
		FURNITURE_CHAIR = 0,	//�֎q
		FURNITURE_TABLE,		//�}�b�g
		FURNITURE_CHEST,		//�L�b�`��
		FURNITURE_TLEX,		//�L�b�`��
		FURNITURE_WOOD,		//�L�b�`��
		FURNITURE_BENCH,		//�L�b�`��
		FURNITURE_MAX,

	}FURNITURE;

	//�����o�֐�
	CFurniture();
	~CFurniture();
	static CFurniture * Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const D3DXVECTOR3 size, FURNITURE type);
	static HRESULT Load(void);
	static void Unload(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	CCollision *GetCollision(void) { return m_pCollision; }

private:
	void CollisionPlayer(void);
	void CollisionEnemy(void);
	void CollisionBoss(void);
	void CollisionBullet(void);

	// �����o�ϐ�
	static LPDIRECT3DTEXTURE9 m_apTexture[FURNITURE_MAX];//�e�N�X�`��
	FURNITURE m_type;
	D3DXVECTOR3 m_pos;      // �ʒu
	D3DXVECTOR3 m_rot;      // �p�x
	D3DXVECTOR3 m_posold;
	D3DXVECTOR3 m_size;     // �T�C�Y
	CCollision *m_pCollision;
	static Model m_model[FURNITURE_MAX];
    static char *m_apTextureName[FURNITURE_MAX];
};

#endif 