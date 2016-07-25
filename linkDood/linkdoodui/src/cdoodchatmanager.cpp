#include "cdoodchatmanager.h"
#include "cdoodchatitem.h"
#include <QDebug>

void CDoodChatManager::initConnect()
{
    qDebug() << Q_FUNC_INFO;
    connect(m_pClient,SIGNAL(chatAvatarChanged(QString,QString)),this,
            SLOT(onChatAvatarChanged(QString,QString)));
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
    connect(m_pClient,SIGNAL(fileProgressResult(int,int,QString,QString,QString)),this,
            SLOT(onChatFileProgress(int,int,QString,QString,QString)));

    connect(m_pClient,SIGNAL(downloadFileResult(int,QString,QString)),this,
            SLOT(onChatDownloadFile(int,QString,QString)));
    connect(m_pClient,SIGNAL(uploadImageResult(QString,QString,QString,int)),this,
            SLOT(onChatupLoadImage(QString,QString,QString,int)));
    connect(m_pClient,SIGNAL(downloadImageResult(int,QString,QString)),this,
            SLOT(onChatDownloadImage(int,QString,QString)));
    connect(m_pClient,SIGNAL(getFileListResult(int,FileInfoList)),this,
            SLOT(onChatGetFileList(int,FileInfoList)));
    connect(m_pClient,SIGNAL(getUserInfoResult(int,Contact)), this, SLOT(onGetUserInfo(int,Contact)));
    connect(m_pClient,SIGNAL(accountInfoChanged(Contact)),this,
            SLOT(onAccountInfoChanged(Contact)));
    connect(m_pClient,SIGNAL(anthAvatarChanged(QString)),this,
            SLOT(onAnthAvatarChanged(QString)));
        connect(m_pClient,SIGNAL(contactInfoChanged(int,Contact)),this,
            SLOT(onContactInfoChanged(int,Contact)));
            connect(m_pClient,SIGNAL(getGroupMemberListReslut(int,QString,MemberList)),this,
                SLOT(onGetGroupMemberListReslut(int,QString,MemberList)));
            /*    connect(m_pClient,SIGNAL(),this,
                    SLOT())*/;
}
void CDoodChatManager::setFileFormat()
{
    mFileFormat["aiff"] = "qrc:/res/fileformat_aiff.png";
    mFileFormat["apk"] = "qrc:/res/fileformat_apk.png";
    mFileFormat["asf"] = "qrc:/res/fileformat_asf.png";
    mFileFormat["bat"] = "qrc:/res/fileformat_bat.png";
    mFileFormat["dll"] = "qrc:/res/fileformat_dll.png";

    mFileFormat["doc"] = "qrc:/res/fileformat_doc.png";
    mFileFormat["excel"] = "qrc:/res/fileformat_excel.png";
    mFileFormat["exe"] = "qrc:/res/fileformat_exe.png";
    mFileFormat["html"] = "qrc:/res/fileformat_html.png";
    mFileFormat["icon"] = "qrc:/res/fileformat_icon.png";

    mFileFormat["pdf"] = "qrc:/res/fileformat_pdf.png";
    mFileFormat["pic"] = "qrc:/res/fileformat_pic.png";
    mFileFormat["ppt"] = "qrc:/res/fileformat_ppt.png";
    mFileFormat["rar"] = "qrc:/res/fileformat_rar.png";
    mFileFormat["txt"] = "qrc:/res/fileformat_txt.png";
}

CDoodChatManager::CDoodChatManager(LinkDoodClient *client, QObject *parent):
    CDoodListModel(parent), m_pClient(client)
{
    qDebug() << Q_FUNC_INFO;
    qRegisterMetaType<CDoodChatManager*>();
    mSelcetSendImagesList.clear();
    mSelcetSendFilesList.clear();
    mChatModel = NULL;
    mActId = mActAvatar = mActName = "";
    m_pUiManager = (linkdoodui_Workspace*)parent;
    initConnect();
    setFileFormat();
}

CDoodChatManager::~CDoodChatManager()
{
    exitChat();
}

