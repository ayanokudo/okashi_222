//=============================================================================
//
// ファイルクラス [file.h]
// Author:KUDO AYANO
//
//=============================================================================
#ifndef _FILE_H_
#define _FILE_H_
#include "main.h"
#include "scene.h"
#include "model.h"

//*****************************************************************************
// 前方宣言
//***************************************************************************** 
class CCollision;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CFile
{
public:
    CFile();
    ~CFile();

    static void Read(void);

    // ボス部屋の当たり判定セッタ/ゲッタ
    static CCollision *BossRoomCollision(void) { return m_Collision; }

private:
    static void SetObject(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CModel::OBJTYPE type, int ntype);
    static CCollision *m_Collision;
};
#endif // !_FILE_H_
