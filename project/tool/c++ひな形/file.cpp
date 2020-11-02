//=============================================================================
//
// �t�@�C���N���X [file.cpp]
// Author:KUDO AYANO
//
//=============================================================================
#include "file.h"
#include "object.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define FILE_NAME "data/Txt/stage.txt"      // �g�p����t�@�C���̖��O
#define READ_BUFFER (128)                   // �ǂݍ��ݗp�o�b�t�@

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
    D3DXVECTOR3 pos;                // �ǂݍ��񂾈ʒu
    CModel::OBJTYPE type;

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
                        if (strcmp(aHead, "TYPE") == 0)
                        {
                            sscanf(aRead, "%s %d", &aDie, &type);//�ʒu���i�[
                        }
                    }
                    CObject::SetObject(pos, type);
                }
            }
        }
    }
    fclose(pFile);
}

//=============================================================================
// [Writing] �t�@�C���̏�������
//=============================================================================
void CFile::Writing(void)
{
    // �ϐ��錾
    FILE *pFile = fopen(FILE_NAME, "w");

    if (pFile)
    {// �t�@�C����������

        fprintf(pFile, "SCRIPT          // �X�N���v�g�J�n \n\n");       // �X�N���v�g�J�n

        CScene* pScene = CScene::GetTop(CScene::OBJTYPE_PLAYER);
        // �I�u�W�F�N�g�̐����f�[�^����������
        while (pScene != NULL)
        {

            if (pScene != CObject::GetPlayer())
            {// �J�[�\���Ɏg���Ă���I�u�W�F�N�g����������
                if (pScene)
                {// �I�u�W�F�N�g���������ꍇ
                    D3DXVECTOR3 pos = ((CModel*)pScene)->GetPos();
                    fprintf(pFile, "\tOBJ_SET\n");
                    fprintf(pFile, "\t\t POS %.1f %.1f %.1f \n", pos.x, pos.y, pos.z);
                    fprintf(pFile, "\t\t TYPE %d \n", pScene->GetType());
                    fprintf(pFile, "\tEND_OBJ_SET\n");
                    fprintf(pFile, "\n");
                }
            }
            pScene = pScene->GetNext();
        }
        pScene = CScene::GetTop(CScene::OBJTYPE_ENEMY);

        // �I�u�W�F�N�g�̐����f�[�^����������
        while (pScene != NULL)
        {
            if (pScene)
            {// �I�u�W�F�N�g���������ꍇ
                D3DXVECTOR3 pos = ((CModel*)pScene)->GetPos();
                fprintf(pFile, "\tOBJ_SET\n");
                fprintf(pFile, "\t\t POS %.1f %.1f %.1f \n", pos.x, pos.y, pos.z);
                fprintf(pFile, "\t\t TYPE %d \n", pScene->GetType());
                fprintf(pFile, "\tEND_OBJ_SET\n");
                fprintf(pFile, "\n");
            }
            pScene = pScene->GetNext();
        }

        pScene = CScene::GetTop(CScene::OBJTYPE_FLOOR);

        // �I�u�W�F�N�g�̐����f�[�^����������
        while (pScene != NULL)
        {
            if (pScene)
            {// �I�u�W�F�N�g���������ꍇ
                D3DXVECTOR3 pos = ((CModel*)pScene)->GetPos();
                fprintf(pFile, "\tOBJ_SET\n");
                fprintf(pFile, "\t\t POS %.1f %.1f %.1f \n", pos.x, pos.y, pos.z);
                fprintf(pFile, "\t\t TYPE %d \n", pScene->GetType());
                fprintf(pFile, "\tEND_OBJ_SET\n");
                fprintf(pFile, "\n");
            }
            pScene = pScene->GetNext();
        }

        pScene = CScene::GetTop(CScene::OBJTYPE_WALL);

        // �I�u�W�F�N�g�̐����f�[�^����������
        while (pScene != NULL)
        {
            if (pScene)
            {// �I�u�W�F�N�g���������ꍇ
                D3DXVECTOR3 pos = ((CModel*)pScene)->GetPos();
                fprintf(pFile, "\tOBJ_SET\n");
                fprintf(pFile, "\t\t POS %.1f %.1f %.1f \n", pos.x, pos.y, pos.z);
                fprintf(pFile, "\t\t TYPE %d \n", pScene->GetType());
                fprintf(pFile, "\tEND_OBJ_SET\n");
                fprintf(pFile, "\n");
            }
            pScene = pScene->GetNext();
        }

        fprintf(pFile, "\n");
        fprintf(pFile, "END_SCRIPT      // �X�N���v�g�I��");   // �X�N���v�g�I��
        fclose(pFile);                  // �t�@�C���������ݏI��
    }
}

void CFile::ObjctWriting(CScene::OBJTYPE tye)
{
}
