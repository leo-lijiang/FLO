#include "MsgMng.h"



//编码登录请求消息
int EncodeLoginReq(const void *pStruct, char **out)
{
    MsgLoginReq *msgLoginReq =  (MsgLoginReq *)pStruct;
    cJSON *type = cJSON_CreateNumber(Msg_Type_LoginReq);
    cJSON *msg = cJSON_CreateObject();
    cJSON_AddStringToObject(msg, "username", msgLoginReq->username);
    cJSON_AddStringToObject(msg, "password", msgLoginReq->pwd);
    cJSON *root = cJSON_CreateObject();
    cJSON_AddItemToObject(root, "type", type);
    cJSON_AddItemToObject(root, "msg", msg);

    *out = cJSON_Print(root);
    cJSON_Delete(root);

    return 0;
}
//解码登录请求消息
int DecodeLoginReq(const char *in, MsgLoginReq *msgLoginReq)
{

   // MsgLoginReq *msgLoginReq =  (MsgLoginReq *)pStruct;
    cJSON *root = cJSON_Parse(in);
    cJSON *jsMsg = cJSON_GetObjectItem(root, "msg");
    cJSON *jsUserName = cJSON_GetObjectItem(jsMsg, "username");
    cJSON *jsPwd = cJSON_GetObjectItem(jsMsg, "password");
    strcpy(msgLoginReq->username, jsUserName->valuestring);
    strcpy(msgLoginReq->pwd, jsPwd->valuestring);

    cJSON_Delete(root);

    return 0;
}
//编码注册请求消息
int EncodeRegReq(const void *pStruct, char **out)
{
    MsgRegReq *msgRegReq =  (MsgRegReq *)pStruct;
    cJSON *type = cJSON_CreateNumber(Msg_Type_RegReq);
    cJSON *msg = cJSON_CreateObject();
    cJSON_AddStringToObject(msg, "username", msgRegReq->username);
    cJSON_AddStringToObject(msg, "password", msgRegReq->pwd);
    cJSON *root = cJSON_CreateObject();
    cJSON_AddItemToObject(root, "type", type);
    cJSON_AddItemToObject(root, "msg", msg);

    *out = cJSON_Print(root);
    cJSON_Delete(root);

    return 0;
}
//解码注册请求消息
int DecodeRegReq(const char *in, MsgRegReq *msgRegReq)
{
    cJSON *root = cJSON_Parse(in);
    cJSON *jsMsg = cJSON_GetObjectItem(root, "msg");
    cJSON *jsUserName = cJSON_GetObjectItem(jsMsg, "username");
    cJSON *jsPwd = cJSON_GetObjectItem(jsMsg, "password");
    strcpy(msgRegReq->username, jsUserName->valuestring);
    strcpy(msgRegReq->pwd, jsPwd->valuestring);

    cJSON_Delete(root);

    return 0;
}

//编码登录应答消息
int EncodeLoginRes(const void *pStruct, char **out)
{
    MsgLoginRes *msgLoginRes =  (MsgLoginRes *)pStruct;
    cJSON *type = cJSON_CreateNumber(Msg_Type_LoginRes);

    cJSON *msg = cJSON_CreateObject();
    cJSON_AddNumberToObject(msg, "result", msgLoginRes->isSuccess);
    cJSON_AddStringToObject(msg, "errInfo", msgLoginRes->errInfo);

    cJSON *root = cJSON_CreateObject();
    cJSON_AddItemToObject(root, "type", type);
    cJSON_AddItemToObject(root, "msg", msg);

    *out = cJSON_Print(root);
    cJSON_Delete(root);

    return 0;
}

//解码登录应答消息
int DecodeLoginRes(const char *in, MsgLoginRes *msgLoginRes)
{
    cJSON *root = cJSON_Parse(in);
    cJSON *jsMsg = cJSON_GetObjectItem(root, "msg");
    cJSON *jsResult = cJSON_GetObjectItem(jsMsg, "result");
    cJSON *jsErrInfo = cJSON_GetObjectItem(jsMsg, "errInfo");
    msgLoginRes->isSuccess = jsResult->valueint;
    strcpy(msgLoginRes->errInfo, jsErrInfo->valuestring);

    cJSON_Delete(root);

    return 0;
}

//编码注册应答消息
int EncodeRegRes(const void *pStruct, char **out)
{
    MsgRegRes *msgRegRes =  (MsgRegRes *)pStruct;
    cJSON *type = cJSON_CreateNumber(Msg_Type_RegRes);

    cJSON *msg = cJSON_CreateObject();
    cJSON_AddNumberToObject(msg, "result", msgRegRes->isSuccess);
    cJSON_AddStringToObject(msg, "errInfo", msgRegRes->errInfo);

    cJSON *root = cJSON_CreateObject();
    cJSON_AddItemToObject(root, "type", type);
    cJSON_AddItemToObject(root, "msg", msg);

    *out = cJSON_Print(root);
    cJSON_Delete(root);

    return 0;
}
//解码注册应答消息
int DecodeRegRes(const char *in, MsgRegRes *msgRegRes)
{
    cJSON *root = cJSON_Parse(in);
    cJSON *jsMsg = cJSON_GetObjectItem(root, "msg");
    cJSON *jsResult = cJSON_GetObjectItem(jsMsg, "result");
    cJSON *jsErrInfo = cJSON_GetObjectItem(jsMsg, "errInfo");
    msgRegRes->isSuccess = jsResult->valueint;
    strcpy(msgRegRes->errInfo, jsErrInfo->valuestring);

    cJSON_Delete(root);

    return 0;
}

