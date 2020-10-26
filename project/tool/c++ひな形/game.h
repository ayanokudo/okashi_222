//=============================================================================
//
// game�w�b�_ [game.h]
// Author : ���V ����
//
//=============================================================================

//��d�C���N���[�h�h�~
#ifndef _GAME_H_
#define _GAME_H_

//*****************************
//�C���N���[�h
//*****************************
#include "main.h"
#include "scene.h"

//=============================
// �O���錾
//=============================
class CRenderer;
class CInputKeyboard;
class CInputJoypad;
class CInputMouse;
class CSound;
class CCamera;
class CLight;
class CDebug;
class CObject;

//*****************************
//�N���X��`
//*****************************

//2d�|���S���N���X
class CGame : public CScene
{
public:
	// �����o�֐�
	CGame();
	~CGame();
	static CGame *Create(void);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);


	static CCamera *GetCamera(void) { return m_pCamera; }  // �J�����̎擾����

    // �I�u�W�F�N�g�̏��̃Q�b�^
    static CObject *GetObjectData(void) { return m_pObject; }

private:
	// �����o�ϐ�
    static CObject *m_pObject;      // �I�u�W�F�N�g�ւ̃|�C���^
	static CCamera *m_pCamera;      // �J����
	static CLight  *m_pLight;       // ���C�g

#if _DEBUG
    static CDebug *m_pDebug;    // �f�o�b�O
#endif // _DEBUG
}; 

#endif