#include "App.h"
#include <QCoreApplication>


App::App(QObject *parent) :
    QObject(parent)
{
    mRoomCount = 0;
    mDeal  = new DealMsg(this);
    //init tofao server
    HttpServer *server = new HttpServer(this);
    connect(server, SIGNAL(requestReady(Tufao::HttpServerRequest&,Tufao::HttpServerResponse&)),
            this, SLOT(slotRequestReady(Tufao::HttpServerRequest&,Tufao::HttpServerResponse&)));
    server->listen(QHostAddress::Any, SERV_PORT);

    //init Tcpserver
    mTcpserver = new QTcpServer(this);
    bool ret = mTcpserver->listen(QHostAddress::Any, TCPServer_PORT);
    if(ret) qDebug() << "listen ok";
    else qDebug() << "listen err";
    connect(mTcpserver, SIGNAL(newConnection()), this, SLOT(slotNewConnection()));
}


void App::slotRequestReady(Tufao::HttpServerRequest& req,Tufao::HttpServerResponse& res)
{
    //read msg
    QByteArray data =  req.readBody();
    QString msgReq(data);
    data.clear();

    //deal msg
    mDeal->InputMsg(msgReq);
    QString result = mDeal->Result();

    //return msg to client
    res.writeHead(HttpResponseStatus::OK);
    //res.end("hello from server");
    res.end(result.toUtf8().data());
}

void App::slotCreateRoom(MsgCreateRoomReq *msgCreateRoomReq)
{
    Room *room = new Room(mRoomCount++, this);
    Player *player = new Player(msgCreateRoomReq->username, room);
#if MYDEBUG
    QString clientIP = msgCreateRoomReq->clientIP;
#else
    int clientIP = msgCreateRoomReq->clientPort;
#endif
    if(mClientsInfo.hasClient(clientIP))
    {
        ClientInfo clientInfo = mClientsInfo.findClient(clientIP);
        player->setTcpSock(clientInfo.value());
        //player->setClientIP(QHostAddress(clientIP));
        player->setStatus(Status_Type_NotPrepare);
    }
    room->addPlayer(player);
    mRooms.insert(room->getRoomNum(), room);

    //encode response msg
    MsgCreateRoomRes msgCreateRoomRes;
    msgCreateRoomRes.isSuccess = 1;
    msgCreateRoomRes.roomNum = room->getRoomNum();
    strcpy(msgCreateRoomRes.errInfo,"create room success");
    char *outdata = NULL;
    MsgEncode(&msgCreateRoomRes, Msg_Type_CreateRoomRes, &outdata);

    emit sigCreateRoomResult(QString(outdata));
    MsgFree(outdata);
}

