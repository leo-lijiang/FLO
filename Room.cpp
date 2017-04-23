#include "Room.h"
#include "MsgMng.h"

Room::Room(int roomNum, QObject *parent) :
    QObject(parent)
{
    mPlayers.clear();
    mPlayers.reserve(mMaxPlayerNum);
    mRoomNum = roomNum;
    mInGame = false;
    initCards();
}

Room::~Room()
{
    for(int i = 0; i < mCards.size(); i++){
        delete mCards[i];
    }
}

void Room::addPlayer(Player *player)
{
    mPlayers.push_back(player);
}

void Room::removePlayer(int pos)
{
    mPlayers.removeAt(pos);
}

int Room::getRoomNum()
{
    return mRoomNum;
}

int Room::getPlayerNumbers()
{
    return mPlayers.size();
}

int Room::getSeat(QString username)
{
    for(int i = 0; i < mPlayers.size(); i++){
        if(mPlayers[i]->getUserName() == username){
            return i;
        }
    }
    return -1;
}

Player *Room::getPlayerInfo(int seatPos)
{
    if(seatPos >= mPlayers.size() || seatPos < 0){
        return NULL;
    }
    return mPlayers[seatPos];
}

Player *Room::prevPlayerInfo(int seatPos)
{
    if(seatPos == 0){
        if(mPlayers.size() >= 3)
            return mPlayers[2];
        else return NULL;
    }
    else if(seatPos == 1){
        if(mPlayers.size() >= 1)
            return mPlayers[0];
        else return NULL;
    }
    else if(seatPos == 2){
        if(mPlayers.size() >= 2)
            return mPlayers[1];
        else return NULL;
    }
    else{
        return NULL;
    }
}

Player *Room::nextPlayerInfo(int seatPos)
{
    if(seatPos == 0){
        if(mPlayers.size() >= 2)
            return mPlayers[1];
        else return NULL;
    }
    else if(seatPos == 1){
        if(mPlayers.size() >= 3)
            return mPlayers[2];
        else return NULL;
    }
    else if(seatPos == 2){
        if(mPlayers.size() >= 1)
            return mPlayers[0];
        else return NULL;
    }
    else{
        return NULL;
    }
}

bool Room::allArePrepare()
{
    int playersNum = getPlayerNumbers();
    if(playersNum != 3){
        return false;
    }
    for(int i = 0; i < playersNum; i++){
        if(mPlayers[i]->getStatus() != Status_Type_IsPrepare){
            return false;
        }
    }
    return true;
}

void Room::setGameStatus(bool isInGame)
{
    mInGame = isInGame;
}

bool Room::isInGame()
{
    return mInGame;
}

void Room::initCards()
{
    CardInfo *cardInfo = NULL;
    for(int i = 3; i < 16; i++){
        cardInfo = new CardInfo;
        cardInfo->color = Card_Color_Spade;
        cardInfo->value = i;
        mCards.push_back(cardInfo);

        cardInfo = new CardInfo;
        cardInfo->color = Card_Color_Heart;
        cardInfo->value = i;
        mCards.push_back(cardInfo);

        cardInfo = new CardInfo;
        cardInfo->color = Card_Color_Club;
        cardInfo->value = i;
        mCards.push_back(cardInfo);

        cardInfo = new CardInfo;
        cardInfo->color = Card_Color_Diamond;
        cardInfo->value = i;
        mCards.push_back(cardInfo);
    }
    cardInfo = new CardInfo;
    cardInfo->color = Card_Color_King;
    cardInfo->value = 16;
    mCards.push_back(cardInfo);

    cardInfo = new CardInfo;
    cardInfo->color = Card_Color_King;
    cardInfo->value = 17;
    mCards.push_back(cardInfo);

}

void Room::resetRoomStatus()
{
    for(int i = 0; i < mPlayers.size(); i++){
        mPlayers[i]->resetStatus();
    }
    mInGame = false;
}

void Room::dealCards()
{
    QVector<CardInfo *> tmp = mCards;
    CardInfo* handCards[3][17];
    for(int j = 0; j < 3; j++){
        for(int i = 0; i < 17; i++){
            int r = rand()%tmp.size();
            handCards[j][i] = tmp[r];
            tmp.remove(r);
        }
    }
    CardInfo* underCards[3];
    for(int i = 0; i < 3; i++){
        underCards[i] = tmp[i];
    }
    int ownerPos = rand()%3;
    for(int i = 0; i < 3; i++){
        dealCardsToPlayer(i, handCards[i], underCards, ownerPos);
    }
    mInGame = true;

}

