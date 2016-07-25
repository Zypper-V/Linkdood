#include "cdoodsysmsgmanager.h"

CDoodSysMsgManager::CDoodSysMsgManager(LinkDoodClient *client, QObject *parent)
    : CDoodListModel(parent), m_pClient(client)
{
    qDebug() << Q_FUNC_INFO;
    qRegisterMetaType<CDoodSysMsgManager*>();
    initConnect();
}

void CDoodSysMsgManager::clickItem(QString id, bool isAgree)
{
    CDoodSysmsgItem* item = m_contactListMap[id];
    if(item != NULL){
        IMSysMsgRespInfo info;
        info.info = "";
        info.msgid = item->msgid();
        info.msgtype = item->msgType().toInt();
        info.targetid = item->targetid();
        info.opertype = isAgree?1:0;

        item->setIsShowButton(false);
        QString text = isAgree?"已同意":"已拒绝";

        item->setRespons(text);
        response(info);
    }
}

void CDoodSysMsgManager::clearListView()
{
    if(m_contactListMap.size() <= 0)
        return;

    QMap<QString, CDoodSysmsgItem*>::const_iterator i = m_contactListMap.constBegin();
    while (i != m_contactListMap.constEnd()) {
        removeItem(m_contactListMap[i.key()]);
        delete m_contactListMap[i.key()];
        m_contactListMap[i.key()] = 0;
        ++i;
    }
    m_contactListMap.clear();
}

void CDoodSysMsgManager::getSysMessages(int type, int count, QString msgid, int flag)
{
    qDebug() << Q_FUNC_INFO;
    m_pClient->getSysMessages(type, count, msgid, flag);
}

void CDoodSysMsgManager::setSysMessagRead(int type, QString msg)
{
    qDebug() << Q_FUNC_INFO;
    m_pClient->setSysMessagRead(type, msg);
}

void CDoodSysMsgManager::response(IMSysMsgRespInfo info)
{
    qDebug() << Q_FUNC_INFO << "targetid:" << info.targetid << "   msgid:" << info.msgid << "  msgtype:" << info.msgtype << "   opertype:" << info.opertype << "  info:" << info.info;
    m_pClient->response(info);
}

void CDoodSysMsgManager::addItemToListView(IMSysMsg sysMsg)
{
    CDoodSysmsgItem* item = new CDoodSysmsgItem(this);
    item->setAvatar(sysMsg.avatar);
    item->setInfo(sysMsg.info);
    item->setIsShowButton(sysMsg.isShowButton);
    item->setMsgid(sysMsg.msgid);
    item->setMsgtypeText(sysMsg.msgtypeText);
    item->setName(sysMsg.name);
    item->setRespons(sysMsg.respons);
    item->setTargetid(sysMsg.targetid);
    item->setTime(sysMsg.time);
    item->setMsgType(sysMsg.msgType);
    addItemBegin(item);

    qDebug()<<Q_FUNC_INFO<<"name:"<<sysMsg.name<<"info:"<<sysMsg.info<<"isShowBtn:"<<sysMsg.isShowButton<<"respons:"<<sysMsg.respons;
    m_contactListMap[sysMsg.msgid] = item;
}

void CDoodSysMsgManager::modifyItemToListView(IMSysMsg sysMsg)
{
    CDoodSysmsgItem* item = m_contactListMap[sysMsg.msgid];
    if(item != NULL){
        removeItem(item);

        item->setAvatar(sysMsg.avatar);
        item->setInfo(sysMsg.info);
        item->setIsShowButton(sysMsg.isShowButton);
        item->setMsgid(sysMsg.msgid);
        item->setMsgtypeText(sysMsg.msgtypeText);
        item->setName(sysMsg.name);
        item->setRespons(sysMsg.respons);
        item->setTargetid(sysMsg.targetid);
        item->setTime(sysMsg.time);
        item->setMsgType(sysMsg.msgType);
        addItemBegin(item);
        qDebug()<<Q_FUNC_INFO<<"name:"<<sysMsg.name<<"info:"<<sysMsg.info<<"isShowBtn:"<<sysMsg.isShowButton<<"respons:"<<sysMsg.respons;
    }
}

void CDoodSysMsgManager::onSysMessageNotice(IMSysMsg sysMsg)
{
    qDebug() << Q_FUNC_INFO;
    if(!m_contactListMap.contains(sysMsg.msgid)){
        addItemToListView(sysMsg);
    }else{
        modifyItemToListView(sysMsg);
    }
}

void CDoodSysMsgManager::onGetSysMessages(int code, IMSysMsgList sysmsgList)
{
    qDebug() << Q_FUNC_INFO;
    for(int i=0;i<sysmsgList.size();++i){
        onSysMessageNotice(sysmsgList.at(i));
    }
}

void CDoodSysMsgManager::initConnect()
{
    qDebug() << Q_FUNC_INFO;
    connect(m_pClient, SIGNAL(sysMessageNotice(IMSysMsg)), this, SLOT(onSysMessageNotice(IMSysMsg)));
    connect(m_pClient, SIGNAL(getSysMessagesResult(int,IMSysMsgList)), this, SLOT(onGetSysMessages(int,IMSysMsgList)));
}
