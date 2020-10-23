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
class CDebug;

//*****************************
//クラス定義
//*****************************

//2dポリゴンクラス
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
	static CPlayer *GetPlayer(void) { return m_pPlayer; }  // プレイヤーの取得処理
private:
	// メンバ変数
	static CCamera*m_pCamera; // カメラ
	static CPlayer*m_pPlayer; // プレイヤー
	static CLight *m_pLight;   // ライト

#if _DEBUG
    static CDebug *m_pDebug;    // デバッグ
#endif // _DEBUG
}; 

#endif