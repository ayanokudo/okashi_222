//=============================================================================
//
// グリッドヘッダ [grid.h]
// Author : 増澤 未来
//
//=============================================================================

//二重インクルード防止
#ifndef _GRID_H_
#define _GRID_H_

//*****************************
//インクルード
//*****************************
#include "main.h"
#include "scene3d.h"

//*****************************
//マクロ定義
//*****************************
#define GRID_SIZE                   (60.0f)        // グリッドの大きさ
#define MAX_GRID                    (800) // グリッドの数

//*****************************
//クラス定義
//*****************************
class CGrid : public CScene3d
{
public:
	//床のテクスチャの種類
	typedef enum
	{
		FLOOR_FLOORING = 0,	//フローリング
		FLOOR_MAT,			//マット
		FLOOR_KITCHEN,		//キッチン
		FLOOR_MAX,			
	}FLOOR;

	//メンバ関数
	CGrid();
	~CGrid();
	static CGrid * Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, FLOOR type);
	static HRESULT Load(void);
	static void Unload(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	//メンバ変数
    static D3DXVECTOR2 m_UV[NUM_VERTEX];// テクスチャ座標の情報
	static LPDIRECT3DTEXTURE9 m_apTexture[FLOOR_MAX];//テクスチャ
	FLOOR m_type;
};

#endif 