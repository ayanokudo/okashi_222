//=============================================================================
//
// life処理 [life.h]
// Author : 筒井俊稀
//
//=============================================================================
#ifndef _LIFE_H_
#define _LIFE_H_

//=============================================================================
//インクルードファイル
//=============================================================================
#include "main.h"
#include "polygon.h"
//*****************************
// 前方宣言
//*****************************

//*****************************
// マクロ定義
//*****************************
#define LIFE_SIZE D3DXVECTOR3(17.0f,21.0f,0.0f)

//*****************************
//クラス
//*****************************
class CLife : public CPolygon
{
public:
	// メンバ関数
	CLife();
	~CLife();
	static CLife *Create(const D3DXVECTOR3 pos);
	static HRESULT Load(void);
	static void Unload(void);
	HRESULT Init(const D3DXVECTOR3 pos);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	// メンバ変数
	static LPDIRECT3DTEXTURE9 m_pTexture;	 // テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9   m_pVtxBuff;	 // 頂点バッファへのポインta

};


#endif
