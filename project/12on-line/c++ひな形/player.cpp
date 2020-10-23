////////////////////////////////////////////////////
//
//    player�N���X�̏���[player.cpp]
//    Author:���V ����
//
////////////////////////////////////////////////////

//******************************
// �C���N���[�h
//******************************
#include "player.h"
#include "manager.h"
#include "renderer.h"
#include "keyboard.h"
#include "joypad.h"
#include "bullet.h"

//*****************************
// �}�N����`
//*****************************
#define MODEL_PATH "./data/Models/cat_sakamoto.x"    //���f���̃p�X
#define PLAYER_SPEED 10
#define PLAYER_MOVE_RATE 0.05f

//*****************************
// �ÓI�����o�ϐ��錾
//*****************************
LPD3DXMESH   CPlayer::m_pMeshModel = NULL;   	//���b�V�����ւ̃|�C���^
LPD3DXBUFFER CPlayer::m_pBuffMatModel = NULL;	//�}�e���A�����ւ̃|�C���^
DWORD        CPlayer::m_nNumMatModel = 0;	    //�}�e���A�����̐�

//******************************
// �R���X�g���N�^
//******************************
CPlayer::CPlayer()
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fRotYDist = 0.0f;
}

//******************************
// �f�X�g���N�^
//******************************
CPlayer::~CPlayer()
{
}

//******************************
// �N���G�C�g
//******************************
CPlayer * CPlayer::Create(D3DXVECTOR3 pos)
{
	// �������̊m��
	CPlayer *pPlayer;
	pPlayer = new CPlayer;

	// ������
	pPlayer->Init();
	pPlayer->SetPos(pos);
	// �e�l�̑���E�Z�b�g
	pPlayer->SetObjType(OBJTYPE_MAP); // �I�u�W�F�N�g�^�C�v

	return pPlayer;
}

//******************************
// �e�N�X�`���̃��[�h
//******************************
HRESULT CPlayer::Load(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	//X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX(MODEL_PATH,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_pBuffMatModel,
		NULL,
		&m_nNumMatModel,
		&m_pMeshModel);

	return S_OK;
}

//******************************
// �e�N�X�`���̃A�����[�h
//******************************
void CPlayer::Unload(void)
{
	//���b�V���̔j��
	if (m_pMeshModel != NULL)
	{
		m_pMeshModel->Release();
		m_pMeshModel = NULL;
	}
	//�}�e���A���̔j��
	if (m_pBuffMatModel != NULL)
	{
		m_pBuffMatModel->Release();
		m_pBuffMatModel = NULL;
	}
}


//******************************
// ����������
//******************************
HRESULT CPlayer::Init(void)
{
	if (FAILED(CModel::Init()))
	{
		return E_FAIL;
	}

	// �e�N�X�`�����蓖��
	BindModel(m_pMeshModel, m_pBuffMatModel, m_nNumMatModel);

	return S_OK;
}

//******************************
// �I������
//******************************
void CPlayer::Uninit(void)
{

	CModel::Uninit();
}

//******************************
// �X�V����
//******************************
void CPlayer::Update(void)
{
	// �ړ�
	Move();
	// �U��
	Attack();
}

//******************************
// �`�揈��
//******************************
void CPlayer::Draw(void)
{
	CModel::Draw();
}

//******************************
// �ړ�����
//******************************
void CPlayer::Move(void)
{
	// �ړ�����
	// ���W
	D3DXVECTOR3 pos = GetPos();
	//�ړ��ʂ̖ڕW�l
	D3DXVECTOR3 moveDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	// �W���C�X�e�B�b�N�̎擾
	DIJOYSTATE js = CManager::GetJoypad()->GetStick(0);

	if (CManager::GetKeyboard()->GetKeyPress(DIK_W) || js.lY <= -600)
	{// ���ړ�
		moveDest.z = -PLAYER_SPEED;

		if (CManager::GetKeyboard()->GetKeyPress(DIK_A) || js.lX <= -600)
		{
			moveDest.z = sinf(45) * -PLAYER_SPEED;
			moveDest.x = cosf(45) * PLAYER_SPEED;
		}
		if (CManager::GetKeyboard()->GetKeyPress(DIK_D) || js.lX >= 600)
		{
			moveDest.z = sinf(45) * -PLAYER_SPEED;
			moveDest.x = cosf(45) * -PLAYER_SPEED;
		}
	}
	else if (CManager::GetKeyboard()->GetKeyPress(DIK_S) || js.lY >= 600)
	{// ���ړ�

		moveDest.z = PLAYER_SPEED;

		if (CManager::GetKeyboard()->GetKeyPress(DIK_A) || js.lX <= -600)
		{
			moveDest.z = sinf(45) * PLAYER_SPEED;
			moveDest.x = cosf(45) * PLAYER_SPEED;
		}
		if (CManager::GetKeyboard()->GetKeyPress(DIK_D) || js.lX >= 600)
		{
			moveDest.z = sinf(45) * PLAYER_SPEED;
			moveDest.x = cosf(45) * -PLAYER_SPEED;
		}
	}
	else if (CManager::GetKeyboard()->GetKeyPress(DIK_A) || js.lX <= -600)
	{// ���ړ�
		moveDest.x = PLAYER_SPEED;

	}
	else if (CManager::GetKeyboard()->GetKeyPress(DIK_D) || js.lX >= 600)
	{// ���ړ�
		moveDest.x = -PLAYER_SPEED;
	}

	// ����
	m_move += (moveDest - m_move) * PLAYER_MOVE_RATE;
	
	// �ړ��ʂ𑫂�
	pos += m_move;

	// ���W�̃Z�b�g
	SetPos(pos);

}

//******************************
// �U������
//******************************
void CPlayer::Attack(void)
{
	if (CManager::GetKeyboard()->GetKeyTrigger(DIK_SPACE))
	{// �e������
		// �v���C���[�̌����Ă�������̎擾
		float fRotY = GetRot().y - D3DXToRadian(90);
		// �ړ���
		D3DXVECTOR3 bulletMove;
		bulletMove.x = cosf(fRotY)*BULLET_SPEED_PLAYER;
		bulletMove.y = 0;
		bulletMove.z = sinf(fRotY)*BULLET_SPEED_PLAYER;
		// �e�����ʒu�̒���
		D3DXVECTOR3 pos = GetPos();
		pos.y += 10;
		// �e�̐���
		CBullet::Create(pos, bulletMove, 300, CBullet::BULLETUSER_PLAYER)->SetColor(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
	}
}
