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
class CCollision
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
	static CCollision *CreateBox(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	static bool CollisionSphere(CCollision*pCollision1, CCollision*pCollision2);
	static bool CollisionBox(CCollision*pCollision1, CCollision*pCollision2);
	static bool CollisionSphereToBox(CCollision*pCollSphere, CCollision*pCollBox);
	static float OnRange(float fPoint, float fMin, float fMax);

	HRESULT Init(D3DXVECTOR3 pos);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	D3DXVECTOR3 GetCollisionSize(void) { return m_size; }
	float GetCollisionRadius(void) { return m_fRadius; }

    // 位置のセッタ/ゲッタ
    void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }
    D3DXVECTOR3 GetPod(void) { return m_pos; }
private:
	void CreateMesh(void);

	// メンバ変数
	LPD3DXMESH m_pMeshModel;	//メッシュ情報へのポインタ
	LPD3DXBUFFER m_pBuffMatModel;	//マテリアル情報へのポインタ
	DWORD m_nNumMatModel;	//マテリアル情報の数
	COLLISIONTYPE m_type;  // コリジョンのタイプ
    D3DXVECTOR3 m_pos;
	float m_fRadius;
	D3DXVECTOR3 m_size;
};

#endif