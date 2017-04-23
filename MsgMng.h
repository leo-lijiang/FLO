#ifndef MSGMNG_H
#define MSGMNG_H
#ifdef __cplusplus
extern "C" {
#endif
#include "cJSON.h"
#include <string.h>
#include <stdlib.h>

#include "Def.h"

//单张牌信息结构体
typedef struct _CardInfo{
    int color;
    int value;
}CardInfo;


/*******************以下是请求消息结构体********************/
//登录请求消息结构体
typedef struct _MsgLoginReq{
    char username[64];
    char pwd[64];
}MsgLoginReq;

//注册请求消息结构体
typedef struct _MsgLoginReq MsgRegReq;

//创建房间请求消息结构体
#if MYDEBUG
typedef struct _MsgCreateRoomReq{
    char username[64];
    char clientIP[32];
}MsgCreateRoomReq;
#else
typedef struct _MsgCreateRoomReq{
    char username[64];
    int clientPort;
}MsgCreateRoomReq;
#endif

//加入房间请求消息结构体
typedef struct _MsgCreateRoomReq MsgJoinRoomReq;

//准备消息结构体
typedef struct _MsgPrepare{
    char username[64];
    int roomNum;
}MsgPrepare;

//取消准备消息结构体
typedef struct _MsgPrepare MsgCanclePrepare;

//抢地主消息结构体
typedef struct _MsgRob{
    char username[64];
    int roomNum;
    int robRet;//是否抢地主标示 1代表抢,0代表不抢
}MsgRob;
//不要牌消息结构体
typedef struct _MsgPrepare MsgPass;


//出牌消息
typedef struct _MsgOutCard{
    char username[64];
    int roomNum;
    int size;
    CardInfo cards[20];
}MsgOutCard;

//游戏结束消息
typedef struct _MsgPrepare MsgGameOverReq;
//离开房间消息
typedef struct _MsgPrepare MsgLeaveRoom;

/****************以下是应答消息结构体************************/
//登录应答消息结构体
typedef struct _MsgLoginRes{
    int isSuccess;
    char errInfo[128];
}MsgLoginRes;

//注册应答消息结构体
typedef struct _MsgLoginRes MsgRegRes;
//创建房间应答消息结构体
typedef struct _MsgCreateRoomRes {
    int isSuccess;
    int roomNum;
    char errInfo[128];
}MsgCreateRoomRes;

//加入房间应答消息结构体
typedef struct  _MsgJoinRoomRes{
    int isSuccess;
    int roomNum;
    int number;
    int playersStatus[2];
    char playersName[2][64];
    char errInfo[128];
}MsgJoinRoomRes;

//其他玩家状态改变消息结构体
typedef struct _MsgOtherStatusChanged{
    char username[64];
    int seat;
    int status;
}MsgOtherStatusChanged;
//发牌消息结构体
typedef struct _MsgDealCards{
    int ownerPos;
    CardInfo handCards[17];
    CardInfo underCards[3];
}MsgDealCards;

//其他人抢地主消息结构体
typedef struct _MsgOtherRob{
    int seat;
    int robRet;
    int nextRober;
}MsgOtherRob;

//抢地主结果消息结构体
typedef struct _MsgRobResult{
    int landOwnerPos;
}MsgRobResult;

//其他人不要牌消息结构体
typedef struct _MsgOtherPass{
    int pos;
}MsgOtherPass;
//其他人出牌消息
typedef struct _MsgOtherOutCard{
    int pos;
    int size;
    CardInfo cards[20];
}MsgOtherOutCard;

//游戏结束消息
typedef struct _MsgGameOver{
    //胜利玩家身份
    int winPos;
}MsgGameOver;
//其他人离开房间消息
typedef struct _MsgOtherLeaveRoom{
    int pos;
    int isPlaying;//1代表游戏进行时离开 0代表游戏没开始离开
}MsgOtherLeaveRoom;

int MsgEncode(const void *pStruct, int msgType, char **outData);

int MsgDecode(const char *inData, void **pStruct, int *msgType);

int MsgFree(void *data);



#ifdef __cplusplus
}
#endif
#endif // MSGMNG_H
