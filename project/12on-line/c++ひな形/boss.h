//=============================================================================
//
// bossヘッダ [boss.h]
// Author : 筒井 俊稀
//
//=============================================================================

//二重インクルード防止
#ifndef _BOSS_H_
#define _BOSS_H_

//*****************************
// インクルード
//*****************************
#include "main.h"
#include "model_hierarchy.h"
#include "player.h"

//*****************************
// 前方宣言
//*****************************
class CCollision;
class CMotion;
class CUi;

//*****************************
// クラス定義
//*****************************

// パーティクルクラス
class CBoss : public CModelHierarchy
{
public:

	// モーション列挙
	typedef enum
	{
		SPAWN = 0,  // 湧くとき
		WALK,       // 歩き
		BREARH,     // ブレス
		SCRATCH,    // ひっかき
		TAIL,       // しっぽ
		MOTION_MAX
	}MOTION;

	// 攻撃列挙
	typedef enum
	{
		ATTACK_BREARH = 0,     // ブレス
		ATTACK_SCRATCH,        // ひっかき
		ATTACK_TAIL,           // しっぽ
		ATTACK_MAX
	}ATTACK;

	//ボスの攻撃方法とスタンのタイプ分け
	typedef enum
	{
		TYPE_ATTACK_RANGE = 0,		// 範囲攻撃
		TYPE_ATTACK_FAR,			// 遠距離攻撃
		TYPE_ATTACK_PROXIMITY,		// 近接攻撃
		TYPE_NUMB,					// 麻痺
		TYPE_MAX
	}BOSS;

	//メンバ関数
	CBoss();
	~CBoss();
	static CBoss *Create(D3DXVECTOR3 pos);
	static HRESULT Load(void);
	static void Unload(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Hit(int nDamage);
	CCollision *GetCollision(void) { return m_pCollision; }
	MOTION      GetMotion(void) { return m_motionState; }

private:
	//各敵キャラの動きの処理
	void Move(void);
	void ChangeTarget(int nNum = 0);
	void Direction(void);
    void Attack(void);

	void Brearh(void);
	void Scratch(void);
	void Tail(void);

	void MotionManager(void);
	void MotionFalse(void);
	void SetMotion(MOTION motionState);

	// メンバ変数
	static CModel::Model m_model[MAX_PARTS_NUM]; // モデル情報
	static int m_nNumModel;                      // モデル数
	static char m_achAnimPath[MOTION_MAX][64];   // アニメーションテキストのパス格納用

	// メンバ変数
	//static LPD3DXMESH m_pMeshModel;	//メッシュ情報へのポインタ
	//static LPD3DXBUFFER m_pBuffMatModel;	//マテリアル情報へのポインタ
	//static DWORD m_nNumMatModel;	//マテリアル情報の数
	//static LPDIRECT3DTEXTURE9 m_apTexture; // テクスチャ
	D3DXVECTOR3 m_move;        // 移動量
	D3DXVECTOR3 m_moveDest;
	CCollision *m_pCollision;        // 当たり判定
	CCollision *m_pCollisionTail;    // しっぽの当たり判定
	CCollision *m_pRadiusColision;
	int m_nLife;
	bool m_bRd;
	float m_fRotYDist;
	int m_nCount;
	int m_nCountMotion;
	int m_nCountRand;
	int m_nCntMove;                 // 移動時のカウント
	int m_nCntBullet;               // 弾を撃つときのカウント
	int m_nTargetNum;               // どのプレイヤーをターゲットしているか
	bool m_bHitTail[MAX_PLAYER];    // しっぽが多段ヒットしないように
	CUi* m_pUi;

	CMotion*m_pMotion[MOTION_MAX];  // アニメーションポインタ
	MOTION m_motionState;           // モーションステート
	bool m_bMotion;                 // 移動を止める系のモーション判定用

};

#endif