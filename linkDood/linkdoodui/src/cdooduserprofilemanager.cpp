#include "cdooduserprofilemanager.h"

CDoodUserProfileManager::CDoodUserProfileManager(LinkDoodClient *client,QObject *parent) :m_pClient(client), QObject(parent), mVerifytype(1)
{
    qRegisterMetaType<CDoodUserProfileManager*>();
    initConnect();
    mVerifytype = 1;
    m_pPackInfo = new CSystemPackageManager(this);
    setAppVer("");
}

CDoodUserProfileManager::~CDoodUserProfileManager()
{
    if(m_pPackInfo != NULL){
        delete m_pPackInfo;
    }
    m_pPackInfo = NULL;
}

void CDoodUserProfileManager::initConnect()
{
    connect(m_pClient, SIGNAL(accountInfoChanged(Contact)), this, SLOT(onAccountInfoChanged(Contact)));
    connect(m_pClient, SIGNAL(connectChanged(QString)), this, SLOT(onConnectChanged(QString)));
    connect(m_pClient, SIGNAL(anthAvatarChanged(QString)), this, SLOT(onAvatarChanged(QString)));
}

QString CDoodUserProfileManager::id() const
{
    return mId;
}

QString CDoodUserProfileManager::setId(const QString &data)
{
    if(mId == data) {
        return data;
    }
    mId = data;
    emit idChanged();
    return mId;
}

QString CDoodUserProfileManager::name() const
{
    return mName;
}

QString CDoodUserProfileManager::setName(const QString &data)
{
    if(mName == data) {
        return data;
    }
    mName = data;
    emit nameChanged();
    return mName;
}

QString CDoodUserProfileManager::thumbAvatar() const
{
    return mThumbAvatar;
}

QString CDoodUserProfileManager::setThumbAvatar(const QString &data)
{
    if(mThumbAvatar == data) {
        return data;
    }
    mThumbAvatar = data;
    emit thumbAvatarChanged();
    return mThumbAvatar;
}

void CDoodUserProfileManager::getAccountInfo()
{
    m_pClient->getAccountInfo();
}

void CDoodUserProfileManager::updateAccountInfo(QString _name, QString _avater, QString _gender, QString _nickid)
{
    Contact user;

    user.id     = id();
    if(_name != "" && _name != name()){
        user.name = _name;
    }
    if(_gender != "" && _gender != gender()){
        user.gender = _gender;
    }
    if(_avater != "" && _avater != avatar()){
        user.avatar = _avater;
    }
    if(_nickid != "" && _nickid != nickId()){
        user.nick_id = _nickid;
    }
    m_pClient->updateAccountInfo(user);
}

void CDoodUserProfileManager::uploadAvatar(QString path)
{
    qDebug() << Q_FUNC_INFO;
    m_pClient->uploadAvatar(path);
}

void CDoodUserProfileManager::setPrivateSettingVerify(int verify)
{
    qDebug() << Q_FUNC_INFO << "verify:" << verify;
    IMPrivateSetting priSet;
    priSet.verifytype = verify;
    setVerifytype(verify);
    m_pClient->setPrivateSetting(priSet);
}

void CDoodUserProfileManager::getPrivateSetting()
{
    qDebug() << Q_FUNC_INFO;
    m_pClient->getPrivateSetting();
}

QString CDoodUserProfileManager::appVer()
{
    return mVersion;
}

void CDoodUserProfileManager::setAppVer(QString data)
{
    if(m_pPackInfo != NULL){
        mVersion = m_pPackInfo->packageInfo("com.vrv.linkDood")->versionName();
        emit appVerChanged();
    }
}

void CDoodUserProfileManager::onAccountInfoChanged(Contact user)
{
    qDebug() << Q_FUNC_INFO;
    if(user.avatar != ""){
        setAvatar(user.avatar);
    }
    if(user.gender != "" ){
        setGender(user.gender);
    }
    if(user.name != ""){
        setName(user.name);
    }
    if(user.thumbAvatar != ""){
        setThumbAvatar(user.thumbAvatar);
    }
    if(user.nick_id != ""){
        setNickId(user.nick_id);
    }
    //setNickId("");
    //setNickId(user.nick_id);
    setId(user.id);
}

void CDoodUserProfileManager::onConnectChanged(QString flag)
{
    qDebug() << Q_FUNC_INFO<<"asasasasasaassa"<<flag;
    setConnectFlag(flag);
}

void CDoodUserProfileManager::onAvatarChanged(QString avatar)
{
    if(avatar != ""){
        setThumbAvatar(avatar);
    }
}

void CDoodUserProfileManager::onUploadAvatarResult(QString orgijson, QString thumbjson, int code)
{

}

