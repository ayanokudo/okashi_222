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
class CBoss;
class CItem;
class CScore;
class CTime;
class CUi;
class CLostPoint;
class CFurniture;
//*****************************
// �}�N����`
//*****************************
#define MAX_PLAYER 2
#define UI_PLAYER 6

//*****************************
//�N���X��`
//*****************************

//�Q�[���N���X
class CGame : public CScene
{
public:
	typedef enum
	{
		GAME_NORMAL=0,
		GAME_BOSS,
		GAME_MAX
	}GAME_MODE;

	// �����o�֐�
	CGame();
	~CGame();
	static CGame *Create(void);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);


	static CCamera    *GetCamera(void) { return m_pCamera; }  // �J�����̎擾����
	static CPlayer    *GetPlayer(int nIndex = 0) { return m_pPlayer[nIndex]; }  // �v���C���[�̎擾����
	static CEnemy     *GetEnemy(void)  { return m_pEnemy; }   // �G�l�~�[�̎擾����
    static CBoss      *GetBoss(void)   { return m_pBoss; }
	static CItem      *GetItem(void)   { return m_pItem; }	   // �A�C�e���̎擾����
	static CScore     *GetScore(void)  { return m_pScore; }   // �X�R�A�̎擾����
	static CTime      *GetTime(void)   { return m_pTime; }	   // �^�C���̎擾����
	static CLostPoint *GetLostPoint(void) { return m_pLostPoint; }	   // �^�C���̎擾����
	static CFurniture *GetFurniture(void) { return m_pFurniture; }
	static GAME_MODE   GetGameMode(void) { return m_gameMode; }
	static void        SetGameMode(GAME_MODE mode);
private:
	void Ui(void);

	// �����o�ϐ�
	static CCamera*m_pCamera;	// �J����
	static CPlayer*m_pPlayer[MAX_PLAYER];	// �v���C���[
	static CEnemy*m_pEnemy;		// �G�l�~�[
    static CBoss   *m_pBoss;    // �{�X
	static CItem*m_pItem;		// �A�C�e��
	static CScore*m_pScore;		// �X�R�A
	static CTime*m_pTime;		// �A�C�e��
	static CLight *m_pLight;	// ���C�g
	static CLostPoint*m_pLostPoint;// �G��������|�C���g
	static CFurniture*m_pFurniture;
	CUi* m_pUi[UI_PLAYER];
	static GAME_MODE m_gameMode;
}; 

#endif