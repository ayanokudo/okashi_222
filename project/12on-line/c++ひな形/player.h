//=============================================================================
//
// playerヘッダ [player.h]
// Author : 増澤 未来
//
//=============================================================================

//二重インクルード防止
#ifndef _PLAYER_H_
#define _PLAYER_H_

//*****************************
// インクルード
//*****************************
#include "main.h"
#include "model_hierarchy.h"
#include "game.h"

//*****************************
// 前方宣言
//*****************************
class CCollision;
class CMotion;
class CLife;

//*****************************
// マクロ定義
//*****************************
#define PLAYER_LIFE 9		// プレイヤー１のライフ

//*****************************
// クラス定義
//*****************************

// パーティクルクラス
class CPlayer : public CModelHierarchy
{
public:
	//各パーツタイプ分け
	typedef enum
	{
		WAIT = 0, // 待機
		WALK,	  // 歩き
		VOICE,	  // 鳴き声
		PUNCH,	  // パンチ
		DASH,	  // 走り
		MOTION_MAX
	}MOTION;

	//移動タイプ分け
	typedef enum
	{
		TYPE_WALK = 0,	//歩き
		TYPE_DASH,		//ダッシュ
		TYPE_MAX
	}PLAYERTYPE;

	//メンバ関数
	CPlayer();
	~CPlayer();
	static CPlayer *Create(D3DXVECTOR3 pos,int nPlayerNum);
	static HRESULT Load(void);
	static void Unload(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Hit(int nDamage);
	void Life(int nLife);

	static bool GetDeath(int nPlayer) { return m_bDeath[nPlayer]; }
	CCollision*GetCollision(void) { return m_pCollision; }
	D3DXVECTOR3 GetMove(void) { return m_move; }
	void GetMove(D3DXVECTOR3 move) { m_move = move; }
	
private:
	void MoveKeyboard(void);
	void MoveController(void);
	void Direction(void);
	void Attack(void);
	void MotionManager(void);
	void MotionFalse(void);
	void SetMotion(MOTION motionState);
	void Dash(void);

	// メンバ変数
	static CModel::Model m_model[MAX_PLAYER][MAX_PARTS_NUM]; // モデル情報
	static int m_nNumModel;                      // モデル数
	static char m_achAnimPath[MOTION_MAX][64];   // アニメーションテキストのパス格納用
	static bool m_bDeath[MAX_PLAYER];

	D3DXVECTOR3 m_move;             // 移動量
	D3DXVECTOR3 m_moveDest;         // 移動量の目標値
	float m_fRotYDist;              // プレイヤーの向いている向きの目標値
	int m_nPlayerNum;               // プレイヤー番号
	CCollision*m_pCollision;        // コリジョンクラスのポインタ
	CMotion*m_pMotion[MOTION_MAX];  // アニメーションポインタ
	int m_nLife;					// プレイヤーのライフ
	MOTION m_motionState;           // 現在のモーション状態
	int m_nSpeed;
	bool m_bMotion;                 // 移動を止める系のモーション判定用
	bool m_bKeyboardMove;           // キーボードで移動しているかの判定用
	CLife *m_pLife[PLAYER_LIFE];
};

#endif