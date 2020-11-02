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

//*****************************
// マクロ定義
//*****************************

//*****************************
// クラス定義
//*****************************

// パーティクルクラス
class CPlayer : public CModelHierarchy
{
public:
	typedef enum
	{
		WAIT = 0, // 待機
		WALK,	  // 歩き
		VOICE,	  // 鳴き声
		PUNCH,	  // パンチ
		DASH,	  // 走り
		MOTION_MAX
	}MOTION;

	typedef enum
	{
		TYPE_WALK,
		TYPE_DASH,
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

	CCollision*GetCollision(void) { return m_pCollision; }
	D3DXVECTOR3 GetMove(void) { return m_move; }
	void GetMove(D3DXVECTOR3 move) { m_move = move; }
	
private:
	void MoveKeyboard(void);
	void MoveController(void);
	void Direction(void);
	void Attack(void);
	void MotionFalse(void);
	void MotionManager(void);

	// メンバ変数
	static CModel::Model m_model[MAX_PLAYER][MAX_PARTS_NUM]; // モデル情報
	static int m_nNumModel;                      // モデル数
	static char m_achAnimPath[MOTION_MAX][64];   // アニメーションテキストのパス格納用

	D3DXVECTOR3 m_move;             // 移動量
	D3DXVECTOR3 m_moveDest;         // 移動量の目標値
	float m_fRotYDist;              // プレイヤーの向いている向きの目標値
	int m_nPlayerNum;               // プレイヤー番号
	CCollision*m_pCollision;        // コリジョンクラスのポインタ
	CMotion*m_pMotion[MOTION_MAX];  // アニメーションポインタ
	int m_nLife;				    // プレイヤーのライフ
	MOTION m_motionState;           // 現在のモーション状態
	int m_nSpeed;
};

#endif