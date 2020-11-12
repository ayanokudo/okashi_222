//=============================================================================
//
// wallヘッダ [wall.h]
// Author : 筒井　俊稀
//
//=============================================================================

//二重インクルード防止
#ifndef _WALL_H_
#define _WALL_H_

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
class CWall : public CScene3d
{
public:
	//床のテクスチャの種類
	typedef enum
	{
		WALL_NORMAL = 0,	//フローリング
		WALL_RIGHT,			//マット
		WALL_LEFT,		//キッチン
		WALL_MAX,
	}WALL;

	//メンバ関数
	CWall();
	~CWall();
	static CWall * Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const D3DXVECTOR3 size, WALL type);
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
	static LPDIRECT3DTEXTURE9 m_apTexture[WALL_MAX];//テクスチャ
	WALL m_type;
	D3DXVECTOR3 m_pos;      // 位置
    D3DXVECTOR3 m_rot;      // 角度
	D3DXVECTOR3 m_posold;
	D3DXVECTOR3 m_size;     // サイズ
	CCollision *m_pCollision;
};

#endif 