#include "cdoodchatmanager.h"
#include "cdoodchatitem.h"
#include <QDebug>
#include <QClipboard>
#include <QMatrix>

void CDoodChatManager::initConnect()
{
    qDebug() << Q_FUNC_INFO;
    connect(m_pClient,SIGNAL(memberListChanged(QString,QString,MemberList)),this,SLOT(onGroupMemberListChanged(QString,QString,MemberList)));
    connect(m_pClient,SIGNAL(uploadImageProgess(QString,QString,int)),this,
            SLOT(onUploadImageProgess(QString,QString,int)));
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
    //    connect(m_pClient,SIGNAL(uploadAvatarResult(QString,QString,int)),this,
    //            SLOT(onUploadAvatarResult(QString,QString,int)));
    connect(m_pClient,SIGNAL(uploadFileResult(QString,QString,int)),this,
            SLOT(onChatUploadFile(QString,QString,int)));
    connect(m_pClient,SIGNAL(fileProgressResult(int,int,QString,QString,QString)),this,
            SLOT(onChatFileProgress(int,int,QString,QString,QString)));

    connect(m_pClient,SIGNAL(downloadFileResult(int,QString,QString)),this,
            SLOT(onChatDownloadFile(int,QString,QString)));
    connect(m_pClient,SIGNAL(uploadImageResult(QString,QString,QString,int)),this,
            SLOT(onChatupLoadImage(QString,QString,QString,int)));
    connect(m_pClient,SIGNAL(downloadMainImageResult(QString,QString)),this,
            SLOT(onDownloadMainImageResult(QString,QString)));
    connect(m_pClient,SIGNAL(downloadImageResult(int,QString,QString)),this,
            SLOT(onChatDownloadImage(int,QString,QString)));
    connect(m_pClient, SIGNAL(downloadHistoryImageResult(int,QString,QString,QString)), this, SLOT(onDownloadHistoryImage(int,QString,QString,QString)));
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
    connect(m_pClient,SIGNAL(transMessageFinishBack(int,QString)),this,
            SLOT(onTransMessageFinishBack(int,QString)));
    connect(m_pClient,SIGNAL(groupInfoChanged(QString,Group)),this,
            SLOT(onGroupInfoChanged(QString,Group)));
    connect(m_pClient,SIGNAL(getOrgUserInfoResult(int,OrgUser)),this,
            SLOT(onGetOrgUserInfoResult(int,OrgUser)));
    connect(m_pClient,SIGNAL(uploadImgeBackUrl(QString,QString,QString,QString,QString)),this,
            SLOT(onUploadImgeBackUrl(QString,QString,QString,QString,QString)));

    connect(m_pClient,SIGNAL(uploadFileBackUrl(QString,QString,QString,QString)),this,
            SLOT(onUploadFileBackUrl(QString,QString,QString,QString)));
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

void CDoodChatManager::initModelConnects(CDoodChatManagerModel* model)
{
    connect(model,SIGNAL(draftChanged(QString)),this,SLOT(onDraftChanged(QString)));
    connect(model,SIGNAL(deleteMessage(QString,QStringList)),this,SLOT(onDeleteMessage(QString,QStringList)));
    connect(model,SIGNAL(downloadImage(QString,QString,QString,QString)),this,SLOT(onDownloadImage(QString,QString,QString,QString)));
    connect(model,SIGNAL(reqestUserInfo(QString)),this,SLOT(onReqestUserInfo(QString)));
}

void CDoodChatManager::switchToChatPage(QString targetId, QString name, QString chatType, QString lastMsgId, int unReadCount, QString icon)
{
    qDebug()<<Q_FUNC_INFO<<"targetId:"<<targetId<<"name:"<<name<<"chatType:"<<chatType<<"lastMsgId:"<<lastMsgId<<"unReadCount:"<<unReadCount<<"icon:"<<icon;
    CDoodChatManagerModel* model = mMsgListModel.value(targetId,NULL);
    if(model != NULL){
        if(targetId != m_sTargetid ||mChatModel==NULL){
            mChatModel = model;
            m_sTargetid = targetId;
        }
    }else{
        model = new CDoodChatManagerModel(this);
        model->setId(targetId);
        model->setAccountId(m_pClient->UserId());
        initModelConnects(model);
        mChatModel = model;
        m_sTargetid = targetId;
        mMsgListModel[targetId] = mChatModel;
    }
    mChatModel->setChatType(chatType);
    mChatModel->setAvatar(icon);
    mChatModel->setName(name);
    mChatModel->mNeedNewMsgCount = unReadCount;
    mChatModel->mNeedNewMsgLastId =lastMsgId;
    mChatModel->updateAccountUserInfo(mActId,mActName,mActAvatar);
    mCurentChatName = name;
    mCurentChatId = targetId;
    mCurentChatType = chatType;

    if(chatType == "2"){
        m_pClient->getGroupMemsList(targetId);
    }else if(mChatModel->name()== mChatModel->id()){
        m_pClient->getUserInfo(targetId);
    }
    emit chatPageChanged();
}

void CDoodChatManager::showUiFinished()
{
    if(mChatModel->msgCount()>0){
        if(mChatModel->lastMsgId() != mChatModel->mNeedNewMsgLastId){
            getMessages(m_sTargetid,mChatModel->mNeedNewMsgCount,mChatModel->mNeedNewMsgLastId,0);
        }
    }else{
        if(mChatModel->mNeedNewMsgLastId != "0"){
            getMessages(m_sTargetid,mChatModel->mNeedNewMsgCount+20,mChatModel->mNeedNewMsgLastId ,0);
        }else {
            getMessages(m_sTargetid,mChatModel->mNeedNewMsgCount+20,"0",1);
        }
    }
    mChatModel->mNeedNewMsgCount = 0;
    mChatModel->mNeedNewMsgLastId = "0";
    emit updateSessionPageMsgReaded(m_sTargetid);
}

void CDoodChatManager::groupChatTipMember(QString membername)
{
    emit groupChatTipMemberResult(membername);
}

void CDoodChatManager::clearList()
{
    qDebug()<<Q_FUNC_INFO;
    QList<CDoodChatManagerModel*> list = mMsgListModel.values();
    for(int i = 0;i<list.size();++i){
        CDoodChatManagerModel* item = list.at(i);
        if(item != NULL){
            item->clearList();
            delete item;
        }
    }
    mMsgListModel.clear();
    mChatModel = NULL;
}

void CDoodChatManager::getMoreHistoryMessage()
{
    if(mChatModel != NULL){
        QString firstMsgId =  mChatModel->firstMsgId();
        if(firstMsgId != "0"){
            getMessages(m_sTargetid,20,firstMsgId,0);
        }
    }
}

void CDoodChatManager::getGroupMemsList(QString groupId)
{
    m_pClient->getGroupMemsList(groupId);
}

CDoodChatManagerModel* CDoodChatManager::chatModel() const
{
    return mChatModel;
}

void CDoodChatManager::isTextOnClipboard()
{
    QClipboard *board = QApplication::clipboard();
    const QMimeData *source = board->mimeData();
    if (source->hasImage())
    {
        return;
    }
    else if (source->hasUrls() && source->urls().size() > 0)
    {
        QUrl url = source->urls().at(0);
        QFileInfo info(url.toLocalFile());
        if (info.exists())
        {
            return;
        }
    }
    //如果是图文混排的话，内容是html, 只提取文本，不支持粘贴的图文混排
    if (source->hasHtml())
    {
        QString strHtml = source->html();

        QTextDocument* textDocu = new QTextDocument;
        textDocu->setHtml(strHtml);
        QTextBlock block = textDocu->begin();
        QString tempStr = "";
        QString textContent = "";
        QString imgPath = "";
        //QTextImageFormat imageFormat;
        //bool isNetImg = false;
        qDebug()<<Q_FUNC_INFO<<"textThml:"<<strHtml;
        for (int index = 0; index < textDocu->blockCount(); index++)
        {
            imgPath = "";
            tempStr = "";
            block = textDocu->findBlockByNumber(index);
            QTextBlock::iterator itBlock;
            for (itBlock = block.begin(); !(itBlock.atEnd()); ++itBlock)
            {
                imgPath = "";
                tempStr = "";
                QTextFragment currentFragment = itBlock.fragment();
                tempStr = currentFragment.text();
                //                if (currentFragment.isValid() && currentFragment.charFormat().isImageFormat())
                //                {
                //                    imageFormat = currentFragment.charFormat().toImageFormat();
                //                    imgPath = imageFormat.name();
                //                    if(imgPath.contains("qrc:")){
                //                        QString emojiPath = "<img src=\""+imgPath+"\" height=\"36\" width=\"36\""+"/>";
                //                        tempStr += tempStr+emojiPath;

                //                    }
                //                }
                textContent +=textContent+tempStr;
            }

        }
        board->setText(textContent);
        qDebug()<<Q_FUNC_INFO<<"textContent:"<<textContent;
    }
}

bool CDoodChatManager::isTextOnly(QString text)
{
    if(text.contains("qrc:")){
        return false;
    }
    return true;
}

bool CDoodChatManager::isMySentFile(QString filePath)
{
    return filePath.contains(APP_SAVE_DATA_PATH);
}

void CDoodChatManager::updateMsgToListView(Msg msg,bool isFromPC)
{
    if(msg.thumb_avatar.startsWith("qrc")){
        isFromPC = true;
    }
    if(mChatModel!= NULL && mChatModel->id() == msg.targetid){
        mChatModel->addItemToListViewModel(msg,"",isFromPC);
    }else{
        CDoodChatManagerModel*  item = mMsgListModel.value(msg.targetid);
        if(item != NULL){
            item->addItemToListViewModel(msg,"",isFromPC);
        }else{
            CDoodChatManagerModel* item = new CDoodChatManagerModel(this);
            initModelConnects(item);
            item->setId(msg.targetid);
            item->setName(msg.targetName);
            item->setAccountId(m_pClient->UserId());
            item->setChatType(m_pClient->userType(msg.targetid));
            item->addItemToListViewModel(msg,"",isFromPC);
            mMsgListModel[msg.targetid] = item;
        }
    }
}

void CDoodChatManager::startPushChatPage()
{
    emit sendShowChatPage(mCurentChatName,mCurentChatId,mCurentChatType);
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

void CDoodChatManager::sendPictrue(QString path,bool isRotate)
{
    QString imgPath =  path;
    QString thumpPath("");
    scaledImage(imgPath,THUMP_PIC_WIDTH,THUMP_PIC_HEIGHT,thumpPath,isRotate);
    Msg msg;
    msg.thumb_url = thumpPath;
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
    //    QImage srcImg(imgPath);
    //    QString tempImagePath =  APP_DATA_PATH +m_pClient->UserId() + "/cache/";
    //    qDebug() <<"QDir tempDir;before  tempImagePath:" << tempImagePath;
    //    QDir tempDir;
    //    if (!tempDir.exists(tempImagePath))
    //    {
    //        tempDir.mkdir(tempImagePath);
    //    }
    //    QFileInfo fileInfo(imgPath);
    //    tempImagePath = tempImagePath+fileInfo.baseName()+ ".jpg";
    //    srcImg.save(tempImagePath, "JPEG", 99);
    //    msg.main_url  = tempImagePath;

    msg.main_url = path;
    mChatModel->addItemToListViewModel(msg);

    QFileInfo fileInfo(imgPath);
    msg.filename  = fileInfo.fileName();
    msg.i_height  = QString::number(THUMP_PIC_HEIGHT);
    msg.i_width   = QString::number(THUMP_PIC_WIDTH);
    this->uploadAndSendImageMsg(msg);
}

void CDoodChatManager::startSendPicture()
{
    qDebug() << Q_FUNC_INFO;
    for(int i=0;i<mSelcetSendImagesList.size();++i){
        sendPictrue(mSelcetSendImagesList.at(i));
    }
    mSelcetSendImagesList.clear();
}

QString CDoodChatManager::cameraFilePath()
{
    return QString::fromStdString(APP_DATA_PATH)+m_pClient->UserId()+"/cache";
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

void CDoodChatManager::setDraft(QString targetId, QQuickTextDocument *item)
{

}

void CDoodChatManager::sendText(QString targetText ,QString oriText,QList<QString> list)
{
    Msg msgText;
    msgText.body = oriText;
    msgText.msgtype = QString::number(MSG_TYPE_TEXT);
    msgText.targetid = m_sTargetid;
    msgText.limit_range=list;
    msgText.fromid = m_pClient->UserId();
    msgText.name = m_pClient->userName();
    msgText.localid = msgText.msgid;
    QDateTime time;
    msgText.time = time.currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    msgText.msgid = m_pClient->createMsgId();
    msgText.localid = msgText.msgid;


    if(m_sTargetid == mChatModel->id()){
        mChatModel->addItemToListViewModel(msgText,targetText,true);
    }

    msgText.body = targetText;
    sendMessage(msgText);
}

void CDoodChatManager::sendText(QQuickTextDocument *item,QString oriText,QList<QString> list)
{
    QString textContent = handleEmojiText(item);
    textContent=textContent.replace("\x1D"," ");
    oriText=oriText.replace("\x1D"," ");
    sendText(textContent,oriText,list);
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
        msg.localid = localId;
        if(pChatItem->msgType()== QString::number(MSG_TYPE_TEXT)){
            msg.msgtype = QString::number(MSG_TYPE_TEXT);
            msg.body = pChatItem->body();
        }else if(pChatItem->msgType()== QString::number(MSG_TYPE_FILE)){
            msg.msgtype = QString::number(MSG_TYPE_FILE);

            pChatItem->setProgress(0);
            msg.f_path = pChatItem->filePath();
            QFileInfo file(msg.f_path);
            msg.filename = file.fileName();
            msg.f_size = QString::number(file.size());

        }else if(pChatItem->msgType()== QString::number(MSG_TYPE_IMG)){
            msg.msgtype = QString::number(MSG_TYPE_IMG);

            msg.main_url  = pChatItem->textMsg();
            msg.thumb_url = pChatItem->tar_thumbAvatar();
            pChatItem->setProgress(0);
            QFile file(msg.main_url);
            msg.filename  = file.fileName();
            msg.i_height  = QString::number(THUMP_PIC_HEIGHT);
            msg.i_width   = QString::number(THUMP_PIC_WIDTH);
        }else if(pChatItem->msgType()== QString::number(MEDIA_MSG_DYNAMIC_EMOJI)){
            msg.msgtype = QString::number(MEDIA_MSG_DYNAMIC_EMOJI);
            QString path = pChatItem->body();
            if(path.contains("file://")){
                path.remove("file://");
            }
            QFileInfo file(path);
            msg.body = file.baseName();
        }
        m_pClient->sendMessage(msg);
    }

}

QString CDoodChatManager::handleEmojiText(QQuickTextDocument *item)
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
    return textContent;
}

void CDoodChatManager::sendMessage(Msg msg)
{
    qDebug() << Q_FUNC_INFO<<msg.limit_range.size();
    if(msg.limit_range.size()>0){
        qDebug() << Q_FUNC_INFO<<msg.limit_range[0];
    }
    msg.fromid = m_pClient->UserId();
    msg.name = m_pClient->userName();
    msg.targetName = mChatModel->getChatName();

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
        iter.value()->deleteAllMessage();

        iter.value()->clearList();
        delete iter.value();
        mMsgListModel.remove(targetid);
    }
    if(targetid == chatPageId()){
        emit removeCurrentChat();
    }
}

