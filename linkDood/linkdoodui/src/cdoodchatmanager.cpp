#include "cdoodchatmanager.h"
#include "cdoodchatitem.h"
#include <QDebug>

void CDoodChatManager::initConnect()
{
    qDebug() << Q_FUNC_INFO;
    connect(m_pClient,SIGNAL(chatAvatarChanged(int64,QString)),this,
            SLOT(onChatAvatarChanged(int64,QString)));
    connect(m_pClient,SIGNAL(offlineMsgNotice(IMOfflineMsgList)),this,
            SLOT(onChatOfflineMsgNotice(IMOfflineMsgList)));
    connect(m_pClient,SIGNAL(chatMessageNotice(Msg)),this,
            SLOT(onChatMessageNotice(Msg)));
    connect(m_pClient,SIGNAL(sendMessageResult(bool,QString,QString)),this,
            SLOT(onChatSendMessageResult(bool,QString,QString)));
    connect(m_pClient,SIGNAL(getMessagesResult(bool,QString,MsgList)),this,
            SLOT(onChatGetMessagesResult(bool,QString,MsgList)));
    connect(m_pClient,SIGNAL(removeChatResult(bool)),this,
            SLOT(onChatRemoveChatResult(bool)));
    connect(m_pClient,SIGNAL(deleteMessagesResult(int)),this,
            SLOT(onChatDeleteMessagesResult(int)));
    connect(m_pClient,SIGNAL(uploadAvatarResult(QString,QString,int)),this,
            SLOT(onUploadAvatarResult(QString,QString,int)));
    connect(m_pClient,SIGNAL(uploadFileResult(QString,QString,int)),this,
            SLOT(onChatUploadFile(QString,QString,int)));
    connect(m_pClient,SIGNAL(fileProgressResult(int,int,QString)),this,
            SLOT(onChatFileProgress(int,int,QString)));
    connect(m_pClient,SIGNAL(downloadFileResult(int,QString,QString)),this,
            SLOT(onChatDownloadFile(int,QString,QString)));
    connect(m_pClient,SIGNAL(uploadImageResult(QString,QString,QString,int)),this,
            SLOT(onChatupLoadImage(QString,QString,QString,int)));
    connect(m_pClient,SIGNAL(downloadImageResult(int,QString,QString)),this,
            SLOT(onChatDownloadImage(int,QString,QString)));
    connect(m_pClient,SIGNAL(getFileListResult(int,FileInfoList)),this,
            SLOT(onChatGetFileList(int,FileInfoList)));


    /*    connect(m_pClient,SIGNAL(),this,
            SLOT())*/;
}

void CDoodChatManager::analyticalMessage(MsgList list)
{
    qDebug() << Q_FUNC_INFO << "size = " << list.size();

    if(list.size() <= 0) {
        return;
    }

    QList <QObject* > msglist;
    for(int i = 0; i < list.size(); ++i) {
        if(!m_oChatMap.contains(list.at(i).msgid)) {
            CDoodChatItem *pChatItem = new CDoodChatItem(this);
            pChatItem->setMsgType(list.at(i).msgtype);
            pChatItem->setActiveType(list.at(i).activeType);
            pChatItem->setMsgId(list.at(i).msgid);
            pChatItem->setTargetId(list.at(i).targetid);
            pChatItem->setFromId(list.at(i).fromid);
            pChatItem->setToId(list.at(i).toid);
            pChatItem->setTime(QDateTime::fromString(list.at(i).time, "yyyy-MM-dd hh:mm:ss"));
            pChatItem->setBody(list.at(i).body);
            if(list.at(i).fromid != m_pClient->UserId()){
                pChatItem->setName(name());
            }else{
                pChatItem->setName(m_pClient->userName());
            }

            //            if(i == 0) {
            //                pChatItem->setShowTime(true);
            //            } else {
            //                if(i - 1 >= 0) {
            //                    pChatItem->setShowTime(checkTimeIsShow(p->lastMessageTime,pChatItem->sendTime()));
            //                }
            //            }

            msglist.append(pChatItem);
            m_oChatMap[list.at(i).msgid] = pChatItem;
            m_oLastMessageTime = QDateTime::fromString(list.at(i).time, "yyyy-MM-dd hh:mm:ss");
            qDebug() << Q_FUNC_INFO << "pChatItem->body() = " << pChatItem->body();
            qDebug() << Q_FUNC_INFO << "pChatItem->time() = " << pChatItem->time();
        }
    }

    if (msglist.size() <= 0) {
        return;
    }

    int nBeginIndexAndSize = 0;
    int nEndIndex = nBeginIndexAndSize + msglist.size() - 1;

    qDebug() << "Dood === nBeginIndex = " << nBeginIndexAndSize;
    qDebug() << "Dood === nEndIndex = " << nEndIndex;

#if 0
    beginInsertRows(QModelIndex(), nBeginIndexAndSize, nEndIndex);

    for(int i = msglist.size()-1; i>=0 ; --i) {
        _list->insert(nBeginIndexAndSize, msglist.at(i));
    }

    endInsertRows();
#else
    for(int i = msglist.size()-1; i>=0 ; --i) {
        addItemBegin(msglist.at(i));
    }
#endif
    emit itemCountChanged();
    // 消息id与数据库的消息id不一致时查询结果可能会有问题
    m_sBeginMsgId = list.at(0).msgid;
}

