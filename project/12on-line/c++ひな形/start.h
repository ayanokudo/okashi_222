//=============================================================================
//
// start�w�b�_ [start.h]
// Author : ���V ����
//
//=============================================================================

//��d�C���N���[�h�h�~
#ifndef _START_H_
#define _START_H_

//*****************************
//�C���N���[�h
//*****************************
#include "main.h"
#include "scene2d.h"

//*****************************
//�N���X��`
//*****************************
class CStart : public CScene2d
{
public:

	//�����o�֐�
	CStart();
	~CStart();
	static CStart * Create(void);
	static HRESULT Load(void);
	static void Unload(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	//�����o�ϐ�
	static LPDIRECT3DTEXTURE9 m_pTexture;//�e�N�X�`��
	int m_nCntLost;                      // ��莞�Ԃŏ���
};

#endif 