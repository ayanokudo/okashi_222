//=============================================================================
//
// floorヘッダ [floor.h]
// Author : 筒井　俊稀
//
//=============================================================================

//二重インクルード防止
#ifndef _FLOOR_H_
#define _FLOOR_H_

//*****************************
//インクルード
//*****************************
#include "main.h"
#include "scene3d.h"

//*****************************
//クラス定義
//*****************************
class CFloor : public CScene3d
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
	CFloor();
	~CFloor();
	static CFloor * Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, FLOOR type);
	static HRESULT Load(void);
	static void Unload(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	//メンバ変数
	static LPDIRECT3DTEXTURE9 m_apTexture[FLOOR_MAX];//テクスチャ
	FLOOR m_type;
};

#endif 