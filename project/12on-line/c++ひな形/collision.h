//=============================================================================
//
// collisionヘッダ [collision.h]
// Author : 増澤 未来
//
//=============================================================================

//二重インクルード防止
#ifndef _COLLISON_H_
#define _COLLISON_H_

//*****************************
// インクルード
//*****************************
#include "main.h"
#include "model.h"

//*****************************
// クラス定義
//*****************************

// 当たり判定クラス
class CCollision : public CModel
{
public:
	typedef enum
	{
		COLLISIONTYPE_BOX = 0,
		COLLISIONTYPE_SPHERE,
		COLLISIONTYPE_MAX,
	}COLLISIONTYPE;
	//メンバ関数
	CCollision();
	~CCollision();
	static CCollision *CreateSphere(D3DXVECTOR3 pos, float fRadius);
	static bool CollisionSphere(CCollision*pCollision1, CCollision*pCollision2);
	static CCollision *CreateBox(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	static bool CollisionBox(CCollision*pCollision1, CCollision*pCollision2);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	void CreateMesh(void);
	// メンバ変数
	LPD3DXMESH m_pMeshModel;	//メッシュ情報へのポインタ
	LPD3DXBUFFER m_pBuffMatModel;	//マテリアル情報へのポインタ
	DWORD m_nNumMatModel;	//マテリアル情報の数
	COLLISIONTYPE m_type;  // コリジョンのタイプ
	float m_fRadius;
	D3DXVECTOR3 m_size;
};

#endif