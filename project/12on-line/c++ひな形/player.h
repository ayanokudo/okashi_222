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

//*****************************
// 前方宣言
//*****************************
class CCollision;
class CAnimation;

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
		ANIM_WAIT = 0,
		ANIM_WALK,
		ANIM_VOICE,
		ANIM_PUNCH,
		ANIM_DASH,
		ANIM_MAX
	}ANIMATION;

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
	void AnimationFalse(void);

	// メンバ変数
	static CModel::Model m_model[MAX_PARTS_NUM];
	static int m_nNumModel;
	static char m_chAnimPath[ANIM_MAX][64]; // アニメーションテキストのパス格納用
	D3DXVECTOR3 m_move;           // 移動量
	D3DXVECTOR3 m_moveDest;       // 移動量の目標値
	float m_fRotYDist;            // プレイヤーの向いている向きの目標値
	int m_nPlayerNum;             // プレイヤー番号
	CCollision*m_pCollision;      // コリジョンクラスのポインタ
	CAnimation*m_pWalkAnim;       // 歩きアニメーション
	CAnimation*m_pAnim[ANIM_MAX]; // アニメーションポインタ
};

#endif