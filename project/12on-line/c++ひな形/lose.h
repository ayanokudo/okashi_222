//=============================================================================
//
// loseヘッダ [lose.h]
// Author : 筒井　俊稀
//
//=============================================================================

//二重インクルード防止
#ifndef _LOSE_H_
#define _LOSE_H_

//*****************************
//インクルード
//*****************************
#include "main.h"
#include "scene.h"

//=============================
// 前方宣言
//=============================
class CPolygon;

//*****************************
//クラス定義
//*****************************

//2dポリゴンクラス
class CLose : public CScene
{
public:
	// メンバ関数
	CLose();
	~CLose();
	static CLose *Create(void);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	// メンバ変数
	static LPDIRECT3DTEXTURE9 m_pTexture;        // テクスチャへのポインタ
	CPolygon *m_pPolygon;

};

#endif