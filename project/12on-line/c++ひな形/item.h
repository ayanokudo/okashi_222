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
	typedef enum
	{
		CANDY = 0,	// 回収するやつ
		KOBAN,		// スコアUP
		LIFE,		// 体力回復
		ITEM_MAX	
	}ITEM;

	//メンバ関数
	CItem();
	~CItem();
	static CItem *Create(D3DXVECTOR3 pos, ITEM type);
	static HRESULT Load(void);
	static void Unload(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	void Direction(void);
	void CollisionItem(void);

	// メンバ変数
	static LPD3DXMESH m_pMeshModel[ITEM_MAX];	//メッシュ情報へのポインタ
	static LPD3DXBUFFER m_pBuffMatModel[ITEM_MAX];	//マテリアル情報へのポインタ
	static DWORD m_nNumMatModel[ITEM_MAX];	//マテリアル情報の数
	static LPDIRECT3DTEXTURE9 m_apTexture; // テクスチャ
	CCollision*m_pCollision;    // コリジョンクラスのポインタ
	ITEM m_type;				// アイテムの種類情報
	int m_nCandy;				// キャンディの数
	float m_fRotYDist;
};

#endif