//编码创建房间请求消息
int EncodeCreateRoomReq(const void *pStruct, char **out)
{
    MsgCreateRoomReq *msgCreateRoomReq =  (MsgCreateRoomReq *)pStruct;
    cJSON *type = cJSON_CreateNumber(Msg_Type_CreateRoomReq);
    cJSON *msg = cJSON_CreateObject();
    cJSON_AddStringToObject(msg, "username", msgCreateRoomReq->username);
#if MYDEBUG
    cJSON_AddStringToObject(msg, "clientIP", msgCreateRoomReq->clientIP);
#else
    cJSON_AddNumberToObject(msg, "clientPort", msgCreateRoomReq->clientPort);
#endif
    cJSON *root = cJSON_CreateObject();
    cJSON_AddItemToObject(root, "type", type);
    cJSON_AddItemToObject(root, "msg", msg);

    *out = cJSON_Print(root);
    cJSON_Delete(root);

    return 0;
}
//解码创建房间请求消息
int DecodeCreateRoomReq(const char *in, MsgCreateRoomReq *msgCreateRoomReq)
{

   // MsgLoginReq *msgLoginReq =  (MsgLoginReq *)pStruct;
    cJSON *root = cJSON_Parse(in);
    cJSON *jsMsg = cJSON_GetObjectItem(root, "msg");
    cJSON *jsUserName = cJSON_GetObjectItem(jsMsg, "username");
    strcpy(msgCreateRoomReq->username, jsUserName->valuestring);
#if MYDEBUG
    cJSON *jsClientIP = cJSON_GetObjectItem(jsMsg, "clientIP");
    strcpy(msgCreateRoomReq->clientIP, jsClientIP->valuestring);
#else
    cJSON *jsClientPort = cJSON_GetObjectItem(jsMsg, "clientPort");
    msgCreateRoomReq->clientPort = jsClientPort->valueint;
#endif
    cJSON_Delete(root);

    return 0;
}

//编码创建房间应答消息
int EncodeCreateRoomRes(const void *pStruct, char **out)
{
    MsgCreateRoomRes *msgCreateRoomRes =  (MsgCreateRoomRes *)pStruct;
    cJSON *type = cJSON_CreateNumber(Msg_Type_CreateRoomRes);

    cJSON *msg = cJSON_CreateObject();
    cJSON_AddNumberToObject(msg, "result", msgCreateRoomRes->isSuccess);
    cJSON_AddNumberToObject(msg, "roomNum",msgCreateRoomRes->roomNum);
    cJSON_AddStringToObject(msg, "errInfo", msgCreateRoomRes->errInfo);

    cJSON *root = cJSON_CreateObject();
    cJSON_AddItemToObject(root, "type", type);
    cJSON_AddItemToObject(root, "msg", msg);

    *out = cJSON_Print(root);
    cJSON_Delete(root);

    return 0;
}
//解码创建房间应答消息
int DecodeCreateRoomRes(const char *in, MsgCreateRoomRes *msgCreateRoomRes)
{
    cJSON *root = cJSON_Parse(in);
    cJSON *jsMsg = cJSON_GetObjectItem(root, "msg");
    cJSON *jsResult = cJSON_GetObjectItem(jsMsg, "result");
    cJSON *jsRoomNum = cJSON_GetObjectItem(jsMsg, "roomNum");
    cJSON *jsErrInfo = cJSON_GetObjectItem(jsMsg, "errInfo");
    msgCreateRoomRes->isSuccess = jsResult->valueint;
    msgCreateRoomRes->roomNum = jsRoomNum->valueint;
    strcpy(msgCreateRoomRes->errInfo, jsErrInfo->valuestring);

    cJSON_Delete(root);

    return 0;
}

//编码加入房间请求消息
int EncodeJoinRoomReq(const void *pStruct, char **out)
{
    MsgJoinRoomReq *msgJoinRoomReq =  (MsgJoinRoomReq *)pStruct;
    cJSON *type = cJSON_CreateNumber(Msg_Type_JoinRoomReq);
    cJSON *msg = cJSON_CreateObject();
    cJSON_AddStringToObject(msg, "username", msgJoinRoomReq->username);
#if MYDEBUG
    cJSON_AddStringToObject(msg, "clientIP", msgJoinRoomReq->clientIP);
#else
    cJSON_AddNumberToObject(msg, "clientPort", msgJoinRoomReq->clientPort);
#endif
    cJSON *root = cJSON_CreateObject();
    cJSON_AddItemToObject(root, "type", type);
    cJSON_AddItemToObject(root, "msg", msg);

    *out = cJSON_Print(root);
    cJSON_Delete(root);

    return 0;
}
//解码加入房间请求消息
int DecodeJoinRoomReq(const char *in, MsgJoinRoomReq *msgJoinRoomReq)
{

   // MsgLoginReq *msgLoginReq =  (MsgLoginReq *)pStruct;
    cJSON *root = cJSON_Parse(in);
    cJSON *jsMsg = cJSON_GetObjectItem(root, "msg");
    cJSON *jsUserName = cJSON_GetObjectItem(jsMsg, "username");
    strcpy(msgJoinRoomReq->username, jsUserName->valuestring);
#if MYDEBUG
    cJSON *jsClientIP = cJSON_GetObjectItem(jsMsg, "clientIP");
    strcpy(msgJoinRoomReq->clientIP, jsClientIP->valuestring);
#else
    cJSON *jsClientPort = cJSON_GetObjectItem(jsMsg, "clientPort");
    msgJoinRoomReq->clientPort = jsClientPort->valueint;
#endif

    cJSON_Delete(root);

    return 0;
}


