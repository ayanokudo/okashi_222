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
#define GRID_MODE_MOVE   (GRID_SIZE * 2)      // �O���b�h���[�h���̈ړ���
#define NORMAL_MODE_MOVE (10.0f)     // �m�[�}�����[�h�̎��̈ړ���
#define INTERVAL         (10)                    //������󂯕t����܂ł̊Ԋu

//*****************************************************************************
// �ÓI�����o�ϐ��錾
//*****************************************************************************
CPlayer::MODEL CObject::m_Model=CPlayer::MODEL_PLAYER;
int CObject::m_ObjctNum = 0;
CModel *CObject::m_pModel[MAX_OBJECT] = {};
CPlayer *CObject::m_pPlayer = NULL;
CCursor *CObject::m_pCursor = NULL;                     // �J�[�\���ւ̃|�C���^


//=============================================================================
// [CObject] �R���X�g���N�^
//=============================================================================
CObject::CObject()
{
    m_Model = CPlayer::MODEL_PLAYER;
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
    ChangeObject();
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
        GridTransform();
    }
}

//=============================================================================
// [Draw] �`�揈��
//=============================================================================
void CObject::Draw(void)
{

}

//=============================================================================
// [GridTransform] �O���b�h�̍��W�ɕϊ�
//=============================================================================
void CObject::GridTransform(void)
{
    m_pos = { GRID_SIZE,0.0f,GRID_SIZE };

}

//=============================================================================
// [ChangeObject] �I�u�W�F�N�g�̕ύX
//=============================================================================
void CObject::ChangeObject(void)
{
    int nModel = m_Model;
    if (CManager::GetKeyboard()->GetKeyTrigger(DIK_1))
    {
        nModel -=  1;
    }
    if (CManager::GetKeyboard()->GetKeyTrigger(DIK_2))
    {
        nModel += 1;
    }
    m_Model = (CPlayer::MODEL)nModel;
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
                switch (m_Model % CPlayer::MODEL_MAX == 0)
                {
                case CPlayer::MODEL_PLAYER:

                    m_pModel[nCnt] = CPlayer::Create(pos);
                    break;

                case CPlayer::MODEL_ENEMY:
                    m_pModel[nCnt] = CEnemy::Create(pos);
                    break;
                }

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
    D3DXVECTOR3 moveDest = { 0.0f,0.0f,0.0f };
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
        if (!m_bGridMode)
        {
            if (CManager::GetKeyboard()->GetKeyPress(DIK_A) || js.lX <= -600)
            {
                moveDest.z = sinf(45) * -fMove;
                moveDest.x = cosf(45) * fMove;
            }
            if (CManager::GetKeyboard()->GetKeyPress(DIK_D) || js.lX >= 600)
            {
                moveDest.z = sinf(45) * -fMove;
                moveDest.x = cosf(45) * -fMove;
            }
        }
    }
    else if (CManager::GetKeyboard()->GetKeyPress(DIK_S) || js.lY >= 600)
    {// ���ړ�

        moveDest.z = fMove;
        if (!m_bGridMode)
        {
            if (CManager::GetKeyboard()->GetKeyPress(DIK_A) || js.lX <= -600)
            {
                moveDest.z = sinf(45) * fMove;
                moveDest.x = cosf(45) * fMove;
            }
            if (CManager::GetKeyboard()->GetKeyPress(DIK_D) || js.lX >= 600)
            {
                moveDest.z = sinf(45) * fMove;
                moveDest.x = cosf(45) * -fMove;
            }
        }
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
