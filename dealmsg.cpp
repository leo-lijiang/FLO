#include "dealmsg.h"
/*
#include <QtSql/QSql>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlField>
#include <QtSql/QSqlError>
#include <QtSql/QSqlResult>
*/
#include "DBConnPool.h"
#include <QDebug>


DealMsg::DealMsg(QObject *parent) :
    QObject(parent)
{
    mReqMsgStruct = NULL;
    mReqMsgType = 0;
    mResMsgChar = NULL;
    mResMsgType = 0;
    mMsgReq.clear();

    connect(this, SIGNAL(sigCreateRoom(MsgCreateRoomReq *)), parent, SLOT(slotCreateRoom(MsgCreateRoomReq *)));
    connect(parent, SIGNAL(sigCreateRoomResult(QString)), this, SLOT(slotCreateRoomResult(QString)));
    connect(this, SIGNAL(sigPrepare(MsgPrepare*)), parent, SLOT(slotPrepare(MsgPrepare*)));
    connect(this, SIGNAL(sigCanclePrepare(MsgCanclePrepare *)), parent, SLOT(slotCanclePrepare(MsgCanclePrepare *)));
    connect(this, SIGNAL(sigRob(MsgRob*)), parent, SLOT(slotRob(MsgRob*)));
    connect(this, SIGNAL(sigPass(MsgPass*)), parent, SLOT(slotPass(MsgPass *)));
    connect(this, SIGNAL(sigOutCard(MsgOutCard*)), parent, SLOT(slotOutCard(MsgOutCard *)));
    connect(this, SIGNAL(sigGameOver(MsgGameOverReq*)), parent, SLOT(slotGameOver(MsgGameOverReq *)));
    connect(this, SIGNAL(sigLeaveRoom(MsgLeaveRoom*)), parent, SLOT(slotLeaveRoom(MsgLeaveRoom *)));

    connect(this, SIGNAL(sigJoinRoom(MsgJoinRoomReq *)), parent, SLOT(slotJoinRoom(MsgJoinRoomReq *)));
    connect(parent, SIGNAL(sigJoinRoomResult(QString)), this, SLOT(slotJoinRoomResult(QString)));

}
void DealMsg::ReqMsgDecode()
{
    MsgDecode(mMsgReq.toUtf8().data(), &mReqMsgStruct, &mReqMsgType);
}

void DealMsg::DealReqMsg()
{



    if(Msg_Type_LoginReq == mReqMsgType){
        //deal login message
        DealLoginReq();
    }
    else if(Msg_Type_RegReq == mReqMsgType){
        //deal register message
        DealRegReq();
    }
    else if(Msg_Type_CreateRoomReq == mReqMsgType){
        //deal createroom message
        DealCreateRoomReq();
    }

    else if(Msg_Type_JoinRoomReq == mReqMsgType){
        //deal join room message
        DealJoinRoomReq();
    }
    else if(Msg_Type_Prepare == mReqMsgType){
        DealPrepare();
    }
    else if(Msg_Type_CanclePrepare == mReqMsgType){
        DealCanclePrepare();
    }
    else if(Msg_Type_Rob == mReqMsgType){
        DealRob();
    }
    else if(Msg_Type_Pass == mReqMsgType){
        DealPass();
    }
    else if(Msg_Type_OutCard == mReqMsgType){
        DealOutCard();
    }
    else if(Msg_Type_GameOverReq == mReqMsgType){
        DealGameOver();
    }
    else if(Msg_Type_LeaveRoom == mReqMsgType){
        DealLeaveRoom();
    }
    else{
        qDebug() << "unknow message type";
    }


}

void DealMsg::DealResMsg()
{
    if(mResMsgChar != NULL){
        mMsgRes = mResMsgChar;
    }
}

void DealMsg::DealLoginReq()
{
    QSqlDatabase db = DBConnPool::openConnection();
    MsgLoginReq *msgLoginReq = (MsgLoginReq *)mReqMsgStruct;
    MsgLoginRes msgLoginRes;
    //write in database
    if(!db.open()){
        qDebug() << "open database error";

        //init return message
        msgLoginRes.isSuccess = 0;
        strcpy(msgLoginRes.errInfo, "open database error");
        MsgEncode(&msgLoginRes, Msg_Type_LoginRes, &mResMsgChar);
        DBConnPool::closeConnection(db);
        return;
    }
    QString sql = QString("select id from users where username='%1' and password='%2'")
            .arg(msgLoginReq->username, msgLoginReq->pwd);
    QSqlQuery result = db.exec(sql);
    if(result.next()){
        msgLoginRes.isSuccess = 1;
        strcpy(msgLoginRes.errInfo, "Login success");
        MsgEncode(&msgLoginRes, Msg_Type_LoginRes, &mResMsgChar);
    }
    else{
        msgLoginRes.isSuccess = 0;
        strcpy(msgLoginRes.errInfo, "Login failed");
        MsgEncode(&msgLoginRes, Msg_Type_LoginRes, &mResMsgChar);
    }
    DBConnPool::closeConnection(db);
}

