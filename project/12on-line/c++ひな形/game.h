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
class CEnemy;

//*****************************
// �}�N����`
//*****************************
#define MAX_PLAYER 2

//*****************************
//�N���X��`
//*****************************

//�Q�[���N���X
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
	static CPlayer *GetPlayer(int nIndex = 0) { return m_pPlayer[nIndex]; }  // �v���C���[�̎擾����
	static CEnemy  *GetEnemy(void)  { return m_pEnemy; }   // �G�l�~�[�̎擾����
private:
	// �����o�ϐ�
	static CCamera*m_pCamera;	// �J����
	static CPlayer*m_pPlayer[MAX_PLAYER];	// �v���C���[
	static CEnemy*m_pEnemy;		// �G�l�~�[
	static CLight *m_pLight;	// ���C�g
}; 

#endif