void CDoodChatManager::addItemToListViewModel(Msg msg,QString textMsgContent)
{
    qDebug() << Q_FUNC_INFO;
    if(!m_oChatMap.contains(msg.msgid)) {

        CDoodChatItem *pChatItem = new CDoodChatItem(this);
        pChatItem->setMsgType(msg.msgtype);
        pChatItem->setActiveType(msg.activeType);
        pChatItem->setMsgId(msg.msgid);
        pChatItem->setTargetId(msg.targetid);
        pChatItem->setFromId(msg.fromid);
        pChatItem->setToId(msg.toid);
        pChatItem->setName(msg.name);
        pChatItem->setTime(QDateTime::fromString(msg.time, "yyyy-MM-dd hh:mm:ss"));
        pChatItem->setBody(msg.body);
        pChatItem->setName(msg.name);
        pChatItem->setLoading(true);
        pChatItem->setTextMsgContent(textMsgContent);
        m_oLastMessageTime = QDateTime::fromString(msg.time, "yyyy-MM-dd hh:mm:ss");
        addItem(pChatItem);
        m_oChatMap[msg.msgid] = pChatItem;

        qDebug() << Q_FUNC_INFO << "pChatItem->body() = " << pChatItem->body();
        qDebug() << Q_FUNC_INFO << "pChatItem->time() = " << pChatItem->time();
    }
}

CDoodChatManager::CDoodChatManager(LinkDoodClient *client, QObject *parent):
    CDoodListModel(parent), m_pClient(client)
{
    qDebug() << Q_FUNC_INFO;
    qRegisterMetaType<CDoodChatManager*>();
    initConnect();
}

CDoodChatManager::~CDoodChatManager()
{
    exitChat();
}

void CDoodChatManager::sendText(QString targetText ,QString oriText)
{
    Msg msgText;
    msgText.body = oriText;
    msgText.msgtype = QString::number(MSG_TYPE_TEXT);
    msgText.targetid = m_sTargetid;
    msgText.fromid = m_pClient->UserId();
    msgText.name = m_pClient->userName();
    QDateTime time;
    msgText.time = time.currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    msgText.msgid = m_pClient->createMsgId();

    qDebug() << Q_FUNC_INFO <<"send message:"<< msgText.msgid;
    addItemToListViewModel(msgText,targetText);
    msgText.body = targetText;
    sendMessage(msgText);
}

void CDoodChatManager::sendText(QQuickTextDocument *item,QString oriText)
{
    QTextDocument* textDocu = item->textDocument();
    QString newLineStr = "";    //区分html和普通文本换行
    if (textDocu->toHtml().contains("<!DOCTYPE HTML PUBLIC"))
    {
        newLineStr = "\n";
    }
    else
    {
        newLineStr = "\n";
    }
    QTextBlock block = textDocu->begin();
    QString tempStr = "";
    QString textContent = "";
    QString imgPath = "";
    QTextImageFormat imageFormat;
    for (int index = 0; index < textDocu->blockCount(); index++)
    {
        imgPath = "";
        tempStr = "";
        block = textDocu->findBlockByNumber(index);
        QTextBlock::iterator itBlock = block.begin();
        for (; !(itBlock.atEnd()); itBlock++)
        {
            imgPath = "";
            tempStr = "";

            QTextFragment currentFragment = itBlock.fragment();
            tempStr = currentFragment.text();
            if (currentFragment.isValid() && currentFragment.charFormat().isImageFormat() && (!tempStr.isSimpleText() && (1 == tempStr.size())))
            {
                //处理图片
                imageFormat = currentFragment.charFormat().toImageFormat();
                imgPath = imageFormat.name();
                if (imgPath.contains("qrc:/"))
                {
                    //是表情，直接嵌入到文本中
                    textContent = textContent +EMOJI_IMAGE+ imgPath+EMOJI_IMAGE;
                    continue;
                }
            }
            textContent = textContent + tempStr;
        }
        textContent = textContent + newLineStr;
    }

    textContent = textContent.trimmed();
    sendText(textContent,oriText);
    qDebug() << Q_FUNC_INFO << "qqqqqqqqqqqq:" << textContent;
}

