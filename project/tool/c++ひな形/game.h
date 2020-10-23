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
class CPlayer;
class CLight;
class CDebug;

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
	static CPlayer *GetPlayer(void) { return m_pPlayer; }  // �v���C���[�̎擾����
private:
	// �����o�ϐ�
	static CCamera*m_pCamera; // �J����
	static CPlayer*m_pPlayer; // �v���C���[
	static CLight *m_pLight;   // ���C�g

#if _DEBUG
    static CDebug *m_pDebug;    // �f�o�b�O
#endif // _DEBUG
}; 

#endif