void CDoodUserProfileManager::onSetPrivateSetting(int code)
{
    qDebug() << Q_FUNC_INFO << "code:" << code;
    emit setPrivateSettingResult(code);
}

void CDoodUserProfileManager::onGetPrivateSetting(int code, IMPrivateSetting ps)
{
    qDebug() << Q_FUNC_INFO << "code:" << code;
    setAllowBirthday(ps.allow_birthday);
    setAllowPhone(ps.allow_phone);
    setAllowEmail(ps.allow_email);
    setVerifytype(ps.verifytype);
    setVipNoticetype(ps.vip_noticetype);
    setAtNoticetype(ps.at_noticetype);
    setGlobalNoticetype(ps.global_noticetype);
}

QString CDoodUserProfileManager::gender() const
{
    return mGender;
}

QString CDoodUserProfileManager::setGender(const QString &data)
{
    qDebug() << Q_FUNC_INFO <<"xingbiexingbiexingbie"<<data;
    mGender = data;
    emit genderChanged();
    return mGender;
}


QString CDoodUserProfileManager::avatar() const
{
    return mAvatar;
}

QString CDoodUserProfileManager::setAvatar(const QString &data)
{
    if(mAvatar == data) {
        return data;
    }
    mAvatar = data;
    emit avatarChanged();
    return mAvatar;
}
QString CDoodUserProfileManager::connectFlag() const
{
    return mConnectFlag;
}

QString CDoodUserProfileManager::setConnectFlag(const QString &data)
{
    if(mConnectFlag == data) {
        return data;
    }
    mConnectFlag = data;
    emit connectFlagChanged();
    return mConnectFlag;
}

QString CDoodUserProfileManager::nickId() const
{
    return mNickId;
}

QString CDoodUserProfileManager::setNickId(const QString &data)
{
    if(data == mNickId)
        return data;
    mNickId = data;
    emit nickIdChanged();
    return mNickId;
}

int CDoodUserProfileManager::allowBirthday() const
{
    return mAllowBirthday;
}

int CDoodUserProfileManager::setAllowBirthday(const int data)
{
    if(data == mAllowBirthday)
        return data;
    mAllowBirthday = data;
    emit allowBirthdayChanged();
    return mAllowBirthday;
}

int CDoodUserProfileManager::allowPhone() const
{
    return mAllowPhone;
}

int CDoodUserProfileManager::setAllowPhone(const int data)
{
    if(data == mAllowPhone)
        return data;
    mAllowPhone = data;
    emit allowPhoneChanged();
    return mAllowPhone;
}

int CDoodUserProfileManager::allowEmail() const
{
    return mAllowEmail;
}

int CDoodUserProfileManager::setAllowEmail(const int data)
{
    if(data == mAllowEmail)
        return data;
    mAllowEmail = data;
    emit allowEmailChanged();
    return mAllowEmail;
}

int CDoodUserProfileManager::verifytype() const
{
    return mVerifytype;
}

int CDoodUserProfileManager::setVerifytype(const int data)
{
    if(data == mVerifytype)
        return data;
    mVerifytype = data;
    emit verifytypeChanged();
    return mVerifytype;
}

int CDoodUserProfileManager::vipNoticetype() const
{
    return mVipNoticetype;
}

int CDoodUserProfileManager::setVipNoticetype(const int data)
{
    if(data == mVipNoticetype)
        return data;
    mVipNoticetype = data;
    emit vipNoticetypeChanged();
    return mVipNoticetype;
}

int CDoodUserProfileManager::atNoticetype() const
{
    return mAtNoticetype;
}

int CDoodUserProfileManager::setAtNoticetype(const int data)
{
    if(data == mAtNoticetype)
        return data;
    mAtNoticetype = data;
    emit atNoticetypeChanged();
    return mAtNoticetype;
}

int CDoodUserProfileManager::globalNoticetype() const
{
    return mGlobalNoticetype;
}

int CDoodUserProfileManager::setGlobalNoticetype(const int data)
{
    if(data == mGlobalNoticetype)
        return data;
    mGlobalNoticetype = data;
    emit globalNoticetypeChanged();
    return mGlobalNoticetype;
}

void CDoodUserProfileManager::clearData()
{
    mId = "";
    mName= "";
    mThumbAvatar= "";
    mGender= "";
    mAvatar= "";
    mConnectFlag= "";
    mNickId= "";

    setNickId("");
    emit idChanged();
    emit nameChanged();
    emit genderChanged();
    emit avatarChanged();
    emit thumbAvatarChanged();
    emit connectFlagChanged();
    emit nickIdChanged();
    emit allowBirthdayChanged();
    emit allowPhoneChanged();
    emit allowEmailChanged();
    emit verifytypeChanged();
    emit vipNoticetypeChanged();
    emit atNoticetypeChanged();
    emit globalNoticetypeChanged();
}

