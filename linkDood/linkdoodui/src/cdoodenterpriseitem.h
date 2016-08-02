#ifndef CDOODENTERPRISEITEM_H
#define CDOODENTERPRISEITEM_H

#include <QObject>
class CDoodEnterPriseItem: public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString id READ id WRITE setId NOTIFY idChanged)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString gender READ gender WRITE setGender NOTIFY genderChanged)
    Q_PROPERTY(QString avatar READ avatar WRITE setAvatar NOTIFY avatarChanged)
    Q_PROPERTY(QString remark READ remark WRITE setRemark NOTIFY remarkChanged)
    Q_PROPERTY(QString order_num READ order_num WRITE setOrder_num NOTIFY order_numChanged)
    Q_PROPERTY(QString thumbAvatar READ thumbAvatar WRITE setThumbAvatar NOTIFY thumbAvatarChanged)
    Q_PROPERTY(QString onlineStatus READ onlineStatus WRITE setOnlineStatus NOTIFY onlineStatusChanged)
public:
    explicit CDoodEnterPriseItem(QObject *parent = 0);
    QString id() const;
    QString setId(const QString &data);

    QString name() const;
    QString setName(const QString &data);

    QString gender() const;
    QString setGender(const QString &data);

    QString avatar() const;
    QString setAvatar(const QString &data);

    QString remark() const;
    QString setRemark(const QString &data);

    QString order_num() const;
    QString setOrder_num(const QString &data);

    QString thumbAvatar() const;
    QString setThumbAvatar(const QString &data);

    QString onlineStatus() const;
    QString setOnlineStatus(const QString &onlineStatus);
signals:
    void idChanged();
    void nameChanged();
    void remarkChanged();
    void genderChanged();
    void avatarChanged();
    void order_numChanged();
    void thumbAvatarChanged();
    void onlineStatusChanged();
public slots:

private:
    QString mId;
    QString mName;
    QString mThumbAvatar;
    QString mGender;
    QString mAvatar;
    QString mOrder_num;
    QString mRemark;
    QString mOnlineStatus;
};

#endif // CDOODENTERPRISEITEM_H
