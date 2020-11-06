//=============================================================================
//
// オブジェクトクラス [object.h]
// Author : AYANO KUDO
//
//=============================================================================
#ifndef _OBJECT_H_
#define _OBJECT_H_
#include "main.h"
#include "model.h"
#include "player.h"

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CModel;
class CPlayer;
class CCursor;
class CCollision;

//*****************************************************************************
// クラスの定義
//*****************************************************************************
// オブジェクトクラス
class CObject : public CScene
{
    typedef enum
    {
        MODEL_PLAYER=0, // プレイヤー
        MODEL_ENEMY,    // 敵
        MODEL_WALL,     // 壁
        MODEL_FLOOR,    // 床
        MODEL_MAX
    }MODEL;      // モデルのファイル名

public:
    // メンバ関数
    CObject();
    ~CObject();

    static CObject *Create(D3DXVECTOR3 pos);
    static HRESULT Load(void);
    static void Unload(void);
    HRESULT Init(void);
    void Uninit(void);
    void Update(void);
    void Draw(void);

    // 配置用にタイプ変換
    CModel::OBJTYPE changeType(void);

    void GridTransform(void);

    void Rotation(void);

   void ChangeObject(void);

   // オブジェクトの種類変更
   void ChangeType(void);

    // オブジェクトの削除
    void DeleteObject(void);

    // オブジェクトのセッタ
    static void SetObject(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CModel::OBJTYPE type);

    // プレイヤーのゲッタ
    static CPlayer *GetPlayer(void) { return m_pPlayer; }

    // オブジェクトの情報のゲッタ
    static CModel *GetObjectData(int nNumObj) { return m_pModel; }

    // 位置情報のゲッタ
    D3DXVECTOR3 GetPos(void) { return m_pos; }

private:
    // メンバ関数
    void Move(void);

    // メンバ変数
    static MODEL m_type;                // 現在選択中のモデルの種類
    D3DXVECTOR3 m_pos;                             // オブジェクトの位置
    static int      m_ObjctNum;                    // オブジェクトの数
    static CPlayer*m_pPlayer;                      // プレイヤー
    static CCursor *m_pCursor;                     // カーソルへのポインタ
    static CModel  *m_pModel;                      // シーン
    CCollision *m_pCollision;                      // 当たり判定

     bool           m_bGridMode;                   //グリッドモードがどうか
     int            m_nCountInterval;              // 操作を受け付けるまでの間隔
};
#endif      // _OBJECT_H_