#ifndef CDOODCONTACTITEM_H
#define CDOODCONTACTITEM_H

#include <QObject>

#define int64 long long
class CDoodContactItem : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString id READ id WRITE setId NOTIFY idChanged)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString gender READ gender WRITE setGender NOTIFY genderChanged)
    Q_PROPERTY(QString timeZone READ timeZone WRITE setTimeZone NOTIFY timeZoneChanged)
    Q_PROPERTY(QString avatar READ avatar WRITE setAvatar NOTIFY avatarChanged)
    Q_PROPERTY(QString isStar READ isStar WRITE setIsStar NOTIFY isStarChanged)
    Q_PROPERTY(QString isVip READ isVip WRITE setIsVip NOTIFY isVipChanged)
    Q_PROPERTY(QString pinYin READ pinYin WRITE setPinYin NOTIFY pinYinChanged)
    Q_PROPERTY(QString remark READ remark WRITE setRemark NOTIFY remarkChanged)
    Q_PROPERTY(QString server READ server WRITE setServer NOTIFY serverChanged)
    Q_PROPERTY(QString thumbAvatar READ thumbAvatar WRITE setThumbAvatar NOTIFY thumbAvatarChanged)
    Q_PROPERTY(QString sectionKey READ sectionKey WRITE setSection NOTIFY sectionChanged)


public:
    explicit CDoodContactItem(QObject *parent = 0);
    QString id() const;
    QString setId(const QString &data);

    QString name() const;
    QString setName(const QString &data);

    QString gender() const;
    QString setGender(const QString &data);

    QString timeZone() const;
    QString setTimeZone(const QString &data);

    QString avatar() const;
    QString setAvatar(const QString &data);

    QString isStar() const;
    QString setIsStar(const QString &data);

    QString isVip() const;
    QString setIsVip(const QString &data);

    QString pinYin() const;
    QString setPinYin(const QString &data);

    QString remark() const;
    QString setRemark(const QString &data);

    QString server() const;
    QString setServer(const QString &data);

    QString thumbAvatar() const;
    QString setThumbAvatar(const QString &data);

    QString sectionKey() const;
    QString setSection(const QString &section);

    bool isOrg() const;
    bool setIsOrg(bool isOrg);

signals:
    void idChanged();
    void nameChanged();
    void isStarChanged();
    void isVipChanged();
    void pinYinChanged();
    void remarkChanged();
    void serverChanged();
    void genderChanged();
    void timeZoneChanged();
    void avatarChanged();
    void thumbAvatarChanged();
    void isOrgChanged();
    void sectionChanged();
public slots:

private:
    QString mId;
    QString mName;
    QString mThumbAvatar;
    QString mGender;
    QString mTimeZone;
    QString mAvatar;
    QString mIsStar;
    QString mIsVip;
    QString mPinYin;
    QString mRemark;
    QString mServer;
    QString mSection;
    bool mIsOrg;

};
#endif // CDOODCONTACTITEM_H
