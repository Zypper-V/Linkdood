#include "cdoodchatitem.h"
#include "common.h"
#include <QImage>
#include <QJsonObject>
#include <QJsonDocument>
#include "linkdoodtypes.h"

CDoodChatItem::CDoodChatItem(QObject *parent) : QObject(parent)
{
    mLoading = false;
    mSatus = true;
    mTextMsg = "";
    mProgress = 1;
    mFileSize = 0;
    mLocalId = "";

    mName = "";
    mThumbAvatar = "";
    mTar_thumbAvatar ="";
    mMsgType = "";
    mActiveType = "";
    mMsgId = "";
    mTargetId ="";
    mFromId = "";
    mToId = "";
    mBody ="";
    mShowTime = false;
    mEnkey = mEnkeyUser=mFileUrl=mImageMainUrl=mImageThumbUrl="";
    mIsImageChange = true;
    mImgW = 80;
    mImgH = 80;
    mTextFormat = Qt::PlainText;
}

void CDoodChatItem::setTextFormat(int format)
{
    mTextFormat = format;
    emit textFormatChanged();
}

int CDoodChatItem::textFormat()
{
    if(mBody.contains("qrc")){
        return Qt::RichText;
    }else{
        return Qt::PlainText;
    }
    // return mTextFormat;
}

void CDoodChatItem::setEnkeyUser(QString data)
{
    mEnkeyUser = data;
    emit enkeyUserChanged();
}

QString CDoodChatItem::enkeyUser()
{
    return mEnkeyUser;
}

int CDoodChatItem::imgWidth()
{
    return mImgW;
}

void CDoodChatItem::setImgWidth(int w)
{
    if(w != 0){
        mImgW = w;
    }
    emit imgWidthChanged();
}

int CDoodChatItem::imgHeight()
{
    return mImgH;
}

void CDoodChatItem::setImgHeight(int h)
{
    if(h != 0){
        h = h>600 ? 600 :h;
        mImgH = h;
    }
    emit imgHeightChanged();
}

long long CDoodChatItem::fileSize() const
{
    return mFileSize;
}

long long CDoodChatItem::setFileSize(const long long data)
{
    if(mFileSize == data) {
        return data;
    }
    mFileSize = data;
    emit fileSizeChanged();
    return mFileSize;
}

QString CDoodChatItem::timeText()
{
    QString time = Common::dealTime(mTime.toMSecsSinceEpoch(),2);
    return time;
}

void CDoodChatItem::setShowTime(bool show)
{
    if(show != mShowTime){
        mShowTime = show;
        emit showTimeChanged();
    }
}

bool CDoodChatItem::showTime()
{
    return mShowTime;
}

int CDoodChatItem::progress() const
{
    return mProgress;
}

int CDoodChatItem::setProgress(const int &data)
{
    if(mProgress == data) {
        return data;
    }
    mProgress = data;
    emit progressChanged();
    return mProgress;
}

bool CDoodChatItem::loading() const
{
    return mLoading;
}

bool CDoodChatItem::setLoading(const bool &data)
{
    if(mLoading == data) {
        return data;
    }
    mLoading = data;
    emit loadingChanged();
    return mLoading;
}

bool CDoodChatItem::status() const
{
    return mSatus;
}

bool CDoodChatItem::setStatus(const bool &data)
{
    if(mSatus == data) {
        return data;
    }
    mSatus = data;
    emit statusChanged();
    return mSatus;
}

bool CDoodChatItem::isImageChange()
{
    return mIsImageChange;
}

void CDoodChatItem::setIsImageChange(bool data)
{
    mIsImageChange = !mIsImageChange;
    emit isImageChangeChanged();
}

QString CDoodChatItem::name() const
{
    if(mName ==""){
        return mFromId;
    }
    return mName;
}

QString CDoodChatItem::setName(const QString &data)
{
    if(mName == data) {
        return data;
    }
    mName = data;
    emit nameChanged();
    return mName;
}

QString CDoodChatItem::thumbAvatar() const
{
    return mThumbAvatar;
}

QString CDoodChatItem::setThumbAvatar(const QString &data)
{
    if(mThumbAvatar == data) {
        return data;
    }
    mThumbAvatar = data;
    emit thumbAvatarChanged();
    return mThumbAvatar;
}


QString CDoodChatItem::tar_thumbAvatar() const
{
    return mTar_thumbAvatar;
}

QString CDoodChatItem::setTar_thumbAvatar(const QString &data)
{
    if(mTar_thumbAvatar == data) {
        return data;
    }
    mTar_thumbAvatar = data;
    emit tar_thumbAvatarChanged();
    return mTar_thumbAvatar;
}

QString CDoodChatItem::msgType() const
{
    return mMsgType;
}

QString CDoodChatItem::setMsgType(const QString &data)
{
    if(mMsgType == data) {
        return data;
    }
    mMsgType = data;
    emit msgTypeChanged();
    return mMsgType;
}

