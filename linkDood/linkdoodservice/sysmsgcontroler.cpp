#include "sysmsgcontroler.h"
#include "IMClient.h"
#include "ISysMsgService.h"
#include "INotifyService.h"
#include <QDebug>
#include "common.h"
void SysMsgControler::init()
{
    service::IMClient::getClient()->getNotify()->setSysMsgObserver(this);
}

SysMsgControler::SysMsgControler(QObject *parent) : QObject(parent)
{

}

void SysMsgControler::onSysMessageNotice(SysMsg &msg)
{
    qDebug()<<Q_FUNC_INFO;
    IMSysMsg sysMsg;
    sysMsg.msgid = QString::number(msg.msgid);
    sysMsg.targetid = QString::number(msg.targetid);
    sysMsg.time =QString::number(msg.time)/* Common:: dealTime(msg.time, 1)*/;
    sysMsg.respons.clear();
    sysMsg.info = QString::fromStdString(msg.info);
    sysMsg.name =QString::fromStdString(msg.name);
    sysMsg.avatar = QString::fromStdString(msg.avatar);
    sysMsg.msgType = QString::number(msg.msgtype);
    sysMsg.operUser = QString::fromStdString(msg.operUser);
    sysMsg.isread = QString::number(msg.isread);

    qDebug()<<Q_FUNC_INFO<<msg.msgtype<<":"<<msg.subtype<<":"<<msg.opertype;
    if(msg.msgtype == 1)
    {
        sysMsg.msgtypeText = "好友申请";
        sysMsg.isShowButton = true;
    }
    else if(msg.msgtype == 2)
    {
        sysMsg.msgtypeText = "好友验证信息";
        sysMsg.isShowButton = false;
        if(msg.subtype ==0 && msg.opertype==2){
            sysMsg.info = sysMsg.operUser + "拒绝了您的好友申请";
        }
    }
    else if(msg.msgtype == 3)
    {
        if(msg.subtype == 1)
        {
            sysMsg.msgtypeText = "群邀请";
            sysMsg.info = sysMsg.operUser + "邀请您加入" + sysMsg.name;
        }
        else if(msg.subtype == 2){
            sysMsg.msgtypeText = "群请求";
        }
        sysMsg.isShowButton = true;
    }
    else
    {
        sysMsg.msgtypeText = "群验证信息";

        if(msg.opertype == 2)
        {
            sysMsg.info = sysMsg.operUser + "同意您加入" + sysMsg.name;
        }
        else if(msg.opertype == 3)
        {
            sysMsg.info = sysMsg.operUser + "拒绝您加入" + sysMsg.name;
        }
        else if(msg.opertype == 5){
            if(msg.name == "#" || msg.name == ""){
                return;
            }
            sysMsg.info = sysMsg.operUser + "解散了群" + sysMsg.name;
            qDebug()<<Q_FUNC_INFO << "  sysMsg.info:" << sysMsg.info;
        }
        else if(msg.opertype == 6)
        {
            if(sysMsg.name.size() == 0)
            {
                sysMsg.name = sysMsg.targetid;
            }
            sysMsg.info = "您被" + sysMsg.operUser + "移出了群" + sysMsg.name;
        }
        else if(msg.opertype == 7)
        {
            if(sysMsg.name.size() == 0)
                sysMsg.name = sysMsg.targetid;
            sysMsg.info = sysMsg.operUser + "主动退出了群" +sysMsg.name;
        }
        sysMsg.isShowButton = false;
    }

    qDebug() << Q_FUNC_INFO << "  msgid:" << sysMsg.msgid << "   targetid:" << sysMsg.targetid << "  time:" << sysMsg.time << "   msgtypeText:" << sysMsg.msgtypeText << "   respons:" << sysMsg.respons << "   name:" << sysMsg.name << "   avatar:" << sysMsg.avatar  << "operUser:" << sysMsg.operUser << "   info:" << sysMsg.info << "   operUser:" << sysMsg.operUser << "sysMsg.isRead:" << sysMsg.isread;
    emit sysMessageNotice(sysMsg);

    QString path = APP_DATA_PATH;
    QString fileName = path+ "config.ini";
    QSettings settings(fileName, QSettings::IniFormat);

    bool ret = settings.value("isSysPage",false).toBool();
    if(!ret){
        emit systemMessageNotice(sysMsg.info,msg.time);
    }
}

void SysMsgControler::response(IMSysMsgRespInfo info)
{
    qDebug()<<Q_FUNC_INFO<<info.info<<" "<<info.msgid<<" "<<info.msgtype<<" "<<info.targetid;
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
        item.msgtype=1;
    }
    if(item.msgtype == 3 || item.msgtype == 4)
    {
        if(info.opertype == 1)
            item.opertype = 2;  //同意
        else if(info.opertype == 0)
            item.opertype = 3;   //拒绝
        item.msgtype=2;
    }
    qDebug()<<Q_FUNC_INFO << "info:" << item.info.c_str() << " msgid:" << item.msgid << "  msgtype:" << item.msgtype << "  targetid:" << item.targetid << "  opertype:" << item.opertype;
    setSysMessagRead(info.msgtype, info.msgid);
    service::IMClient::getClient()->getSysMsg()->response(item,std::bind(&SysMsgControler::_response,this,std::placeholders::_1));
}

