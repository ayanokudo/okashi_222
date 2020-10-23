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
#include "scene3d.h"#include "debug_log.h"
#include "collision.h"

//*****************************
// �}�N����`
//*****************************
#define MODEL_PATH "./data/Models/cat_sakamoto.x"    //���f���̃p�X
#define PLAYER_SPEED 10                          // �ړ��X�s�[�h
#define PLAYER_MOVE_RATE 0.05f                   // �ړ��̊����̌W��
#define PLAYER_DIRECTION_RATE 0.1f              // ������ς���Ƃ��̌W��
#define PLAYER_RADIUS 100                       // �v���C���[�̔��a
//*****************************
// �ÓI�����o�ϐ��錾
//*****************************
LPD3DXMESH   CPlayer::m_pMeshModel = NULL;   	//���b�V�����ւ̃|�C���^
LPD3DXBUFFER CPlayer::m_pBuffMatModel = NULL;	//�}�e���A�����ւ̃|�C���^
DWORD        CPlayer::m_nNumMatModel = 0;	    //�}�e���A�����̐�

//******************************
// �R���X�g���N�^
//******************************
CPlayer::CPlayer():CModel(OBJTYPE_PLAYER)
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_moveDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fRotYDist = 0.0f;
	m_nPlayerNum = 0;
	m_pCollision = NULL;
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
CPlayer * CPlayer::Create(D3DXVECTOR3 pos, int nPlayerNum)
{
	// �������̊m��
	CPlayer *pPlayer;
	pPlayer = new CPlayer;

	// ������
	pPlayer->Init();
	
	// �e�l�̑���E�Z�b�g
	pPlayer->SetPos(pos);
	// �e�l�̑���E�Z�b�g
	pPlayer->SetObjType(OBJTYPE_PLAYER); // �I�u�W�F�N�g�^�C�v
	pPlayer->m_nPlayerNum = nPlayerNum;
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
	// �����蔻��̐���
	m_pCollision = CCollision::CreateSphere(GetPos(), PLAYER_RADIUS);
	return S_OK;
}

//******************************
// �I������
//******************************
void CPlayer::Uninit(void)
{
	// �R���W�����̏I������
	if (m_pCollision != NULL)
	{
		m_pCollision->Uninit();
		m_pCollision = NULL;
	}

	CModel::Uninit();
}

//******************************
// �X�V����
//******************************
void CPlayer::Update(void)
{
	// �ڕW�l�̏�����
	m_moveDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// �ړ��i�L�[�{�[�h�j
	MoveKeyboard();

	// �ړ��i�R���g���[���[�j
	MoveController();

	// ����
	m_move += (m_moveDest - m_move) * PLAYER_MOVE_RATE;

	// ���W
	D3DXVECTOR3 pos = GetPos();
	// �ړ��ʂ𑫂�
	pos += m_move;

	// ���W�̃Z�b�g
	SetPos(pos);

	// �����̊Ǘ�
	Direction();
	// �U��
	Attack();

	// �����蔻��̈ʒu�X�V
	m_pCollision->SetPos(GetPos());
}

//******************************
// �`�揈��
//******************************
void CPlayer::Draw(void)
{
	CModel::Draw();
}