//编码加入房间应答消息
int EncodeJoinRoomRes(const void *pStruct, char **out)
{
    MsgJoinRoomRes *msgJoinRoomRes =  (MsgJoinRoomRes *)pStruct;
    cJSON *type = cJSON_CreateNumber(Msg_Type_JoinRoomRes);

    cJSON *msg = cJSON_CreateObject();
    cJSON_AddNumberToObject(msg, "result", msgJoinRoomRes->isSuccess);
    cJSON *playersStatus = cJSON_CreateIntArray(msgJoinRoomRes->playersStatus, 2);
    cJSON_AddItemToObject(msg, "playersStatus", playersStatus);
    cJSON *playersName = cJSON_CreateArray();
    cJSON *playerName_1 = cJSON_CreateString(msgJoinRoomRes->playersName[0]);
    cJSON *playerName_2 = cJSON_CreateString(msgJoinRoomRes->playersName[1]);
    cJSON_AddItemToArray(playersName, playerName_1);
    cJSON_AddItemToArray(playersName, playerName_2);

    cJSON_AddItemToObject(msg, "playersName", playersName);
    cJSON_AddNumberToObject(msg, "number", msgJoinRoomRes->number);
    cJSON_AddNumberToObject(msg, "roomNum",msgJoinRoomRes->roomNum);
    cJSON_AddStringToObject(msg, "errInfo", msgJoinRoomRes->errInfo);

    cJSON *root = cJSON_CreateObject();
    cJSON_AddItemToObject(root, "type", type);
    cJSON_AddItemToObject(root, "msg", msg);

    *out = cJSON_Print(root);
    cJSON_Delete(root);

    return 0;
}
//解码加入房间应答消息
int DecodeJoinRoomRes(const char *in, MsgJoinRoomRes *msgJoinRoomRes)
{
    cJSON *root = cJSON_Parse(in);
    cJSON *jsMsg = cJSON_GetObjectItem(root, "msg");

    cJSON *jsResult = cJSON_GetObjectItem(jsMsg, "result");
    cJSON *jsPlayersStatusArr = cJSON_GetObjectItem(jsMsg, "playersStatus");
    cJSON *jsPlayersNameArr = cJSON_GetObjectItem(jsMsg, "playersName");
    cJSON *jsNumber = cJSON_GetObjectItem(jsMsg, "number");
    cJSON *jsRoomNum = cJSON_GetObjectItem(jsMsg, "roomNum");
    cJSON *jsErrInfo = cJSON_GetObjectItem(jsMsg, "errInfo");

    int i;
    int size = cJSON_GetArraySize(jsPlayersStatusArr);
    for(i = 0; i < size; i++){
        cJSON *temp = cJSON_GetArrayItem(jsPlayersStatusArr, i);
        msgJoinRoomRes->playersStatus[i] = temp->valueint;
    }
    size = cJSON_GetArraySize(jsPlayersNameArr);
    for(i = 0; i < size; i++){
        cJSON *temp = cJSON_GetArrayItem(jsPlayersNameArr, i);
        strcpy(msgJoinRoomRes->playersName[i], temp->valuestring);
    }

    msgJoinRoomRes->isSuccess = jsResult->valueint;
    msgJoinRoomRes->roomNum = jsRoomNum->valueint;
    msgJoinRoomRes->number = jsNumber->valueint;
    strcpy(msgJoinRoomRes->errInfo, jsErrInfo->valuestring);

    cJSON_Delete(root);

    return 0;
}
//编码准备消息
int EncodePrepare(const void *pStruct, char **out)
{
    MsgPrepare *msgPrepare =  (MsgPrepare *)pStruct;
    cJSON *type = cJSON_CreateNumber(Msg_Type_Prepare);
    cJSON *msg = cJSON_CreateObject();
    cJSON_AddStringToObject(msg, "username", msgPrepare->username);
    cJSON_AddNumberToObject(msg, "roomNum", msgPrepare->roomNum);
    cJSON *root = cJSON_CreateObject();
    cJSON_AddItemToObject(root, "type", type);
    cJSON_AddItemToObject(root, "msg", msg);

    *out = cJSON_Print(root);
    cJSON_Delete(root);

    return 0;
}
//解码准备消息
int DecodePrepare(const char *in, MsgPrepare *msgPrepare)
{

   // MsgLoginReq *msgLoginReq =  (MsgLoginReq *)pStruct;
    cJSON *root = cJSON_Parse(in);
    cJSON *jsMsg = cJSON_GetObjectItem(root, "msg");
    cJSON *jsUserName = cJSON_GetObjectItem(jsMsg, "username");
    cJSON *jsRoomNum = cJSON_GetObjectItem(jsMsg, "roomNum");
    strcpy(msgPrepare->username, jsUserName->valuestring);
    msgPrepare->roomNum = jsRoomNum->valueint;

    cJSON_Delete(root);

    return 0;
}
//编码其他玩家状态改变消息
int EncodeOtherStatusChanged(const void *pStruct, char **out)
{
    MsgOtherStatusChanged *msgOtherStatusChanged =  (MsgOtherStatusChanged *)pStruct;
    cJSON *type = cJSON_CreateNumber(Msg_Type_OtherStatusChanged);
    cJSON *msg = cJSON_CreateObject();
    cJSON_AddStringToObject(msg, "username", msgOtherStatusChanged->username);
    cJSON_AddNumberToObject(msg, "seat", msgOtherStatusChanged->seat);
    cJSON_AddNumberToObject(msg, "status", msgOtherStatusChanged->status);
    cJSON *root = cJSON_CreateObject();
    cJSON_AddItemToObject(root, "type", type);
    cJSON_AddItemToObject(root, "msg", msg);

    *out = cJSON_Print(root);
    cJSON_Delete(root);

    return 0;
}

//解码其他玩家状态改变消息
int DecodeOtherStatusChanged(const char *in, MsgOtherStatusChanged *msgOtherStatusChanged)
{

   // MsgLoginReq *msgLoginReq =  (MsgLoginReq *)pStruct;
    cJSON *root = cJSON_Parse(in);
    cJSON *jsMsg = cJSON_GetObjectItem(root, "msg");
    cJSON *jsUserName = cJSON_GetObjectItem(jsMsg, "username");
    cJSON *jsSeat = cJSON_GetObjectItem(jsMsg, "seat");
    cJSON *jsStatus = cJSON_GetObjectItem(jsMsg, "status");
    strcpy(msgOtherStatusChanged->username, jsUserName->valuestring);
    msgOtherStatusChanged->seat = jsSeat->valueint;
    msgOtherStatusChanged->status = jsStatus->valueint;

    cJSON_Delete(root);

    return 0;
}

