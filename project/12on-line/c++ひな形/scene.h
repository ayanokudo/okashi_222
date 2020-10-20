//=============================================================================
//
// sceneヘッダ [scene.h]
// Author : 増澤 未来
//
//=============================================================================

//二重インクルード防止
#ifndef _SCENE_H_
#define _SCENE_H_

//インクルード
#include "main.h"

//***********************************
//マクロ定義
//***********************************
#define MAX_SCENE 1280   // ポリゴンの最大数

//=============================
//クラス定義
//=============================

//シーンクラス
class CScene
{
public:
	// オブジェクトタイプ列挙
	// 描画順
	typedef enum
	{
		OBJTYPE_NONE = 0,
		OBJTYPE_BG,         // 背景
		OBJTYPE_MAP,        // マップ
		OBJTYPE_MANACIRCLE, // マナサークル
		OBJTYPE_ITEM,       // アイテム
		OBJTYPE_EFFECT,     // エフェクト
		OBJTYPE_BULLET,     // 弾
		OBJTYPE_PLAYER,     // プレイヤー
		OBJTYPE_ENEMY,      // エネミー
		OBJTYPE_EXPLOSION,  // 爆発
		OBJTYPE_PARTICLE,   // パーティクル
		OBJTYPE_BOMB,       // ボム
		OBJTYPE_UI,         // UI
		OBJTYPE_FLOOR,		// 床
		OBJTYPE_MAX,        // タイプの最大数
	}OBJTYPE;

	// メンバ関数
	CScene();
	virtual ~CScene();
	static void ReleaseAll(void);
	static void UpdateAll(void);
	static void DrawAll(void);
	static int GetNumAll(void) { return m_nNumAll; }
	static CScene* GetScene(int nIndex) { return m_apScene[nIndex]; }
	void SetObjType(const OBJTYPE objType) { m_type = objType; }
	OBJTYPE GetType(void) { return m_type; }
	int GetIndex(void) { return m_nNumIndex; } // 配列番号の取得


	// 純粋仮想関数
	virtual HRESULT Init(void) = 0;
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;
	
protected:
	void Release(void);
private:
	// メンバ変数
	static CScene *m_apScene[MAX_SCENE];   // ポリゴン管理用
	static int m_nNumAll;                  // 生成したポリゴン数
	int m_nNumIndex;                       // 生成したポリゴンの配列
	OBJTYPE m_type;                        // オブジェクトタイプ
};

#endif