void App::slotJoinRoom(MsgJoinRoomReq *msgJoinRoomReq)
{
    //find join able room
    int roomNum = -1;
    Room *room = NULL;
    QMap<int, Room*>::iterator it = mRooms.begin();
    for(; it != mRooms.end(); ++it){
        //检查房间人数是否已满
        if(it.value()->getPlayerNumbers() < Room::mMaxPlayerNum){
            roomNum = it.key();
            room = it.value();
            break;
        }
    }
    //encode response msg
    MsgJoinRoomRes msgJoinRoomRes;
    //此处清0内存 不需要的信息就不赋值了
    memset(&msgJoinRoomRes, 0, sizeof(msgJoinRoomRes));

    if(it != mRooms.end() && room != NULL){

        Player *player = new Player(msgJoinRoomReq->username, room);
#if MYDEBUG
        QString clientIP = msgJoinRoomReq->clientIP;
#else
        int clientIP = msgJoinRoomReq->clientPort;
#endif
        //player->setClientIP(QHostAddress(clientIP));
        if(mClientsInfo.hasClient(clientIP))
        {
            ClientInfo clientInfo = mClientsInfo.findClient(clientIP);
            player->setTcpSock(clientInfo.value());           
        }
        room->addPlayer(player);
        player->setStatus(Status_Type_NotPrepare);

        msgJoinRoomRes.isSuccess = 1;
        int seatPos = room->getSeat(msgJoinRoomReq->username);
        Player *prevPlayer = room->prevPlayerInfo(seatPos);
        Player *nextPlayer = room->nextPlayerInfo(seatPos);
        if(prevPlayer != NULL){
            msgJoinRoomRes.number = 2;
            msgJoinRoomRes.playersStatus[0] = prevPlayer->getStatus();
            strcpy(msgJoinRoomRes.playersName[0], prevPlayer->getUserName().toUtf8().data());
        }
        if(nextPlayer != NULL){
            msgJoinRoomRes.number = 3;
            msgJoinRoomRes.playersStatus[1] = nextPlayer->getStatus();
            strcpy(msgJoinRoomRes.playersName[1], nextPlayer->getUserName().toUtf8().data());
        }
        msgJoinRoomRes.roomNum = roomNum;
        strcpy(msgJoinRoomRes.errInfo,"join room success");
    }
    else{
        //qDebug() << "-----------117-----------------------";
        msgJoinRoomRes.isSuccess = 0;
        msgJoinRoomRes.roomNum = roomNum;
//        strcpy(msgJoinRoomRes.playersName[0], "no name");
//        strcpy(msgJoinRoomRes.playersName[1], "no name");
//        msgJoinRoomRes.playersStatus[0] = 0;
//        msgJoinRoomRes.playersStatus[1] = 0;
        strcpy(msgJoinRoomRes.errInfo, "no room has available seat");
    }
    char *outdata = NULL;

    MsgEncode(&msgJoinRoomRes, Msg_Type_JoinRoomRes, &outdata);
    qDebug() << "-----------120-------------";
    emit sigJoinRoomResult(QString(outdata));
    //free memory
    MsgFree(outdata);
}

void App::slotPrepare(MsgPrepare *msgPrepare)
{
    auto it = mRooms.find(msgPrepare->roomNum);
    if(it != mRooms.end()){
        Room *room = it.value();
        int seatPos = room->getSeat(msgPrepare->username);
        qDebug() << QString("App.cpp::143---seat:%1 username:%2").arg(seatPos).arg(msgPrepare->username);
        Player *player = room->getPlayerInfo(seatPos);
        player->setStatus(Status_Type_IsPrepare);

        bool allArePrepare = room->allArePrepare();
        if(allArePrepare){
            qDebug() << "deal ---------149---";
            room->dealCards();
        }
    }
    else{
        qDebug() << "can not find room with this roomNum";
    }
}

void App::slotCanclePrepare(MsgCanclePrepare *msgCanclePrepare)
{
    auto it = mRooms.find(msgCanclePrepare->roomNum);
    if(it != mRooms.end()){
        Room *room = it.value();
        int seatPos = room->getSeat(msgCanclePrepare->username);
        Player *player = room->getPlayerInfo(seatPos);
        player->setStatus(Status_Type_NotPrepare);
    }
    else{
        qDebug() << "can not find room with this roomNum";
    }
}

void App::slotRob(MsgRob *msgRob)
{
    auto it = mRooms.find(msgRob->roomNum);
    if(it != mRooms.end()){
        Room *room = it.value();
        int seatPos = room->getSeat(msgRob->username);
        Player *player = room->getPlayerInfo(seatPos);
        if(msgRob->robRet == 0){
            //not rob
            player->setRobAble(false);
        }
        else if(msgRob->robRet == 1){
            //rob
            player->setHasRobed(true);
        }
        //Player *player = room->getPlayerInfo(seatPos);

    }
    else{
        qDebug() << "can not find room with this roomNum----app::183";
    }
}

