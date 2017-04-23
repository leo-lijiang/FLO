#ifndef ROOM_H
#define ROOM_H

#include <QObject>
#include "Player.h"
#include <QVector>
#include "MsgMng.h"

class Room : public QObject
{
    Q_OBJECT
public:
    explicit Room(int roomNum, QObject *parent = 0);
    ~Room();
    void addPlayer(Player *player);
    void removePlayer(int pos);
    int getRoomNum();
    int getPlayerNumbers();
    int getSeat(QString username);
    Player* getPlayerInfo(int seatPos);
    Player* prevPlayerInfo(int seatPos);
    Player* nextPlayerInfo(int seatPos);
    bool allArePrepare();
    void setGameStatus(bool isInGame);
    bool isInGame();
    void initCards();
    void resetRoomStatus();

    //发牌
    void dealCards();
    void dealCardsToPlayer(int seat, CardInfo **handCards, CardInfo **underCards, int ownerPos);

signals:

public slots:
    void slotStatusChanged(int status);
    void slotQuitRob();
    void slotJoinRob();
    void slotImLandOwner(Player *send);
public:
    static const int mMaxPlayerNum = 3;
private:

    QVector<Player *> mPlayers;
    int mRoomNum;//房间编号
    QVector<CardInfo *> mCards;
    bool mInGame;
};

#endif // ROOM_H
