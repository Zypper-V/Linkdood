#include "sysmsgcontroler.h"
#include "IMClient.h"
#include "ISysMsgService.h"
#include "INotifyService.h"
#include <QDebug>

SysMsgControler::SysMsgControler(QObject *parent) : QObject(parent)
{
    service::IMClient::getClient()->getNotify()->setSysMsgObserver(this);
}

void SysMsgControler::onSysMessageNotice(SysMsg &msg)
{
    qDebug()<<Q_FUNC_INFO;
    IMSysMsg sysMsg;
    sysMsg.msgid = QString::number(msg.msgid);
    sysMsg.targetid = QString::number(msg.targetid);
    sysMsg.time = dealTime(msg.time, 1);
    sysMsg.respons.clear();
    sysMsg.info = QString::fromStdString(msg.info);
    sysMsg.name =QString::fromStdString(msg.name);
    sysMsg.avatar = QString::fromStdString(msg.avatar);
    sysMsg.msgType = QString::number(msg.msgtype);
    if(msg.msgtype == 1)
    {
        sysMsg.msgtypeText = "好友申请";
        sysMsg.isShowButton = true;
    }
    else if(msg.msgtype == 2)
    {
        sysMsg.msgtypeText = "好友验证信息";
//        if(msg.opertype == 1)
//            sysMsg.respons = "已同意";
//        else if(msg.opertype == 2)
//            sysMsg.respons = "已拒绝";
        sysMsg.isShowButton = false;
    }
    else if(msg.msgtype == 3)
    {
        sysMsg.msgtypeText = "群请求";
        sysMsg.isShowButton = true;
    }
    else
    {
        sysMsg.msgtypeText = "群验证信息";

        qDebug()<<Q_FUNC_INFO << "0_____________________________msg.opertype:" << msg.opertype << "  sysMsg.info:" << sysMsg.info;
        if(msg.opertype == 5)
        {
            sysMsg.info = sysMsg.name + "被解散";
             qDebug()<<Q_FUNC_INFO << "  sysMsg.info:" << sysMsg.info;
        }
        else if(msg.opertype == 6)
        {
            sysMsg.info = "您被移出了群 " + sysMsg.name;
        }
        sysMsg.isShowButton = false;
    }  

    qDebug() << Q_FUNC_INFO << "  msgid:" << sysMsg.msgid << "   targetid:" << sysMsg.targetid << "  time:" << sysMsg.time << "   msgtypeText:" << sysMsg.msgtypeText << "   respons:" << sysMsg.respons << "   name:" << sysMsg.name << "   avatar:" << sysMsg.avatar << "   info:" << sysMsg.info;
    emit sysMessageNotice(sysMsg);
}

void SysMsgControler::response(IMSysMsgRespInfo info)
{
    qDebug()<<Q_FUNC_INFO;
    SysMsgRespInfo item;
    item.info = info.info.toStdString();
    item.msgid = info.msgid.toLongLong();
    item.msgtype = info.msgtype;
    item.targetid = info.targetid.toLongLong();
    if(item.msgtype == 1 || item.msgtype == 2)
    {
        if(info.opertype == 1)
            item.opertype = 1;  //同意
        else if(info.opertype == 0)
            item.opertype = 2;  //拒绝
    }
    if(item.msgtype == 3 || item.msgtype == 4)
    {
        if(info.opertype == 1)
            item.opertype = 2;  //同意
        else if(info.opertype == 0)
            item.opertype = 3;   //拒绝
    }
    qDebug()<<Q_FUNC_INFO << "info:" << item.info.c_str() << " msgid:" << item.msgid << "  msgtype:" << item.msgtype << "  targetid:" << item.targetid << "  opertype:" << item.opertype;
    setSysMessagRead(item.msgtype, info.msgid);
    service::IMClient::getClient()->getSysMsg()->response(item,std::bind(&SysMsgControler::_response,this,std::placeholders::_1));
}

void SysMsgControler::getSysMessages(int type, int count, QString msgid, int flag)
{
    qDebug()<<Q_FUNC_INFO;
    service::IMClient::getClient()->getSysMsg()->getMessages(type,count,msgid.toLongLong(),flag,std::bind(&SysMsgControler::_getSysMessages,this,std::placeholders::_1,std::placeholders::_2));
}

void SysMsgControler::_response(service::ErrorInfo &info)
{
    qDebug()<<Q_FUNC_INFO;
//    emit responseResult(info.code());
}

