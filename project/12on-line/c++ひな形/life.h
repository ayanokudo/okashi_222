//=============================================================================
//
// life���� [life.h]
// Author : ����r�H
//
//=============================================================================
#ifndef _LIFE_H_
#define _LIFE_H_

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "polygon.h"
//*****************************
// �O���錾
//*****************************

//*****************************
// �}�N����`
//*****************************
#define LIFE_SIZE D3DXVECTOR3(17.0f,21.0f,0.0f)

//*****************************
//�N���X
//*****************************
class CLife : public CPolygon
{
public:
	// �����o�֐�
	CLife();
	~CLife();
	static CLife *Create(const D3DXVECTOR3 pos);
	static HRESULT Load(void);
	static void Unload(void);
	HRESULT Init(const D3DXVECTOR3 pos);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	// �����o�ϐ�
	static LPDIRECT3DTEXTURE9 m_pTexture;	 // �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9   m_pVtxBuff;	 // ���_�o�b�t�@�ւ̃|�C��ta

};


#endif
