#ifndef CDOODUSERPROFILEMANAGER_H
#define CDOODUSERPROFILEMANAGER_H

#include <QObject>
#include "linkdoodclient.h"

class CDoodUserProfileManager : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString id READ id WRITE setId NOTIFY idChanged)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString gender READ gender WRITE setGender NOTIFY genderChanged)
    Q_PROPERTY(QString avatar READ avatar WRITE setAvatar NOTIFY avatarChanged)
    Q_PROPERTY(QString thumbAvatar READ thumbAvatar WRITE setThumbAvatar NOTIFY thumbAvatarChanged)

public:
    explicit CDoodUserProfileManager(LinkDoodClient *client = 0,QObject *parent = 0);

    QString id() const;
    Q_INVOKABLE QString setId(const QString &data);

    QString name() const;
    Q_INVOKABLE QString setName(const QString &data);

    QString gender() const;
    Q_INVOKABLE QString setGender(const QString &data);


    QString avatar() const;
    Q_INVOKABLE QString setAvatar(const QString &data);


    QString thumbAvatar() const;
    Q_INVOKABLE QString setThumbAvatar(const QString &data);

    //获取账户信息
    Q_INVOKABLE void getAccountInfo(void);
signals:
    void idChanged();
    void nameChanged();
    void genderChanged();
    void avatarChanged();
    void thumbAvatarChanged();
public slots:
    //推送用户信息
    void onAccountInfoChanged(Contact user);
private:
    QString mId;
    QString mName;
    QString mThumbAvatar;
    QString mGender;
    QString mAvatar;

    void initConnect();
    LinkDoodClient *m_pClient;
};

#endif // CDOODUSERPROFILEMANAGER_H
