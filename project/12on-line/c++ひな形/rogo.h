//=============================================================================
//
// title�w�b�_ [title.h]
// Author : ���� �r�H
//
//=============================================================================

//��d�C���N���[�h�h�~
#ifndef _ROGO_H_
#define _ROGO_H_

//*****************************
//�C���N���[�h
//*****************************
#include "main.h"
#include "scene.h"

//=============================
// �O���錾
//=============================
class CPolygon;
class CScene2d;

//*****************************
//�N���X��`
//*****************************

//2d�|���S���N���X
class CRogo : public CScene
{
public:
	typedef enum
	{
		BG = 0,
		EXIT,
		START,
		TUTORIAL,
		MENU_MAX
	}TITLE_MENU;

	// �L�̎��
	typedef enum
	{
		MILK = 0,
		CHOCO,
		CAT_MAX
	};

	// �����o�֐�
	CRogo();
	~CRogo();
	static CRogo *Create(void);
	static HRESULT Load(void);
	static void Unload(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	// �����o�ϐ�
	static LPDIRECT3DTEXTURE9 m_apTexture[MENU_MAX];        // �e�N�X�`���ւ̃|�C���^
	static LPDIRECT3DTEXTURE9 m_apCatTex[CAT_MAX];        // �e�N�X�`���ւ̃|�C���^
	CPolygon *m_apPolygon[MENU_MAX];
	int m_nMenu;
	bool m_bStick;
	int m_nCount;
	CScene2d*m_pScene2d[CAT_MAX];

	// �L�̃A�j���[�V�����p
	int m_nCntAnim;       // �A�j���[�V�����J�E���g
	int m_nAnimX;         // �A�j���[�V����X��
	int m_nAnimY;         // �A�j���[�V����Y��
};

#endif