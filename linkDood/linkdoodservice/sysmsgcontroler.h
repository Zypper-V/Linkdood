#ifndef SYSMSGCONTROLER_H
#define SYSMSGCONTROLER_H

#include <QObject>
#include "ISysMsgObserver.h"
#include "ErrorInfo.hpp"
#include "linkdoodtypes.h"

class SysMsgControler : public QObject,public ISysMsgObserver
{
    Q_OBJECT
public:
    explicit SysMsgControler(QObject *parent = 0);

    /*********************************************
    * @brief onSysMessageNotice
    * @description: 监听系统消息
    * @param[in] msg 传入消息
    *********************************************/
    void onSysMessageNotice(SysMsg& msg);

    /************************************
    * @brief response
    * @description: 回应
    * @param[in] userid 传入消息回应信息
    * @param[in] await  传入接收结果回调
    ************************************/
    void response(IMSysMsgRespInfo info);

    /***********************************************
    * @brief setMessagRead
    * @description: 设置消息已读
    * @param[in] type 传入操作类型1 好友请求验证框已读|2 好友请求返回框已读| 3 设置验证请求消息已读|4 设置群验证响应消息已读
    * @param[in] msgs 传入消息id
    ************************************************/
    void setSysMessagRead(int type, QString msg);

    /**********************************************
    * @brief getMessages
    * @description: 获取消息
    * @param[in] type  传入响应消息类型 0 全部 1 加好友请求 2 加好友响应 3 加群请求 4 加群
    * @param[in] count 传入数量
    * @param[in] msgid 传入消息id
    * @param[in] flag   传入偏移标志 0 向上偏移 1 向下偏移
    **********************************************/
    void getSysMessages(int type,int count,QString msgid,int flag);

signals:
    //系统消息推送
    void sysMessageNotice(IMSysMsg msg);
    void getSysMessagesReult(int code, IMSysMsgList sysMsgList);
//    void responseResult(int code);
public slots:
private:
    //处理时间显示
    //type 1 会话列表时间 2聊天界面时间
    QString dealTime(qint64 msgtime,int type);

    void _response(service::ErrorInfo& info);
    void _getSysMessages(service::ErrorInfo info,std::vector<SysMsg> sysmsgs);
};

#endif // SYSMSGCONTROLER_H
