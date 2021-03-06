//=============================================================================
//
// numberヘッダ [number.h]
// Author : 増澤 未来
//
//=============================================================================

//二重インクルード防止
#ifndef _NUMBER_H_
#define _NUMBER_H_

//*****************************
//インクルード
//*****************************
#include "main.h"

//*****************************
//クラス定義
//*****************************

//ナンバークラス
class CNumber
{
public:
	typedef enum
	{
		FLASH_STATE_NONE = 0,
		FLASH_STATE_IN,
		FLASH_STATE_OUT,
		FLASH_STATE_MAX
	}FLASH_STATE_NUMBER;
	// メンバ関数
	CNumber();
	~CNumber();
	static CNumber *Create(const int nNum, const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXCOLOR col);
	static HRESULT Load(void);
	static void Unload(void);

	HRESULT Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXCOLOR col);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetNumber(const int nNumber);
	void Flashing(void);
	// カラーのセット、取得
	void SetColor(const D3DXCOLOR col);
	D3DXCOLOR GetColor(void) { return m_col; }
private:
	// メンバ変数
	static LPDIRECT3DTEXTURE9 m_pTexture;	 // テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9   m_pVtxBuff;	 // 頂点バッファへのポイン
	int m_nNumber; // ナンバー
	D3DXCOLOR m_col;
	bool m_bFlash;
	FLASH_STATE_NUMBER m_FlashState;
};

#endif