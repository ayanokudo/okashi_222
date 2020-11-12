//=============================================================================
//
// titleヘッダ [title.h]
// Author : 増澤 未来
//
//=============================================================================

//二重インクルード防止
#ifndef _TITLE_H_
#define _TITLE_H_

//*****************************
//インクルード
//*****************************
#include "main.h"
#include "scene.h"

//=============================
// 前方宣言
//=============================
class CPolygon;
class CUi;

//*****************************
//クラス定義
//*****************************

//2dポリゴンクラス
class CTitle : public CScene
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

	// メンバ関数
	CTitle();
	~CTitle();
	static CTitle *Create(void);
	static HRESULT Load(void);
	static void Unload(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	// メンバ変数
	static LPDIRECT3DTEXTURE9 m_apTexture[MENU_MAX];        // テクスチャへのポインタ
	CPolygon *m_apPolygon[MENU_MAX];
	CUi* m_pUi;
	int m_nMenu;
	bool m_bStick;

};

#endif