void DealMsg::DealRegReq()
{

    QSqlDatabase db = DBConnPool::openConnection();

    MsgRegReq *msgRegReq = (MsgRegReq *)mReqMsgStruct;
    MsgRegRes msgRegRes;

    //write in database
    if(!db.open()){
        qDebug() << "open database error";

        //init return message
        msgRegRes.isSuccess = 0;
        strcpy(msgRegRes.errInfo, "open database error");
        MsgEncode(&msgRegRes, Msg_Type_RegRes, &mResMsgChar);
        DBConnPool::closeConnection(db);

        return;
    }
    QString sql = QString("insert into users(username, password) values('%1', '%2')")
            .arg(msgRegReq->username, msgRegReq->pwd);
    QSqlQuery result = db.exec(sql);
    if(result.lastError().type() == QSqlError::NoError){
        msgRegRes.isSuccess = 1;
        strcpy(msgRegRes.errInfo, "register success");
        MsgEncode(&msgRegRes, Msg_Type_RegRes, &mResMsgChar);
    }
    else{
        qDebug() << result.lastError().text();
        msgRegRes.isSuccess = 0;
        strcpy(msgRegRes.errInfo, "register failed");
        MsgEncode(&msgRegRes, Msg_Type_RegRes, &mResMsgChar);
    }
    DBConnPool::closeConnection(db);
}

void DealMsg::DealCreateRoomReq()
{
    MsgCreateRoomReq *msgCreateRoomReq = (MsgCreateRoomReq *)mReqMsgStruct;
    //MsgCreateRoomRes msgCreateRoomRes;
    emit sigCreateRoom(msgCreateRoomReq);
}

void DealMsg::DealJoinRoomReq()
{
    MsgJoinRoomReq *msgJoinRoomReq = (MsgJoinRoomReq *)mReqMsgStruct;
    //MsgCreateRoomRes msgCreateRoomRes;
    emit sigJoinRoom(msgJoinRoomReq);
}

void DealMsg::DealPrepare()
{
    MsgPrepare *msgPrepare = (MsgPrepare *)mReqMsgStruct;
    //MsgCreateRoomRes msgCreateRoomRes;
    emit sigPrepare(msgPrepare);
}

void DealMsg::DealCanclePrepare()
{
    MsgCanclePrepare *msgCanclePrepare = (MsgCanclePrepare *)mReqMsgStruct;
    //MsgCreateRoomRes msgCreateRoomRes;
    emit sigCanclePrepare(msgCanclePrepare);
}

void DealMsg::DealRob()
{
    MsgRob *msgRob = (MsgRob *)mReqMsgStruct;
    emit sigRob(msgRob);
}

void DealMsg::DealPass()
{
    MsgPass *msgPass = (MsgPass *)mReqMsgStruct;
    emit sigPass(msgPass);
}

void DealMsg::DealOutCard()
{
    MsgOutCard *msgOutCard = (MsgOutCard *)mReqMsgStruct;
    emit sigOutCard(msgOutCard);
}

void DealMsg::DealGameOver()
{
    MsgGameOverReq *msgGameOverReq = (MsgGameOverReq *)mReqMsgStruct;
    emit sigGameOver(msgGameOverReq);
}

void DealMsg::DealLeaveRoom()
{
    MsgLeaveRoom *msgLeaveRoom = (MsgLeaveRoom *)mReqMsgStruct;
    emit sigLeaveRoom(msgLeaveRoom);
}

void DealMsg::slotCreateRoomResult(QString result)
{
    mMsgRes = result;
}

void DealMsg::slotJoinRoomResult(QString result)
{
    mMsgRes = result;
}

QString DealMsg::Result()
{
    QString result = mMsgRes;

    mMsgRes.clear();
    if(mReqMsgStruct != NULL){
        MsgFree(mReqMsgStruct);
        mReqMsgStruct = NULL;
    }
    if(mResMsgChar != NULL){
        MsgFree(mResMsgChar);
        mResMsgChar = NULL;
    }

    return result;
}

void DealMsg::InputMsg(QString msg)
{
    mMsgReq = msg;
    ReqMsgDecode();

    DealReqMsg();

    DealResMsg();
}
DealMsg::~DealMsg()
{
    if(mReqMsgStruct != NULL){
        MsgFree(mReqMsgStruct);
    }
    if(mResMsgChar != NULL){
        MsgFree(mResMsgChar);
    }
}

