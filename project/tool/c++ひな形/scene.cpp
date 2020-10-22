//=================================================
//
//    scene�N���X�̏���[scene.cpp]
//    Author:���V ����
//
//=================================================

//***********************************
// �C���N���[�h
//***********************************
#include "scene.h"
#include "scene2d.h"

//***********************************
//�ÓI�����o�ϐ��錾
//***********************************
CScene *CScene::m_apScene[MAX_SCENE] = {};
int CScene::m_nNumAll = 0;

//===================================
// �R���X�g���N�^
//===================================
CScene::CScene()
{
	for (int nCntScene = 0; nCntScene < MAX_SCENE; nCntScene++)
	{
		if (m_apScene[nCntScene] == NULL)
		{
			m_apScene[nCntScene] = this;
			m_nNumIndex = nCntScene;
			m_nNumAll++;
			m_type = OBJTYPE_NONE;
			break;
		}
	}
}
//===================================
// �f�X�g���N�^
//===================================
CScene::~CScene()
{
}

//====================================
// ���ׂďI������
//====================================
void CScene::ReleaseAll(void)
{
	for (int nCntScene = 0; nCntScene < MAX_SCENE; nCntScene++)
	{
		if (m_apScene[nCntScene] != NULL)
		{
			m_apScene[nCntScene]->Uninit();

		}
	}
}

//====================================
// ���ׂčX�V
//====================================
void CScene::UpdateAll(void)
{
	for (int nCntScene = 0; nCntScene < MAX_SCENE; nCntScene++)
	{
		if (m_apScene[nCntScene] != NULL)
		{
			m_apScene[nCntScene]->Update();
		}
	}
}

//====================================
// ���ׂĕ`��
//====================================
void CScene::DrawAll(void)
{
	OBJTYPE objType = OBJTYPE_NONE;

	// �I�u�W�F�N�g�^�C�v�������[�v
	for (int nCntLayer = 0; nCntLayer < OBJTYPE_MAX; nCntLayer++)
	{
		
		objType = (OBJTYPE)nCntLayer;

		// �I�u�W�F�N�g�̍ő吔�����[�v
		for (int nCntScene = 0; nCntScene < MAX_SCENE; nCntScene++)
		{

			if (m_apScene[nCntScene] != NULL)
			{
				if (m_apScene[nCntScene]->m_type == objType)
				{
					// �`�揈��
					m_apScene[nCntScene]->Draw();
				}
			}

		}
	}
}

//====================================
//�������̔j��
//====================================
void CScene::Release(void)
{
	int nNum = m_nNumIndex;
	if (m_apScene[nNum] != NULL)
	{
		delete m_apScene[nNum];
		m_apScene[nNum] = NULL;
		m_nNumAll--;
	}
}
