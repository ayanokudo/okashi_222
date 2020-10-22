//=============================================================================
//
// floor�w�b�_ [floor.h]
// Author : ����@�r�H
//
//=============================================================================

//��d�C���N���[�h�h�~
#ifndef _FLOOR_H_
#define _FLOOR_H_

//*****************************
//�C���N���[�h
//*****************************
#include "main.h"
#include "scene3d.h"

//*****************************
//�N���X��`
//*****************************
class CFloor : public CScene3d
{
public:
	//���̃e�N�X�`���̎��
	typedef enum
	{
		FLOOR_FLOORING = 0,	//�t���[�����O
		FLOOR_MAT,			//�}�b�g
		FLOOR_KITCHEN,		//�L�b�`��
		FLOOR_MAX,
	}FLOOR;

	//�����o�֐�
	CFloor();
	~CFloor();
	static CFloor * Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, FLOOR type);
	static HRESULT Load(void);
	static void Unload(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	//�����o�ϐ�
	static LPDIRECT3DTEXTURE9 m_apTexture[FLOOR_MAX];//�e�N�X�`��
	FLOOR m_type;
};

#endif 