//=============================================================================
//
// resultヘッダ [result.h]
// Author : 増澤 未来
//
//=============================================================================

//二重インクルード防止
#ifndef _RESULT_H_
#define _RESULT_H_

//*****************************
//インクルード
//*****************************
#include "main.h"
#include "scene.h"

//=============================
// 前方宣言
//=============================
class CPolygon;
class CRanking;
class CScore;

//*****************************
//クラス定義
//*****************************

//2dポリゴンクラス
class CResult : public CScene
{
public:
	// メンバ関数
	CResult();
	~CResult();
	static CResult *Create(void);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CRanking *GetRanking(void) { return m_pRanking; }
	static CScore *GetScore(void) { return m_pScore; }
private:
	// メンバ変数
	static LPDIRECT3DTEXTURE9 m_pTexture;        // テクスチャへのポインタ
	CPolygon *m_pPolygon;
	static CRanking *m_pRanking;
	static CScore *m_pScore;

};

#endif