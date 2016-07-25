#ifndef CDOODSYSMSGITEM_H
#define CDOODSYSMSGITEM_H

#include <QObject>

class CDoodSysmsgItem : public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool isShowButton READ isShowButton WRITE setIsShowButton NOTIFY  isShowButtonChanged)
    Q_PROPERTY(QString msgid READ msgid WRITE setMsgid NOTIFY msgidChanged)
    Q_PROPERTY(QString targetid READ targetid WRITE setTargetid NOTIFY targetidChanged)
    Q_PROPERTY(QString time READ time WRITE setTime NOTIFY timeChanged)
    Q_PROPERTY(QString msgtypeText READ msgtypeText WRITE setMsgtypeText NOTIFY msgtypeTextChanged)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString avatar READ avatar WRITE setAvatar NOTIFY avatarChanged)
    Q_PROPERTY(QString respons READ respons WRITE setRespons NOTIFY responsChanged)
    Q_PROPERTY(QString info READ info WRITE setInfo NOTIFY infoChanged)
    Q_PROPERTY(QString msgType READ msgType WRITE setMsgType NOTIFY msgTypeChanged)

public:
    explicit CDoodSysmsgItem(QObject *parent = 0);

    bool isShowButton() const;
    bool setIsShowButton(bool data);

    QString msgType() const;
    QString setMsgType(QString data);

    QString msgid() const;
    QString setMsgid(QString data);

    QString targetid() const;
    QString setTargetid(QString data);

    QString time() const;
    QString setTime(QString data);

    QString msgtypeText() const;
    QString setMsgtypeText(QString data);

    QString name() const;
    QString setName(QString data);

    QString avatar() const;
    QString setAvatar(QString data);

    QString respons() const;
    QString setRespons(QString data);

    QString info() const;
    QString setInfo(QString data);


signals:
    void isShowButtonChanged();
    void msgidChanged();
    void targetidChanged();
    void timeChanged();
    void msgtypeTextChanged();
    void nameChanged();
    void avatarChanged();
    void responsChanged();
    void infoChanged();
    void msgTypeChanged();
private:
    bool    mIsShowButton;  //是否显示按钮
    QString mMsgid;         //消息ID
    QString mTargetid;      //目标ID
    QString mTime;          //时间
    QString mMsgtypeText;   //消息类型
    QString mName;          //消息来源名称
    QString mAvatar;        //消息来源头像
    QString mRespons;       //响应
    QString mInfo;          //消息内容
    QString mMsgType;
};

#endif // CDOODSYSMSGITEM_H
