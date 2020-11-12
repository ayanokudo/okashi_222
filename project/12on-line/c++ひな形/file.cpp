//=============================================================================
//
// �t�@�C���N���X [file.cpp]
// Author:KUDO AYANO
//
//=============================================================================
#include "file.h"
#include "player.h"
#include "enemy.h"
#include "wall.h"
#include "floor.h"
#include "furniture.h"
#include "collision.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define FILE_NAME "data/Texts/StageData/stage.txt"      // �g�p����t�@�C���̖��O
#define READ_BUFFER (128)                               // �ǂݍ��ݗp�o�b�t�@
#define WALL_SIZE {60.0f,500.0f,0.0f}                   // �ǂ̑傫��
#define FLOOR_SIZE {120.0f,0.0f,120.0f}                 // ���̑傫��
#define COLLISION_SIZE {1200.0f,500.0f,100.0f}            // �����蔻��̑傫��

//=============================================================================
// [CFile] �R���X�g���N�^
//=============================================================================
CFile::CFile()
{

}

//=============================================================================
// [~CFile] �f�X�g���N�^
//=============================================================================
CFile::~CFile()
{

}

//=============================================================================
// [Read] �t�@�C���̓ǂݍ���
//=============================================================================
void CFile::Read(void)
{
    // �ϐ��錾
    char aRead[READ_BUFFER];    // ������ǂݍ��ݗp
    char aHead[READ_BUFFER];    // ��r�p
    char aDie[READ_BUFFER];             // �s�K�v�ȕ�����ǂݍ���
    FILE *pFile = fopen(FILE_NAME, "r");
    D3DXVECTOR3 pos;            // �ǂݍ��񂾈ʒu
    D3DXVECTOR3 rot;            // �ǂݍ��񂾊p�x
    CModel::OBJTYPE type;
    int ntype;                 // �I�u�W�F�N�g���Ƃ̃^�C�v

    if (pFile)
    {// �t�@�C���ǂݍ���
        while (strcmp(aHead, "SCRIPT"))
        {
            fgets(aRead, sizeof(aRead), pFile);
            sscanf(aRead, "%s", &aHead);
        }
        // SCREPT��ǂݍ��񂾎�
        if (strcmp(aHead, "SCRIPT") == 0)
        {
            while (strcmp(aHead, "END_SCRIPT") != 0)//END_SCRIPT��ǂݍ��ނ܂Ń��[�v
            {
                // ������̓ǂݍ���
                fgets(aRead, sizeof(aRead), pFile);//�ʒu�s�P�ʂŕ������ǂݍ���
                sscanf(aRead, "%s", &aHead);//�ǂݍ��񂾃e�L�X�g���r�p�ϐ��ɑ��

                if (strcmp(aHead, "OBJ_SET") == 0)// OBJSET��ǂݍ��񂾎�
                {
                    while (strcmp(aHead, "END_OBJ_SET") != 0)// END_OBJSET��ǂݍ��ނ܂Ń��[�v
                    {
                        // ������̓ǂݍ���
                        fgets(aRead, sizeof(aRead), pFile);//�ʒu�s�P�ʂŕ������ǂݍ���
                        sscanf(aRead, "%s", &aHead);//�ǂݍ��񂾃e�L�X�g���r�p�ϐ��ɑ��
                                                    // �ʒu�̐ݒ�
                        if (strcmp(aHead, "POS") == 0)
                        {
                            sscanf(aRead, "%s %f %f %f", &aDie, &pos.x, &pos.y, &pos.z);//�ʒu���i�[
                        }
                        // �p�x�̐ݒ�
                        if (strcmp(aHead, "ROT") == 0)
                        {
                            sscanf(aRead, "%s %f %f %f", &aDie, &rot.x, &rot.y, &rot.z);//�ʒu���i�[
                        }
                        if (strcmp(aHead, "TYPE") == 0)
                        {
                            sscanf(aRead, "%s %d", &aDie, &type);//�ʒu���i�[
                        }
                        if (strcmp(aHead, "OBJ_TYPE") == 0)
                        {
                            sscanf(aRead, "%s %d", &aDie, &ntype);//�I�u�W�F�N�g�̃^�C�v�����i�[
                        }
                    }
                    SetObject(pos, D3DXToRadian(rot), type, ntype);
                }
            }
            fclose(pFile);
        }
    }
}

//=============================================================================
// [SetObject] �I�u�W�F�N�g�̔z�u
// Author : AYANO KUDO
// ����
//pos : �ʒu
//=============================================================================
void CFile::SetObject(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CModel::OBJTYPE type, int ntype)
{
    switch (type)
    {
    case CModel::OBJTYPE_ENEMY:
        CEnemy::Create(pos, (CEnemy::ENEMY)ntype);
        break;

    case CModel::OBJTYPE_WALL:
         CWall::Create(pos,rot, WALL_SIZE, (CWall::WALL)ntype);
        break;
        
    case CModel::OBJTYPE_FLOOR:
        CFloor::Create(pos,rot, FLOOR_SIZE, (CFloor::FLOOR)ntype);
        break;

	case CModel::OBJTYPE_FURNITURE:
		CFurniture::Create(pos, rot, FLOOR_SIZE, (CFurniture::FURNITURE)ntype);
		break;

    case CModel::OBJTYPE_COLLISION:
        CCollision::CreateBox(pos, COLLISION_SIZE);
        break;
    }
}

