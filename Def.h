#ifndef DEF_H
#define DEF_H

#ifdef __cplusplus
extern "C" {
#endif

#define MYDEBUG 0     //1是ip标识  0是端口标示


#define CLT_PORT 8888
#define SERV_PORT 9001
#define TCPServer_PORT 9002
#define SERV_IP "192.168.195.254"
//#define SERV_IP "192.168.14.159"

#define Type_Base                      1000

//消息类型宏(客户端消息)
#define Msg_Type_Base                   Type_Base+100
#define Msg_Type_LoginReq               Msg_Type_Base+1  //登录请求消息
#define Msg_Type_RegReq                 Msg_Type_Base+2  //注册请求消息
#define Msg_Type_CreateRoomReq          Msg_Type_Base+3  //创建房间请求消息
#define Msg_Type_JoinRoomReq            Msg_Type_Base+4  //加入房间请求消息
#define Msg_Type_Prepare                Msg_Type_Base+5  //准备消息
#define Msg_Type_CanclePrepare          Msg_Type_Base+6  //取消准备消息
#define Msg_Type_Rob                    Msg_Type_Base+7  //抢地主请求消息
#define Msg_Type_Pass                   Msg_Type_Base+8  //不要牌消息
#define Msg_Type_OutCard                Msg_Type_Base+9  //出牌消息
#define Msg_Type_GameOverReq            Msg_Type_Base+10 //游戏结束消息（客户端发送给服务器）
#define Msg_Type_LeaveRoom              Msg_Type_Base+11 //离开房间消息

//消息类型宏（服务器消息）
#define Msg_Type_LoginRes               Msg_Type_Base+101 //登录应答消息
#define Msg_Type_RegRes                 Msg_Type_Base+102 //注册应答消息
#define Msg_Type_CreateRoomRes          Msg_Type_Base+103 //创建房间应答消息
#define Msg_Type_JoinRoomRes            Msg_Type_Base+104 //加入房间应答消息
#define Msg_Type_OtherStatusChanged     Msg_Type_Base+105 //房间中其他玩家状态改变消息
#define Msg_Type_DealCards              Msg_Type_Base+106 //服务器发牌消息
#define Msg_Type_OtherRob               Msg_Type_Base+107 //其他人抢地主消息
#define Msg_Type_RobResult              Msg_Type_Base+108 //抢地主结果消息
#define Msg_Type_OtherPass              Msg_Type_Base+109 //其他人不要牌消息
#define Msg_Type_OtherOutCard           Msg_Type_Base+110 //其他人出牌消息
#define Msg_Type_GameOver               Msg_Type_Base+111 //游戏结束消息（服务器通知客户端）
#define Msg_Type_OtherLeaveRoom         Msg_Type_Base+112 //其他人离开房间消息

//玩家状态
#define Status_Type_Base                Type_Base+500
#define Status_Type_NotInRoom           Status_Type_Base+1 //不在房间状态
#define Status_Type_NotPrepare          Status_Type_Base+2 //在房间但未准备状态
#define Status_Type_IsPrepare           Status_Type_Base+3 //在房间已准备状态
#define Status_Type_Playing             Status_Type_Base+4 //正在游戏中状态

//相对位置
#define Position_Prev                   1    //上手位位置标记
#define Position_Next                   2    //下手位位置
#define Position_Mine                   3    //自己位置

//牌的花色
#define Card_Color_Spade                1    //黑桃
#define Card_Color_Heart                2    //红桃
#define Card_Color_Club                 3    //梅花
#define Card_Color_Diamond              4    //方块
#define Card_Color_King                 5    //王

//牌型
#define WRONG 0
#define SOLA 1 //单张牌
#define PAIR 2 //对子
#define KING_PAIR 3 //王炸
#define SAN 4//三个
#define SAN_ADD_ONE 5 //三带一
#define SAN_ADD_TWO 6 //三带一对
#define BOOM 7  //炸弹
#define ORDER 8 //顺子
#define BOOM_ADD_TWO 9  //四带二
#define DOUBLE_ORDER 10 //连对
#define FLY 11  //飞机
#define FLY_AND_ONE 12 //飞机都带单
#define FLY_AND_TWO 13 //飞机都带对

//身份
#define Role_LandOwner                  1    //地主
#define Role_Farmer                     2    //农民



#ifdef __cplusplus
}
#endif
#endif // DEF_H
