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

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_OBJECT (128)            // 配置できるオブジェクトの数

//*****************************************************************************
// クラスの定義
//*****************************************************************************
// オブジェクトクラス
class CObject : public CScene
{
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

    void GridTransform(void);

    void ChangeObject(void);

    static void SetObject(D3DXVECTOR3 pos);

    static CPlayer *GetPlayer(void) { return m_pPlayer; }  // プレイヤーの取得処理
    static CModel *GetObjectData(int nNumObj) { return m_pModel[nNumObj]; }

    D3DXVECTOR3 GetPos(void) { return m_pos; }
private:
    // メンバ関数
    void Move(void);

    // メンバ変数
    static CPlayer::MODEL m_Model;                        // 現在選択中のモデル
    D3DXVECTOR3 m_pos;                             // オブジェクトの位置
    static int      m_ObjctNum;                    // オブジェクトの数
    static CPlayer*m_pPlayer;                      // プレイヤー
    static CCursor *m_pCursor;                     // カーソルへのポインタ
    static CModel  *m_pModel[MAX_OBJECT];          // シーン

     bool           m_bGridMode;                   //グリッドモードがどうか
     int            m_nCountInterval;              // 操作を受け付けるまでの間隔
};
#endif      // _OBJECT_H_