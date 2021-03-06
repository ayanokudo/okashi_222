//=============================================================================
//
// scoreヘッダ [score.h]
// Author : 増澤 未来
//
//=============================================================================

//二重インクルード防止
#ifndef _SCORE_H_
#define _SCORE_H_

//*****************************
//インクルード
//*****************************
#include "main.h"
#include "scene.h"

//*****************************
//前方宣言
//*****************************
class CNumber;
class CUi;

//*****************************
//マクロ定義
//*****************************
#define MAX_SCORE_DIGIT 6  // スコアの最大桁数
#define MAX_RANKING 5

//*****************************
//クラス定義
//*****************************

//2dポリゴンクラス
class CScore : public CScene
{
public:
	// メンバ関数
	CScore();
	~CScore();
	static CScore *Create(const D3DXVECTOR3 pos,const D3DXVECTOR3 size);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void ReadFile(void);
	void WriteFile(void);
	int SaveScore(void);
	static void AddScore(int nPoint) { m_nScore += nPoint; }
	static int GetScore(int nCount) { return m_nRankingScore[nCount]; }
	static void ResetScore(void) { m_nScore = 0; }
private:
	// メンバ変数
	CNumber* m_apNumber[MAX_SCORE_DIGIT];
	static int m_nRankingScore[MAX_RANKING];
	static int m_nScore;
	CUi *m_pUi;
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_size;
};

#endif