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
#define COLLET_PAR_DIGIT 3 // %の桁数
#define COLLET_DIGIT 2     // 回収した数の桁数

//*****************************
// クラス定義
//*****************************

// 回収率クラス
class CCollect :CScene
{
public:
	typedef enum
	{
		SLASH = 0,
		PERCENT,
		MAX_PARTS
	}PARTS;
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
	static void Collect(void) { m_nNumCollect++; }

private:
	// メンバ変数
	static LPDIRECT3DTEXTURE9 m_apTexture[MAX_PARTS]; // テクスチャへのポインタ
	static int m_nNumCollect;             // 回収した数
	int m_nPerCollect;                    // 回収率
	CPolygon*m_pPolygon[MAX_PARTS];       // ナンバー以外の画像
	CNumber*m_pNumObj[COLLET_DIGIT];      // 回収対象の数のナンバーポリゴン
	CNumber*m_pNumCollect[COLLET_DIGIT];  // 回収した数のナンバーポリゴン
	CNumber*m_pNumPer[COLLET_PAR_DIGIT];  // %のナンバーポリゴン
};

#endif