void App::slotPass(MsgPass *msgPass)
{
    auto it = mRooms.find(msgPass->roomNum);
    if(it != mRooms.end()){
        Room *room = it.value();
        int seatPos = room->getSeat(msgPass->username);
        Player *nextPlayer = room->nextPlayerInfo(seatPos);
        Player *prevPlayer = room->prevPlayerInfo(seatPos);
        //send to next player
        MsgOtherPass msgOtherPass;
        QTcpSocket *sock = nextPlayer->getTcpSock();
        msgOtherPass.pos = Position_Prev;
        char *data = NULL;
        MsgEncode(&msgOtherPass, Msg_Type_OtherPass, &data);
        sock->write(data);
        MsgFree(data);
        //send to prev player
        sock = prevPlayer->getTcpSock();
        msgOtherPass.pos = Position_Next;
        MsgEncode(&msgOtherPass, Msg_Type_OtherPass, &data);
        sock->write(data);
        MsgFree(data);
    }
    else{
        qDebug() << "can not find room with this roomNum----app::183";
    }
}

void App::slotOutCard(MsgOutCard *msgOutCard)
{
    auto it = mRooms.find(msgOutCard->roomNum);
    if(it != mRooms.end()){
        Room *room = it.value();
        int seatPos = room->getSeat(msgOutCard->username);
        Player *nextPlayer = room->nextPlayerInfo(seatPos);
        Player *prevPlayer = room->prevPlayerInfo(seatPos);
        //send to next player
        MsgOtherOutCard msgOtherOutCard;
        QTcpSocket *sock = nextPlayer->getTcpSock();
        msgOtherOutCard.pos = Position_Prev;
        msgOtherOutCard.size = msgOutCard->size;
        for(int i = 0; i < msgOutCard->size; i++){
            msgOtherOutCard.cards[i] = msgOutCard->cards[i];
        }
        char *data = NULL;
        MsgEncode(&msgOtherOutCard, Msg_Type_OtherOutCard, &data);
        sock->write(data);
        MsgFree(data);
        //send to prev player
        sock = prevPlayer->getTcpSock();
        msgOtherOutCard.pos = Position_Next;
        MsgEncode(&msgOtherOutCard, Msg_Type_OtherOutCard, &data);
        sock->write(data);
        MsgFree(data);
    }
    else{
        qDebug() << "can not find room with this roomNum----app::183";
    }
}

void App::slotGameOver(MsgGameOverReq *msgGameOverReq)
{
    auto it = mRooms.find(msgGameOverReq->roomNum);
    if(it != mRooms.end()){
        Room *room = it.value();
        int seatPos = room->getSeat(msgGameOverReq->username);
        Player *self = room->getPlayerInfo(seatPos);
        Player *nextPlayer = room->nextPlayerInfo(seatPos);
        Player *prevPlayer = room->prevPlayerInfo(seatPos);
        //send to next player
        MsgGameOver msgGameOver;
        QTcpSocket *sock = nextPlayer->getTcpSock();
        //msgGameOver.winPos = Position_Prev;
        msgGameOver.winPos = self->getRole();
        char *data = NULL;
        MsgEncode(&msgGameOver, Msg_Type_GameOver, &data);
        sock->write(data);
        //MsgFree(data);
        //send to prev player
        sock = prevPlayer->getTcpSock();
        //msgGameOver.winPos = Position_Next;
        //MsgEncode(&msgGameOver, Msg_Type_GameOver, &data);
        sock->write(data);
        MsgFree(data);
        //重置房间内玩家状态
        room->resetRoomStatus();
    }
    else{
        qDebug() << "can not find room with this roomNum----app::183";
    }
}

