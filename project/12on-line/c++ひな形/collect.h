//=============================================================================
//
// collectヘッダ [collect.h]
// Author : 増澤 未来
//
//=============================================================================

//二重インクルード防止
#ifndef _COLLECT_H_
#define _COLLECT_H_

//*****************************
// インクルード
//*****************************
#include "main.h"
#include "scene.h"

//*****************************
// 前方宣言
//*****************************
class CNumber;
class CPolygon;

//*****************************
// マクロ定義
//*****************************
#define COLLET_OBJ_NUM_DIGIT 2 // 回収対象数の桁数
#define COLLET_NUM_DIGIT 3     // 回収率の桁数

//*****************************
// クラス定義
//*****************************

// 回収率クラス
class CCollect :CScene
{
public:

	//メンバ関数
	CCollect();
	~CCollect();
	static CCollect *Create(void);
	static HRESULT Load(void);
	static void Unload(void);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static void InitVariable(void);
	static void AddObj(int nNum = 1) { m_nNumObj += nNum; }
	static void Collect(void) { m_nNumCollect++; }

private:
	// メンバ変数
	static LPDIRECT3DTEXTURE9 m_pTexture;        // テクスチャへのポインタ
	static int m_nNumObj;      // 回収対象の数
	static int m_nNumCollect;  // 回収した数
	float m_fPerCollect;       // 回収率
	CPolygon*m_pPolygon;       // "/"の画像
	CNumber*m_pNumObj[COLLET_OBJ_NUM_DIGIT]; // 回収対象の数のナンバーポリゴン
	CNumber*m_pNumCollect[COLLET_NUM_DIGIT]; // 回収した数のナンバーポリゴン
};

#endif