//编码取消准备消息类型
int EncodeCanclePrepare(const void *pStruct, char **out)
{
    MsgCanclePrepare *msgCanclePrepare =  (MsgCanclePrepare *)pStruct;
    cJSON *type = cJSON_CreateNumber(Msg_Type_CanclePrepare);
    cJSON *msg = cJSON_CreateObject();
    cJSON_AddStringToObject(msg, "username", msgCanclePrepare->username);
    cJSON_AddNumberToObject(msg, "roomNum", msgCanclePrepare->roomNum);
    cJSON *root = cJSON_CreateObject();
    cJSON_AddItemToObject(root, "type", type);
    cJSON_AddItemToObject(root, "msg", msg);

    *out = cJSON_Print(root);
    cJSON_Delete(root);

    return 0;

}
//解码取消准备消息
int DecodeCanclePrepare(const char *in, MsgCanclePrepare *msgCanclePrepare)
{
    // MsgLoginReq *msgLoginReq =  (MsgLoginReq *)pStruct;
     cJSON *root = cJSON_Parse(in);
     cJSON *jsMsg = cJSON_GetObjectItem(root, "msg");
     cJSON *jsUserName = cJSON_GetObjectItem(jsMsg, "username");
     cJSON *jsRoomNum = cJSON_GetObjectItem(jsMsg, "roomNum");
     strcpy(msgCanclePrepare->username, jsUserName->valuestring);
     msgCanclePrepare->roomNum = jsRoomNum->valueint;

     cJSON_Delete(root);

     return 0;
}

//编码发牌消息
int EncodeDealCards(const void *pStruct, char **out)
{
    MsgDealCards *msgDealCards = (MsgDealCards *)pStruct;

    cJSON *type = cJSON_CreateNumber(Msg_Type_DealCards);
    cJSON *msg = cJSON_CreateObject();
    cJSON *ownerPos = cJSON_CreateNumber(msgDealCards->ownerPos);
    cJSON *handCards = cJSON_CreateArray();
    int i;
    int size = sizeof(msgDealCards->handCards) / sizeof(msgDealCards->handCards[0]);
    for(i = 0; i < size; i++){
        cJSON *cardInfo = cJSON_CreateObject();
        cJSON_AddNumberToObject(cardInfo, "color", msgDealCards->handCards[i].color);
        cJSON_AddNumberToObject(cardInfo, "value", msgDealCards->handCards[i].value);
        cJSON_AddItemToArray(handCards, cardInfo);
    }
    cJSON *underCards = cJSON_CreateArray();
    size = sizeof(msgDealCards->underCards) / sizeof(msgDealCards->underCards[0]);
    for(i = 0; i < size; i++){
        cJSON *cardInfo = cJSON_CreateObject();
        cJSON_AddNumberToObject(cardInfo, "color", msgDealCards->underCards[i].color);
        cJSON_AddNumberToObject(cardInfo, "value", msgDealCards->underCards[i].value);
        cJSON_AddItemToArray(underCards, cardInfo);
    }
    cJSON_AddItemToObject(msg, "ownerPos", ownerPos);
    cJSON_AddItemToObject(msg, "handCards", handCards);
    cJSON_AddItemToObject(msg, "underCards", underCards);
    cJSON *root = cJSON_CreateObject();
    cJSON_AddItemToObject(root, "type", type);
    cJSON_AddItemToObject(root, "msg", msg);

    *out = cJSON_Print(root);
    cJSON_Delete(root);
    return 0;
}

//解码发牌消息
int DecodeDealCards(const char *in, MsgDealCards *msgDealCards)
{

    cJSON *root = cJSON_Parse(in);
    cJSON *jsMsg = cJSON_GetObjectItem(root, "msg");
    cJSON *jsOwnerPos = cJSON_GetObjectItem(jsMsg, "ownerPos");
    msgDealCards->ownerPos = jsOwnerPos->valueint;
    cJSON *jsHandCards = cJSON_GetObjectItem(jsMsg, "handCards");
    cJSON *jsUnderCards = cJSON_GetObjectItem(jsMsg, "underCards");
    int i;
    int size = cJSON_GetArraySize(jsHandCards);
    for(i = 0; i < size; i++){
        cJSON *cardInfo = cJSON_GetArrayItem(jsHandCards, i);
        cJSON *color = cJSON_GetObjectItem(cardInfo, "color");
        cJSON *value = cJSON_GetObjectItem(cardInfo, "value");
        msgDealCards->handCards[i].color = color->valueint;
        msgDealCards->handCards[i].value = value->valueint;
    }

    size = cJSON_GetArraySize(jsUnderCards);
    for(i = 0; i < size; i++){
        cJSON *cardInfo = cJSON_GetArrayItem(jsUnderCards, i);
        cJSON *color = cJSON_GetObjectItem(cardInfo, "color");
        cJSON *value = cJSON_GetObjectItem(cardInfo, "value");
        msgDealCards->underCards[i].color = color->valueint;
        msgDealCards->underCards[i].value = value->valueint;
    }

    cJSON_Delete(root);

    return 0;
}

//编码抢地主消息
int EncodeRob(const void *pStruct, char **out)
{
    MsgRob *msgRob =  (MsgRob *)pStruct;
    cJSON *type = cJSON_CreateNumber(Msg_Type_Rob);
    cJSON *msg = cJSON_CreateObject();
    cJSON_AddStringToObject(msg, "username", msgRob->username);
    cJSON_AddNumberToObject(msg, "roomNum", msgRob->roomNum);
    cJSON_AddNumberToObject(msg, "rob", msgRob->robRet);
    cJSON *root = cJSON_CreateObject();
    cJSON_AddItemToObject(root, "type", type);
    cJSON_AddItemToObject(root, "msg", msg);

    *out = cJSON_Print(root);
    cJSON_Delete(root);

    return 0;

}
//解码抢地主消息
int DecodeRob(const char *in, MsgRob *msgRob)
{

     cJSON *root = cJSON_Parse(in);
     cJSON *jsMsg = cJSON_GetObjectItem(root, "msg");
     cJSON *jsUserName = cJSON_GetObjectItem(jsMsg, "username");
     cJSON *jsRoomNum = cJSON_GetObjectItem(jsMsg, "roomNum");
     cJSON *jsRob = cJSON_GetObjectItem(jsMsg, "rob");
     strcpy(msgRob->username, jsUserName->valuestring);
     msgRob->roomNum = jsRoomNum->valueint;
     msgRob->robRet = jsRob->valueint;

     cJSON_Delete(root);

     return 0;
}

