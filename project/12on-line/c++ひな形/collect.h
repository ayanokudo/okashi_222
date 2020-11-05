//=============================================================================
//
// collect�w�b�_ [collect.h]
// Author : ���V ����
//
//=============================================================================

//��d�C���N���[�h�h�~
#ifndef _COLLECT_H_
#define _COLLECT_H_

//*****************************
// �C���N���[�h
//*****************************
#include "main.h"
#include "scene.h"

//*****************************
// �O���錾
//*****************************
class CNumber;
class CPolygon;

//*****************************
// �}�N����`
//*****************************
#define COLLET_PAR_DIGIT 3 // %�̌���
#define COLLET_DIGIT 2     // ����������̌���

//*****************************
// �N���X��`
//*****************************

// ������N���X
class CCollect :CScene
{
public:
	typedef enum
	{
		SLASH = 0,
		PERCENT,
		MAX_PARTS
	}PARTS;
	//�����o�֐�
	CCollect();
	~CCollect();
	static CCollect *Create(void);
	static HRESULT Load(void);
	static void Unload(void);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static void InitVariable(void);
	static void Collect(void) { m_nNumCollect++; }

private:
	// �����o�ϐ�
	static LPDIRECT3DTEXTURE9 m_apTexture[MAX_PARTS]; // �e�N�X�`���ւ̃|�C���^
	static int m_nNumCollect;             // ���������
	int m_nPerCollect;                    // �����
	CPolygon*m_pPolygon[MAX_PARTS];       // �i���o�[�ȊO�̉摜
	CNumber*m_pNumObj[COLLET_DIGIT];      // ����Ώۂ̐��̃i���o�[�|���S��
	CNumber*m_pNumCollect[COLLET_DIGIT];  // ����������̃i���o�[�|���S��
	CNumber*m_pNumPer[COLLET_PAR_DIGIT];  // %�̃i���o�[�|���S��
};

#endif