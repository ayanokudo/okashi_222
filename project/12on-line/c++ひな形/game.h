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
class CItem;
class CScore;
class CTime;
class CUi;

//*****************************
// マクロ定義
//*****************************
#define MAX_PLAYER 2
#define UI_PLAYER 5

//*****************************
//クラス定義
//*****************************

//ゲームクラス
class CGame : public CScene
{
public:
	// メンバ関数
	CGame();
	~CGame();
	static CGame *Create(void);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);


	static CCamera *GetCamera(void) { return m_pCamera; }  // カメラの取得処理
	static CPlayer *GetPlayer(int nIndex = 0) { return m_pPlayer[nIndex]; }  // プレイヤーの取得処理
	static CEnemy  *GetEnemy(void)  { return m_pEnemy; }   // エネミーの取得処理
	static CItem   *GetItem(void)	{ return m_pItem; }	   // アイテムの取得処理
	static CScore  *GetScore(void)  { return m_pScore; }   // スコアの取得処理
	static CTime   *GetTime(void)   { return m_pTime; }	   // タイムの取得処理
private:
	// メンバ変数
	static CCamera*m_pCamera;	// カメラ
	static CPlayer*m_pPlayer[MAX_PLAYER];	// プレイヤー
	static CEnemy*m_pEnemy;		// エネミー
	static CItem*m_pItem;		// アイテム
	static CScore*m_pScore;		// スコア
	static CTime*m_pTime;		// アイテム
	static CLight *m_pLight;	// ライト
	CUi* m_pUi[UI_PLAYER];
}; 

#endif