//=============================================================================
//
// wall�w�b�_ [wall.h]
// Author : ����@�r�H
//
//=============================================================================

//��d�C���N���[�h�h�~
#ifndef _WALL_H_
#define _WALL_H_

//*****************************
//�C���N���[�h
//*****************************
#include "main.h"
#include "scene3d.h"

//*****************************
//�O���錾
//*****************************
class CPlayer;
class CCollision;
//*****************************
//�N���X��`
//*****************************
class CWall : public CScene3d
{
public:
	//���̃e�N�X�`���̎��
	typedef enum
	{
		WALL_1 = 0,	//�t���[�����O
		WALL_2,			//�}�b�g
		WALL_3,		//�L�b�`��
		WALL_MAX,
	}WALL;

	//�����o�֐�
	CWall();
	~CWall();
	static CWall * Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, WALL type);
	static HRESULT Load(void);
	static void Unload(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	CCollision *GetCollision(void) { return m_pCollision; }

private:
	//�����o�ϐ�
	static LPDIRECT3DTEXTURE9 m_apTexture[WALL_MAX];//�e�N�X�`��
	WALL m_type;
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_posold;
	D3DXVECTOR3 m_size;
	CCollision *m_pCollision;
};

#endif 