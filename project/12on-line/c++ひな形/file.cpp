//=============================================================================
//
// ファイルクラス [file.cpp]
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
// マクロ定義
//*****************************************************************************
#define FILE_NAME "data/Texts/StageData/stage.txt"      // 使用するファイルの名前
#define READ_BUFFER (128)                               // 読み込み用バッファ
#define WALL_SIZE {60.0f,500.0f,0.0f}                   // 壁の大きさ
#define FLOOR_SIZE {120.0f,0.0f,120.0f}                 // 床の大きさ
#define COLLISION_SIZE {1200.0f,500.0f,100.0f}            // 当たり判定の大きさ

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
    CModel::OBJTYPE type;
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
                            sscanf(aRead, "%s %f %f %f", &aDie, &rot.x, &rot.y, &rot.z);//位置を格納
                        }
                        if (strcmp(aHead, "TYPE") == 0)
                        {
                            sscanf(aRead, "%s %d", &aDie, &type);//位置を格納
                        }
                        if (strcmp(aHead, "OBJ_TYPE") == 0)
                        {
                            sscanf(aRead, "%s %d", &aDie, &ntype);//オブジェクトのタイプをを格納
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
// [SetObject] オブジェクトの配置
// Author : AYANO KUDO
// 引数
//pos : 位置
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