void CDoodChatManager::resendMessage(QString msgId)
{
    qDebug() << Q_FUNC_INFO;
    CDoodChatItem *pChatItem = m_oChatMap.value(msgId);
    if(pChatItem != NULL && pChatItem->msgType()== QString::number(MSG_TYPE_TEXT)){

        pChatItem->setLoading(true);
        pChatItem->setStatus(true);

        Msg msgText;
        msgText.body = pChatItem->textMsgContent();
        msgText.msgtype = QString::number(MSG_TYPE_TEXT);
        msgText.targetid = pChatItem->targetId();
        msgText.fromid =pChatItem->fromId();
        msgText.name = pChatItem->name();
        QDateTime time;
        msgText.time = time.currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
        msgText.msgid = pChatItem->msgId();

        qDebug() << Q_FUNC_INFO <<"send message:"<< msgText.msgid;
        sendMessage(msgText);
    }
}

void CDoodChatManager::sendMessage(Msg msg)
{
    qDebug() << Q_FUNC_INFO;
    m_pClient->sendMessage(msg);
    msg.fromid = m_pClient->UserId();
    msg.name = m_pClient->userName();
}

void CDoodChatManager::sendDyEmojiMsg(QString path)
{
     qDebug() << Q_FUNC_INFO;
     Msg msg;
     msg.body = path;
     msg.msgtype = QString::number(MEDIA_MSG_DYNAMIC_EMOJI);
     msg.targetid = m_sTargetid;
     msg.fromid = m_pClient->UserId();
     msg.name = m_pClient->userName();
     QDateTime time;
     msg.time = time.currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
     msg.msgid = m_pClient->createMsgId();

     addItemToListViewModel(msg);
     //TODO
     msg.body = path;
     sendMessage(msg);
}

void CDoodChatManager::getMessages(QString targetid, int count)
{
    qDebug() << Q_FUNC_INFO;
    m_pClient->getMessages(targetid,m_sBeginMsgId,count,0);
}

void CDoodChatManager::removeChat(QString targetid)
{
    qDebug() << Q_FUNC_INFO;
    m_pClient->removeChat(targetid);
}

void CDoodChatManager::setMessageRead(QString targetid)
{
    qDebug() << Q_FUNC_INFO;
    m_pClient->setMessageRead(targetid,"0");
}

void CDoodChatManager::getUnReadMessages()
{
    qDebug() << Q_FUNC_INFO;
    m_pClient->getUnReadMessages();
}

void CDoodChatManager::deleteMessage(QString targetid, QStringList msgs)
{
    qDebug() << Q_FUNC_INFO;
    m_pClient->deleteMessage(targetid,msgs);
}

QString CDoodChatManager::id() const
{
    qDebug() << Q_FUNC_INFO;
    return mId;
}

void CDoodChatManager::setId(const QString &id)
{
    qDebug() << Q_FUNC_INFO;
    mId = id;
    emit idChanged();
}

QString CDoodChatManager::name() const
{
    qDebug() << Q_FUNC_INFO;
    return mName;
}

void CDoodChatManager::setName(const QString &name)
{
    qDebug() << Q_FUNC_INFO;
    mName = name;
    emit nameChanged();
}

void CDoodChatManager::entryChat(const QString &targetid)
{
    qDebug() << Q_FUNC_INFO << targetid;
    m_sTargetid = targetid;
    m_pClient->entryChat(targetid);
}

void CDoodChatManager::exitChat()
{
    qDebug() << Q_FUNC_INFO;
    m_pClient->exitChat(m_sTargetid);
}

void CDoodChatManager::deleteMessageListItem()
{
    qDebug() << Q_FUNC_INFO;
    initChatState();
    if(m_oChatMap.size() <= 0)
        return;

    QMap<QString, CDoodChatItem*>::const_iterator i = m_oChatMap.constBegin();
    while (i != m_oChatMap.constEnd()) {
        removeItem(m_oChatMap[i.key()]);
        delete m_oChatMap[i.key()];
        m_oChatMap[i.key()] = 0;
        ++i;
    }
    m_oChatMap.clear();
}

void CDoodChatManager::showChatPage(QString chatName,
                                    QString targetid,
                                    QString chatType,
                                    QString icon)
{
    qDebug() << Q_FUNC_INFO;
    emit sendShowChatPage(chatName, targetid, chatType, icon);
}

void CDoodChatManager::initChatState()
{
    qDebug() << Q_FUNC_INFO;
    m_sBeginMsgId = "";
    m_sTargetid = "";
}

