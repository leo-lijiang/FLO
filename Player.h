#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QString>
#include <QTcpSocket>
#include <QHostAddress>

class Player : public QObject
{
    Q_OBJECT
public:
    explicit Player(QString username, QObject *parent = 0);

    void setTcpSock(QTcpSocket *pTcpsock);
    void setClientIP(QHostAddress clientIP);
    void setStatus(int status);
    void setHasRobed(bool b);
    void setRobAble(bool b);
    void setRole(int role);
    const QString& getUserName() const;
    int getStatus();
    QTcpSocket *getTcpSock();
    bool getRobAble();
    bool getHasRobed();
    int getRole();

    void resetStatus();
signals:
    void sigStatusChanged(int status);
    void sigImLandOwner(Player *player);
    void sigQuitRob();
    void sigJoinRob();
public slots:

private:
    QString mUserName;
    QTcpSocket *mTcpSock;
    QHostAddress mClientIP;
    int mStatus;
    bool mHasRobed;
    bool mRobAble;
    int mRole;
};

#endif // PLAYER_H
