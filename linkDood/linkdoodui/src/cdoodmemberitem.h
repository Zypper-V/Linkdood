#ifndef CDOODMEMBERITEM_H
#define CDOODMEMBERITEM_H


#include <QObject>

#define int64 long long
class CDoodMemberItem : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString id READ id WRITE setId NOTIFY idChanged)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString avatar READ avatar WRITE setAvatar NOTIFY avatarChanged)
    Q_PROPERTY(QString thumbAvatar READ thumbAvatar WRITE setThumbAvatar NOTIFY thumbAvatarChanged)
    Q_PROPERTY(QString gender READ gender WRITE setGender NOTIFY genderChanged)
    Q_PROPERTY(QString team READ team WRITE setTeam NOTIFY teamChanged)
    Q_PROPERTY(QString groupid READ groupid WRITE setGroupid NOTIFY groupidChanged)
    Q_PROPERTY(QString remark READ remark WRITE setRemark NOTIFY remarkChanged)
    Q_PROPERTY(QString member_type READ member_type WRITE setMember_type NOTIFY member_typeChanged)
    Q_PROPERTY(QString sectionKey READ sectionKey WRITE setSection NOTIFY sectionChanged)
    Q_PROPERTY(QString isChoose READ isChoose WRITE setIsChoose NOTIFY isChooseChanged)

public:
    explicit CDoodMemberItem(QObject *parent = 0);
    QString id() const;
    QString setId(const QString &data);

    QString name() const;
    QString setName(const QString &data);

    QString avatar() const;
    QString setAvatar(const QString &data);

    QString thumbAvatar() const;
    QString setThumbAvatar(const QString &data);

    QString gender() const;
    QString setGender(const QString &data);

    QString team() const;
    QString setTeam(const QString &data);

    QString groupid() const;
    QString setGroupid(const QString &data);

    QString remark() const;
    QString setRemark(const QString &data);

    QString member_type() const;
    QString setMember_type(const QString &data);

    QString sectionKey() const;
    QString setSection(const QString &section);

    QString isChoose() const;
    QString setIsChoose(const QString &data);

signals:
    void idChanged();
    void nameChanged();
    void avatarChanged();
    void thumbAvatarChanged();
    void genderChanged();
    void teamChanged();
    void groupidChanged();
    void remarkChanged();
    void member_typeChanged();
    void sectionChanged();
    void isChooseChanged();
public slots:

private:
    QString mId;
    QString mName;
    QString mThumbAvatar;
    QString mAvatar;
    QString mGender;
    QString mTeam;
    QString mGroupid;
    QString mRemark;
    QString mMember_type;
    QString mSection;
    QString mIsChoose;
};

#endif // CDOODMEMBERITEM_H