void SysMsgControler::_getSysMessages(service::ErrorInfo info, std::vector<SysMsg> sysmsgs)
{
    qDebug()<<Q_FUNC_INFO;
    IMSysMsgList msgList;
    IMSysMsg sysMsg;
    for(int i = 0; i < sysmsgs.size(); i++)
    {       
        qDebug() << "sysmsgs_name:" << sysmsgs[i].name.c_str() << "  operType:" << sysmsgs[i].opertype;
        sysMsg.respons.clear();
        sysMsg.isShowButton = false;
        sysMsg.msgid = QString::number(sysmsgs[i].msgid);
        sysMsg.targetid = QString::number(sysmsgs[i].targetid);
        sysMsg.time = dealTime(sysmsgs[i].time, 1);
        sysMsg.respons.clear();      
        sysMsg.name =QString::fromStdString(sysmsgs[i].name);
        sysMsg.avatar = QString::fromStdString(sysmsgs[i].avatar);
        sysMsg.msgType = QString::number(sysmsgs[i].msgtype);
        sysMsg.info = QString::fromStdString(sysmsgs[i].info);

        if(sysmsgs[i].msgtype == 1)
        {
            sysMsg.msgtypeText = "好友申请";
            if(sysmsgs[i].isread == 0) //未读
                sysMsg.isShowButton = true;
            else
            {
                if(sysmsgs[i].opertype == 1)
                    sysMsg.respons = "已同意";
                else if(sysmsgs[i].opertype == 2)
                    sysMsg.respons = "已拒绝";
            }
        }
        else if(sysmsgs[i].msgtype == 2)
        {
            sysMsg.msgtypeText = "好友验证信息";
        }
        else if(sysmsgs[i].msgtype == 3)
        {
            sysMsg.msgtypeText = "群请求";
            if(sysmsgs[i].isread == 0)
                sysMsg.isShowButton = true;
            else
            {
                if(sysmsgs[i].opertype == 3)
                    sysMsg.respons = "已拒绝";
                else if(sysmsgs[i].opertype == 2)
                    sysMsg.respons = "已同意";
            }
        }
        else
        {
            sysMsg.msgtypeText = "群验证信息";
            if(sysmsgs[i].opertype == 5)
            {
                sysMsg.info = QString::fromStdString(sysmsgs[i].name) + "被解散";
                 qDebug()<<Q_FUNC_INFO << "  sysMsg.info:" << sysMsg.info;
            }
            else if(sysmsgs[i].opertype == 6)
            {
                sysMsg.info = "您被移出了群 " + QString::fromStdString(sysmsgs[i].name);
            }
        }


        qDebug() << "  msgid:" << sysMsg.msgid << "   targetid:" << sysMsg.targetid << "  time:" << sysMsg.time << "   msgtypeText:" << sysMsg.msgtypeText << "   respons:" << sysMsg.respons << "   name:" << sysMsg.name << "   avatar:" << sysMsg.avatar << "   info:" << sysMsg.info;
        msgList.push_back(sysMsg);
    }
    emit getSysMessagesReult(info.code(), msgList);
}

void SysMsgControler::setSysMessagRead(int type, QString msg)
{
    qDebug()<<Q_FUNC_INFO << "msgtype:" << type << "   msgid:" << msg;
    std::vector<int64> list;
    list.push_back(msg.toLongLong());
    service::IMClient::getClient()->getSysMsg()->setMessagRead(type,list);
}

QString SysMsgControler::dealTime(qint64 msgtime, int type)
{
    QString strDateTime("");
    QDateTime msgDateTime;
    int distance = 0;
    if (!msgtime)
    {
        return strDateTime;
    }
    msgDateTime.setMSecsSinceEpoch(msgtime);
    distance = msgDateTime.daysTo(QDateTime::currentDateTime());
    //今天
    if (qFabs(distance) <= 0)
    {
        strDateTime = msgDateTime.toString("HH:mm");
    }
    //昨天
    else if (qFabs(distance) <= 1)
    {
        if ( 1 == type)
        {
            strDateTime = "昨天";
        }
        else {
            strDateTime = "昨天" + QString::fromLocal8Bit(" ") + msgDateTime.toString("HH:mm");
        }

    }
    //前天
    else if (qFabs(distance) <= 2)
    {
        if (1 == type)
        {
            strDateTime = "前天";
        }
        else {
            strDateTime = "前天" + QString::fromLocal8Bit(" ") + msgDateTime.toString("HH:mm");
        }
    }
    else
    {
        if (1 == type)
        {
            strDateTime = msgDateTime.toString("MM月dd日");
        }
        else {
            strDateTime = msgDateTime.toString("MM月dd日") +QString::fromLocal8Bit(" ")+msgDateTime.toString("HH:mm");
        }
    }
    return strDateTime;
}
