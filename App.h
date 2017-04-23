#ifndef APP_H
#define APP_H

#include <QObject>
#include <tufao-1/Tufao/HttpServer>
#include <tufao-1/Tufao/HttpServerRequest>
#include <tufao-1/Tufao/HttpServerResponse>
#include <QString>
#include <QMap>
#include <QTcpServer>
#include <QTcpSocket>

#include "MsgMng.h"
#include "Room.h"
#include "Player.h"
#include "ClientsInfo.h"
#include "dealmsg.h"



using namespace Tufao;

class App : public QObject
{
    Q_OBJECT
public:
    explicit App(QObject *parent = 0);
private:
    //QString DealAllMsg(const QString &msgReq);

signals:
    void sigCreateRoomResult(QString result);
    void sigJoinRoomResult(QString result);

public slots:
    void slotRequestReady(Tufao::HttpServerRequest&,Tufao::HttpServerResponse&);

    void slotCreateRoom(MsgCreateRoomReq *msgCreateRoomReq);
    void slotJoinRoom(MsgJoinRoomReq *msgJoinRoomReq);
    void slotPrepare(MsgPrepare *msgPrepare);
    void slotCanclePrepare(MsgCanclePrepare *msgCanclePrepare);
    void slotRob(MsgRob *msgRob);
    void slotPass(MsgPass *msgPass);
    void slotOutCard(MsgOutCard *msgOutCard);
    void slotGameOver(MsgGameOverReq *msgGameOverReq);
    void slotLeaveRoom(MsgLeaveRoom *msgLeaveRoom);

    void slotNewConnection();
    void slotDataReceived();

private:
    QMap<int, Room*> mRooms;
    int mRoomCount;

    QTcpServer *mTcpserver;

    //QTcpSocket *mTcpSock;

    ClientsInfo mClientsInfo;

    DealMsg *mDeal;//消息 处理器


};

#endif // APP_H
