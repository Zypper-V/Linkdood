#ifndef CDOODUSERPROFILEMANAGER_H
#define CDOODUSERPROFILEMANAGER_H

#include <QObject>
#include "linkdoodclient.h"
#include "csystempackagemanager.h"
class CDoodUserProfileManager : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString id READ id WRITE setId NOTIFY idChanged)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString gender READ gender WRITE setGender NOTIFY genderChanged)
    Q_PROPERTY(QString avatar READ avatar WRITE setAvatar NOTIFY avatarChanged)
    Q_PROPERTY(QString thumbAvatar READ thumbAvatar WRITE setThumbAvatar NOTIFY thumbAvatarChanged)
    Q_PROPERTY(QString connectFlag READ connectFlag WRITE setConnectFlag NOTIFY connectFlagChanged)
    Q_PROPERTY(QString nickId READ nickId WRITE setNickId NOTIFY nickIdChanged)

    Q_PROPERTY(int allowBirthday READ allowBirthday WRITE setAllowBirthday NOTIFY allowBirthdayChanged)
    Q_PROPERTY(int allowPhone READ allowPhone WRITE setAllowPhone NOTIFY allowPhoneChanged)
    Q_PROPERTY(int allowEmail READ allowEmail WRITE setAllowEmail NOTIFY allowEmailChanged)
    Q_PROPERTY(int verifytype READ verifytype WRITE setVerifytype NOTIFY verifytypeChanged)
    Q_PROPERTY(int vipNoticetype READ vipNoticetype WRITE setVipNoticetype NOTIFY vipNoticetypeChanged)
    Q_PROPERTY(int atNoticetype READ atNoticetype WRITE setAtNoticetype NOTIFY atNoticetypeChanged)
    Q_PROPERTY(int globalNoticetype READ globalNoticetype WRITE setGlobalNoticetype NOTIFY globalNoticetypeChanged)

    Q_PROPERTY(QString appVer READ appVer WRITE setAppVer NOTIFY appVerChanged)

public:
    explicit CDoodUserProfileManager(LinkDoodClient *client = 0,QObject *parent = 0);
    ~CDoodUserProfileManager();
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

    Q_INVOKABLE QString connectFlag() const;
    Q_INVOKABLE QString setConnectFlag(const QString &data);

    Q_INVOKABLE QString nickId() const;
    Q_INVOKABLE QString setNickId(const QString &data);

    Q_INVOKABLE int allowBirthday() const;
    Q_INVOKABLE int setAllowBirthday(const int data);

    Q_INVOKABLE int allowPhone() const;
    Q_INVOKABLE int setAllowPhone(const int data);

    Q_INVOKABLE int allowEmail() const;
    Q_INVOKABLE int setAllowEmail(const int data);

    Q_INVOKABLE int verifytype() const;
    Q_INVOKABLE int setVerifytype(const int data);

    Q_INVOKABLE int vipNoticetype() const;
    Q_INVOKABLE int setVipNoticetype(const int data);

    Q_INVOKABLE int atNoticetype() const;
    Q_INVOKABLE int setAtNoticetype(const int data);

    Q_INVOKABLE int globalNoticetype() const;
    Q_INVOKABLE int setGlobalNoticetype(const int data);


    Q_INVOKABLE void clearData();
    //获取账户信息
    Q_INVOKABLE void getAccountInfo(void);
    //更新用户信息
    Q_INVOKABLE void updateAccountInfo(QString name,QString avater,QString gender, QString nickid = "");

    //上传头像
    Q_INVOKABLE void uploadAvatar(QString path);
    Q_INVOKABLE void setPrivateSettingVerify(int verify);
    Q_INVOKABLE void getPrivateSetting();
    QString appVer();
    void setAppVer(QString data);
signals:
    void idChanged();
    void nameChanged();
    void genderChanged();
    void avatarChanged();
    void thumbAvatarChanged();
    void connectFlagChanged();
    void nickIdChanged();
    void allowBirthdayChanged();
    void allowPhoneChanged();
    void allowEmailChanged();
    void verifytypeChanged();
    void vipNoticetypeChanged();
    void atNoticetypeChanged();
    void globalNoticetypeChanged();
    void appVerChanged();

    void setPrivateSettingResult(int code);
    void getPrivateSettingResult(int code, IMPrivateSetting ps);

public slots:
    //推送用户信息
    void onAccountInfoChanged(Contact user);
    void onConnectChanged(QString flag);
    void onAvatarChanged(QString avatar);
    void onUploadAvatarResult(QString orgijson, QString thumbjson, int code);
    void onSetPrivateSetting(int code);
    void onGetPrivateSetting(int code, IMPrivateSetting ps);
private:
    QString mId;
    QString mName;
    QString mThumbAvatar;
    QString mGender;
    QString mAvatar;
    QString mConnectFlag;
    QString mNickId;
    QString mVersion;

    int mAllowBirthday;		//	生日可见状态 1：所有人可见 2：仅好友可见 3：仅自己可见，默认1
    int mAllowPhone;		//	电话可见状态 1：所有人可见 2：仅好友可见 3：仅自己可见，默认1
    int mAllowEmail;		//	邮箱可见状态 1：所有人可见 2：仅好友可见 3：仅自己可见，默认1
    int mVerifytype;	    //	验证方式 1：需要验证信息,2:不允许任何人添加,3:允许任何人添加，默认1
    int mVipNoticetype;		//	V标消息通知类型 1:表示始终有声音提醒，2：表示始终无声音提醒 3:不始终提醒，默认1
    int mAtNoticetype;		//	@相关人提醒模式 1:表示始终有声音提醒，2：表示始终无声音提醒 3:不始终提醒，默认1
    int mGlobalNoticetype;	//	全局消息通知 1:通知详情，2：通知源，隐藏内容 3:完全隐藏，默认2

    void initConnect();
    LinkDoodClient *m_pClient;
    CSystemPackageManager* m_pPackInfo;
};

#endif // CDOODUSERPROFILEMANAGER_H