void Room::dealCardsToPlayer(int seat, CardInfo **handCards, CardInfo **underCards, int ownerPos)
{
    Player *player = getPlayerInfo(seat);
    QTcpSocket *sock = player->getTcpSock();
    MsgDealCards msgDealCards;
    for(int i = 0; i < 17; i++){
        msgDealCards.handCards[i] = *(handCards[i]);
    }
    for(int i = 0; i < 3; i++){
        msgDealCards.underCards[i] = *(underCards[i]);
    }
    if(ownerPos == seat){
        msgDealCards.ownerPos = Position_Mine;
    }
    else{
        if((ownerPos-seat) == 1 || (ownerPos-seat) == -2){
            msgDealCards.ownerPos = Position_Next;
        }
        else if((ownerPos-seat) == -1 || (ownerPos-seat) == 2){
            msgDealCards.ownerPos = Position_Prev;
        }
        else{
            qDebug() << "room::cpp----pos set err";
        }
    }
    char *data = NULL;
    MsgEncode(&msgDealCards, Msg_Type_DealCards, &data);
    qDebug() << data;
    sock->write(data);
    MsgFree(data);
}

void Room::slotStatusChanged(int status)
{
    Player *send = (Player *)sender();
    int seatPos = getSeat(send->getUserName());
    qDebug() << QString("room.cpp::93-----seat:%1 username:%2").arg(seatPos).arg(send->getUserName());
    Player *prevPlayer = prevPlayerInfo(seatPos);
    if(prevPlayer != NULL){
        MsgOtherStatusChanged msgOtherStatusChanged;
        strcpy(msgOtherStatusChanged.username, send->getUserName().toUtf8().data());
        msgOtherStatusChanged.status = status;
        msgOtherStatusChanged.seat = Position_Next;
        char *data = NULL;
        MsgEncode(&msgOtherStatusChanged, Msg_Type_OtherStatusChanged, &data);
        QTcpSocket *sock = prevPlayer->getTcpSock();
        sock->write(data);
        qDebug() << data;
        MsgFree(data);
    }
    Player *nextPlayer = nextPlayerInfo(seatPos);
    if(nextPlayer != NULL){
        MsgOtherStatusChanged msgOtherStatusChanged;
        strcpy(msgOtherStatusChanged.username, send->getUserName().toUtf8().data());
        msgOtherStatusChanged.status = status;
        msgOtherStatusChanged.seat = Position_Prev;
        char *data = NULL;
        MsgEncode(&msgOtherStatusChanged, Msg_Type_OtherStatusChanged, &data);
        QTcpSocket *sock = nextPlayer->getTcpSock();
        sock->write(data);
        qDebug() << data;
        MsgFree(data);
    }
}

void Room::slotQuitRob()
{
    Player *send = (Player *)sender();
    int seatPos = getSeat(send->getUserName());
    Player *nextPlayer = nextPlayerInfo(seatPos);
    Player *prevPlayer = prevPlayerInfo(seatPos);
    if(nextPlayer->getRobAble()){
        if(nextPlayer->getHasRobed() && !(prevPlayer->getRobAble())){
            slotImLandOwner(nextPlayer);
            return;
        }
        //send to next player;
        MsgOtherRob msgOtherRob;
        msgOtherRob.seat = Position_Prev;
        msgOtherRob.robRet = 0;
        msgOtherRob.nextRober = Position_Mine;
        char *data = NULL;
        MsgEncode(&msgOtherRob, Msg_Type_OtherRob, &data);
        QTcpSocket *sock = nextPlayer->getTcpSock();
        sock->write(data);
        qDebug() << data;
        MsgFree(data);

        //send to prev player
        msgOtherRob.seat = Position_Next;
        msgOtherRob.nextRober = Position_Prev;
        MsgEncode(&msgOtherRob, Msg_Type_OtherRob, &data);
        sock = prevPlayer->getTcpSock();
        sock->write(data);
        qDebug() << data;
        MsgFree(data);
        return;
    }
    else if(prevPlayer->getRobAble()){
        if(prevPlayer->getHasRobed()){
            slotImLandOwner(prevPlayer);
            return;
        }
        //send to next player;
        MsgOtherRob msgOtherRob;
        msgOtherRob.seat = Position_Prev;
        msgOtherRob.robRet = 0;
        msgOtherRob.nextRober = Position_Next;
        char *data = NULL;
        MsgEncode(&msgOtherRob, Msg_Type_OtherRob, &data);
        QTcpSocket *sock = nextPlayer->getTcpSock();
        sock->write(data);
        qDebug() << data;
        MsgFree(data);

        //send to prev player
        msgOtherRob.seat = Position_Next;
        msgOtherRob.nextRober = Position_Mine;
        MsgEncode(&msgOtherRob, Msg_Type_OtherRob, &data);
        sock = prevPlayer->getTcpSock();
        sock->write(data);
        qDebug() << data;
        MsgFree(data);
        return;
    }
    else{
        qDebug() << "no one rob restart----";
    }
}

