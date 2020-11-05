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
#define COLLET_OBJ_NUM_DIGIT 2 // ����Ώې��̌���
#define COLLET_NUM_DIGIT 3     // ������̌���

//*****************************
// �N���X��`
//*****************************

// ������N���X
class CCollect :CScene
{
public:

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
	static void AddObj(int nNum = 1) { m_nNumObj += nNum; }
	static void Collect(void) { m_nNumCollect++; }

private:
	// �����o�ϐ�
	static LPDIRECT3DTEXTURE9 m_pTexture;        // �e�N�X�`���ւ̃|�C���^
	static int m_nNumObj;      // ����Ώۂ̐�
	static int m_nNumCollect;  // ���������
	float m_fPerCollect;       // �����
	CPolygon*m_pPolygon;       // "/"�̉摜
	CNumber*m_pNumObj[COLLET_OBJ_NUM_DIGIT]; // ����Ώۂ̐��̃i���o�[�|���S��
	CNumber*m_pNumCollect[COLLET_NUM_DIGIT]; // ����������̃i���o�[�|���S��
};

#endif