void SysMsgControler::getSysMessages(int type, int count, QString msgid, int flag)
{
    qDebug()<<Q_FUNC_INFO;
    service::IMClient::getClient()->getSysMsg()->getMessages(type,count,msgid.toLongLong(),flag,std::bind(&SysMsgControler::_getSysMessages,this,std::placeholders::_1,std::placeholders::_2));
}

void SysMsgControler::removeSysMessage(QString type,QString msgid)
{
    qDebug()<<Q_FUNC_INFO<<msgid;
    std::vector<int64> msgs;
    msgs.push_back(msgid.toLongLong());
    service::IMClient::getClient()->getSysMsg()->removeMessages(type.toInt(),msgs,std::bind(&SysMsgControler::_removeSysMessage,this,std::placeholders::_1));
}

void SysMsgControler::_removeSysMessage(service::ErrorInfo info)
{
    qDebug()<<Q_FUNC_INFO<<info.code();
    emit removeSysMessageResult(QString::number(info.code()));
}

void SysMsgControler::_response(service::ErrorInfo &info)
{
    qDebug()<<Q_FUNC_INFO<<"code:"<<info.code();
    //    emit responseResult(info.code());
}

void SysMsgControler::_getSysMessages(service::ErrorInfo info, std::vector<SysMsg> sysmsgs)
{
    qDebug()<<Q_FUNC_INFO;
    IMSysMsgList msgList;

    for(int i = 0; i < sysmsgs.size(); i++)
    {
        IMSysMsg sysMsg;
        sysMsg.respons.clear();
        sysMsg.isShowButton = false;
        sysMsg.msgid = QString::number(sysmsgs[i].msgid);
        sysMsg.targetid = QString::number(sysmsgs[i].targetid);
        sysMsg.time = QString::number(sysmsgs[i].time)/*Common::dealTime(sysmsgs[i].time, 1)*/;
        sysMsg.respons.clear();
        sysMsg.name =QString::fromStdString(sysmsgs[i].name);
        sysMsg.avatar = QString::fromStdString(sysmsgs[i].avatar);
        sysMsg.msgType = QString::number(sysmsgs[i].msgtype);
        sysMsg.info = QString::fromStdString(sysmsgs[i].info);
        sysMsg.operUser = QString::fromStdString(sysmsgs[i].operUser);
        sysMsg.isread = QString::number(sysmsgs[i].isread);

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
                else{
                    sysMsg.respons = "已处理";
                }
            }
        }
        else if(sysmsgs[i].msgtype == 2)
        {
            sysMsg.msgtypeText = "好友验证信息";
            if(sysmsgs[i].subtype ==0 && sysmsgs[i].opertype==2){
                sysMsg.info = sysMsg.operUser + "拒绝了您的好友申请";
            }
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
            if(sysmsgs[i].opertype == 2)
            {
                sysMsg.info = sysMsg.operUser + "同意您加入" + sysMsg.name;
            }
            else if(sysmsgs[i].opertype == 3)
            {
                sysMsg.info = sysMsg.operUser + "拒绝您加入" + sysMsg.name;
            }
            else if(sysmsgs[i].opertype == 5)
            {
                if(sysMsg.name == "#" || sysMsg.name =="")
                {
                    continue;
                }
                sysMsg.info = sysMsg.operUser + "解散了群" + sysMsg.name;
                qDebug()<<Q_FUNC_INFO << "  sysMsg.info:" << sysMsg.info;
            }
            else if(sysmsgs[i].opertype == 6)
            {
                if(sysMsg.name.size() == 0)
                {
                    sysMsg.name = sysMsg.targetid;
                }
                sysMsg.info = "您被" + sysMsg.operUser + "移出了群" + sysMsg.name;
            }
            else if(sysmsgs[i].opertype == 7)
            {
                if(sysMsg.name.size() == 0)
                    sysMsg.name = sysMsg.targetid;
                sysMsg.info = sysMsg.operUser + "主动退出了群" +sysMsg.name;
            }
        }
        if(!sysMsg.isShowButton){
            setSysMessagRead(sysMsg.msgType.toInt(),sysMsg.msgid);
        }
        qDebug() << "  msgid:" << sysMsg.msgid << "   targetid:" << sysMsg.targetid << "  time:" << sysMsg.time << "   msgtypeText:" << sysMsg.msgtypeText << "   respons:" << sysMsg.respons << "   name:" << sysMsg.name << "   avatar:" << sysMsg.avatar << "  operUser:" << sysMsg.operUser << "   info:" << sysMsg.info;
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

