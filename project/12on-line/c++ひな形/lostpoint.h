//=============================================================================
//
// loastpointヘッダ [loastpoint.h]
// Author : 増澤 未来
//
//=============================================================================

//二重インクルード防止
#ifndef _LOST_POINT_H_
#define _LOST_POINT_H_

//*****************************
//インクルード
//*****************************
#include "main.h"
#include "scene.h"

//=============================
// 前方宣言
//=============================
class CCollision;

//=============================
// マクロ定義
//=============================
#define MAX_LOSTPOINT 20   // ポイントの最大数
#define MAX_ROUTEPOINT 5   // ポイントの最大数
//*****************************
//クラス定義
//*****************************

//ロストポイントのクラス
class CLostPoint : public CScene
{
public:

	// メンバ関数
	CLostPoint();
	~CLostPoint();
	static CLostPoint *Create(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	
	void sort(D3DXVECTOR3 pos);
	D3DXVECTOR3 GetLostPos(int nNum) { return m_pointPos[nNum]; }
	D3DXVECTOR3 GetRoutePos(int nNum) { return m_routePos[nNum]; }

	CCollision* GetLostCollision(int nNum) { return m_pCollisionLost[nNum]; }
	CCollision* GetRouteCollision(int nNum) { return m_pCollisionRoute[nNum]; }

	int GetNumLostPoint(void) { return m_nPointNum; }
	int GetNumRoutePoint(void) { return m_nRouteNum; }
private:
	void SaveText(int nMode);
	void LoadText(void);
	// メンバ変数
	CCollision*m_pCollisionLost[MAX_LOSTPOINT];  // 当たり判定
	D3DXVECTOR3 *m_pointPos; // ポイントのポス
	int m_nPointNum;         // ポイント数
	 
	CCollision*m_pCollisionRoute[MAX_ROUTEPOINT];  // 当たり判定
	D3DXVECTOR3 *m_routePos; // ポイントのポス
	int m_nRouteNum;         // ポイント数
	

};

#endif