//编码其他人抢地主消息
int EncodeOtherRob(const void *pStruct, char **out)
{
    MsgOtherRob *msgOtherRob =  (MsgOtherRob *)pStruct;
    cJSON *type = cJSON_CreateNumber(Msg_Type_OtherRob);
    cJSON *msg = cJSON_CreateObject();
    cJSON_AddNumberToObject(msg, "seat", msgOtherRob->seat);
    cJSON_AddNumberToObject(msg, "robRet", msgOtherRob->robRet);
    cJSON_AddNumberToObject(msg, "nextRober", msgOtherRob->nextRober);
    cJSON *root = cJSON_CreateObject();
    cJSON_AddItemToObject(root, "type", type);
    cJSON_AddItemToObject(root, "msg", msg);

    *out = cJSON_Print(root);
    cJSON_Delete(root);

    return 0;

}
//解码其他人抢地主消息
int DecodeOtherRob(const char *in, MsgOtherRob *msgOtherRob)
{

     cJSON *root = cJSON_Parse(in);
     cJSON *jsMsg = cJSON_GetObjectItem(root, "msg");

     cJSON *jsSeat = cJSON_GetObjectItem(jsMsg, "seat");
     cJSON *jsRobRet = cJSON_GetObjectItem(jsMsg, "robRet");
     cJSON *jsNextRober = cJSON_GetObjectItem(jsMsg, "nextRober");
     msgOtherRob->seat = jsSeat->valueint;
     msgOtherRob->robRet = jsRobRet->valueint;
     msgOtherRob->nextRober = jsNextRober->valueint;

     cJSON_Delete(root);

     return 0;
}

//编码抢地主结果消息
int EncodeRobResult(const void *pStruct, char **out)
{
    MsgRobResult *msgRobResult =  (MsgRobResult *)pStruct;
    cJSON *type = cJSON_CreateNumber(Msg_Type_RobResult);
    cJSON *msg = cJSON_CreateObject();
    cJSON_AddNumberToObject(msg, "landOwnerPos", msgRobResult->landOwnerPos);
    cJSON *root = cJSON_CreateObject();
    cJSON_AddItemToObject(root, "type", type);
    cJSON_AddItemToObject(root, "msg", msg);

    *out = cJSON_Print(root);
    cJSON_Delete(root);

    return 0;

}
//解码抢地主结果消息
int DecodeRobResult(const char *in, MsgRobResult *msgRobResult)
{

     cJSON *root = cJSON_Parse(in);
     cJSON *jsMsg = cJSON_GetObjectItem(root, "msg");
     cJSON *jsLandOwnerPos = cJSON_GetObjectItem(jsMsg, "landOwnerPos");
     msgRobResult->landOwnerPos = jsLandOwnerPos->valueint;
     cJSON_Delete(root);

     return 0;
}

//编码不要牌消息
int EncodePass(const void *pStruct, char **out)
{
    MsgPass *msgPass =  (MsgPass *)pStruct;
    cJSON *type = cJSON_CreateNumber(Msg_Type_Pass);
    cJSON *msg = cJSON_CreateObject();
    cJSON_AddStringToObject(msg, "username", msgPass->username);
    cJSON_AddNumberToObject(msg, "roomNum", msgPass->roomNum);
    cJSON *root = cJSON_CreateObject();
    cJSON_AddItemToObject(root, "type", type);
    cJSON_AddItemToObject(root, "msg", msg);

    *out = cJSON_Print(root);
    cJSON_Delete(root);

    return 0;
}
//解码不要牌消息
int DecodePass(const char *in, MsgPass *msgPass)
{

   // MsgLoginReq *msgLoginReq =  (MsgLoginReq *)pStruct;
    cJSON *root = cJSON_Parse(in);
    cJSON *jsMsg = cJSON_GetObjectItem(root, "msg");
    cJSON *jsUserName = cJSON_GetObjectItem(jsMsg, "username");
    cJSON *jsRoomNum = cJSON_GetObjectItem(jsMsg, "roomNum");
    strcpy(msgPass->username, jsUserName->valuestring);
    msgPass->roomNum = jsRoomNum->valueint;

    cJSON_Delete(root);

    return 0;
}

//编码其他人不要牌消息
int EncodeOtherPass(const void *pStruct, char **out)
{
    MsgOtherPass *msgOtherPass =  (MsgOtherPass *)pStruct;
    cJSON *type = cJSON_CreateNumber(Msg_Type_OtherPass);
    cJSON *msg = cJSON_CreateObject();
    cJSON_AddNumberToObject(msg, "pos", msgOtherPass->pos);
    cJSON *root = cJSON_CreateObject();
    cJSON_AddItemToObject(root, "type", type);
    cJSON_AddItemToObject(root, "msg", msg);

    *out = cJSON_Print(root);
    cJSON_Delete(root);

    return 0;
}
//解码其他人不要牌消息
int DecodeOtherPass(const char *in, MsgOtherPass *msgOtherPass)
{

   // MsgLoginReq *msgLoginReq =  (MsgLoginReq *)pStruct;
    cJSON *root = cJSON_Parse(in);
    cJSON *jsMsg = cJSON_GetObjectItem(root, "msg");
    cJSON *jsPos = cJSON_GetObjectItem(jsMsg, "pos");

    msgOtherPass->pos = jsPos->valueint;

    cJSON_Delete(root);

    return 0;
}

