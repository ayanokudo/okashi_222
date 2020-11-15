//=============================================================================
//
// wallヘッダ [wall.h]
// Author : 筒井　俊稀
//
//=============================================================================

//二重インクルード防止
#ifndef _FURNITURE_H_
#define _FURNITURE_H_

//*****************************
//インクルード
//*****************************
#include "main.h"
#include "scene3d.h"
#include "model.h"

//*****************************
//前方宣言
//*****************************
class CPlayer;
class CCollision;

//*****************************
//クラス定義
//*****************************
class CFurniture : public CModel
{
public:
	//床のテクスチャの種類
	typedef enum
	{
		FURNITURE_CHAIR = 0,	//椅子
		FURNITURE_TABLE,		//マット
		FURNITURE_CHEST,		//キッチン
		FURNITURE_TLEX,		//キッチン
		FURNITURE_WOOD,		//キッチン
		FURNITURE_BENCH,		//キッチン
		FURNITURE_MAX,

	}FURNITURE;

	//メンバ関数
	CFurniture();
	~CFurniture();
	static CFurniture * Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const D3DXVECTOR3 size, FURNITURE type);
	static HRESULT Load(void);
	static void Unload(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	CCollision *GetCollision(void) { return m_pCollision; }

private:
	void CollisionPlayer(void);
	void CollisionEnemy(void);
	void CollisionBoss(void);
	void CollisionBullet(void);

	// メンバ変数
	static LPDIRECT3DTEXTURE9 m_apTexture[FURNITURE_MAX];//テクスチャ
	FURNITURE m_type;
	D3DXVECTOR3 m_pos;      // 位置
	D3DXVECTOR3 m_rot;      // 角度
	D3DXVECTOR3 m_posold;
	D3DXVECTOR3 m_size;     // サイズ
	CCollision *m_pCollision;
	static Model m_model[FURNITURE_MAX];
    static char *m_apTextureName[FURNITURE_MAX];
};

#endif 