//=============================================================================
//
// �t�@�C���N���X [file.h]
// Author:KUDO AYANO
//
//=============================================================================
#ifndef _FILE_H_
#define _FILE_H_
#include "main.h"
#include "scene.h"
#include "model.h"

//*****************************************************************************
// �O���錾
//***************************************************************************** 
class CCollision;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CFile
{
public:
    CFile();
    ~CFile();

    static void Read(void);

    // �{�X�����̓����蔻��Z�b�^/�Q�b�^
    static CCollision *BossRoomCollision(void) { return m_Collision; }

private:
    static void SetObject(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CModel::OBJTYPE type, int ntype);
    static CCollision *m_Collision;
};
#endif // !_FILE_H_