void Room::slotJoinRob()
{
    Player *send = (Player *)sender();
    int seatPos = getSeat(send->getUserName());
    Player *nextPlayer = nextPlayerInfo(seatPos);
    Player *prevPlayer = prevPlayerInfo(seatPos);

    if((!nextPlayer->getRobAble()) && (!prevPlayer->getRobAble())){
        slotImLandOwner(send);
    }
    else if(nextPlayer->getRobAble()){
        //send to next player;
        MsgOtherRob msgOtherRob;
        msgOtherRob.seat = Position_Prev;
        msgOtherRob.robRet = 1;
        msgOtherRob.nextRober = Position_Mine;
        char *data = NULL;
        MsgEncode(&msgOtherRob, Msg_Type_OtherRob, &data);
        QTcpSocket *sock = nextPlayer->getTcpSock();
        sock->write(data);
        qDebug() << data;
        MsgFree(data);

        //send to prev player
        msgOtherRob.seat = Position_Next;
        msgOtherRob.nextRober = Position_Prev;
        MsgEncode(&msgOtherRob, Msg_Type_OtherRob, &data);
        sock = prevPlayer->getTcpSock();
        sock->write(data);
        qDebug() << data;
        MsgFree(data);
        return;
    }
    else if(prevPlayer->getRobAble()){
        //send to next player;
        MsgOtherRob msgOtherRob;
        msgOtherRob.seat = Position_Prev;
        msgOtherRob.robRet = 1;
        msgOtherRob.nextRober = Position_Next;
        char *data = NULL;
        MsgEncode(&msgOtherRob, Msg_Type_OtherRob, &data);
        QTcpSocket *sock = nextPlayer->getTcpSock();
        sock->write(data);
        qDebug() << data;
        MsgFree(data);

        //send to prev player
        msgOtherRob.seat = Position_Next;
        msgOtherRob.nextRober = Position_Mine;
        MsgEncode(&msgOtherRob, Msg_Type_OtherRob, &data);
        sock = prevPlayer->getTcpSock();
        sock->write(data);
        qDebug() << data;
        MsgFree(data);
        return;
    }

}

void Room::slotImLandOwner(Player *send)
{
    int seatPos = getSeat(send->getUserName());
    Player *nextPlayer = nextPlayerInfo(seatPos);
    Player *prevPlayer = prevPlayerInfo(seatPos);

    send->setRole(Role_LandOwner);
    nextPlayer->setRole(Role_Farmer);
    prevPlayer->setRole(Role_Farmer);

    //send to mine
    MsgRobResult msgRobResult;
    char *data = NULL;
    msgRobResult.landOwnerPos = Position_Mine;
    QTcpSocket *sock = send->getTcpSock();
    MsgEncode(&msgRobResult, Msg_Type_RobResult, &data);
    sock->write(data);
    MsgFree(data);

    //send to next player
    msgRobResult.landOwnerPos = Position_Prev;
    sock = nextPlayer->getTcpSock();
    MsgEncode(&msgRobResult, Msg_Type_RobResult, &data);
    sock->write(data);
    MsgFree(data);

    //send to prev player
    msgRobResult.landOwnerPos = Position_Next;
    sock = prevPlayer->getTcpSock();
    MsgEncode(&msgRobResult, Msg_Type_RobResult, &data);
    sock->write(data);
    MsgFree(data);
}