QString CDoodChatItem::activeType() const
{
    return mActiveType;
}

QString CDoodChatItem::setActiveType(const QString &data)
{
    if(mActiveType == data) {
        return data;
    }
    mActiveType = data;
    emit activeTypeChanged();
    return mActiveType;
}

QString CDoodChatItem::msgId() const
{
    return mMsgId;
}

QString CDoodChatItem::setMsgId(const QString &data)
{
    if(mMsgId == data) {
        return data;
    }
    mMsgId = data;
    emit msgIdChanged();
    return mMsgId;
}

QString CDoodChatItem::targetId() const
{
    return mTargetId;
}

QString CDoodChatItem::setTargetId(const QString &data)
{
    if(mTargetId == data) {
        return data;
    }
    mTargetId = data;
    emit targetIdChanged();
    return mTargetId;
}

QString CDoodChatItem::fromId() const
{
    return mFromId;
}

QString CDoodChatItem::setFromId(const QString &data)
{
    if(mFromId == data) {
        return data;
    }
    mFromId = data;
    emit fromIdChanged();
    return mFromId;
}

QString CDoodChatItem::toId() const
{
    return mToId;
}

QString CDoodChatItem::setToId(const QString &data)
{
    if(mToId == data) {
        return data;
    }
    mToId = data;
    emit toIdChanged();
    return mToId;
}

QDateTime CDoodChatItem::time() const
{
    return mTime;
}

QDateTime CDoodChatItem::setTime(const QDateTime &data)
{
    if(mTime == data) {
        return data;
    }
    mTime = data;
    emit timeChanged();
    return mTime;
}

QString CDoodChatItem::body()
{
    if(msgType() == "2"){
        QString tmp = mBody;
        QByteArray bytes = tmp.toLocal8Bit();
        if(tmp.startsWith("{\"body\":")){
            QJsonParseError error;
            QJsonDocument jsonDocument = QJsonDocument::fromJson(bytes, &error);
            if (error.error == QJsonParseError::NoError && jsonDocument.isObject()){
                tmp = jsonDocument.object()["body"].toString();
            }else{
                if(tmp.contains("body\":")){
                    tmp.remove(0,9);
                    tmp.remove(tmp.length()-2,2);
                }
            }
            if(tmp.contains("qrc:")){
                tmp.replace("\n", "<br>");
            }
            return tmp;
        }
    }
    return mBody;
}

QString CDoodChatItem::setBody(const QString &data)
{
    if(data!= "" /*&& mBody != data*/){
        mBody = data;

        if(msgType() == "5"){
            mIsImageChange = !mIsImageChange;
            QString path = mBody;
            if(path.startsWith("file://")){
                path.remove("file://");
            }
            QImage img(path);
            setImgWidth(img.width());
            setImgHeight(img.height());
            emit isImageChangeChanged();
        }
        emit bodyChanged();
    }

    return mBody;
}

QString CDoodChatItem::encrypt_key() const
{
    return mEncrypt_key;
}

QString CDoodChatItem::setEncrypt_key(const QString &data)
{
    if(data!=""){
        mEncrypt_key=data;
        emit encrypt_keyChanged();
    }
    return mEncrypt_key;
}

QString CDoodChatItem::bodyBig() const
{
    return mBodyBig;
}

QString CDoodChatItem::setBodyBig(const QString &data)
{
    if(data!=""){
        mBodyBig=data;
        emit bodyBigChanged();
    }
    return mBodyBig;
}

QString CDoodChatItem::localId() const
{
    return mLocalId;
}

QString CDoodChatItem::setLocalId(const QString &data)
{
    if(mLocalId == data) {
        return data;
    }
    mLocalId = data;
    emit bodyChanged();
    return mLocalId;
}

QString CDoodChatItem::textMsg()
{
    return mTextMsg;
}

QString CDoodChatItem::setTextMsg(const QString &data)
{
    if(mTextMsg == data)
        return data;
    mTextMsg = data;
    emit textMsgChanged();
    return mTextMsg;
}

QString CDoodChatItem::filePath()
{
    return mFilePath;
}

QString CDoodChatItem::setFilePath(const QString &data)
{
    if(data!="" && data!=mFilePath){
        mFilePath = data;
        emit filePathChanged();
    }
    return mFilePath;
}

QString CDoodChatItem::contactThumbAvatar()
{
    return mContactThumbAvatar;
}

QString CDoodChatItem::setContactThumbAvatar(const QString &data)
{
    if("" == data){
        return mContactThumbAvatar;
    }
    mContactThumbAvatar = data;
    emit contactThumbAvatarChanged();
    return mContactThumbAvatar;
}

void CDoodChatItem::setIsMyselft(bool isMyselft)
{
    mIsMyselft = isMyselft;
}



