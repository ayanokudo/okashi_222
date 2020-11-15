//=============================================================================
//
// gage�w�b�_ [gage.h]
// Author : ���V ����
//
//=============================================================================

//��d�C���N���[�h�h�~
#ifndef _GAGE_H_
#define _GAGE_H_

//*****************************
//�C���N���[�h
//*****************************
#include "main.h"
#include "scene.h"

//*****************************
//�O���錾
//*****************************
class CPolygon;

//*****************************
//�N���X��`
//*****************************

//�Q�[�W�N���X
class CGage : public CScene
{
public:
	// HP�o�[�̃p�[�c��
	typedef enum
	{
		BAR_BACK = 0,
		BAR_RED,
		BAR_FRONT,
		BAR_FRAME,
		BAR_PARTS_MAX,
	}BAR_PARTS;

	// �����o�֐�
	CGage();
	~CGage();
	static CGage *Create(void);
	static HRESULT Load(void);
	static void Unload(void);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	// �����o�ϐ�
	static LPDIRECT3DTEXTURE9 m_pTexture;     // �e�N�X�`���ւ̃|�C���^
	static LPDIRECT3DTEXTURE9 m_pIconTexture; // �A�C�R���̃e�N�X�`��
	CPolygon* m_apPolygon[BAR_PARTS_MAX]; // ���C�t�`��p�̃|���S��
	CPolygon* m_pIcon;                    // �A�C�R���摜
	float m_fRedLife;                     // �Ԃ��Q�[�W�����񂾂񌸂��Ă����p
	D3DXVECTOR3 m_leftPos;                // ���C�t�̍��[
	float m_fBarWidht;                    // ��
	float m_fBarHeight;                   // ����
	int m_nMaxNum;                       // ���C�t�̍ő吔
};

#endif