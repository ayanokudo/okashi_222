//=============================================================================
//
// itemヘッダ [item.h]
// Author : 筒井　俊稀
//
//=============================================================================

//二重インクルード防止
#ifndef _ITEM_H_
#define _ITEM_H_

//*****************************
// インクルード
//*****************************
#include "main.h"
#include "model.h"

//*****************************
// 前方宣言
//*****************************
class CCollision;

//*****************************
// クラス定義
//*****************************

// パーティクルクラス
class CItem : public CModel
{
public:

	//メンバ関数
	CItem();
	~CItem();
	static CItem *Create(D3DXVECTOR3 pos);
	static HRESULT Load(void);
	static void Unload(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	void Direction(void);
	void Attack(void);

	// メンバ変数
	static LPD3DXMESH m_pMeshModel;	//メッシュ情報へのポインタ
	static LPD3DXBUFFER m_pBuffMatModel;	//マテリアル情報へのポインタ
	static DWORD m_nNumMatModel;	//マテリアル情報の数
	static LPDIRECT3DTEXTURE9 m_apTexture; // テクスチャ
	CCollision*m_pCollision;    // コリジョンクラスのポインタ
};

#endif