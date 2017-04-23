#ifndef DEALMSG_H
#define DEALMSG_H

#include <QObject>
#include "MsgMng.h"
#include <QString>

class DealMsg : public QObject
{
    Q_OBJECT
public:
    explicit DealMsg(QObject *parent = 0);
    QString Result();
    void InputMsg(QString msg);
    ~DealMsg();
private:
    void ReqMsgDecode();
    void DealReqMsg();
    void DealResMsg();

    void DealLoginReq();
    void DealRegReq();
    void DealCreateRoomReq();
    void DealJoinRoomReq();
    void DealPrepare();
    void DealCanclePrepare();
    void DealRob();
    void DealPass();
    void DealOutCard();
    void DealGameOver();
    void DealLeaveRoom();
signals:
    void sigCreateRoom(MsgCreateRoomReq *msgCreateRoomReq);
    void sigJoinRoom(MsgJoinRoomReq *msgJoinRoomReq);
    void sigPrepare(MsgPrepare *msgPrepare);
    void sigCanclePrepare(MsgCanclePrepare *msgCanclePrepare);
    void sigRob(MsgRob *msgRob);
    void sigPass(MsgPass *msgPass);
    void sigOutCard(MsgOutCard *msgOutCard);
    void sigGameOver(MsgGameOverReq *msgGameOverReq);
    void sigLeaveRoom(MsgLeaveRoom *msgLeaveRoom);
public slots:
    void slotCreateRoomResult(QString result);
    void slotJoinRoomResult(QString result);
private:
    QString mMsgReq;
    QString mMsgRes;

    void *mReqMsgStruct;
    char *mResMsgChar;
    int mReqMsgType;
    int mResMsgType;
};

#endif // DEALMSG_H