void CDoodChatManager::switchToChatPage(QString targetId, QString name,QString chatType,QString lastMsgId,int unReadCount,QString icon)
{
    qDebug() << Q_FUNC_INFO<<"targetId:"<<targetId<<"chatType:"<<chatType <<"name:"<<name<<"lastId:"<<lastMsgId;
    if(mChatModel != NULL && mChatModel->id() == targetId){
        if(unReadCount != 0){
            //mChatModel->updateUnreadMsg(lastMsgId,unReadCount);
            getMessages(m_sTargetid,unReadCount,lastMsgId,0);
        }
        mChatModel->setId(targetId);
        mChatModel->setName(name);
        mChatModel->setChatType(chatType);
        mChatModel->setAvatar(icon);
        mChatModel->updateAccountUserInfo(mActId,mActName,mActAvatar);
        emit ChatPageChanged();
        emit sendShowChatPage(name,targetId,chatType);
    }else{
        m_sTargetid = targetId;
        QMap<QString,CDoodChatManagerModel*>::iterator iter = mMsgListModel.find(targetId);
        if(iter != mMsgListModel.end() && iter.value() != NULL){
            if(mChatModel != NULL){
                mMsgListModel[mChatModel->id()] = mChatModel;
            }
            mChatModel = iter.value();
        }else{
            CDoodChatManagerModel* item = new CDoodChatManagerModel(this);
            item->setId(targetId);
            item->setName(name);
            item->setChatType(chatType);
            item->setAccountId(m_pClient->UserId());
            if(mChatModel != NULL){
                mMsgListModel[mChatModel->id()] = mChatModel;
            }
            mChatModel = item;
            mMsgListModel[targetId] = item;
            if(chatType == "2"){
                m_pClient->getMemberList(targetId);
            }
        }
        if(unReadCount != 0){
            //mChatModel->updateUnreadMsg(lastMsgId,unReadCount);
            getMessages(m_sTargetid,unReadCount,lastMsgId,0);
        }
        if(mChatModel != NULL){
            mChatModel->setId(targetId);
            mChatModel->setName(name);
            mChatModel->setChatType(chatType);
            mChatModel->setAvatar(icon);
            mChatModel->updateAccountUserInfo(mActId,mActName,mActAvatar);
        }
        emit ChatPageChanged();
        emit sendShowChatPage(name,targetId,chatType);
    }
}

void CDoodChatManager::updateUnreadMsg()
{
    if(mChatModel ->unReadMsgCount() != 0){
        getMessages(m_sTargetid,mChatModel->unReadMsgCount(),mChatModel->lastMsgId(),0);
    }
    mChatModel->updateUnreadMsg("",0);
}

CDoodChatManagerModel* CDoodChatManager::chatModel() const
{
    return mChatModel;
}

void CDoodChatManager::updateMsgToListView(Msg msg)
{
    if(mChatModel!= NULL && mChatModel->id() == msg.targetid){
        mChatModel->addItemToListViewModel(msg);
    }else{
        CDoodChatManagerModel*  item = mMsgListModel.value(msg.targetid);
        if(item != NULL){
            item->addItemToListViewModel(msg);
        }else{
            CDoodChatManagerModel* item = new CDoodChatManagerModel(this);
            item->setId(msg.targetid);
            item->setName(msg.targetName);
            item->setAccountId(m_pClient->UserId());
            item->addItemToListViewModel(msg);
            mMsgListModel[msg.targetid] = item;
        }
    }
}

int CDoodChatManager::selectImageCount()
{
    return mSelcetSendImagesList.size();
}

void CDoodChatManager::setSelectImageCount(int count)
{
    emit selectImageCountChanged();
}

void CDoodChatManager::setSelectImageCount(int oper, QString url)
{
    if(oper == 1){
        mSelcetSendImagesList.push_back(url);
    }else if(oper == 0){
        mSelcetSendImagesList.clear();
    }
    else{
        mSelcetSendImagesList.removeOne(url);
    }
    setSelectImageCount(0);
    qDebug()<<Q_FUNC_INFO<<"11111111111:"<<url;
}

bool CDoodChatManager::imageExisted(QString url)
{
    for(int i= 0;i<mSelcetSendImagesList.size();++i ){
        if(mSelcetSendImagesList.at(i) == url){
            return true;
        }
    }
    return false;
}

