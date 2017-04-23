#include "Player.h"

Player::Player(QString username, QObject *parent) :
    QObject(parent)
{
    mUserName = username;
    mTcpSock = NULL;
    mStatus = 0;
    mRobAble = true;
    mHasRobed = false;

    connect(this, SIGNAL(sigStatusChanged(int)), parent, SLOT(slotStatusChanged(int)));
    connect(this, SIGNAL(sigImLandOwner(Player*)), parent, SLOT(slotImLandOwner(Player*)));
    connect(this, SIGNAL(sigQuitRob()), parent, SLOT(slotQuitRob()));
    connect(this, SIGNAL(sigJoinRob()), parent, SLOT(slotJoinRob()));
}

void Player::setTcpSock(QTcpSocket *pTcpsock)
{
    mTcpSock = pTcpsock;
}

void Player::setClientIP(QHostAddress clientIP)
{
    mClientIP = clientIP;
}

void Player::setStatus(int status)
{
    mStatus = status;
    emit sigStatusChanged(mStatus);
}

void Player::setHasRobed(bool b)
{
    if(mHasRobed){
        emit sigImLandOwner(this);
    }
    else{
        mHasRobed = b;
        emit sigJoinRob();
    }
}

void Player::setRobAble(bool b)
{
    mRobAble = b;
    emit sigQuitRob();
}

void Player::setRole(int role)
{
    mRole = role;
}

const QString &Player::getUserName() const
{
    return mUserName;
}

int Player::getStatus()
{
    return mStatus;
}

QTcpSocket *Player::getTcpSock()
{
    return mTcpSock;
}

bool Player::getRobAble()
{
    return mRobAble;
}

bool Player::getHasRobed()
{
    return mHasRobed;
}

int Player::getRole()
{
    return mRole;
}

void Player::resetStatus()
{
     mStatus = 0;
     mHasRobed = false;
     mRobAble = true;
}
