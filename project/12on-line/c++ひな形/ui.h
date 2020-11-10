//=============================================================================
//
//	ui�w�b�_ [ui.h]
//	Author : ����@�r�H
//
//=============================================================================

//��d�C���N���[�h�h�~
#ifndef _UI_H_
#define _UI_H_

#define MAX_UI UI_MAX
//*****************************
//�C���N���[�h
//*****************************
#include "main.h"
#include "scene.h"

//*****************************
// �N���X��`
//*****************************

//UI�N���X
class CUi
{
public:
	//UI�̎��
	typedef enum
	{
		UI_TIME = 0,	//�^�C��
		UI_TITLE,		//�^�C�g��
		UI_ENTER,		//�v���X�G���^�[
		UI_WARNING,		//�댯
		UI_ATTACK_NAIL,	//�U����
		UI_ATTACK_CRY,	//�U������
		UI_DASH,		//�_�b�V��
		UI_CHOCO,		//�`���R
		UI_MILK,		//�~���N
		UI_MAX
	}UI;

	CUi();
	~CUi();

	static CUi *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXCOLOR col, const UI type);
	static HRESULT Load(void);
	static void Unload(void);

	HRESULT Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXCOLOR col, const UI type);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// �J���[�̃Z�b�g�A�擾
	void SetColor(const D3DXCOLOR col);
	D3DXCOLOR GetColor(void) { return m_col; }
private:
	// �����o�ϐ�
	static LPDIRECT3DTEXTURE9 m_apTexture[MAX_UI];	 // �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9   m_pVtxBuff;	 // ���_�o�b�t�@�ւ̃|�C��
	D3DXCOLOR m_col;
	D3DXVECTOR3 m_move;					 // �ړ���
	D3DXVECTOR3 m_pos;
	UI m_type;
	float m_fAngle;                      // �|���S���̉�]�p�x
	D3DXVECTOR3 m_size;                  // �|���S���̃T�C�Y
};
#endif // !_UI_H_