void CDoodChatManager::startSendPicture()
{
    qDebug() << Q_FUNC_INFO;
    for(int i=0;i<mSelcetSendImagesList.size();++i){
        QString imgPath =  mSelcetSendImagesList.at(i);
        QString thumpPath("");
        scaledImage(imgPath,THUMP_PIC_WIDTH,THUMP_PIC_HEIGHT,thumpPath);
        Msg msg;
        msg.thumb_url = thumpPath;
        qDebug() << "msg.thumb_url = thumpPath;end thumpPath:"<<thumpPath;
        if(!thumpPath.startsWith("file://")){
            thumpPath = "file://"+thumpPath;
        }
        qDebug() << Q_FUNC_INFO<<"22222:"<<thumpPath<<"targetId:"<<m_sTargetid;
        msg.body = thumpPath;
        msg.msgtype = QString::number(MSG_TYPE_IMG);
        msg.targetid = m_sTargetid;
        msg.fromid = m_pClient->UserId();
        msg.name = m_pClient->userName();
        QDateTime time;
        msg.time = time.currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
        msg.msgid = m_pClient->createMsgId();
        msg.localid = msg.msgid;

        //保存原图
        QImage srcImg(imgPath);
        QString tempImagePath =  APP_DATA_PATH +m_pClient->UserId() + "/cache/";
        qDebug() <<"QDir tempDir;before  tempImagePath:" << tempImagePath;
        QDir tempDir;
        if (!tempDir.exists(tempImagePath))
        {
            tempDir.mkdir(tempImagePath);
        }
        QFileInfo fileInfo(imgPath);
        tempImagePath = tempImagePath+fileInfo.baseName()+ ".jpg";
        qDebug() <<"srcImg.save;before  tempImagePath:" << tempImagePath;
        srcImg.save(tempImagePath, "JPEG", 99);
        qDebug() <<"srcImg.save;end  tempImagePath:" << tempImagePath;



        msg.main_url  = tempImagePath;

        mChatModel->addItemToListViewModel(msg);

        msg.filename  = fileInfo.fileName();
        msg.i_height  = QString::number(THUMP_PIC_HEIGHT);
        msg.i_width   = QString::number(THUMP_PIC_WIDTH);
        this->uploadAndSendImageMsg(msg);
    }
    mSelcetSendImagesList.clear();
}

int CDoodChatManager::selectFileCount()
{
    return mSelcetSendFilesList.size();
}

void CDoodChatManager::setSelectFileCount(int count)
{
    emit selectFileCountChanged();
}

void CDoodChatManager::setSelectFileCount(int oper, QString url)
{
    if(oper == 1){
        mSelcetSendFilesList.push_back(url);
    }else if(oper == 0){
        mSelcetSendFilesList.clear();
    }
    else{
        mSelcetSendFilesList.removeOne(url);
    }
    setSelectFileCount(0);
}

bool CDoodChatManager::fileExisted(QString url)
{
    for(int i= 0;i<mSelcetSendFilesList.size();++i ){
        if(mSelcetSendFilesList.at(i) == url){
            return true;
        }
    }
    return false;
}

void CDoodChatManager::startSendFile()
{
    qDebug()<<Q_FUNC_INFO;
    for(int i=0;i<mSelcetSendFilesList.size();++i){
        QString filePath = mSelcetSendFilesList.at(i);
        sendFile(filePath);
    }
}

void CDoodChatManager::sendFile(QString path)
{
    Msg fileMsg;
    fileMsg.body = path;
    fileMsg.msgtype = QString::number(MSG_TYPE_FILE);
    fileMsg.targetid = m_sTargetid;
    fileMsg.fromid = m_pClient->UserId();
    fileMsg.name = m_pClient->userName();
    QDateTime time;
    fileMsg.time = time.currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    fileMsg.msgid = m_pClient->createMsgId();
    fileMsg.localid = fileMsg.msgid;
    QFileInfo file(path);

    fileMsg.f_size = QString::number(file.size());
    fileMsg.f_path = path;
    fileMsg.filename = file.fileName();

    mChatModel->addItemToListViewModel(fileMsg,file.fileName());


    uploadAndSendFileMsg(fileMsg);
}

