//=============================================================================
//
// lose�w�b�_ [lose.h]
// Author : ����@�r�H
//
//=============================================================================

//��d�C���N���[�h�h�~
#ifndef _LOSE_H_
#define _LOSE_H_

//*****************************
//�C���N���[�h
//*****************************
#include "main.h"
#include "scene.h"

//=============================
// �O���錾
//=============================
class CPolygon;

//*****************************
//�N���X��`
//*****************************

//2d�|���S���N���X
class CLose : public CScene
{
public:
	// �����o�֐�
	CLose();
	~CLose();
	static CLose *Create(void);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	// �����o�ϐ�
	static LPDIRECT3DTEXTURE9 m_pTexture;        // �e�N�X�`���ւ̃|�C���^
	CPolygon *m_pPolygon;

};

#endif