#include "cdoodfileviewmanager.h"

void CDoodFileViewManager::initConnect()
{
    connect(m_pClient,SIGNAL(downloadFileResult(int,QString,QString)),this,SLOT(onChatDownloadFile(int,QString,QString)));
    connect(m_pClient,SIGNAL(fileProgressResult(int,int,QString,QString,QString)),this,SLOT(onChatFileProgress(int,int,QString,QString,QString)));
}

void CDoodFileViewManager::init()
{
    mId="";
    mSize = 0;
    mFileName = "";
    mStatus = 0;
    mUrl ="";
    mPath = "";
    mEncryptKey = "";
    mEncryptUser ="";
    mProggress = 0;
}

CDoodFileViewManager::CDoodFileViewManager(LinkDoodClient *client,QObject *parent):QObject(parent),m_pClient(client)
{
    qRegisterMetaType<CDoodFileViewManager*>();
    init();
    initConnect();
}

void CDoodFileViewManager::downloadFile(QString id)
{
    qDebug()<<Q_FUNC_INFO<<"id:"<<id;
    if(id != ""){
        mId = id;
    }
    setStatus(2);
    m_pClient->downloadFile(mFileName,mUrl,mEncryptKey,mId,"");
}

void CDoodFileViewManager::openFile()
{

}

void CDoodFileViewManager::showFilePage(QString id, QString fileName, QString url, QString encryptKey, long long size, QString encryptUser)
{
    qDebug()<<Q_FUNC_INFO;

    QString path("");
    QFileInfo file;

    if(url != ""){//send
        path = QString::fromStdString(APP_DATA_PATH)+m_pClient->UserId()+"/file/encryfile/"+fileName;
    }else{
        path = fileName;
    }
    file.setFile(path);
    setFileName(file.fileName());

    mId = id;
    mUrl = url;
    mEncryptKey = encryptKey;
    if(encryptUser != ""){
        mEncryptUser = encryptUser;
    }
    if(size != 0){
        setSize(size);
    }

    if(file.exists()){
        setPath(path);
        setProggress(100);
        setStatus(3);
        setSize(file.size());
    }else{
        setPath("");
        setProggress(0);
        setStatus(1);
    }

}

void CDoodFileViewManager::reset()
{
    init();
}

void CDoodFileViewManager::setField(QString& field, QString data,QString fieldName)
{
    if(field != data){
        field = data;
        fieldName = fieldName+"Changed";
        QMetaObject::invokeMethod(this,fieldName.toLatin1().constData(), Qt::DirectConnection);
    }
}

void CDoodFileViewManager::setField(int &field, int data,QString fieldName)
{
    if(field != data){
        field = data;
        fieldName = fieldName+"Changed";
        QMetaObject::invokeMethod(this,fieldName.toLatin1().constData(), Qt::DirectConnection);
    }
}

void CDoodFileViewManager::setField(long long &field, long long data,QString fieldName)
{
    if(field != data){
        field = data;
        fieldName = fieldName+"Changed";
        QMetaObject::invokeMethod(this,fieldName.toLatin1().constData(), Qt::DirectConnection);
    }
}

QString CDoodFileViewManager::id()
{
    return mId;
}

QString CDoodFileViewManager::url()
{
    return mUrl;
}

QString CDoodFileViewManager::encryptUser()
{
    return mEncryptUser;
}

QString CDoodFileViewManager::encryptKey()
{
    return mEncryptKey;
}

QString CDoodFileViewManager::fileName()
{
    return mFileName;
}

int CDoodFileViewManager::status()
{
    return mStatus;
}

QString CDoodFileViewManager::path()
{
    return mPath;
}

long long CDoodFileViewManager::size()
{
    return mSize;
}

int CDoodFileViewManager::proggress()
{
    return mProggress;
}

void CDoodFileViewManager::setId(QString data)
{
    setField(mId,data,"id");
}

void CDoodFileViewManager::setUrl(QString data)
{
    setField(mUrl,data,"url");
    emit urlChanged();
}

void CDoodFileViewManager::setEncryptUser(QString data)
{
    setField(mEncryptUser,data,"encryptUser");
    emit encryptUserChanged();
}

void CDoodFileViewManager::setEncryptKey(QString data)
{
    setField(mEncryptKey,data,"encryptKey");
    emit encryptKeyChanged();
}

void CDoodFileViewManager::setPath(QString data)
{
    setField(mPath,data,"path");
    emit pathChanged();
}

void CDoodFileViewManager::setFileName(QString data)
{
    setField(mFileName,data,"fileName");
    emit fileNameChanged();
}

void CDoodFileViewManager::setStatus(int data)
{
    setField(mStatus,data,"status");
    emit statusChanged();
}

void CDoodFileViewManager::setSize(long long data)
{
    setField(mSize,data,"size");
    emit sizeChanged();
}

void CDoodFileViewManager::setProggress(int data)
{
    setField(mProggress,data,"proggress");
    emit proggressChanged();
}

void CDoodFileViewManager::onChatFileProgress(int extra_req, int process, QString info, QString localId, QString targetId)
{
    if(localId == mId){
        setProggress(process);
    }
}
void CDoodFileViewManager::onChatDownloadFile(int code, QString localpath, QString localId)
{
    qDebug() << Q_FUNC_INFO<<"code:"<< code;
    if(localId == mId){
        if(code == 0){
            setStatus(3);
            setProggress(100);
            setPath(localpath);
        }else{
            setPath("");
            setProggress(0);
            setStatus(1);
        }
    }
}
