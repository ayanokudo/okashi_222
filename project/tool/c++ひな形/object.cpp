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
#include "grid.h"
#include "collision.h"
#include "wall.h"
#include "floor.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MODEL_PATH "./data/Models/cat V1.x"    //���f���̃p�X
#define GRID_MODE_MOVE   (GRID_SIZE * 2)      // �O���b�h���[�h���̈ړ���
#define NORMAL_MODE_MOVE (10.0f)     // �m�[�}�����[�h�̎��̈ړ���
#define INTERVAL         (10)                    //������󂯕t����܂ł̊Ԋu
#define OBJECT_RADIUS    (50.0f)                // �I��͈͂̔��a

//*****************************************************************************
// �ÓI�����o�ϐ��錾
//*****************************************************************************
CObject::MODEL CObject::m_type= MODEL_PLAYER;
int CObject::m_ObjctNum = 0;
CModel *CObject::m_pModel = NULL;
CPlayer *CObject::m_pPlayer = NULL;
CCursor *CObject::m_pCursor = NULL;                     // �J�[�\���ւ̃|�C���^


//=============================================================================
// [CObject] �R���X�g���N�^
//=============================================================================
CObject::CObject()
{
    m_type = MODEL_PLAYER;
    m_pos = { GRID_SIZE,0.0f,GRID_SIZE };
    m_ObjctNum = 0;
    m_bGridMode = true;
    m_nCountInterval = INTERVAL;
    m_pCollision = NULL;
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
    m_pCollision = CCollision::CreateSphere(m_pos, OBJECT_RADIUS);
    return S_OK;
}

//=============================================================================
// [Uninit] �I������
//=============================================================================
void CObject::Uninit(void)
{

    // �R���W�����̏I������
    if (m_pCollision != NULL)
    {
        m_pCollision->Uninit();
        m_pCollision = NULL;
    }
}

