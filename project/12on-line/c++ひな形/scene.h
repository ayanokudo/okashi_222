//=============================================================================
//
// scene�w�b�_ [scene.h]
// Author : ���V ����
//
//=============================================================================

//��d�C���N���[�h�h�~
#ifndef _SCENE_H_
#define _SCENE_H_

//�C���N���[�h
#include "main.h"

//***********************************
//�}�N����`
//***********************************
#define MAX_SCENE 1280   // �|���S���̍ő吔

//=============================
//�N���X��`
//=============================

//�V�[���N���X
class CScene
{
public:
	// �I�u�W�F�N�g�^�C�v��
	// �`�揇
	typedef enum
	{
		OBJTYPE_NONE = 0,
		OBJTYPE_BG,         // �w�i
		OBJTYPE_MAP,        // �}�b�v
		OBJTYPE_MANACIRCLE, // �}�i�T�[�N��
		OBJTYPE_ITEM,       // �A�C�e��
		OBJTYPE_EFFECT,     // �G�t�F�N�g
		OBJTYPE_BULLET,     // �e
		OBJTYPE_PLAYER,     // �v���C���[
		OBJTYPE_ENEMY,      // �G�l�~�[
		OBJTYPE_EXPLOSION,  // ����
		OBJTYPE_PARTICLE,   // �p�[�e�B�N��
		OBJTYPE_BOMB,       // �{��
		OBJTYPE_UI,         // UI
		OBJTYPE_FLOOR,		// ��
		OBJTYPE_MAX,        // �^�C�v�̍ő吔
	}OBJTYPE;

	// �����o�֐�
	CScene();
	virtual ~CScene();
	static void ReleaseAll(void);
	static void UpdateAll(void);
	static void DrawAll(void);
	static int GetNumAll(void) { return m_nNumAll; }
	static CScene* GetScene(int nIndex) { return m_apScene[nIndex]; }
	void SetObjType(const OBJTYPE objType) { m_type = objType; }
	OBJTYPE GetType(void) { return m_type; }
	int GetIndex(void) { return m_nNumIndex; } // �z��ԍ��̎擾


	// �������z�֐�
	virtual HRESULT Init(void) = 0;
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;
	
protected:
	void Release(void);
private:
	// �����o�ϐ�
	static CScene *m_apScene[MAX_SCENE];   // �|���S���Ǘ��p
	static int m_nNumAll;                  // ���������|���S����
	int m_nNumIndex;                       // ���������|���S���̔z��
	OBJTYPE m_type;                        // �I�u�W�F�N�g�^�C�v
};

#endif