void CDoodChatManager::uploadAvatar(QString path)
{
    qDebug() << Q_FUNC_INFO;
    m_pClient->uploadAvatar(path);
}

void CDoodChatManager::uploadFile(QString path, QString property)
{
    qDebug() << Q_FUNC_INFO;
    m_pClient->uploadFile(path, property);
}

void CDoodChatManager::downloadFile(QString path, QString url, QString property)
{
    qDebug() << Q_FUNC_INFO;
    m_pClient->downloadFile(path, url, property);
}

void CDoodChatManager::uploadImage(QString thumbimg, QString srcimg, QString property)
{
    qDebug() << Q_FUNC_INFO;
    m_pClient->uploadImage(thumbimg, srcimg, property);
}

void CDoodChatManager::downloadImage(QString url, QString property)
{
    qDebug() << Q_FUNC_INFO;
    m_pClient->downloadImage(url, property);
}

bool CDoodChatManager::decryptFile(QString encryptkey, QString srcpath, QString destpath)
{
    qDebug() << Q_FUNC_INFO;
    return m_pClient->decryptFile(encryptkey, srcpath, destpath);
}

void CDoodChatManager::getFileList(int64 targetid, int64 fileid, int count, int flag)
{
    qDebug() << Q_FUNC_INFO;
    m_pClient->getFileList(targetid, fileid, count, flag);
}


void CDoodChatManager::onChatAvatarChanged(int64 id, QString avatar)
{
    qDebug() << Q_FUNC_INFO;
    // emit chatAvatarChanged(id,avatar);
}

void CDoodChatManager::onChatOfflineMsgNotice(IMOfflineMsgList msgList)
{
    qDebug() << Q_FUNC_INFO << msgList.size();
    //emit offlineMsgNotice(msgList);
}

void CDoodChatManager::onChatMessageNotice(Msg msg)
{
    qDebug() << Q_FUNC_INFO << msg.body;
    qDebug() << Q_FUNC_INFO << msg.msgid;
    qDebug() << Q_FUNC_INFO << msg.msgtype;
    qDebug() << Q_FUNC_INFO <<"ssssssssssss"<< msg.name;
    if(msg.fromid == m_pClient->UserId()){
        msg.name = m_pClient->userName();
    }else{
        msg.name = name();
    }

    addItemToListViewModel(msg);
}

void CDoodChatManager::onChatSendMessageResult(bool code, QString sendTime, QString msgId)
{
   QStringList list = msgId.split(":");
   QString curMsgId= list[0],localId= list[1];
   CDoodChatItem* item = m_oChatMap.value(localId);
   if(item != NULL){
        item->setLoading(false);
        item->setStatus(code);

        //将缓冲中map中id更新服务端的msgid
        if(curMsgId != localId){
            item->setMsgId(curMsgId);
            m_oChatMap.remove(localId);
            m_oChatMap.insert(curMsgId,item);
        }
   }
}

void CDoodChatManager::onChatGetMessagesResult(bool code, QString sessionId, MsgList msgList)
{
    qDebug() << Q_FUNC_INFO << code << sessionId << msgList.size();
    if (msgList.size() <= 0) {
        return;
    }
    qDebug() << Q_FUNC_INFO <<"DDD:" << name();
    analyticalMessage(msgList);
}

void CDoodChatManager::onChatRemoveChatResult(bool code)
{
    qDebug() << Q_FUNC_INFO;
    //    emit removeChatResult(code);
}

void CDoodChatManager::onChatDeleteMessagesResult(int code)
{

}

void CDoodChatManager::onChatUploadAvatar(QString orgijson, QString thumbjson, int code)
{
    qDebug() << Q_FUNC_INFO;
}

void CDoodChatManager::onChatUploadFile(QString tagetid, QString jasoninfo, int code)
{
    qDebug() << Q_FUNC_INFO;
}

void CDoodChatManager::onChatFileProgress(int extra_req, int process, QString info)
{
    qDebug() << Q_FUNC_INFO;
}

void CDoodChatManager::onChatDownloadFile(int code, QString localpath, QString tagetid)
{
    qDebug() << Q_FUNC_INFO;
}

void CDoodChatManager::onChatupLoadImage(QString tagetid, QString orgijson, QString thumbjson, int code)
{
    qDebug() << Q_FUNC_INFO;
}

void CDoodChatManager::onChatDownloadImage(int code, QString localpath, QString tagetid)
{
    qDebug() << Q_FUNC_INFO;
}

void CDoodChatManager::onChatGetFileList(int code, FileInfoList files)
{
    qDebug() << Q_FUNC_INFO;
}

void CDoodChatManager::onUploadAvatarResult(QString orgijson, QString thumbjson, int code)
{

}
