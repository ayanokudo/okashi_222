////////////////////////////////////////////////////
//
//    ロストポイントの処理[LostPoint.cpp]
//    Author:増澤 未来
//
////////////////////////////////////////////////////


//=============================
// インクルード
//=============================
#include "LostPoint.h"
#include "manager.h"
#include "keyboard.h"
#include "collision.h"
#include "player.h"
#include "game.h"

//**********************************
// 静的メンバ変数宣言
//**********************************

//**********************************
// マクロ定義
//**********************************
#define POINT_TEXT "data/Texts/LostPoint.txt" // ポイント記憶用テキストファイル
#define POINT_TEXT_ROUTE "data/Texts/RoutePoint.txt" // ポイント記憶用テキストファイル
#define COLLISION_RADIUS 120                  // 当たり判定の半径
#define MODE_EDIT false                        // エディットモードか


//=============================
// コンストラクタ
//=============================
CLostPoint::CLostPoint()
{
	memset(m_pCollisionLost, 0, sizeof(m_pCollisionLost));
	m_pointPos = NULL;
	m_nPointNum = 0;

	memset(m_pCollisionRoute, 0, sizeof(m_pCollisionRoute));
	m_routePos = NULL;
	m_nRouteNum = 0;
}

//=============================
// デストラクタ
//=============================
CLostPoint::~CLostPoint()
{
}

//=============================
// クリエイト
//=============================
CLostPoint * CLostPoint::Create(void)
{
	// メモリの確保
	CLostPoint *pLostPoint = new CLostPoint;

	if (pLostPoint != NULL)
	{
		// 初期化
		pLostPoint->Init();
	}
	return pLostPoint;
}

//=============================
// 初期化処理
//=============================
HRESULT CLostPoint::Init(void)
{
	// ポイント数の初期化
	m_nPointNum = 0;

#if MODE_EDIT
	// エディットモード

	// メモリの確保
	m_pointPos = new D3DXVECTOR3[MAX_LOSTPOINT];
	m_routePos = new D3DXVECTOR3[MAX_ROUTEPOINT];

#else

	// テキストの読み込み
	LoadText();

#endif

	return S_OK;
}

//=============================
// 終了処理
//=============================
void CLostPoint::Uninit(void)
{
	if (m_pointPos != NULL)
	{
		delete[] m_pointPos;
		m_pointPos = NULL;
	}

	if (m_routePos != NULL)
	{
		delete[] m_routePos;
		m_routePos = NULL;
	}

	// 開放処理
	Release();
}


//=============================
// 更新処理
//=============================
void CLostPoint::Update(void)
{
#if MODE_EDIT
	// エディットモード

	// ロストポイント
	// 座標の保存
	if (CManager::GetKeyboard()->GetKeyTrigger(DIK_RETURN))
	{
		m_pointPos[m_nPointNum] = CGame::GetPlayer(1)->GetPos();
		m_pCollisionLost[m_nPointNum] = CCollision::CreateSphere(m_pointPos[m_nPointNum], COLLISION_RADIUS);
		m_nPointNum++;
	}
	if (CManager::GetKeyboard()->GetKeyTrigger(DIK_NUMPADENTER))
	{
		SaveText(0);
	}

	// ルートポイント

	// 座標の保存
	if (CManager::GetKeyboard()->GetKeyTrigger(DIK_RSHIFT))
	{
		m_routePos[m_nRouteNum] = CGame::GetPlayer(1)->GetPos();
		m_pCollisionRoute[m_nPointNum] = CCollision::CreateSphere(m_routePos[m_nRouteNum], COLLISION_RADIUS);
		m_nRouteNum++;
	}
	if (CManager::GetKeyboard()->GetKeyTrigger(DIK_NUMPADPLUS))
	{
		SaveText(1);
	}



#else


#endif
}


//=============================
// 描画処理
//=============================
void CLostPoint::Draw(void)
{
	
}

