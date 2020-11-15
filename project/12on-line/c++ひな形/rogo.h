//=============================================================================
//
// titleヘッダ [title.h]
// Author : 筒井 俊稀
//
//=============================================================================

//二重インクルード防止
#ifndef _ROGO_H_
#define _ROGO_H_

//*****************************
//インクルード
//*****************************
#include "main.h"
#include "scene.h"

//=============================
// 前方宣言
//=============================
class CPolygon;
class CScene2d;

//*****************************
//クラス定義
//*****************************

//2dポリゴンクラス
class CRogo : public CScene
{
public:
	typedef enum
	{
		BG = 0,
		EXIT,
		START,
		TUTORIAL,
		MENU_MAX
	}TITLE_MENU;

	// 猫の種類
	typedef enum
	{
		MILK = 0,
		CHOCO,
		CAT_MAX
	};

	// メンバ関数
	CRogo();
	~CRogo();
	static CRogo *Create(void);
	static HRESULT Load(void);
	static void Unload(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	// メンバ変数
	static LPDIRECT3DTEXTURE9 m_apTexture[MENU_MAX];        // テクスチャへのポインタ
	static LPDIRECT3DTEXTURE9 m_apCatTex[CAT_MAX];        // テクスチャへのポインタ
	CPolygon *m_apPolygon[MENU_MAX];
	int m_nMenu;
	bool m_bStick;
	int m_nCount;
	CScene2d*m_pScene2d[CAT_MAX];

	// 猫のアニメーション用
	int m_nCntAnim;       // アニメーションカウント
	int m_nAnimX;         // アニメーションX軸
	int m_nAnimY;         // アニメーションY軸
};

#endif