void CDoodChatManager::sendText(QString targetText ,QString oriText)
{
    Msg msgText;
    msgText.body = oriText;
    msgText.msgtype = QString::number(MSG_TYPE_TEXT);
    msgText.targetid = m_sTargetid;
    msgText.fromid = m_pClient->UserId();
    msgText.name = m_pClient->userName();
    msgText.localid = msgText.msgid;
    QDateTime time;
    msgText.time = time.currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    msgText.msgid = m_pClient->createMsgId();
    msgText.localid = msgText.msgid;

    if(m_sTargetid == mChatModel->id()){
        mChatModel->addItemToListViewModel(msgText,targetText);
    }
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
}

void CDoodChatManager::resendMessage(QString localId)
{

    qDebug() << Q_FUNC_INFO;
    CDoodChatItem *pChatItem = mChatModel->itemById(localId);

    if(pChatItem != NULL){

        pChatItem->setLoading(true);
        pChatItem->setStatus(true);

        Msg msg;
        msg.targetid = pChatItem->targetId();
        msg.fromid =pChatItem->fromId();
        msg.name = pChatItem->name();
        QDateTime time;
        msg.time = time.currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
        msg.msgid = pChatItem->msgId();

        if(pChatItem->msgType()== QString::number(MSG_TYPE_TEXT)){
            msg.msgtype = QString::number(MSG_TYPE_TEXT);
            msg.body = pChatItem->textMsg();
        }

        if(pChatItem->msgType()== QString::number(MSG_TYPE_FILE)){
            msg.msgtype = QString::number(MSG_TYPE_FILE);

            pChatItem->setProgress(0);
            msg.f_path = pChatItem->body();
            QFile file(msg.f_path);
            msg.filename = file.fileName();
            msg.f_size = pChatItem->fileSize();
        }

        if(pChatItem->msgType()== QString::number(MSG_TYPE_IMG)){
            msg.msgtype = QString::number(MSG_TYPE_IMG);

            msg.main_url  = pChatItem->textMsg();
            msg.thumb_url = pChatItem->tar_thumbAvatar();
            QFile file(msg.main_url);
            msg.filename  = file.fileName();
            msg.i_height  = QString::number(THUMP_PIC_HEIGHT);
            msg.i_width   = QString::number(THUMP_PIC_WIDTH);
        }
        sendMessage(msg);
    }

}

void CDoodChatManager::sendMessage(Msg msg)
{
    qDebug() << Q_FUNC_INFO;

    msg.fromid = m_pClient->UserId();
    msg.name = m_pClient->userName();
    msg.targetName = mChatModel->name();

    m_pClient->sendMessage(msg);
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
    msg.localid = msg.msgid;
    mChatModel->addItemToListViewModel(msg);
    //TODO
    if(path.contains("file://")){
        path.remove("file://");
    }
    QFileInfo file(path);
    msg.body = file.baseName();
    sendMessage(msg);
}

void CDoodChatManager::getMessages(QString targetid, int count,QString lastMsgid,int flag)
{
    qDebug() << Q_FUNC_INFO;
    m_pClient->getMessages(targetid,lastMsgid,count,flag);
}

