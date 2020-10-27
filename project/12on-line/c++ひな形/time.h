//=============================================================================
//
// timeヘッダ [time.h]
// Author : 増澤 未来
//
//=============================================================================

//二重インクルード防止
#ifndef _TIME_H_
#define _TIME_H_

//*****************************
//インクルード
//*****************************
#include "main.h"
#include "scene.h"

//*****************************
//前方宣言
//*****************************
class CNumber;

//*****************************
//マクロ定義
//*****************************
#define MAX_TIME_DIGIT 3  // スコアの最大桁数

//*****************************
//クラス定義
//*****************************

//2dポリゴンクラス
class CTime : public CScene
{
public:
	// メンバ関数
	CTime();
	~CTime();
	static CTime *Create(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	// メンバ変数
	CNumber* m_apNumber[MAX_TIME_DIGIT];
	static int m_nScore;

};

//#endif