//编码出牌消息
int EncodeOutCard(const void *pStruct, char **out)
{
    MsgOutCard *msgOutCard =  (MsgOutCard *)pStruct;
    cJSON *type = cJSON_CreateNumber(Msg_Type_OutCard);
    cJSON *msg = cJSON_CreateObject();
    cJSON_AddStringToObject(msg, "username", msgOutCard->username);
    cJSON_AddNumberToObject(msg, "roomNum", msgOutCard->roomNum);
    cJSON_AddNumberToObject(msg, "size", msgOutCard->size);

    cJSON *cards = cJSON_CreateArray();
    int i;
    int size = msgOutCard->size;
    for(i = 0; i < size; i++){
        cJSON *cardInfo = cJSON_CreateObject();
        cJSON_AddNumberToObject(cardInfo, "color", msgOutCard->cards[i].color);
        cJSON_AddNumberToObject(cardInfo, "value", msgOutCard->cards[i].value);
        cJSON_AddItemToArray(cards, cardInfo);
    }

    cJSON_AddItemToObject(msg, "cards", cards);

    cJSON *root = cJSON_CreateObject();
    cJSON_AddItemToObject(root, "type", type);
    cJSON_AddItemToObject(root, "msg", msg);

    *out = cJSON_Print(root);
    cJSON_Delete(root);

    return 0;
}
//解码出牌消息
int DecodeOutCard(const char *in, MsgOutCard *msgOutCard)
{

    cJSON *root = cJSON_Parse(in);
    cJSON *jsMsg = cJSON_GetObjectItem(root, "msg");
    cJSON *jsRoomNum = cJSON_GetObjectItem(jsMsg, "roomNum");
    msgOutCard->roomNum = jsRoomNum->valueint;
    cJSON *jsSize = cJSON_GetObjectItem(jsMsg, "size");
    msgOutCard->size = jsSize->valueint;
    cJSON *jsUserName = cJSON_GetObjectItem(jsMsg, "username");
    strcpy(msgOutCard->username, jsUserName->valuestring);

    cJSON *jsCards = cJSON_GetObjectItem(jsMsg, "cards");

    int i;
    int size = msgOutCard->size;
    for(i = 0; i < size; i++){
        cJSON *cardInfo = cJSON_GetArrayItem(jsCards, i);
        cJSON *color = cJSON_GetObjectItem(cardInfo, "color");
        cJSON *value = cJSON_GetObjectItem(cardInfo, "value");
        msgOutCard->cards[i].color = color->valueint;
        msgOutCard->cards[i].value = value->valueint;
    }


    cJSON_Delete(root);

    return 0;
}

//编码其他玩家出牌消息
int EncodeOtherOutCard(const void *pStruct, char **out)
{
    MsgOtherOutCard *msgOtherOutCard =  (MsgOtherOutCard *)pStruct;
    cJSON *type = cJSON_CreateNumber(Msg_Type_OtherOutCard);
    cJSON *msg = cJSON_CreateObject();
    cJSON_AddNumberToObject(msg, "pos", msgOtherOutCard->pos);
    cJSON_AddNumberToObject(msg, "size", msgOtherOutCard->size);

    cJSON *cards = cJSON_CreateArray();
    int i;
    int size = msgOtherOutCard->size;
    for(i = 0; i < size; i++){
        cJSON *cardInfo = cJSON_CreateObject();
        cJSON_AddNumberToObject(cardInfo, "color", msgOtherOutCard->cards[i].color);
        cJSON_AddNumberToObject(cardInfo, "value", msgOtherOutCard->cards[i].value);
        cJSON_AddItemToArray(cards, cardInfo);
    }

    cJSON_AddItemToObject(msg, "cards", cards);

    cJSON *root = cJSON_CreateObject();
    cJSON_AddItemToObject(root, "type", type);
    cJSON_AddItemToObject(root, "msg", msg);

    *out = cJSON_Print(root);
    cJSON_Delete(root);

    return 0;
}
//解码其他玩家出牌消息
int DecodeOtherOutCard(const char *in, MsgOtherOutCard *msgOtherOutCard)
{

    cJSON *root = cJSON_Parse(in);
    cJSON *jsMsg = cJSON_GetObjectItem(root, "msg");
    cJSON *jsPos = cJSON_GetObjectItem(jsMsg, "pos");
    msgOtherOutCard->pos = jsPos->valueint;
    cJSON *jsSize = cJSON_GetObjectItem(jsMsg, "size");
    msgOtherOutCard->size = jsSize->valueint;


    cJSON *jsCards = cJSON_GetObjectItem(jsMsg, "cards");

    int i;
    int size = msgOtherOutCard->size;
    for(i = 0; i < size; i++){
        cJSON *cardInfo = cJSON_GetArrayItem(jsCards, i);
        cJSON *color = cJSON_GetObjectItem(cardInfo, "color");
        cJSON *value = cJSON_GetObjectItem(cardInfo, "value");
        msgOtherOutCard->cards[i].color = color->valueint;
        msgOtherOutCard->cards[i].value = value->valueint;
    }


    cJSON_Delete(root);

    return 0;
}

//编码游戏结束消息（to server）
int EncodeGameOverReq(const void *pStruct, char **out)
{
    MsgGameOverReq *msgGameOverReq =  (MsgGameOverReq *)pStruct;
    cJSON *type = cJSON_CreateNumber(Msg_Type_GameOverReq);
    cJSON *msg = cJSON_CreateObject();
    cJSON_AddStringToObject(msg, "username", msgGameOverReq->username);
    cJSON_AddNumberToObject(msg, "roomNum", msgGameOverReq->roomNum);
    cJSON *root = cJSON_CreateObject();
    cJSON_AddItemToObject(root, "type", type);
    cJSON_AddItemToObject(root, "msg", msg);

    *out = cJSON_Print(root);
    cJSON_Delete(root);

    return 0;
}
//解码游戏结束消息（to server）
int DecodeGameOverReq(const char *in, MsgGameOverReq *msgGameOverReq)
{

   // MsgLoginReq *msgLoginReq =  (MsgLoginReq *)pStruct;
    cJSON *root = cJSON_Parse(in);
    cJSON *jsMsg = cJSON_GetObjectItem(root, "msg");
    cJSON *jsUserName = cJSON_GetObjectItem(jsMsg, "username");
    cJSON *jsRoomNum = cJSON_GetObjectItem(jsMsg, "roomNum");
    strcpy(msgGameOverReq->username, jsUserName->valuestring);
    msgGameOverReq->roomNum = jsRoomNum->valueint;

    cJSON_Delete(root);

    return 0;
}