//=============================
// ソート
//=============================
void CLostPoint::sort(D3DXVECTOR3 pos)
{
	// 距離の近い順に並び替え

	// ロストポイント
	for (int nCntSort = 0; nCntSort < m_nPointNum; nCntSort++)
	{
		for (int nCnt = nCntSort + 1; nCnt < m_nPointNum; nCnt++)
		{
			// 距離を測る
			float fDist = GetDistance(pos, m_pointPos[nCntSort]);
			
			// 距離を比べる
			if (fDist > GetDistance(pos, m_pointPos[nCnt]))
			{// 近かった時
				// 保存
				D3DXVECTOR3 save = m_pointPos[nCntSort];

				// 並び替え
				m_pointPos[nCntSort] = m_pointPos[nCnt];
				m_pointPos[nCnt] = save;

				m_pCollisionLost[nCntSort]->SetPos(m_pointPos[nCntSort]);
				m_pCollisionLost[nCnt]->SetPos(m_pointPos[nCnt]);
			}

		}
	}

	// ルートポイント
	for (int nCntSort = 0; nCntSort < m_nRouteNum; nCntSort++)
	{
		for (int nCnt = nCntSort + 1; nCnt < m_nRouteNum; nCnt++)
		{
			// 距離を測る
			float fDist = GetDistance(pos, m_routePos[nCntSort]);

			// 距離を比べる
			if (fDist > GetDistance(pos, m_routePos[nCnt]))
			{// 近かった時
			 // 保存
				D3DXVECTOR3 save = m_routePos[nCntSort];

				// 並び替え
				m_routePos[nCntSort] = m_routePos[nCnt];
				m_routePos[nCnt] = save;

				m_pCollisionRoute[nCntSort]->SetPos(m_routePos[nCntSort]);
				m_pCollisionRoute[nCnt]->SetPos(m_routePos[nCnt]);
			}

		}
	}
}

#if MODE_EDIT
//=============================
// テキストファイルのセーブ
//=============================
void CLostPoint::SaveText(int nMode)
{
	FILE*pFile = NULL;

	if (nMode == 0)
	{// ロストポイント
		// ファイルオープン
		pFile = fopen(POINT_TEXT, "w");

		if (pFile != NULL)
		{
			fprintf(pFile, "%d\n", m_nPointNum);
			for (int nCnt = 0; nCnt < m_nPointNum; nCnt++)
			{
				fprintf(pFile, "%f %f %f\n", m_pointPos[nCnt].x, m_pointPos[nCnt].y, m_pointPos[nCnt].z);
			}

			fclose(pFile);
		}
	}
	else
	{// ルートポイント
		// ファイルオープン
		pFile = fopen(POINT_TEXT_ROUTE, "w");

		if (pFile != NULL)
		{
			fprintf(pFile, "%d\n", m_nRouteNum);
			for (int nCnt = 0; nCnt < m_nRouteNum; nCnt++)
			{
				fprintf(pFile, "%f %f %f\n", m_routePos[nCnt].x, m_routePos[nCnt].y, m_routePos[nCnt].z);
			}

			fclose(pFile);
		}
	}
}
#else
//=============================
// テキストファイルのロード
//=============================
void CLostPoint::LoadText(void)
{
	
	FILE*pFile = NULL;

	// ロストポイント

	// ファイルオープン
	pFile = fopen(POINT_TEXT, "r");

	if (pFile != NULL)
	{
		fscanf(pFile, "%d", &m_nPointNum);

		m_pointPos = new D3DXVECTOR3[m_nPointNum];

		for (int nCnt = 0; nCnt < m_nPointNum; nCnt++)
		{
			fscanf(pFile, "%f %f %f", &m_pointPos[nCnt].x, &m_pointPos[nCnt].y, &m_pointPos[nCnt].z);

			m_pCollisionLost[nCnt] = CCollision::CreateSphere(m_pointPos[nCnt], COLLISION_RADIUS);
		}

		fclose(pFile);
	}

	// ルートポイント

	pFile = fopen(POINT_TEXT_ROUTE, "r");

	if (pFile != NULL)
	{
		fscanf(pFile, "%d", &m_nRouteNum);

		m_routePos = new D3DXVECTOR3[m_nRouteNum];

		for (int nCnt = 0; nCnt < m_nRouteNum; nCnt++)
		{
			fscanf(pFile, "%f %f %f", &m_routePos[nCnt].x, &m_routePos[nCnt].y, &m_routePos[nCnt].z);

			m_pCollisionRoute[nCnt] = CCollision::CreateSphere(m_routePos[nCnt], COLLISION_RADIUS);
		}

		fclose(pFile);
	}

}
#endif