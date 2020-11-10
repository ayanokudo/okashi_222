//=============================================================================
//
// ファイルクラス [file.cpp]
// Author:KUDO AYANO
//
//=============================================================================
#include "file.h"
#include "object.h"
#include "enemy.h"
#include "wall.h"
#include "floor.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define FILE_NAME "data/Txt/stage.txt"      // 使用するファイルの名前
#define READ_BUFFER (128)                   // 読み込み用バッファ

//=============================================================================
// [CFile] コンストラクタ
//=============================================================================
CFile::CFile()
{

}

//=============================================================================
// [~CFile] デストラクタ
//=============================================================================
CFile::~CFile()
{

}

//=============================================================================
// [Read] ファイルの読み込み
//=============================================================================
void CFile::Read(void)
{
    // 変数宣言
    char aRead[READ_BUFFER];    // 文字列読み込み用
    char aHead[READ_BUFFER];    // 比較用
    char aDie[READ_BUFFER];             // 不必要な文字を読み込む
    FILE *pFile = fopen(FILE_NAME, "r");
    D3DXVECTOR3 pos;            // 読み込んだ位置
    D3DXVECTOR3 rot;            // 読み込んだ角度
    CModel::OBJTYPE type;       // オブジェクトの種類
    int ntype;                 // オブジェクトごとのタイプ

    if (pFile)
    {// ファイル読み込み
        while (strcmp(aHead, "SCRIPT"))
        {
            fgets(aRead, sizeof(aRead), pFile);
            sscanf(aRead, "%s", &aHead);
        }
        // SCREPTを読み込んだ時
        if (strcmp(aHead, "SCRIPT") == 0)
        {
            while (strcmp(aHead, "END_SCRIPT") != 0)//END_SCRIPTを読み込むまでループ
            {
                // 文字列の読み込み
                fgets(aRead, sizeof(aRead), pFile);//位置行単位で文字列を読み込み
                sscanf(aRead, "%s", &aHead);//読み込んだテキストを比較用変数に代入

                if (strcmp(aHead, "OBJ_SET") == 0)// OBJSETを読み込んだ時
                {
                    while (strcmp(aHead, "END_OBJ_SET") != 0)// END_OBJSETを読み込むまでループ
                    {
                        // 文字列の読み込み
                        fgets(aRead, sizeof(aRead), pFile);//位置行単位で文字列を読み込み
                        sscanf(aRead, "%s", &aHead);//読み込んだテキストを比較用変数に代入
                        // 位置の設定
                        if (strcmp(aHead, "POS") == 0)
                        {
                            sscanf(aRead, "%s %f %f %f", &aDie, &pos.x, &pos.y, &pos.z);//位置を格納
                        }
                        // 角度の設定
                        if (strcmp(aHead, "ROT") == 0)
                        {
                            sscanf(aRead, "%s %f %f %f", &aDie, &rot.x, &rot.y, &rot.z);//角度を格納
                        }
                        if (strcmp(aHead, "TYPE") == 0)
                        {
                            sscanf(aRead, "%s %d", &aDie, &type);//種類を格納
                        }
                        if (strcmp(aHead, "OBJ_TYPE") == 0)
                        {
                            sscanf(aRead, "%s %d", &aDie, &ntype);//オブジェクトのタイプをを格納
                        }
                    }
                    CObject::SetObject(pos, D3DXToRadian(rot),type,ntype);
                }
            }
        }
    }
    fclose(pFile);
}

//=============================================================================
// [Writing] ファイルの書き込み
//=============================================================================
void CFile::Writing(void)
{
    // 変数宣言
    FILE *pFile = fopen(FILE_NAME, "w");

    if (pFile)
    {// ファイル書き込み

        fprintf(pFile, "SCRIPT          // スクリプト開始 \n\n");       // スクリプト開始

        CScene* pScene = CScene::GetTop(CScene::OBJTYPE_PLAYER);
        // オブジェクトの数分データを書きだす
        while (pScene != NULL)
        {
            if (pScene != CObject::GetPlayer())
            {// カーソルに使われていないオブジェクトを書き込み
                if (pScene)
                {// オブジェクトがあった場合
                    D3DXVECTOR3 pos = ((CModel*)pScene)->GetPos();
                    D3DXVECTOR3 rot = ((CModel*)pScene)->GetRot();

                    fprintf(pFile, "\tOBJ_SET\n");
                    fprintf(pFile, "\t\t POS %.1f %.1f %.1f \n", pos.x, pos.y, pos.z);
                    fprintf(pFile, "\t\t ROT %.1f %.1f %.1f \n", rot.x, rot.y, rot.z);
                    fprintf(pFile, "\t\t TYPE %d \n", pScene->GetType());
                    fprintf(pFile, "\tEND_OBJ_SET\n");
                    fprintf(pFile, "\n");
                }
            }
            pScene = pScene->GetNext();
        }
        // 敵オブジェクト書き込み
        ObjctWriting(pFile, CScene::OBJTYPE_ENEMY);

        // 床オブジェクト書き込み
        ObjctWriting(pFile, CScene::OBJTYPE_FLOOR);

        // 壁オブジェクト書き込み
        ObjctWriting(pFile, CScene::OBJTYPE_WALL);

        // 家具オブジェクト書き込み
        ObjctWriting(pFile, CScene::OBJTYPE_FURNITURE);

        fprintf(pFile, "\n");
        fprintf(pFile, "END_SCRIPT      // スクリプト終了");   // スクリプト終了
        fclose(pFile);                  // ファイル書き込み終了
    }
}

//=============================================================================
// [Writing] ファイルの書き込み
//=============================================================================
void CFile::ObjctWriting(FILE *pFile,CScene::OBJTYPE type)
{
    CScene* pScene = CScene::GetTop(type);

    // オブジェクトの数分データを書きだす
    while (pScene != NULL)
    {
        if (pScene)
        {// オブジェクトがあった場合
            D3DXVECTOR3 pos = ((CModel*)pScene)->GetPos();
            D3DXVECTOR3 rot = D3DXToDegree(((CModel*)pScene)->GetRot());

            fprintf(pFile, "\tOBJ_SET\n");
            fprintf(pFile, "\t\t POS %.1f %.1f %.1f \n", pos.x, pos.y, pos.z);
            fprintf(pFile, "\t\t ROT %.1f %.1f %.1f \n", rot.x, rot.y, rot.z);
            fprintf(pFile, "\t\t TYPE %d \n", pScene->GetType());
            fprintf(pFile, "\t\t OBJ_TYPE %d \n", GetObjectType(pScene));
            fprintf(pFile, "\tEND_OBJ_SET\n");
            fprintf(pFile, "\n");
        }
        pScene = pScene->GetNext();
    }
}

//=============================================================================
// [GetObjectType] オブジェクトごとのタイプを取得
//=============================================================================
int CFile::GetObjectType(CScene* pScene)
{
    int nType=0;
    switch (pScene->GetType())
    {
    case CScene::OBJTYPE_ENEMY:
        nType =((CEnemy*)pScene)->CEnemy::GetType();
        break;
    }
    return nType;
}

