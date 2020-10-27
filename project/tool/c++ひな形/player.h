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
// プレイヤークラス
class CPlayer : public CModel
{
public:
    // モデルの情報
    typedef enum
    {
        MODEL_PLAYER,
        MODEL_ENEMY,
        MODEL_MAX
    }MODEL;      // モデルのファイル名

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
    // メンバ関数
	void Controll(void);
	// メンバ変数
    static char*              m_apModelData[MODEL_MAX];// モデルの情報
	static LPD3DXMESH         m_pMeshModel[MODEL_MAX];	//メッシュ情報へのポインタ
	static LPD3DXBUFFER       m_pBuffMatModel[MODEL_MAX];	//マテリアル情報へのポインタ
	static DWORD              m_nNumMatModel[MODEL_MAX];	//マテリアル情報の数
	static LPDIRECT3DTEXTURE9 m_apTexture; // テクスチャ
	D3DXVECTOR3 m_move;        // 移動量


};

#endif