#ifndef CDDODUSERDATAITEM_H
#define CDDODUSERDATAITEM_H
#include <QObject>
#include "linkdoodtypes.h"

class LinkDoodClient;
class CDoodUserDataManage : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString remark READ remark WRITE setRemark NOTIFY remarkChanged)
    Q_PROPERTY(QString id READ id WRITE setId NOTIFY idChanged)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString gender READ gender WRITE setGender NOTIFY genderChanged)
    Q_PROPERTY(QString avatar READ avatar WRITE setAvatar NOTIFY avatarChanged)
    Q_PROPERTY(QString thumbAvatar READ thumbAvatar WRITE setThumbAvatar NOTIFY thumbAvatarChanged)
    Q_PROPERTY(bool isFriend READ isFriend WRITE setIsFriend NOTIFY isFriendChanged)
    Q_PROPERTY(QString phone READ phone WRITE setPhone NOTIFY phoneChanged)
    Q_PROPERTY(QString buttonType READ buttonType WRITE setButtonType NOTIFY buttonTypeChanged)
    Q_PROPERTY(QString groupid READ groupid WRITE setGroupid NOTIFY groupidChanged)
    Q_PROPERTY(QString memberType READ memberType WRITE setMemberType NOTIFY memberTypeChanged)
public:
    explicit CDoodUserDataManage(LinkDoodClient *client = 0,QObject *parent = 0);

    Q_INVOKABLE void clearData();

    Q_INVOKABLE void setRemark(QString remark);
    QString remark();
    QString phone();
    void    setPhone(QString phone);
    QString id() const;
    Q_INVOKABLE QString setId(const QString &data);

    QString name() const;
    Q_INVOKABLE QString setName(const QString &data);

    QString gender() const;
    Q_INVOKABLE QString setGender(const QString &data);


    QString buttonType() const;
    Q_INVOKABLE QString setButtonType(const QString &data);

    QString groupid() const;
    Q_INVOKABLE QString setGroupid(const QString &data);

    QString memberType() const;
    Q_INVOKABLE QString setMemberType(const QString &data);

    QString avatar() const;
    Q_INVOKABLE QString setAvatar(const QString &data);

    QString thumbAvatar() const;
    Q_INVOKABLE QString setThumbAvatar(const QString &data);

    bool isFriend() const;
    Q_INVOKABLE bool setIsFriend(const bool &data);

signals:
    void idChanged();
    void nameChanged();
    void genderChanged();
    void avatarChanged();
    void thumbAvatarChanged();
    void isFriendChanged();
    void buttonTypeChanged();
    void groupidChanged();
    void memberTypeChanged();
    void remarkChanged();
    void phoneChanged();
public slots:
    void onGetContactInfoResult(Contact contact);
private:
    QString mId;
    QString mName;
    QString mThumbAvatar;
    QString mGender;
    QString mAvatar;
    bool mIsFriend;
    QString mRemark;
    QString mPhone;
    QString mButtonType;  //1.群成员点击自己 2.群主/管理员点其他成员 3.点击好友
    QString mGroupid;
    QString mMemberType;
    LinkDoodClient *m_pClient;
    void initConnect();
};
#endif // CDOODCONTACTITEM_H
