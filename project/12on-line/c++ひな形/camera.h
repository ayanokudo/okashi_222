//=============================================================================
//
// cameraヘッダ [camera.h]
// Author : 増澤 未来
//
//=============================================================================

//二重インクルード防止
#ifndef _CAMERA_H_
#define _CAMERA_H_

//*****************************
// インクルード
//*****************************
#include "main.h"
#include "scene2d.h"

//*****************************
// クラス定義
//*****************************

//プレイヤークラス
class CCamera
{
public:
	//メンバ関数
	CCamera();
	~CCamera();

	static CCamera *Create();
	static void Release(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void SetCamera(void);
	D3DXVECTOR3 GetPos(void) { return m_posV; }
	D3DXVECTOR3 GetLookPos(void) { return m_posR; }
	D3DXMATRIX GetViewMtx(void) { return m_mtxView; }
	D3DXMATRIX GetProjectionMtx(void) { return m_mtxProjection; }

private:
	// メンバ変数
	static CCamera *m_pCamera;
	D3DXVECTOR3 m_posV;//カメラの座標
	D3DXVECTOR3 m_posR;//注視点
	D3DXVECTOR3 m_vecU;//上方向ベクトル
	D3DXMATRIX  m_mtxProjection;//プロジェクションマトリックス
	D3DXMATRIX  m_mtxView;//ビューマトリックス
	float m_fViewExtent; // 視野角の拡縮用
	int m_nCntPlayerDeath;// プレイヤーの片方が死んでから一定カウント挙動を変える
#ifdef _DEBUG
	// 球面座標
	float m_fRad;   // 目標からの距離
	float m_fTheta;  // 角度シータ
	float m_fPhi;    // 角度ファイ
#endif
};

#endif