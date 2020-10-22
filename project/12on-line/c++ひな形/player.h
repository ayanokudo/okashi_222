//=============================================================================
//
// playerヘッダ [player.h]
// Author : 増澤 未来
//
//=============================================================================

//二重インクルード防止
#ifndef _PLAYER_H_
#define _PLAYER_H_

//*****************************
// インクルード
//*****************************
#include "main.h"
#include "model.h"

//*****************************
// クラス定義
//*****************************

// パーティクルクラス
class CPlayer : public CModel
{
public:

	//メンバ関数
	CPlayer();
	~CPlayer();
	static CPlayer *Create(D3DXVECTOR3 pos);
	static HRESULT Load(void);
	static void Unload(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	void Move(void);
	void Attack(void);

	// メンバ変数
	static LPD3DXMESH m_pMeshModel;	//メッシュ情報へのポインタ
	static LPD3DXBUFFER m_pBuffMatModel;	//マテリアル情報へのポインタ
	static DWORD m_nNumMatModel;	//マテリアル情報の数
	static LPDIRECT3DTEXTURE9 m_apTexture; // テクスチャ
	D3DXVECTOR3 m_move;        // 移動量
};

#endif