void CDoodChatManager::removeChat(QString targetid)
{
    qDebug() << Q_FUNC_INFO;
    if(mChatModel != NULL && mChatModel->id() == targetid){
        mChatModel = NULL;
    }
    QMap<QString,CDoodChatManagerModel*>::iterator iter= mMsgListModel.find(targetid);
    if(iter != mMsgListModel.end()){
        iter.value()->clearList();
        delete iter.value();
        mMsgListModel.remove(targetid);
    }
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

void CDoodChatManager::entryChat(const QString &targetid)
{
    qDebug() << Q_FUNC_INFO << targetid;
    m_sTargetid = targetid;
    //m_pClient->entryChat(targetid);

    qDebug() << Q_FUNC_INFO;
    QString path = APP_DATA_PATH;
    QString fileName = path+ "config.ini";
    QSettings settings(fileName, QSettings::IniFormat);
    settings.setValue("SessionTargetID",targetid);

}

void CDoodChatManager::exitChat()
{
    qDebug() << Q_FUNC_INFO;
    m_pClient->exitChat(m_sTargetid);
}

void CDoodChatManager::downloadFile(QString localId, QString targetId)
{
    QMap<QString,CDoodChatManagerModel*>::iterator it = mMsgListModel.find(targetId);
    if(it == mMsgListModel.end())
        return;
    CDoodChatItem* chatItem = it.value()->itemById(localId);
    if(chatItem == NULL)
        return;
    downloadFile(chatItem->textMsg(), chatItem->thumbAvatar(), chatItem->body(),localId, targetId);
}

QString CDoodChatManager::judgeFileFromat(QString filePath)
{
    QFileInfo file(filePath);
    QMap<QString, QString>::iterator it = mFileFormat.find(file.suffix());
    if(it == mFileFormat.end())
        return "qrc:/res/fileformat_icon.png";
    return it.value();
}

void CDoodChatManager::getUserInfo(QString userid)
{
    qDebug() << Q_FUNC_INFO << "userid:" << userid;
    m_pClient->getUserInfo(userid);
}

void CDoodChatManager::uploadAndSendFileMsg(Msg msg)
{
    qDebug() << Q_FUNC_INFO;
    m_pClient->uploadAndSendFileMsg(msg);
}

void CDoodChatManager::downloadFile(QString path, QString url, QString json,QString localId,QString targetId)
{
    qDebug() << Q_FUNC_INFO;
    m_pClient->downloadFile(path, url, json,localId,targetId);
}

void CDoodChatManager::uploadAndSendImageMsg(Msg msg)
{
    qDebug() << Q_FUNC_INFO;
    m_pClient->uploadAndSendImageMsg(msg);
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

void CDoodChatManager::onGetGroupMemberListReslut(int code, QString id, MemberList list)
{
    CDoodChatManagerModel* item = mMsgListModel.value(id);
    if(item != NULL){
        item->updateGroupMems(list);
    }
}

void CDoodChatManager::onAccountInfoChanged(Contact user)
{
    if(user.id != ""){
        mActId = user.id;
    }
    if(user.name != ""){
        mActName = user.name;
    }
    if(user.avatar != ""){
        mActAvatar = user.avatar;
    }
    QList<CDoodChatManagerModel*> list = mMsgListModel.values();
    int size = list.size();
    for(int i=0;i<size;++i){
        CDoodChatManagerModel* item = list.at(i);
        if(item != NULL){
            item->updateAccountUserInfo(user.id,user.name,user.avatar);
        }
    }
}

void CDoodChatManager::onAnthAvatarChanged(QString avatar)
{
    if(avatar !=""){
        QList<CDoodChatManagerModel*> list = mMsgListModel.values();
        int size = list.size();
        for(int i=0;i<size;++i){
            CDoodChatManagerModel* item = list.at(i);
            if(item != NULL){
                item->updateAccountUserInfo("","",avatar);
            }
        }
        mActAvatar = avatar;
    }
}

void CDoodChatManager::onContactInfoChanged(int oper, Contact user)
{
    if(oper == 2){
        if(user.name !="" || user.thumbAvatar !=""){
            QList<CDoodChatManagerModel*>list = mMsgListModel.values();
            for(int i=0;i<list.size();++i){
                CDoodChatManagerModel* item = list.at(i);
                if(item != NULL){
                    item->updateItemData(user.id,user.name,user.avatar);
                }
            }
        }
    }
}


void CDoodChatManager::onChatAvatarChanged(QString id, QString avatar)
{
    qDebug() << Q_FUNC_INFO<< "111111111111111111avater:"<<avatar;
    if(id != ""){
        if(mChatModel != NULL){
            mChatModel->updateAvatar(id,avatar);
        }
        QMap<QString,CDoodChatManagerModel*>::iterator iter = mMsgListModel.begin();
        for(;iter != mMsgListModel.end();++iter){
            iter.value()->updateAvatar(id,avatar);
        }
    }
}

void CDoodChatManager::onChatOfflineMsgNotice(IMOfflineMsgList msgList)
{
    qDebug() << Q_FUNC_INFO << msgList.size();
    //emit offlineMsgNotice(msgList);
}

void CDoodChatManager::onChatMessageNotice(Msg msg)
{
    if(msg.localid =="" || msg.localid =="0"){
        msg.localid = m_pClient->createMsgId();
    }
    updateMsgToListView(msg);

    emit newMessageNotice();
}

void CDoodChatManager::onChatSendMessageResult(bool code, QString sendTime, QString msgId)
{
    QStringList list = msgId.split(":");
    QString curMsgId= list[0],localId= list[1],targetId= list[2];
    CDoodChatItem* item = NULL;
    if(mChatModel->id() == targetId){
        item = mChatModel->itemById(localId);
    }else{
        QMap<QString,CDoodChatManagerModel*>::iterator iter  = mMsgListModel.find(targetId);
        if(iter != mMsgListModel.end()){
            CDoodChatManagerModel* model = iter.value();
            if(model != NULL){
                item = model->itemById(localId);
            }
        }
    }
    if(item != NULL){
        item->setLoading(false);
        item->setStatus(code);
        item->setMsgId(curMsgId);
    }
}

void CDoodChatManager::onChatGetMessagesResult(bool code, QString sessionId, MsgList msgList)
{
    if(mChatModel != NULL && mChatModel->id() == sessionId){
        qDebug() << Q_FUNC_INFO<< "mChatModel size:"<<msgList.size();
        mChatModel->analyzeMsg(msgList);
    }else{
        QMap<QString,CDoodChatManagerModel*>::iterator model = mMsgListModel.find(sessionId);
        if(model != mMsgListModel.end()){
            model.value()->analyzeMsg(msgList);
        }
    }
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

void CDoodChatManager::onChatFileProgress(int extra_req, int process, QString info,QString localId,QString tagetId)

{
    qDebug() << Q_FUNC_INFO<< "tagetId:"<<tagetId<<" localId:"<<localId<<" process:"<<process;
    if(mChatModel->id() == tagetId){
        CDoodChatItem * item = mChatModel->itemById(localId);
        if(item != NULL){
            item->setProgress(process);
        }
    }else{
        QMap<QString,CDoodChatManagerModel*>::iterator iter = mMsgListModel.find(tagetId);
        if(iter != mMsgListModel.end()){
            CDoodChatItem * item = iter.value()->itemById(localId);
            if(item != NULL){
                item->setProgress(process);
            }
        }
    }
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

void CDoodChatManager::onGetUserInfo(int code, Contact contact)
{
    //    emit getUserInfoResult(code, contact);
}

void CDoodChatManager::scaledImage(QString sourceImagePath, float scaledWidth, float scaledHeight, QString &outImagePath)
{
    qDebug()<<Q_FUNC_INFO<<"1111111111111:"<<sourceImagePath;
    QSize sourceSize;
    int sourceWidth = 0;
    int sourceHeight = 0;
    int resultWidth = 0;
    int resultHeight = 0;
    float scaledNum = 0;      //缩放比例

    QImage sourceImage(sourceImagePath);
    sourceSize = sourceImage.size();
    sourceWidth = sourceSize.width();
    sourceHeight = sourceSize.height();

    if (sourceWidth >= scaledWidth && sourceHeight >= scaledHeight)
    {
        if (sourceWidth >= sourceHeight)
        {
            scaledNum = scaledWidth / sourceWidth;
            resultWidth = scaledWidth;
            resultHeight = scaledNum*sourceHeight;
        }
        else
        {
            scaledNum = scaledHeight / sourceHeight;
            resultHeight = scaledHeight;
            resultWidth = scaledNum*sourceWidth;
        }
    }
    else if (sourceWidth >= scaledWidth && sourceHeight <= scaledHeight)
    {
        scaledNum = scaledWidth / sourceWidth;
        resultWidth = scaledWidth;
        resultHeight = scaledNum*sourceHeight;
    }
    else if (sourceWidth <= scaledWidth && sourceHeight >= scaledHeight)
    {
        scaledNum = scaledHeight / sourceHeight;
        resultHeight = scaledHeight;
        resultWidth = scaledNum*sourceWidth;
    }
    else
    {
        resultWidth = sourceWidth;
        resultHeight = sourceHeight;
    }
    QImage destinationImage400x300 = sourceImage.scaled(QSize(resultWidth, resultHeight), Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
    QFileInfo fileInfo(sourceImagePath);


    QString tempImagePath =  APP_DATA_PATH +m_pClient->UserId() + "/cache";
    QDir tempDir;
    if (!tempDir.exists(tempImagePath))
    {
        tempDir.mkdir(tempImagePath);
    }

    outImagePath = tempImagePath + "/" + fileInfo.baseName() + "_" + QString::number(scaledWidth)
            + "x" + QString::number(scaledHeight) + ".jpg";
    destinationImage400x300.save(outImagePath, "JPEG", 99);

}