void CDoodChatManager::setMessageRead(QString targetid,QString msgid)
{
    qDebug() << Q_FUNC_INFO;
    m_pClient->setMessageRead(targetid,msgid);
}

void CDoodChatManager::getUnReadMessages()
{
    qDebug() << Q_FUNC_INFO;
    m_pClient->getUnReadMessages();
}

void CDoodChatManager::deleteMessage(QString targetid, QString localId)
{
    qDebug() << Q_FUNC_INFO;
    QStringList msgs;
    if(mChatModel != NULL){
        CDoodChatItem*item = mChatModel->itemById(localId);
        if(item != NULL){
            msgs.push_back(item->msgId());
        }
        m_pClient->deleteMessage(targetid,msgs);
        mChatModel->removeItemById(localId);
    }

}

void CDoodChatManager::revokeMessage(QString targetId, QString localId)
{
    qDebug()<<Q_FUNC_INFO;
    CDoodChatManagerModel* model = mMsgListModel.value(targetId,NULL);
    if(model != NULL){
        CDoodChatItem*item = model->itemById(localId);
        if(item != NULL){
            QDateTime cur = QDateTime::currentDateTime();
            qint64 dx = cur.secsTo(item->time());
            if(qFabs(dx)>60*5){
                emit revokeMessageOutTime();
            }else{
                Msg revokeMsg;
                revokeMsg.body = "您撤回了一条消息";
                revokeMsg.msgtype = QString::number(MEDIA_MSG_REVOKE);
                revokeMsg.targetid = m_sTargetid;
                revokeMsg.fromid = m_pClient->UserId();
                revokeMsg.name = m_pClient->userName();
                revokeMsg.msgid = item->msgId();
                revokeMsg.localid = item->localId();

                sendMessage(revokeMsg);
            }
        }
    }
}

