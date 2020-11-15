//=============================================================================
//
// startヘッダ [start.h]
// Author : 増澤 未来
//
//=============================================================================

//二重インクルード防止
#ifndef _START_H_
#define _START_H_

//*****************************
//インクルード
//*****************************
#include "main.h"
#include "scene2d.h"

//*****************************
//クラス定義
//*****************************
class CStart : public CScene2d
{
public:

	//メンバ関数
	CStart();
	~CStart();
	static CStart * Create(void);
	static HRESULT Load(void);
	static void Unload(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	//メンバ変数
	static LPDIRECT3DTEXTURE9 m_pTexture;//テクスチャ
	int m_nCntLost;                      // 一定時間で消す
};

#endif 