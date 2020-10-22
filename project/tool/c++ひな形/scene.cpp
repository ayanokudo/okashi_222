//=================================================
//
//    sceneクラスの処理[scene.cpp]
//    Author:増澤 未来
//
//=================================================

//***********************************
// インクルード
//***********************************
#include "scene.h"
#include "scene2d.h"

//***********************************
//静的メンバ変数宣言
//***********************************
CScene *CScene::m_apScene[MAX_SCENE] = {};
int CScene::m_nNumAll = 0;

//===================================
// コンストラクタ
//===================================
CScene::CScene()
{
	for (int nCntScene = 0; nCntScene < MAX_SCENE; nCntScene++)
	{
		if (m_apScene[nCntScene] == NULL)
		{
			m_apScene[nCntScene] = this;
			m_nNumIndex = nCntScene;
			m_nNumAll++;
			m_type = OBJTYPE_NONE;
			break;
		}
	}
}
//===================================
// デストラクタ
//===================================
CScene::~CScene()
{
}

//====================================
// すべて終了処理
//====================================
void CScene::ReleaseAll(void)
{
	for (int nCntScene = 0; nCntScene < MAX_SCENE; nCntScene++)
	{
		if (m_apScene[nCntScene] != NULL)
		{
			m_apScene[nCntScene]->Uninit();

		}
	}
}

//====================================
// すべて更新
//====================================
void CScene::UpdateAll(void)
{
	for (int nCntScene = 0; nCntScene < MAX_SCENE; nCntScene++)
	{
		if (m_apScene[nCntScene] != NULL)
		{
			m_apScene[nCntScene]->Update();
		}
	}
}

//====================================
// すべて描画
//====================================
void CScene::DrawAll(void)
{
	OBJTYPE objType = OBJTYPE_NONE;

	// オブジェクトタイプ数分ループ
	for (int nCntLayer = 0; nCntLayer < OBJTYPE_MAX; nCntLayer++)
	{
		
		objType = (OBJTYPE)nCntLayer;

		// オブジェクトの最大数分ループ
		for (int nCntScene = 0; nCntScene < MAX_SCENE; nCntScene++)
		{

			if (m_apScene[nCntScene] != NULL)
			{
				if (m_apScene[nCntScene]->m_type == objType)
				{
					// 描画処理
					m_apScene[nCntScene]->Draw();
				}
			}

		}
	}
}

//====================================
//メモリの破棄
//====================================
void CScene::Release(void)
{
	int nNum = m_nNumIndex;
	if (m_apScene[nNum] != NULL)
	{
		delete m_apScene[nNum];
		m_apScene[nNum] = NULL;
		m_nNumAll--;
	}
}
