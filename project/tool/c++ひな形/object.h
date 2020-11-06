//=============================================================================
//
// �I�u�W�F�N�g�N���X [object.h]
// Author : AYANO KUDO
//
//=============================================================================
#ifndef _OBJECT_H_
#define _OBJECT_H_
#include "main.h"
#include "model.h"
#include "player.h"

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CModel;
class CPlayer;
class CCursor;
class CCollision;

//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
// �I�u�W�F�N�g�N���X
class CObject : public CScene
{
    typedef enum
    {
        MODEL_PLAYER=0, // �v���C���[
        MODEL_ENEMY,    // �G
        MODEL_WALL,     // ��
        MODEL_FLOOR,    // ��
        MODEL_MAX
    }MODEL;      // ���f���̃t�@�C����

public:
    // �����o�֐�
    CObject();
    ~CObject();

    static CObject *Create(D3DXVECTOR3 pos);
    static HRESULT Load(void);
    static void Unload(void);
    HRESULT Init(void);
    void Uninit(void);
    void Update(void);
    void Draw(void);

    // �z�u�p�Ƀ^�C�v�ϊ�
    CModel::OBJTYPE changeType(void);

    void GridTransform(void);

    void Rotation(void);

   void ChangeObject(void);

   // �I�u�W�F�N�g�̎�ޕύX
   void ChangeType(void);

    // �I�u�W�F�N�g�̍폜
    void DeleteObject(void);

    // �I�u�W�F�N�g�̃Z�b�^
    static void SetObject(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CModel::OBJTYPE type);

    // �v���C���[�̃Q�b�^
    static CPlayer *GetPlayer(void) { return m_pPlayer; }

    // �I�u�W�F�N�g�̏��̃Q�b�^
    static CModel *GetObjectData(int nNumObj) { return m_pModel; }

    // �ʒu���̃Q�b�^
    D3DXVECTOR3 GetPos(void) { return m_pos; }

private:
    // �����o�֐�
    void Move(void);

    // �����o�ϐ�
    static MODEL m_type;                // ���ݑI�𒆂̃��f���̎��
    D3DXVECTOR3 m_pos;                             // �I�u�W�F�N�g�̈ʒu
    static int      m_ObjctNum;                    // �I�u�W�F�N�g�̐�
    static CPlayer*m_pPlayer;                      // �v���C���[
    static CCursor *m_pCursor;                     // �J�[�\���ւ̃|�C���^
    static CModel  *m_pModel;                      // �V�[��
    CCollision *m_pCollision;                      // �����蔻��

     bool           m_bGridMode;                   //�O���b�h���[�h���ǂ���
     int            m_nCountInterval;              // ������󂯕t����܂ł̊Ԋu
};
#endif      // _OBJECT_H_