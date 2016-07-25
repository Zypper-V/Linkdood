#ifndef CDOODGROUPITEM_H
#define CDOODGROUPITEM_H

#include <QObject>

#define int64 long long
class CDoodGroupItem : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString id READ id WRITE setId NOTIFY idChanged)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString timeZone READ timeZone WRITE setTimeZone NOTIFY timeZoneChanged)
    Q_PROPERTY(QString avatar READ avatar WRITE setAvatar NOTIFY avatarChanged)
    Q_PROPERTY(QString pinYin READ pinYin WRITE setPinYin NOTIFY pinYinChanged)
    Q_PROPERTY(QString server READ server WRITE setServer NOTIFY serverChanged)
    Q_PROPERTY(QString thumbAvatar READ thumbAvatar WRITE setThumbAvatar NOTIFY thumbAvatarChanged)
    Q_PROPERTY(QString level READ level WRITE setLevel NOTIFY levelChanged)
    Q_PROPERTY(QString sectionKey READ sectionKey WRITE setSection NOTIFY sectionChanged)


    Q_PROPERTY(QString f_fileid READ f_fileid WRITE setF_fileid NOTIFY f_fileidChanged)
    Q_PROPERTY(QString f_userid READ f_userid WRITE setF_userid NOTIFY f_useridChanged)
    Q_PROPERTY(QString f_username READ f_username WRITE setF_username NOTIFY f_usernameChanged)
    Q_PROPERTY(QString f_targetid READ f_targetid WRITE setF_targetid NOTIFY f_targetidChanged)
    Q_PROPERTY(QString f_size READ f_size WRITE setF_size NOTIFY f_sizeChanged)
    Q_PROPERTY(QString f_time READ f_time WRITE setF_time NOTIFY f_timeChanged)
    Q_PROPERTY(QString f_path READ f_path WRITE setF_path NOTIFY f_pathChanged)
    Q_PROPERTY(QString f_name READ f_name WRITE setF_name NOTIFY f_nameChanged)
    Q_PROPERTY(QString f_url READ f_url WRITE setF_url NOTIFY f_urlChanged)
    Q_PROPERTY(QString f_encrypt_key READ f_encrypt_key WRITE setF_encrypt_key NOTIFY f_encrypt_keyChanged)
public:
    explicit CDoodGroupItem(QObject *parent = 0);
    QString id() const;
    QString setId(const QString &data);

    QString name() const;
    QString setName(const QString &data);

    QString timeZone() const;
    QString setTimeZone(const QString &data);

    QString avatar() const;
    QString setAvatar(const QString &data);

    QString pinYin() const;
    QString setPinYin(const QString &data);

    QString server() const;
    QString setServer(const QString &data);

    QString thumbAvatar() const;
    QString setThumbAvatar(const QString &data);

    QString level() const;
    QString setLevel(const QString &data);

    QString sectionKey() const;
    QString setSection(const QString &section);

    QString f_fileid() const;
    QString setF_fileid(const QString &data);

    QString f_userid() const;
    QString setF_userid(const QString &data);

    QString f_username() const;
    QString setF_username(const QString &data);

    QString f_targetid() const;
    QString setF_targetid(const QString &data);

    QString f_size() const;
    QString setF_size(const QString &data);

    QString f_time() const;
    QString setF_time(const QString &data);

    QString f_path() const;
    QString setF_path(const QString &data);

    QString f_name() const;
    QString setF_name(const QString &data);

    QString f_url() const;
    QString setF_url(const QString &data);

    QString f_encrypt_key() const;
    QString setF_encrypt_key(const QString &data);

signals:
    void idChanged();
    void nameChanged();
    void pinYinChanged();
    void serverChanged();
    void timeZoneChanged();
    void avatarChanged();
    void thumbAvatarChanged();
    void levelChanged();
    void sectionChanged();

    void f_fileidChanged();
    void f_useridChanged();
    void f_usernameChanged();
    void f_targetidChanged();
    void f_sizeChanged();
    void f_timeChanged();
    void f_pathChanged();
    void f_nameChanged();
    void f_urlChanged();
    void f_encrypt_keyChanged();
public slots:

private:
    QString mId;
    QString mName;
    QString mThumbAvatar;
    QString mTimeZone;
    QString mAvatar;
    QString mPinYin;
    QString mServer;
    QString mLevel;
    QString mSection;

    QString mF_fileid;
    QString mF_userid;
    QString mF_username;
    QString mF_targetid;
    QString mF_size;
    QString mF_time;
    QString mF_path;
    QString mF_name;
    QString mF_url;
    QString mF_encrypt_key;
};
#endif // CDOODGROUPITEM_H
