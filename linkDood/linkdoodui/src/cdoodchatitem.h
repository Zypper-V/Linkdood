#ifndef CDOODCHATITEM_H
#define CDOODCHATITEM_H

#include <QObject>
#include <QDateTime>

#define int64 long long

class CDoodChatItem : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString filePath READ filePath WRITE setFilePath NOTIFY filePathChanged)
    Q_PROPERTY(QString localId READ localId WRITE setLocalId NOTIFY localIdChanged)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString msgType READ msgType WRITE setMsgType NOTIFY msgTypeChanged)
    Q_PROPERTY(QString activeType READ activeType WRITE setActiveType NOTIFY activeTypeChanged)
    Q_PROPERTY(QString msgId READ msgId WRITE setMsgId NOTIFY msgIdChanged)
    Q_PROPERTY(QString targetId READ targetId WRITE setTargetId NOTIFY targetIdChanged)
    Q_PROPERTY(QString fromId READ fromId WRITE setFromId NOTIFY fromIdChanged)
    Q_PROPERTY(QString toId READ toId WRITE setToId NOTIFY toIdChanged)
    Q_PROPERTY(QDateTime time READ time WRITE setTime NOTIFY timeChanged)
    Q_PROPERTY(QString body READ body WRITE setBody NOTIFY bodyChanged)
    Q_PROPERTY(QString thumbAvatar READ thumbAvatar WRITE setThumbAvatar NOTIFY thumbAvatarChanged)
    Q_PROPERTY(QString tar_thumbAvatar READ tar_thumbAvatar WRITE setTar_thumbAvatar NOTIFY tar_thumbAvatarChanged)
    Q_PROPERTY(bool loading READ loading WRITE setLoading NOTIFY loadingChanged)
    Q_PROPERTY(bool status READ status WRITE setStatus NOTIFY statusChanged)
    Q_PROPERTY(int progress READ progress WRITE setProgress NOTIFY progressChanged)
    Q_PROPERTY(QString textMsg READ textMsg WRITE setTextMsg NOTIFY textMsgChanged)
    Q_PROPERTY(long long fileSize READ fileSize WRITE setFileSize NOTIFY fileSizeChanged)
    Q_PROPERTY(QString contactThumbAvatar READ contactThumbAvatar WRITE setContactThumbAvatar NOTIFY contactThumbAvatarChanged)


public:

    explicit CDoodChatItem(QObject *parent = 0);

    long long fileSize() const;
    long long setFileSize(const long long data);

    int progress() const;
    int setProgress(const int &data);

    bool loading() const;
    bool setLoading(const bool &data);

    bool status() const;
    bool setStatus(const bool &data);

    QString name() const;
    QString setName(const QString &data);

    QString thumbAvatar() const;
    QString setThumbAvatar(const QString &data);

    QString tar_thumbAvatar() const;
    QString setTar_thumbAvatar(const QString &data);

    QString msgType() const;
    QString setMsgType(const QString &data);

    QString activeType() const;
    QString setActiveType(const QString &data);

    QString msgId() const;
    QString setMsgId(const QString &data);

    QString targetId() const;
    QString setTargetId(const QString &data);

    QString fromId() const;
    QString setFromId(const QString &data);

    QString toId() const;
    QString setToId(const QString &data);

    QDateTime time() const;
    QDateTime setTime(const QDateTime &data);

    QString body() const;
    QString setBody(const QString &data);

    QString localId() const;
    QString setLocalId(const QString &data);

    QString textMsg();
    QString setTextMsg(const QString&data);

    QString filePath();
    QString setFilePath(const QString&data);

    QString contactThumbAvatar();
    QString setContactThumbAvatar(const QString &data);

    void setIsMyselft(bool isMyselft);
signals:
    void thumbAvatarChanged();
    void tar_thumbAvatarChanged();
    void msgTypeChanged();
    void activeTypeChanged();
    void msgIdChanged();
    void targetIdChanged();
    void fromIdChanged();
    void toIdChanged();
    void timeChanged();
    void bodyChanged();
    void nameChanged();
    void loadingChanged();
    void statusChanged();
    void progressChanged();
    void fileSizeChanged();
    void localIdChanged();
    void textMsgChanged();    
    void contactThumbAvatarChanged();
    void filePathChanged();
private:
    QString mName;
    QString mThumbAvatar;    //为位图片时表示图片缩略图地址，为文件时表示文件下载地址
    QString mTar_thumbAvatar; //当为文件时表示encrypt_user
    QString mMsgType;// 消息类型
    QString mActiveType;// 消息事件属性 1. 阅后即焚 2 有问必答 3 活动
    QString mMsgId;// 消息 ID
    QString mTargetId; // 会话者 ID (群或用户等)
    QString mFromId;// 发送者 ID
    QString mToId;// 发送者 ID
    QDateTime mTime;// 发送时间
    QString mBody;// 消息内容  当接收的为文件时表示encrypt_key
    QString mTextMsg;//文本消息解析后内容 当发送的是文件时，这里保存文件名   当接收的为文件时表示文件名
    bool    mLoading;//true消息正在加载或发送中
    bool    mSatus;//true消息加载或发送成功
    int     mProgress;//图片或文件发送进度
    bool    mIsMyselft;// i send
    long long mFileSize;
    QString mLocalId;
    QString mContactThumbAvatar;
    QString mFilePath;
};

#endif // CDOODCHATITEM_H