//编码游戏结束消息（from server）
int EncodeGameOver(const void *pStruct, char **out)
{
    MsgGameOver *msgGameOver =  (MsgGameOver *)pStruct;
    cJSON *type = cJSON_CreateNumber(Msg_Type_GameOver);
    cJSON *msg = cJSON_CreateObject();
    cJSON_AddNumberToObject(msg, "winPos", msgGameOver->winPos);
    cJSON *root = cJSON_CreateObject();
    cJSON_AddItemToObject(root, "type", type);
    cJSON_AddItemToObject(root, "msg", msg);

    *out = cJSON_Print(root);
    cJSON_Delete(root);

    return 0;
}
//解码游戏结束消息（from server）
int DecodeGameOver(const char *in, MsgGameOver *msgGameOver)
{

   // MsgLoginReq *msgLoginReq =  (MsgLoginReq *)pStruct;
    cJSON *root = cJSON_Parse(in);
    cJSON *jsMsg = cJSON_GetObjectItem(root, "msg");
    cJSON *jsWinPos = cJSON_GetObjectItem(jsMsg, "winPos");
    msgGameOver->winPos = jsWinPos->valueint;

    cJSON_Delete(root);

    return 0;
}

//编码离开房间消息
int EncodeLeaveRoom(const void *pStruct, char **out)
{
    MsgLeaveRoom *msgLeaveRoom =  (MsgLeaveRoom *)pStruct;
    cJSON *type = cJSON_CreateNumber(Msg_Type_LeaveRoom);
    cJSON *msg = cJSON_CreateObject();
    cJSON_AddStringToObject(msg, "username", msgLeaveRoom->username);
    cJSON_AddNumberToObject(msg, "roomNum", msgLeaveRoom->roomNum);
    cJSON *root = cJSON_CreateObject();
    cJSON_AddItemToObject(root, "type", type);
    cJSON_AddItemToObject(root, "msg", msg);

    *out = cJSON_Print(root);
    cJSON_Delete(root);

    return 0;
}
//解码离开房间消息
int DecodeLeaveRoom(const char *in, MsgLeaveRoom *msgLeaveRoom)
{

   // MsgLoginReq *msgLoginReq =  (MsgLoginReq *)pStruct;
    cJSON *root = cJSON_Parse(in);
    cJSON *jsMsg = cJSON_GetObjectItem(root, "msg");
    cJSON *jsUserName = cJSON_GetObjectItem(jsMsg, "username");
    cJSON *jsRoomNum = cJSON_GetObjectItem(jsMsg, "roomNum");
    strcpy(msgLeaveRoom->username, jsUserName->valuestring);
    msgLeaveRoom->roomNum = jsRoomNum->valueint;

    cJSON_Delete(root);

    return 0;
}

//编码其他人离开房间消息
int EncodeOtherLeaveRoom(const void *pStruct, char **out)
{
    MsgOtherLeaveRoom *msgOtherLeaveRoom =  (MsgOtherLeaveRoom *)pStruct;
    cJSON *type = cJSON_CreateNumber(Msg_Type_OtherLeaveRoom);
    cJSON *msg = cJSON_CreateObject();
    cJSON_AddNumberToObject(msg, "pos", msgOtherLeaveRoom->pos);
    cJSON_AddNumberToObject(msg, "isPlaying", msgOtherLeaveRoom->isPlaying);
    cJSON *root = cJSON_CreateObject();
    cJSON_AddItemToObject(root, "type", type);
    cJSON_AddItemToObject(root, "msg", msg);

    *out = cJSON_Print(root);
    cJSON_Delete(root);

    return 0;
}
//解码其他人离开房间消息
int DecodeOtherLeaveRoom(const char *in, MsgOtherLeaveRoom *msgOtherLeaveRoom)
{

   // MsgLoginReq *msgLoginReq =  (MsgLoginReq *)pStruct;
    cJSON *root = cJSON_Parse(in);
    cJSON *jsMsg = cJSON_GetObjectItem(root, "msg");
    cJSON *jsPos = cJSON_GetObjectItem(jsMsg, "pos");
    cJSON *jsIsPlaying = cJSON_GetObjectItem(jsMsg, "isPlaying");
    msgOtherLeaveRoom->pos = jsPos->valueint;
    msgOtherLeaveRoom->isPlaying = jsIsPlaying->valueint;

    cJSON_Delete(root);

    return 0;
}