//******************************
// �ړ�����(�L�[�{�[�h)
//******************************
void CPlayer::MoveKeyboard(void)
{
	// �ړ�����

	// �W���C�X�e�B�b�N�̎擾
	DIJOYSTATE js = CManager::GetJoypad()->GetStick(0);

	if (CManager::GetKeyboard()->GetKeyPress(DIK_W))
	{// ���ړ�
		m_moveDest.z = -PLAYER_SPEED;

		// �����̐ݒ�
		m_fRotYDist = D3DXToRadian(0);

		if (CManager::GetKeyboard()->GetKeyPress(DIK_A))
		{
			// �����̐ݒ�
			m_fRotYDist = D3DXToRadian(-45);

			m_moveDest.z = sinf(45) * -PLAYER_SPEED;
			m_moveDest.x = cosf(45) * PLAYER_SPEED;
		}
		if (CManager::GetKeyboard()->GetKeyPress(DIK_D))
		{
			// �����̐ݒ�
			m_fRotYDist = D3DXToRadian(45);

			m_moveDest.z = sinf(45) * -PLAYER_SPEED;
			m_moveDest.x = cosf(45) * -PLAYER_SPEED;
		}
	}
	else if (CManager::GetKeyboard()->GetKeyPress(DIK_S))
	{// ���ړ�
	
	    // �����̐ݒ�
		m_fRotYDist = D3DXToRadian(180);
		m_moveDest.z = PLAYER_SPEED;

		if (CManager::GetKeyboard()->GetKeyPress(DIK_A))
		{
			// �����̐ݒ�
			m_fRotYDist = D3DXToRadian(225);

			m_moveDest.z = sinf(45) * PLAYER_SPEED;
			m_moveDest.x = cosf(45) * PLAYER_SPEED;
		}
		if (CManager::GetKeyboard()->GetKeyPress(DIK_D))
		{
			// �����̐ݒ�
			m_fRotYDist = D3DXToRadian(135);

			m_moveDest.z = sinf(45) * PLAYER_SPEED;
			m_moveDest.x = cosf(45) * -PLAYER_SPEED;
		}
	}
	else if (CManager::GetKeyboard()->GetKeyPress(DIK_A))
	{// ���ړ�
	 
	    // �����̐ݒ�
		m_fRotYDist = D3DXToRadian(-90);

		m_moveDest.x = PLAYER_SPEED;

	}
	else if (CManager::GetKeyboard()->GetKeyPress(DIK_D))
	{// ���ړ�
	 
	    // �����̐ݒ�
		m_fRotYDist = D3DXToRadian(90);

		m_moveDest.x = -PLAYER_SPEED;
	}

	

}
//******************************
// �ړ�����(�R���g���[���[)
//******************************
void CPlayer::MoveController(void)
{
	// �W���C�X�e�B�b�N�̏��̎擾
	DIJOYSTATE js = CManager::GetJoypad()->GetStick(m_nPlayerNum);

	// �X�e�B�b�N���ǂꂭ�炢�|����Ă��邩�ŃX�s�[�h�̒���
	float fSpeedX = 0.0f;
	float fSpeedZ = 0.0f;
	if (js.lX < 0)
	{
		fSpeedX = 0 - js.lX;
	}
	else if (js.lX > 0)
	{
		fSpeedX = js.lX - 0;
	}

	if (js.lY < 0)
	{
		fSpeedZ = 0 - js.lY;
	}

	else if (js.lY > 0)
	{
		fSpeedZ = js.lY - 0;
	}

	// �X�e�B�b�N���|����Ă���p�x
	float fAngle = atan2f(js.lY, js.lX);
	// �X�e�B�b�N�����ȏ�|����Ă���Ƃ�
	if (js.lX >= 10 || js.lX <= -10 || js.lY >= 10 || js.lY <= -10)
	{
		// �ړ��ʂ̖ڕW�l
		m_moveDest.x = cosf(fAngle) * -fSpeedX / 100;
		m_moveDest.z = sinf(fAngle) * fSpeedZ / 100;
		// �����̐ݒ�
		m_fRotYDist = atan2f(js.lX, -js.lY);
	}

	// ����
	m_move += (m_moveDest - m_move) * PLAYER_MOVE_RATE;

	// ���W
	D3DXVECTOR3 pos = GetPos();
	// �ړ��ʂ𑫂�
	pos += m_move;

	// ���W�̃Z�b�g
	SetPos(pos);

	
}

//******************************
// �L�����N�^�[�̌����̐ݒ�
//******************************
void CPlayer::Direction(void)
{
	// ���݂̃��b�g�̎擾
	D3DXVECTOR3 rot = GetRot();

	// �O����Ɖ�]���Ȃ��悤����
	while (m_fRotYDist - rot.y > D3DXToRadian(180))
	{
		m_fRotYDist -= D3DXToRadian(360);
	}
	while (m_fRotYDist - rot.y < D3DXToRadian(-180))
	{
		m_fRotYDist += D3DXToRadian(360);
	}

	// �����̍X�V
	rot.y += (m_fRotYDist - rot.y)*PLAYER_DIRECTION_RATE;
	// �����̐ݒ�
	SetRot(rot);
}

//******************************
// �U������
//******************************
void CPlayer::Attack(void)
{
	if (CManager::GetKeyboard()->GetKeyTrigger(DIK_SPACE) || CManager::GetJoypad()->GetJoystickTrigger(2, m_nPlayerNum))
	{// �e������
		// �v���C���[�̌����Ă�������̎擾
		float fRotY = GetRot().y - D3DXToRadian(90);
		// �ړ���
		D3DXVECTOR3 bulletMove;
		bulletMove.x = cosf(fRotY)*-BULLET_SPEED_PLAYER;
		bulletMove.y = 0;
		bulletMove.z = sinf(fRotY)*BULLET_SPEED_PLAYER;
		// �e�����ʒu�̒���
		D3DXVECTOR3 pos = GetPos();
		pos.y += 10;
		// �e�̐���
		CBullet::Create(pos, bulletMove, 300, CBullet::BULLETUSER_PLAYER)->SetColor(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
	}
}
