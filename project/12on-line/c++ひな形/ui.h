//=============================================================================
//
//	uiヘッダ [ui.h]
//	Author : 筒井　俊稀
//
//=============================================================================

//二重インクルード防止
#ifndef _UI_H_
#define _UI_H_

#define MAX_UI UI_MAX
//*****************************
//インクルード
//*****************************
#include "main.h"
#include "scene.h"

//*****************************
// クラス定義
//*****************************

//UIクラス
class CUi
{
public:
	//UIの種類
	typedef enum
	{
		UI_TIME = 0,	//タイム
		UI_TITLE,		//タイトル
		UI_ENTER,		//プレスエンター
		UI_WARNING,		//危険
		UI_ATTACK_NAIL,	//攻撃爪
		UI_ATTACK_CRY,	//攻撃鳴き声
		UI_DASH,		//ダッシュ
		UI_CHOCO,		//チョコ
		UI_MILK,		//ミルク
		UI_MAX
	}UI;

	CUi();
	~CUi();

	static CUi *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXCOLOR col, const UI type);
	static HRESULT Load(void);
	static void Unload(void);

	HRESULT Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXCOLOR col, const UI type);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// カラーのセット、取得
	void SetColor(const D3DXCOLOR col);
	D3DXCOLOR GetColor(void) { return m_col; }
private:
	// メンバ変数
	static LPDIRECT3DTEXTURE9 m_apTexture[MAX_UI];	 // テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9   m_pVtxBuff;	 // 頂点バッファへのポイン
	D3DXCOLOR m_col;
	D3DXVECTOR3 m_move;					 // 移動量
	D3DXVECTOR3 m_pos;
	UI m_type;
	float m_fAngle;                      // ポリゴンの回転角度
	D3DXVECTOR3 m_size;                  // ポリゴンのサイズ
};
#endif // !_UI_H_