int MsgEncode(const void *pStruct, int msgType, char **outData)
{
    char *out = NULL;
    switch(msgType)
    {
    case Msg_Type_LoginReq:
        EncodeLoginReq(pStruct, &out);
        break;
    case Msg_Type_LoginRes:
        EncodeLoginRes(pStruct, &out);
        break;
    case Msg_Type_RegReq:
        EncodeRegReq(pStruct, &out);
        break;
    case Msg_Type_RegRes:
        EncodeRegRes(pStruct, &out);
        break;
    case Msg_Type_CreateRoomReq:
        EncodeCreateRoomReq(pStruct, &out);
        break;
    case Msg_Type_CreateRoomRes:
        EncodeCreateRoomRes(pStruct, &out);
        break;
    case Msg_Type_JoinRoomReq:
        EncodeJoinRoomReq(pStruct, &out);
        break;
    case Msg_Type_JoinRoomRes:
        EncodeJoinRoomRes(pStruct, &out);
        break;
    case Msg_Type_Prepare:
        EncodePrepare(pStruct, &out);
        break;
    case Msg_Type_OtherStatusChanged:
        EncodeOtherStatusChanged(pStruct, &out);
        break;
    case Msg_Type_CanclePrepare:
        EncodeCanclePrepare(pStruct, &out);
        break;
    case Msg_Type_DealCards:
        EncodeDealCards(pStruct, &out);
        break;
    case Msg_Type_Rob:
        EncodeRob(pStruct, &out);
        break;
    case Msg_Type_OtherRob:
        EncodeOtherRob(pStruct, &out);
        break;
    case Msg_Type_RobResult:
        EncodeRobResult(pStruct, &out);
        break;
    case Msg_Type_Pass:
        EncodePass(pStruct, &out);
        break;
    case Msg_Type_OtherPass:
        EncodeOtherPass(pStruct, &out);
        break;
    case Msg_Type_OutCard:
        EncodeOutCard(pStruct, &out);
        break;
    case Msg_Type_OtherOutCard:
        EncodeOtherOutCard(pStruct, &out);
        break;
    case Msg_Type_GameOverReq:
        EncodeGameOverReq(pStruct, &out);
        break;
    case Msg_Type_GameOver:
        EncodeGameOver(pStruct, &out);
        break;
    case Msg_Type_LeaveRoom:
        EncodeLeaveRoom(pStruct, &out);
        break;
    case Msg_Type_OtherLeaveRoom:
        EncodeOtherLeaveRoom(pStruct, &out);
        break;
    default:
        break;
    }
    //数据末尾加2个\n （产生一个空行）
    if(out != NULL){
        int len = strlen(out);
        *outData = malloc(len + 3);
        strcpy(*outData, out);
        (*outData)[len] = '\n';
        (*outData)[len+1] = '\n';
        (*outData)[len+2] = '\0';
        free(out);
    }

    return 0;
}

int MsgDecode(const char *inData, void **pStruct, int *msgType)
{
    //去掉数据末尾的\n；
    int len = strlen(inData);
    char *in = malloc(len+1);
    strcpy(in, inData);
    in[len - 1] = '\0';

    //开始解码
    int iType = 0;
    cJSON *root = cJSON_Parse(in);
    cJSON *jsType = cJSON_GetObjectItem(root, "type");
    iType = jsType->valueint;
    *msgType = iType;
    switch(iType)
    {
    case Msg_Type_LoginReq:
        *pStruct = malloc(sizeof(MsgLoginReq));
        DecodeLoginReq(in, *pStruct);
        break;
    case Msg_Type_LoginRes:
        *pStruct = malloc(sizeof(MsgLoginRes));
        DecodeLoginRes(in, *pStruct);
        break;
    case Msg_Type_RegReq:
        *pStruct = malloc(sizeof(MsgRegReq));
        DecodeRegReq(in, *pStruct);
        break;
    case Msg_Type_RegRes:
        *pStruct = malloc(sizeof(MsgRegRes));
        DecodeRegRes(in, *pStruct);
        break;
    case Msg_Type_CreateRoomReq:
        *pStruct = malloc(sizeof(MsgCreateRoomReq));
        DecodeCreateRoomReq(in, *pStruct);
        break;
    case Msg_Type_CreateRoomRes:
        *pStruct = malloc(sizeof(MsgCreateRoomRes));
        DecodeCreateRoomRes(in, *pStruct);
        break;
    case Msg_Type_JoinRoomReq:
        *pStruct = malloc(sizeof(MsgJoinRoomReq));
        DecodeJoinRoomReq(in, *pStruct);
        break;
    case Msg_Type_JoinRoomRes:
        *pStruct = malloc(sizeof(MsgJoinRoomRes));
        DecodeJoinRoomRes(in, *pStruct);
        break;
    case Msg_Type_Prepare:
        *pStruct = malloc(sizeof(MsgPrepare));
        DecodePrepare(in, *pStruct);
        break;
    case Msg_Type_OtherStatusChanged:
        *pStruct = malloc(sizeof(MsgOtherStatusChanged));
        DecodeOtherStatusChanged(in, *pStruct);
        break;
    case Msg_Type_CanclePrepare:
        *pStruct = malloc(sizeof(MsgCanclePrepare));
        DecodeCanclePrepare(in, *pStruct);
        break;
    case Msg_Type_DealCards:
        *pStruct = malloc(sizeof(MsgDealCards));
        DecodeDealCards(in, *pStruct);
        break;
    case Msg_Type_Rob:
        *pStruct = malloc(sizeof(MsgRob));
        DecodeRob(in, *pStruct);
        break;
    case Msg_Type_OtherRob:
        *pStruct = malloc(sizeof(MsgOtherRob));
        DecodeOtherRob(in, *pStruct);
        break;
    case Msg_Type_RobResult:
        *pStruct = malloc(sizeof(MsgRobResult));
        DecodeRobResult(in, *pStruct);
        break;
    case Msg_Type_Pass:
        *pStruct = malloc(sizeof(MsgPass));
        DecodePass(in, *pStruct);
        break;
    case Msg_Type_OtherPass:
        *pStruct = malloc(sizeof(MsgOtherPass));
        DecodeOtherPass(in, *pStruct);
        break;
    case Msg_Type_OutCard:
        *pStruct = malloc(sizeof(MsgOutCard));
        DecodeOutCard(in, *pStruct);
        break;
    case Msg_Type_OtherOutCard:
        *pStruct = malloc(sizeof(MsgOtherOutCard));
        DecodeOtherOutCard(in, *pStruct);
        break;
    case Msg_Type_GameOverReq:
        *pStruct = malloc(sizeof(MsgGameOverReq));
        DecodeGameOverReq(in, *pStruct);
        break;
    case Msg_Type_GameOver:
        *pStruct = malloc(sizeof(MsgGameOver));
        DecodeGameOver(in, *pStruct);
        break;
    case Msg_Type_LeaveRoom:
        *pStruct = malloc(sizeof(MsgLeaveRoom));
        DecodeLeaveRoom(in, *pStruct);
        break;
    case Msg_Type_OtherLeaveRoom:
        *pStruct = malloc(sizeof(MsgOtherLeaveRoom));
        DecodeOtherLeaveRoom(in, *pStruct);
        break;
    default:
        break;
    }

    free(in);
    return 0;
}

int MsgFree(void *data)
{
    if(data != NULL) free(data);
    return 0;
}
