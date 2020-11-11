//------------------------------------------
//
//	ランキングの処理[ranking.h]
//	Author : 増澤 未来
//
//------------------------------------------

//二重インクルード防止
#ifndef _RANKING_H_
#define _RANKING_H_

//------------------------------------------
//	インクルードファイル
//------------------------------------------
#include "main.h"
#include "scene.h"

//------------------------------------------
//	前方宣言
//------------------------------------------
class CNumber;

#define MAX_RANKING_DIGIT 5		// スコアの最大桁数
#define MAX_NUMBER_DIGIT 6		// 
//------------------------------------------
//	ランキングクラス
//------------------------------------------
class CRanking : public CScene
{
public:
	CRanking();
	~CRanking();

	static CRanking *Create(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	CNumber *m_apNumber[MAX_RANKING_DIGIT][MAX_NUMBER_DIGIT];//ナンバー情報
	int m_anRankingDate[MAX_RANKING_DIGIT];	//ランキング情報
	int m_nCount;						//
	int m_nRank;						//
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_size;
};

#endif // !_RANKING_H_
