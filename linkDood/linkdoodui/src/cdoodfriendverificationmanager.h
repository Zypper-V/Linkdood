#ifndef CDOODFRIENDVERIFICATIONMANAGER_H
#define CDOODFRIENDVERIFICATIONMANAGER_H

#include <QObject>

class CDoodFriendVerificationManager : public QObject
{
    Q_OBJECT
public:

    Q_PROPERTY(QString id READ id WRITE setId NOTIFY idChanged)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString thumbAvatar READ thumbAvatar WRITE setThumbAvatar NOTIFY thumbAvatarChanged)
    Q_PROPERTY(QString myName READ myName WRITE setMyName NOTIFY myNameChanged)
public:
    explicit CDoodFriendVerificationManager(QObject *parent = 0);

    QString id() const;
    Q_INVOKABLE QString setId(const QString &data);

    QString name() const;
    Q_INVOKABLE QString setName(const QString &data);

    QString thumbAvatar() const;
    Q_INVOKABLE QString setThumbAvatar(const QString &data);

    QString myName() const;
    Q_INVOKABLE QString setMyName(const QString &data);

signals:
    void idChanged();
    void nameChanged();
    void thumbAvatarChanged();
    void myNameChanged();

public slots:

private:
    QString mId;
    QString mName;
    QString mThumbAvatar;
    QString mMyname;
};

#endif // CDOODFRIENDVERIFICATIONMANAGER_H
