//=============================================================================
//
// gameヘッダ [game.h]
// Author : 増澤 未来
//
//=============================================================================

//二重インクルード防止
#ifndef _GAME_H_
#define _GAME_H_

//*****************************
//インクルード
//*****************************
#include "main.h"
#include "scene.h"

//=============================
// 前方宣言
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
// マクロ定義
//*****************************
#define MAX_PLAYER 2
#define UI_PLAYER 6

//*****************************
//クラス定義
//*****************************

//ゲームクラス
class CGame : public CScene
{
public:
	typedef enum
	{
		GAME_NORMAL=0,
		GAME_BOSS,
		GAME_MAX
	}GAME_MODE;

	// メンバ関数
	CGame();
	~CGame();
	static CGame *Create(void);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);


	static CCamera    *GetCamera(void) { return m_pCamera; }  // カメラの取得処理
	static CPlayer    *GetPlayer(int nIndex = 0) { return m_pPlayer[nIndex]; }  // プレイヤーの取得処理
	static CEnemy     *GetEnemy(void)  { return m_pEnemy; }   // エネミーの取得処理
    static CBoss      *GetBoss(void)   { return m_pBoss; }
	static CItem      *GetItem(void)   { return m_pItem; }	   // アイテムの取得処理
	static CScore     *GetScore(void)  { return m_pScore; }   // スコアの取得処理
	static CTime      *GetTime(void)   { return m_pTime; }	   // タイムの取得処理
	static CLostPoint *GetLostPoint(void) { return m_pLostPoint; }	   // タイムの取得処理
	static CFurniture *GetFurniture(void) { return m_pFurniture; }
	static GAME_MODE   GetGameMode(void) { return m_gameMode; }
	static void        SetGameMode(GAME_MODE mode);
private:
	void Ui(void);

	// メンバ変数
	static CCamera*m_pCamera;	// カメラ
	static CPlayer*m_pPlayer[MAX_PLAYER];	// プレイヤー
	static CEnemy*m_pEnemy;		// エネミー
    static CBoss   *m_pBoss;    // ボス
	static CItem*m_pItem;		// アイテム
	static CScore*m_pScore;		// スコア
	static CTime*m_pTime;		// アイテム
	static CLight *m_pLight;	// ライト
	static CLostPoint*m_pLostPoint;// 敵が消えるポイント
	static CFurniture*m_pFurniture;
	CUi* m_pUi[UI_PLAYER];
	static GAME_MODE m_gameMode;
}; 

#endif