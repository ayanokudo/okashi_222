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

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_OBJECT (128)            // �z�u�ł���I�u�W�F�N�g�̐�

//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
// �I�u�W�F�N�g�N���X
class CObject : public CScene
{
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

    void GridTransform(void);

    void ChangeObject(void);

    static void SetObject(D3DXVECTOR3 pos);

    static CPlayer *GetPlayer(void) { return m_pPlayer; }  // �v���C���[�̎擾����
    static CModel *GetObjectData(int nNumObj) { return m_pModel[nNumObj]; }

    D3DXVECTOR3 GetPos(void) { return m_pos; }
private:
    // �����o�֐�
    void Move(void);

    // �����o�ϐ�
    static CPlayer::MODEL m_Model;                        // ���ݑI�𒆂̃��f��
    D3DXVECTOR3 m_pos;                             // �I�u�W�F�N�g�̈ʒu
    static int      m_ObjctNum;                    // �I�u�W�F�N�g�̐�
    static CPlayer*m_pPlayer;                      // �v���C���[
    static CCursor *m_pCursor;                     // �J�[�\���ւ̃|�C���^
    static CModel  *m_pModel[MAX_OBJECT];          // �V�[��

     bool           m_bGridMode;                   //�O���b�h���[�h���ǂ���
     int            m_nCountInterval;              // ������󂯕t����܂ł̊Ԋu
};
#endif      // _OBJECT_H_