void CDoodChatManager::transforMessage(QString targetid, QString targetName,QString avatar,QString localId)
{
    qDebug() << Q_FUNC_INFO;
    CDoodChatItem *pChatItem = mChatModel->itemById(localId);

    if(pChatItem != NULL){

        Msg msg;

        msg.targetName = targetName;
        msg.thumb_avatar = avatar;
        msg.isTransMsg = true;
        msg.targetid = targetid;
        msg.fromid =m_pClient->UserId();
        msg.name = m_pClient->userName();
        msg.localid = localId;
        msg.toid = targetid;
        QDateTime time;
        msg.time = time.currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
        msg.msgid = pChatItem->msgId();

        if(pChatItem->msgType()== QString::number(MSG_TYPE_TEXT)){
            msg.msgtype = QString::number(MSG_TYPE_TEXT);
            msg.msgProperties= pChatItem->textMsg();
            msg.body = pChatItem->body();
        }else if(pChatItem->msgType()== QString::number(MEDIA_MSG_DYNAMIC_EMOJI)){
            msg.msgtype = QString::number(MEDIA_MSG_DYNAMIC_EMOJI);
            QFileInfo file(pChatItem->body());
            msg.body = file.baseName();
        }
        else if(pChatItem->msgType()== QString::number(MSG_TYPE_FILE)){
            msg.msgtype = QString::number(MSG_TYPE_FILE);

            msg.f_path = pChatItem->filePath();
            QFile file(msg.f_path);
            msg.filename = file.fileName();
            msg.f_size = pChatItem->fileSize();

            msg.encrypt_user = pChatItem->mEnkeyUser;
            msg.encrypt_key = pChatItem->mEnkey;
            msg.f_url = pChatItem->mFileUrl;
        }
        else if(pChatItem->msgType()== QString::number(MSG_TYPE_IMG)){
            msg.msgtype = QString::number(MSG_TYPE_IMG);

            msg.main_url  = pChatItem->textMsg();
            QFile file(msg.main_url);
            msg.filename  = file.fileName();
            msg.i_height  = QString::number(THUMP_PIC_HEIGHT);
            msg.i_width   = QString::number(THUMP_PIC_WIDTH);

            msg.main_url = pChatItem->mImageMainUrl;
            msg.thumb_url = pChatItem->mImageThumbUrl;

            msg.encrypt_user = pChatItem->mEnkeyUser;
            msg.encrypt_key = pChatItem->mEnkey;
        }
        m_pClient->sendMessage(msg);
    }
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
    if(mChatModel != NULL){
        mChatModel->exitChat();
    }
}