//=============================================================================
// [Update] �X�V����
//=============================================================================
void CObject::Update(void)
{
    // ���W�̈ړ�
    Move();

    // �z�u����I�u�W�F�N�g�̕ύX
    if (CManager::GetKeyboard()->GetKeyTrigger(DIK_1)||
        CManager::GetKeyboard()->GetKeyTrigger(DIK_2))
    {
        ChangeObject();
    }

    // �I�u�W�F�N�g�̔z�u
    if (CManager::GetKeyboard()->GetKeyTrigger(DIK_SPACE))
    {
        // �^�C�v��z�u�p�ɕϊ�
        SetObject(CObject::GetPlayer()->GetPos(), changeType());
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

    // �I�u�W�F�N�g�̍폜
    if (CManager::GetKeyboard()->GetKeyTrigger(DIK_BACK))
    {
        DeleteObject();
    }
    // �I�u�W�F�N�g�̉�]
    Rotation();
    // �����蔻��̈ʒu�X�V
    m_pCollision->SetPos(GetPos());
}

//=============================================================================
// [Draw] �`�揈��
//=============================================================================
void CObject::Draw(void)
{

}

//=============================================================================
// [changeType] �z�u�p�Ƀ^�C�v��ϊ�
//=============================================================================
CModel::OBJTYPE CObject::changeType(void)
{
    CModel::OBJTYPE type;
    switch (m_type)
    {
    case MODEL_PLAYER:
        type = OBJTYPE_PLAYER;
        break;

    case MODEL_ENEMY:
        type = OBJTYPE_ENEMY;
        break;

    case MODEL_WALL:
        type = OBJTYPE_WALL;
        break;

    case MODEL_FLOOR:
        type = OBJTYPE_FLOOR;
        break;
        
    }

    return type;
}

//=============================================================================
// [GridTransform] �O���b�h�̍��W�ɕϊ�
//=============================================================================
void CObject::GridTransform(void)
{
    m_pos = { GRID_SIZE,0.0f,GRID_SIZE };
}

//=============================================================================
// [Rotation] �I�u�W�F�N�g�̉�]
//=============================================================================
void CObject::Rotation(void)
{
    // �z�u�����I�u�W�F�N�g�Ɠ������Ă��邩���ׂ�
    for (int nCount = 0; nCount < PRIORITY_NUM; nCount++)
    {
        // �擪�̃A�h���X���擾
        CScene *pScene = CScene::GetTop(nCount);
        while (pScene != NULL)
        {
            // ���̃A�h���X��ۑ�
            CScene *pNext = pScene->GetNext();

            if (pScene != m_pPlayer&&
                pScene->GetType() == OBJTYPE_PLAYER ||
                pScene->GetType() == OBJTYPE_ENEMY ||
                pScene->GetType() == OBJTYPE_WALL ||
                pScene->GetType() == OBJTYPE_FLOOR)
            {
                if (CCollision::CollisionSphere(m_pCollision, ((CModel*)pScene)->GetCollision()))
                {
                    D3DXVECTOR3 rot = ((CModel*)pScene)->GetRot();
                    if (CManager::GetKeyboard()->GetKeyTrigger(DIK_I))
                    {
                        rot.y += D3DXToRadian(90);
                    }
                    if (CManager::GetKeyboard()->GetKeyTrigger(DIK_K))
                    {
                        rot.y -= D3DXToRadian(90);
                    }
                    ((CModel*)pScene)->SetRot(rot);
                }
            }
            // ���̃A�h���X���擾
            pScene = pNext;
        }
    }
}

//=============================================================================
// [ChangeObject] �I�u�W�F�N�g�̕ύX
//=============================================================================
void CObject::ChangeObject(void)
{
    int nModel = m_type;
    if (CManager::GetKeyboard()->GetKeyTrigger(DIK_1))
    {
        nModel -=  1;
    }
    if (CManager::GetKeyboard()->GetKeyTrigger(DIK_2))
    {
        nModel += 1;
    }
    // �ő�l�ȏ�/�ŏ��l�ȉ��ɂȂ����烋�[�v
    if (nModel >= MODEL_MAX)
    {
        nModel = MODEL_PLAYER;
    }
    if (nModel < MODEL_PLAYER)
    {
        nModel = MODEL_MAX-1;
    }

    m_type = (MODEL)nModel;
}

//=============================================================================
// [DeleteObject] �I�u�W�F�N�g�̍폜
//=============================================================================
void CObject::DeleteObject(void)
{
    // �z�u�����I�u�W�F�N�g�Ɠ������Ă��邩���ׂ�
    for (int nCount = 0; nCount < PRIORITY_NUM; nCount++)
    {
        // �擪�̃A�h���X���擾
        CScene *pScene = CScene::GetTop(nCount);
        while (pScene != NULL)
        {
            // ���̃A�h���X��ۑ�
            CScene *pNext = pScene->GetNext();

            if (pScene !=m_pPlayer&&
                pScene->GetType() == OBJTYPE_PLAYER ||
                pScene->GetType() == OBJTYPE_ENEMY ||
                pScene->GetType() == OBJTYPE_WALL||
                pScene->GetType() == OBJTYPE_FLOOR)
            {
                if (CCollision::CollisionSphere(m_pCollision, ((CModel*)pScene)->GetCollision()))
                {
                    pScene->Uninit();
                    pScene = NULL;
                    return;
                }
            }
            // ���̃A�h���X���擾
            pScene = pNext;
        }
    }
}

//=============================================================================
// [SetObject] �I�u�W�F�N�g�̔z�u
// Author : AYANO KUDO
// ����
//pos : �ʒu
//=============================================================================
void CObject::SetObject(D3DXVECTOR3 pos, CModel::OBJTYPE type)
{
    switch (type)
    {
    case CModel::OBJTYPE_PLAYER:

        m_pModel= CPlayer::Create(pos);
        break;

    case CModel::OBJTYPE_ENEMY:
        m_pModel = CEnemy::Create(pos);
        break;

    case CModel::OBJTYPE_WALL:
        m_pModel = CWall::Create(pos);
        break;

    case CModel::OBJTYPE_FLOOR:
        m_pModel = CFloor::Create(pos);
        break;
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