void App::slotLeaveRoom(MsgLeaveRoom *msgLeaveRoom)
{
    auto it = mRooms.find(msgLeaveRoom->roomNum);
    if(it != mRooms.end()){
        Room *room = it.value();
        //the last one in room leave
        if(room->getPlayerNumbers() == 1){
            delete room;
            mRooms.erase(it);
            return;
        }
        //not the last one
        int seatPos = room->getSeat(msgLeaveRoom->username);
        Player *self = room->getPlayerInfo(seatPos);
        Player *nextPlayer = room->nextPlayerInfo(seatPos);
        Player *prevPlayer = room->prevPlayerInfo(seatPos);

        if(room->isInGame()){
            //send to next player
            MsgOtherLeaveRoom msgOtherLeaveRoom;
            QTcpSocket *sock = nextPlayer->getTcpSock();
            //msgGameOver.winPos = Position_Prev;
            msgOtherLeaveRoom.pos = Position_Prev;
            msgOtherLeaveRoom.isPlaying = 1;
            char *data = NULL;
            MsgEncode(&msgOtherLeaveRoom, Msg_Type_OtherLeaveRoom, &data);
            sock->write(data);
            MsgFree(data);
            //send to prev player
            sock = prevPlayer->getTcpSock();
            msgOtherLeaveRoom.pos = Position_Next;
            MsgEncode(&msgOtherLeaveRoom, Msg_Type_OtherLeaveRoom, &data);
            sock->write(data);
            MsgFree(data);
            //重置房间内玩家状态and in game status
            room->resetRoomStatus();
        }
        else{
            //send to next player
            MsgOtherLeaveRoom msgOtherLeaveRoom;
            if(nextPlayer != NULL){
                QTcpSocket *sock = nextPlayer->getTcpSock();
                //msgGameOver.winPos = Position_Prev;
                msgOtherLeaveRoom.pos = Position_Prev;
                msgOtherLeaveRoom.isPlaying = 0;
                char *data = NULL;
                MsgEncode(&msgOtherLeaveRoom, Msg_Type_OtherLeaveRoom, &data);
                sock->write(data);
                MsgFree(data);
            }
            //send to prev player
            if(prevPlayer != NULL){
                QTcpSocket *sock = prevPlayer->getTcpSock();
                msgOtherLeaveRoom.pos = Position_Next;
                msgOtherLeaveRoom.isPlaying = 0;
                char *data = NULL;
                MsgEncode(&msgOtherLeaveRoom, Msg_Type_OtherLeaveRoom, &data);
                sock->write(data);
                MsgFree(data);
            }
        }
        room->removePlayer(seatPos);
        delete self;

    }
    else{
        qDebug() << "can not find room with this roomNum----app::183";
    }
}

void App::slotNewConnection()
{
#if MYDEBUG
    QTcpSocket *sock;
    while(mTcpserver->hasPendingConnections()){
        sock = mTcpserver->nextPendingConnection();
        //connect(mTcpSock, SIGNAL(disconnected()), this, SLOT(slotPlayerLeave()));
        connect(sock, SIGNAL(readyRead()), this, SLOT(slotDataReceived()));
        mClientsInfo.addClient(sock->peerAddress().toString(), sock);
    }
#else
    QTcpSocket *sock;
    while(mTcpserver->hasPendingConnections()){
        sock = mTcpserver->nextPendingConnection();
        //connect(mTcpSock, SIGNAL(disconnected()), this, SLOT(slotPlayerLeave()));
        connect(sock, SIGNAL(readyRead()), this, SLOT(slotDataReceived()));
        mClientsInfo.addClient(sock->peerPort(), sock);
    }
#endif
}

void App::slotDataReceived()
{
    //read msg
    QTcpSocket *sock = (QTcpSocket *)sender();

    static QByteArray pack;
    while(sock->bytesAvailable())
    {
        QByteArray buf = sock->readLine(512);
        //qDebug() << buf;
        if(buf.size() > 1){
            pack += buf;
        }
        else{
            //qDebug() << buf.size();
            QString msgReq(pack);
            pack.clear();
            qDebug() << msgReq;
            //deal msg
            //DealMsg deal(msgReq, this);
            mDeal->InputMsg(msgReq);

            QString result = mDeal->Result();

            //write msg
            if(result.isNull()) continue;

            sock->write(result.toUtf8().data());
        }
    }
    /*
    QByteArray data = sock->readAll();
    QString msgReq(data);
    data.clear();
    qDebug() << msgReq;
    mDeal->InputMsg(msgReq);

    QString result = mDeal->Result();

    //write msg
    if(result.isNull()) return;

    sock->write(result.toUtf8().data());
    */
}