QString CDoodChatManager::chatPageId()
{
    qDebug() << Q_FUNC_INFO;
    QString path = APP_DATA_PATH;
    QString fileName = path+ "config.ini";
    QSettings settings(fileName, QSettings::IniFormat);
    return settings.value("SessionTargetID","").toString();
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

void CDoodChatManager::downloadMainImage(QString main_url, QString encryptkey, QString targetId)
{
    qDebug() << Q_FUNC_INFO<<main_url<<encryptkey<<targetId;
    m_pClient->downloadMainImage(main_url,encryptkey,targetId);
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

void CDoodChatManager::downloadHistoryImage(QString url, QString property, QString targetid, QString localid)
{
    qDebug() << Q_FUNC_INFO;
    m_pClient->downloadHistoryImage(url, property, targetid, localid);
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

void CDoodChatManager::groupMemsChanged(QString groupid, int size)
{
    CDoodChatManagerModel* item = mMsgListModel.value(groupid,NULL);
    if(item != NULL){
        item->updateGroupSize(size);
    }
}

void CDoodChatManager::onDraftChanged(QString draft)
{

    emit draftChanged(m_sTargetid,mChatModel->avatar(),mChatModel->getChatName(),mChatModel->chatType(),draft);
}

void CDoodChatManager::onDeleteMessage(QString targetId, QStringList msgs)
{
    qDebug()<<Q_FUNC_INFO;
    m_pClient->deleteMessage(targetId,msgs);
}

void CDoodChatManager::onGetOrgUserInfoResult(int code, OrgUser orguser)
{
    CDoodChatManagerModel* item = mMsgListModel.value(orguser.id,NULL);
    if(item != NULL){
        item->setName(orguser.name);
    }
}

void CDoodChatManager::onUploadImageProgess(QString targetId, QString localId, int progress )
{
    qDebug()<<Q_FUNC_INFO;
    CDoodChatManagerModel* item = mMsgListModel.value(targetId);
    if(item != NULL){
        CDoodChatItem*chatItem = item->itemById(localId);
        if(chatItem != NULL){
            chatItem->setProgress(progress);
            if(progress == 100){
                chatItem->setLoading(false);
            }
            qDebug()<<Q_FUNC_INFO<<"progress:"<<progress;
        }
    }
}

void CDoodChatManager::onGetGroupMemberListReslut(int code, QString id, MemberList list)
{
    if(list.size() == 0){
        return;
    }
    CDoodChatManagerModel* item = mMsgListModel.value(id,NULL);
    if(item != NULL){
        item->updateGroupMems(list);
    }
}

void CDoodChatManager::onGroupMemberListChanged(QString operType, QString GroupId, MemberList memberlist)
{
    qDebug()<<Q_FUNC_INFO;
    CDoodChatManagerModel* item = mMsgListModel.value(GroupId,NULL);
    if(item != NULL){
        if(operType =="32"){//delete
            int len = memberlist.size();
            for(int i =0;i<len;++i){
                item->removeItemsByFromId(memberlist.at(i).id);
            }
        }else if(operType =="1"){
            item->addGroupMems(memberlist);
        }
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
    qDebug()<<Q_FUNC_INFO<<avatar;
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

void CDoodChatManager::onDownloadImage(QString targetId, QString localId, QString url, QString enkey)
{
    downloadHistoryImage(url,enkey,targetId,localId);
}

void CDoodChatManager::onDownloadMainImageResult(QString main_url, QString localpath)
{
    qDebug() << Q_FUNC_INFO;
    emit downloadMainImageResult(main_url,localpath);
}


void CDoodChatManager::onChatAvatarChanged(QString id, QString avatar)
{
    //    qDebug() << Q_FUNC_INFO<<"id:"<<id<< "avater:"<<avatar;
    if(id != ""){
        QList<CDoodChatManagerModel*> list = mMsgListModel.values();
        int len = list.size();
        for(int i = 0;i<len;++i){
            CDoodChatManagerModel* item = list.at(i);
            if(item != NULL){
                item->updateAvatar(id,avatar);
            }
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
    bool isFromPC = false;
    if(msg.localid =="" || msg.localid =="0"){
        msg.localid = m_pClient->createMsgId();
    }
    if(msg.fromid == m_pClient->UserId()){
        CDoodChatManagerModel* item = mMsgListModel.value(msg.targetid,NULL);
        if(item != NULL && item->chatType() =="6"){
            msg.thumb_avatar = "qrc:/res/icon_pc.png";
        }
        isFromPC = true;
    }
    updateMsgToListView(msg,isFromPC);

    emit newMessageNotice();
}

void CDoodChatManager::onChatSendMessageResult(bool code, QString sendTime, QString msgId)
{
    QStringList list = msgId.split(":");
    QString curMsgId= list[0],localId= list[1],targetId= list[2];

    CDoodChatItem* item = NULL;
    CDoodChatManagerModel* model = NULL;
    if(mChatModel->id() == targetId){
        item = mChatModel->itemById(localId);
        model = mChatModel;
    }else{
        QMap<QString,CDoodChatManagerModel*>::iterator iter  = mMsgListModel.find(targetId);
        if(iter != mMsgListModel.end()){
            model = iter.value();
            if(model != NULL){
                item = model->itemById(localId);
            }
        }
    }
    if(list.at(list.size()-1) == "revoke"){
        deleteMessage(targetId,localId);
        Msg msg;
        msg.body = "您撤回了一条消息";
        msg.msgtype = QString::number(MSG_TYPE_TIP);
        msg.fromid = m_pClient->UserId();
        msg.targetid = targetId;
        msg.localid = localId;
        msg.msgid = curMsgId;
        QDateTime time = QDateTime::fromMSecsSinceEpoch(sendTime.toLongLong());
        msg.time = time.toString("yyyy-MM-dd hh:mm:ss");
        if(model != NULL){
            model->addItemToListViewModel(msg);
        }
    }else{
        if(item != NULL){
            item->setLoading(false);
            item->setStatus(code);
            item->setMsgId(curMsgId);
            //item->setTime(sendTime);
        }
    }
}

void CDoodChatManager::onChatGetMessagesResult(bool code, QString sessionId, MsgList msgList)
{
    if(mChatModel != NULL && mChatModel->id() == sessionId){
        qDebug() << Q_FUNC_INFO<< "mChatModel size:"<<msgList.size();
        mChatModel->analyzeHistoryMsg(msgList);
        //        emit chatPageChanged();
    }else{
        QMap<QString,CDoodChatManagerModel*>::iterator model = mMsgListModel.find(sessionId);
        if(model != mMsgListModel.end()){
            model.value()->analyzeHistoryMsg(msgList);
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

void CDoodChatManager::onDownloadHistoryImage(int code, QString localpath, QString targetid, QString localid)
{
    CDoodChatManagerModel* item = mMsgListModel.value(targetid,NULL);
    if(item != NULL){
        CDoodChatItem* chatItem = item->itemById(localid);
        if(chatItem != NULL){
            if(code == 0){
                chatItem->setLoading(false);
                chatItem->setBody("file:// "+localpath);
            }else{
                chatItem->setLoading(false);
                chatItem->setStatus(false);
            }
        }
    }
}

void CDoodChatManager::onTransMessageFinishBack(int code, QString info)
{
    QStringList list = info.split(":");
    QString targetId = list.at(0),localId=list.at(1),name=list.at(2),avatar=list.at(3),time=list.at(4);
    if(mChatModel != NULL){
        CDoodChatItem* chatItem = mChatModel->itemById(localId);
        if(chatItem != NULL){
            CDoodChatManagerModel* model = mMsgListModel.value(targetId);
            if(model == NULL){
                model = new CDoodChatManagerModel(this);
                initModelConnects(model);
                model->setId(targetId);
                model->setName(name);
                model->setChatType("1");
                model->setAvatar(avatar);
                mMsgListModel[targetId] = model;
            }
            QDateTime msgDate = QDateTime::fromString(time, "yyyy-MM-dd hh:mm:ss");
            //bool bShow = isJudageShowTime(msgDate);

            CDoodChatItem *pChatItem = new CDoodChatItem(model);
            pChatItem->setLocalId(m_pClient->createMsgId());
            pChatItem->setMsgType(chatItem->msgType());
            pChatItem->setActiveType(chatItem->activeType());
            pChatItem->setMsgId(chatItem->msgId());
            pChatItem->setTargetId(targetId);
            pChatItem->setFromId(m_pClient->UserId());
            pChatItem->setName(chatItem->name());
            pChatItem->setTime(msgDate);
            pChatItem->setShowTime(false);
            pChatItem->setLoading(false);
            pChatItem->setContactThumbAvatar(mActAvatar);
            pChatItem->setIsMyselft(true);
            if(chatItem->msgType().toInt() == MSG_TYPE_FILE){
                pChatItem->setFileSize(chatItem->fileSize());
                pChatItem->setThumbAvatar(chatItem->thumbAvatar());
                pChatItem->setTar_thumbAvatar(chatItem->tar_thumbAvatar());
                pChatItem->setTextMsg(chatItem->textMsg());
                pChatItem->setBody(chatItem->body());
                pChatItem->setFilePath(chatItem->filePath());

                pChatItem->mFileUrl = pChatItem->mFileUrl;
            }
            else if(chatItem->msgType().toInt() == MSG_TYPE_IMG){

                pChatItem->setBody(chatItem->body());
                pChatItem->setTar_thumbAvatar(chatItem->tar_thumbAvatar());
                pChatItem->setTextMsg(chatItem->textMsg());

                pChatItem->mImageMainUrl = chatItem->mImageMainUrl;
                pChatItem->mImageThumbUrl = chatItem->mImageThumbUrl;
            }
            else{
                pChatItem->setBody(chatItem->body());
            }
            pChatItem->mEnkey =chatItem->mEnkey;
            pChatItem->mEnkeyUser = chatItem->mEnkeyUser;
            model->addChatItemtoMap(pChatItem);
        }
    }
    qDebug()<<Q_FUNC_INFO<<"trans msg code:"<<code;

    emit transforMessageBack(code);
}

void CDoodChatManager::onUploadFileBackUrl(QString targetId, QString localId, QString fileUrl, QString enkey)
{
    CDoodChatManagerModel* item = mMsgListModel.value(targetId,NULL);
    if(item != NULL){
        CDoodChatItem* chatItem = item->itemById(localId);
        if(chatItem != NULL){
            chatItem->mFileUrl = fileUrl;
            chatItem->mEnkey = enkey;
            chatItem->mEnkeyUser = targetId;
        }
    }
}

void CDoodChatManager::onUploadImgeBackUrl(QString targetId, QString localId, QString thumbUrl,QString mainUrl, QString enkey)
{
    CDoodChatManagerModel* item = mMsgListModel.value(targetId,NULL);
    if(item != NULL){
        CDoodChatItem* chatItem = item->itemById(localId);
        if(chatItem != NULL){
            chatItem->mImageMainUrl = mainUrl;
            chatItem->mImageThumbUrl = thumbUrl;
            chatItem->mEnkey = enkey;
            chatItem->mEnkeyUser = targetId;
            chatItem->setEncrypt_key(enkey);
            chatItem->setBodyBig(mainUrl);
        }
    }
}

void CDoodChatManager::onChatGetFileList(int code, FileInfoList files)
{
    qDebug() << Q_FUNC_INFO;
}

void CDoodChatManager::onGetUserInfo(int code, Contact contact)
{
    QList<CDoodChatManagerModel*> list = mMsgListModel.values();
    for(int i = 0;i<list.size();++i){
        CDoodChatManagerModel*model = list.at(i);
        if(model != NULL){
            model->updateItemData(contact.id,contact.name,contact.thumbAvatar);
        }
    }
}

void CDoodChatManager::onReqestUserInfo(QString userId)
{
    m_pClient->getUserInfo(userId);
}

void CDoodChatManager::onGroupInfoChanged(QString type, Group gp)
{
    QList<CDoodChatManagerModel*> list = mMsgListModel.values();
    for(int i =0; i<list.size();++i){
        CDoodChatManagerModel* model = list.at(i);
        if(model != NULL){
            if(model->id() == gp.id){
                model->setName(gp.name);
                if(gp.thumbAvatar != ""){
                    model->setAvatar(gp.thumbAvatar);
                }
                return;
            }
        }
    }
}

void CDoodChatManager::scaledImage(QString sourceImagePath, float scaledWidth, float scaledHeight, QString &outImagePath,bool isRotate)
{
    qDebug()<<Q_FUNC_INFO<<"1111111111111:"<<sourceImagePath;
    QSize sourceSize;
    int sourceWidth = 0;
    int sourceHeight = 0;
    int resultWidth = 0;
    int resultHeight = 0;
    float scaledNum = 0;      //缩放比例

    QImage sourceImage(sourceImagePath);
    if(isRotate){
        QMatrix matrix;
        matrix.rotate(90);
        sourceImage = sourceImage.transformed(matrix);
    }
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

    QImage destinationImage400x300 = sourceImage.scaled(QSize(resultWidth, resultHeight), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    QFileInfo fileInfo(sourceImagePath);


    QString tempImagePath = APP_DATA_PATH +m_pClient->UserId() + "/cache";
    QDir tempDir;
    if (!tempDir.exists(tempImagePath))
    {
        tempDir.mkdir(tempImagePath);
    }

    outImagePath = tempImagePath + "/" + fileInfo.baseName() + "_" + QString::number(scaledWidth)
            + "x" + QString::number(scaledHeight) + ".jpg";
    destinationImage400x300.save(outImagePath, "JPEG", 99);

}
