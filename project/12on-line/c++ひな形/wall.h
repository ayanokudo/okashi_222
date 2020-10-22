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

//*****************************
//クラス定義
//*****************************
class CWall : public CScene3d
{
public:
	//床のテクスチャの種類
	typedef enum
	{
		WALL_1 = 0,	//フローリング
		WALL_2,			//マット
		WALL_3,		//キッチン
		WALL_MAX,
	}WALL;

	//メンバ関数
	CWall();
	~CWall();
	static CWall * Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, WALL type);
	static HRESULT Load(void);
	static void Unload(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	//メンバ変数
	static LPDIRECT3DTEXTURE9 m_apTexture[WALL_MAX];//テクスチャ
	WALL m_type;
};

#endif 