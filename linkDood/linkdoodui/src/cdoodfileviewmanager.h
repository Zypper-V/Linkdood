#ifndef CDOODFILEVIEWMANAGER_H
#define CDOODFILEVIEWMANAGER_H

#include <QObject>
#include "linkdoodclient.h"

class CDoodFileViewManager: public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString id READ id WRITE setId NOTIFY idChanged)
    Q_PROPERTY(int status READ status WRITE setStatus NOTIFY statusChanged)
    Q_PROPERTY(int proggress READ proggress WRITE setProggress NOTIFY proggressChanged)
    Q_PROPERTY(QString url READ url WRITE setUrl NOTIFY urlChanged)
    Q_PROPERTY(QString encryptUser READ encryptUser WRITE setEncryptUser NOTIFY encryptUserChanged)
    Q_PROPERTY(QString encryptKey READ encryptKey WRITE setEncryptKey NOTIFY encryptKeyChanged)
    Q_PROPERTY(long long size READ size WRITE setSize NOTIFY sizeChanged)
    Q_PROPERTY(QString path READ path WRITE setPath NOTIFY pathChanged)
    Q_PROPERTY(QString fileName READ fileName WRITE setFileName NOTIFY fileNameChanged)
public:
    explicit CDoodFileViewManager(LinkDoodClient *client = 0,QObject *parent = 0);

    //下载文件
    Q_INVOKABLE void downloadFile(QString id="");
    Q_INVOKABLE void openFile();
    Q_INVOKABLE void showFilePage(QString id,QString fileName,QString url,QString encryptKey,long long size=0,QString encryptUser="");
    Q_INVOKABLE void reset();
    QString id();
    QString url();
    QString encryptUser();
    QString encryptKey();
    QString fileName();
    int status();
    QString path();
    long long size();
    int proggress();

    void setId(QString data);
    void setUrl(QString data);
    void setEncryptUser(QString data);
    void setEncryptKey(QString data);
    void setPath(QString data);
    void setFileName(QString data);
    void setStatus(int data);
    void setSize(long long data);
    void setProggress(int data);
    void init();

signals:
    void idChanged();
    void statusChanged();
    void urlChanged();
    void encryptUserChanged();
    void encryptKeyChanged();
    void sizeChanged();
    void pathChanged();
    void fileNameChanged();
    void proggressChanged();
public slots:
    //文件进度
    void onChatFileProgress(int extra_req, int process, QString info,QString localId,QString targetId);
    void onChatDownloadFile(int code, QString localpath, QString localId);
protected:
    QString mId;
    int     mStatus;
    QString mUrl;
    QString mEncryptUser;
    QString mEncryptKey;
    QString mPath;
    QString mFileName;
    long long mSize;
    int       mProggress;

    LinkDoodClient *m_pClient;

    void initConnect();
    void setField(QString& field,QString data,QString fieldName);
    void setField(int& field,int data,QString fieldName);
    void setField(long long& field,long long data,QString fieldName);
};

#endif // CDOODFILEVIEWMANAGER_H
