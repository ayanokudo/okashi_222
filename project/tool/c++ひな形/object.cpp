//=============================================================================
//
// �I�u�W�F�N�g�N���X [object.cpp]
// Author : AYANO KUDO
//
//=============================================================================
#include "object.h"
#include "manager.h"
#include "renderer.h"
#include "keyboard.h"
#include "game.h"
#include "player.h"
#include "enemy.h"
#include "file.h"
#include "joypad.h"
#include "cursor.h"
#include "floor.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MODEL_PATH "./data/Models/cat V1.x"    //���f���̃p�X
#define GRID_MODE_MOVE   (GRID_SIZE)      // �O���b�h���[�h���̈ړ���
#define NORMAL_MODE_MOVE (3.0f)     // �m�[�}�����[�h�̎��̈ړ���
#define INTERVAL         (7)                    //������󂯕t����܂ł̊Ԋu

//*****************************************************************************
// �ÓI�����o�ϐ��錾
//*****************************************************************************
int CObject::m_ObjctNum = 0;
CModel *CObject::m_pModel[MAX_OBJECT] = {};
CPlayer *CObject::m_pPlayer = NULL;
CCursor *CObject::m_pCursor = NULL;                     // �J�[�\���ւ̃|�C���^


//=============================================================================
// [CObject] �R���X�g���N�^
//=============================================================================
CObject::CObject()
{
    m_pos = { GRID_SIZE,0.0f,GRID_SIZE };
    m_ObjctNum = 0;
    m_bGridMode = true;
    m_nCountInterval = INTERVAL;
    
}

//=============================================================================
// [~CObject] �f�X�g���N�^
//=============================================================================
CObject::~CObject()
{

}

//=============================================================================
// [Create] �I�u�W�F�N�g�̐���
//=============================================================================
CObject * CObject::Create(D3DXVECTOR3 pos)
{
    CObject *pObject = NULL;
    if (!pObject)
    {
        pObject = new CObject;
        pObject->Init();
        // �e�l�̑���E�Z�b�g
    }
    return pObject;
}

//=============================================================================
// [Load] �e�N�X�`���̓ǂݍ���
//=============================================================================
HRESULT CObject::Load(void)
{
    return S_OK;
}

//=============================================================================
// [Unload] �e�N�X�`���̔j��
//=============================================================================
void CObject::Unload(void)
{

}

//=============================================================================
// [Init] ����������
//=============================================================================
HRESULT CObject::Init(void)
{
    // �v���C���[�̐���
    m_pPlayer = CPlayer::Create(m_pos);
    m_pCursor = CCursor::Create(m_pos);
    return S_OK;
}

//=============================================================================
// [Uninit] �I������
//=============================================================================
void CObject::Uninit(void)
{

}

//=============================================================================
// [Update] �X�V����
//=============================================================================
void CObject::Update(void)
{
    // ���W�̈ړ�
    Move();

    // �I�u�W�F�N�g�̔z�u
    if (CManager::GetKeyboard()->GetKeyTrigger(DIK_SPACE))
    {
        SetObject(CObject::GetPlayer()->GetPos());
    }

    // �t�@�C����������
    if (CManager::GetKeyboard()->GetKeyTrigger(DIK_F1))
    {
        CFile::Writing();
    }

    // ���[�h�ؑ�
    if (CManager::GetKeyboard()->GetKeyTrigger(DIK_F2))
    {
        m_bGridMode ^= true;
    }
}

//=============================================================================
// [Draw] �`�揈��
//=============================================================================
void CObject::Draw(void)
{

}

//=============================================================================
// [SetObject] �I�u�W�F�N�g�̔z�u
// Author : AYANO KUDO
// ����
//pos : �ʒu
//=============================================================================
void CObject::SetObject(D3DXVECTOR3 pos)
{
        // ���݂̈ʒu�ɃI�u�W�F�N�g�̔z�u������
        for (int nCnt = 0; nCnt < MAX_OBJECT; nCnt++)
        {
            if (m_pModel[nCnt] == NULL)
            {
                m_pModel[nCnt] = CEnemy::Create(pos);
                break;// ��̂��z�u���邽�߂Ƀ��[�v�𔲂���
            }
        }
}

//=============================================================================
// [Move] �ړ�����
//=============================================================================
void CObject::Move(void)
{

    //�ړ��ʂ̖ڕW�l
    D3DXVECTOR3 moveDest = {0.0f,0.0f,0.0f};
    // �W���C�X�e�B�b�N�̎擾
    DIJOYSTATE js = CManager::GetJoypad()->GetStick(0);
    float fMove = 0.0f;// �ړ���

    m_ObjctNum++;
    if (m_bGridMode)
    {
        if (m_ObjctNum >= INTERVAL)
        {
        fMove = GRID_MODE_MOVE;
        m_ObjctNum = 0;
        }
    }
    else
    {
        fMove = NORMAL_MODE_MOVE;
    }

    if (CManager::GetKeyboard()->GetKeyPress(DIK_W) || js.lY <= -600)
    {// ���ړ�
        moveDest.z = -fMove;

        //if (CManager::GetKeyboard()->GetKeyPress(DIK_A) || js.lX <= -600)
        //{
        //    moveDest.z = sinf(45) * -fMove;
        //    moveDest.x = cosf(45) * fMove;
        //}
        //if (CManager::GetKeyboard()->GetKeyPress(DIK_D) || js.lX >= 600)
        //{
        //    moveDest.z = sinf(45) * -fMove;
        //    moveDest.x = cosf(45) * -fMove;
        //}
    }
    else if (CManager::GetKeyboard()->GetKeyPress(DIK_S) || js.lY >= 600)
    {// ���ړ�

        moveDest.z = fMove;

        //if (CManager::GetKeyboard()->GetKeyPress(DIK_A) || js.lX <= -600)
        //{
        //    moveDest.z = sinf(45) * fMove;
        //    moveDest.x = cosf(45) * fMove;
        //}
        //if (CManager::GetKeyboard()->GetKeyPress(DIK_D) || js.lX >= 600)
        //{
        //    moveDest.z = sinf(45) * fMove;
        //    moveDest.x = cosf(45) * -fMove;
        //}
    }
    else if (CManager::GetKeyboard()->GetKeyPress(DIK_A) || js.lX <= -600)
    {// ���ړ�
        moveDest.x = fMove;

    }
    else if (CManager::GetKeyboard()->GetKeyPress(DIK_D) || js.lX >= 600)
    {// ���ړ�
        moveDest.x = -fMove;
    }

    // �ړ��ʂ𑫂�
    m_pos += moveDest;
    m_pPlayer->SetPos(m_pos);
    m_pCursor->SetPos(m_pos);

}
