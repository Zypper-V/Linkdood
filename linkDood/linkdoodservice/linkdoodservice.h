#ifndef LINKDOODSERVICE_H
#define LINKDOODSERVICE_H

#include <QObject>
#include "authcontroler.h"

class CSystemPackageManager;

class LinkDoodService : public QObject
{
    Q_OBJECT

public:
    void static createService();

    static LinkDoodService* instance();

    QString installPath();
    QString dataPath();

public:
    static LinkDoodService* m_pInstance;

private:
    LinkDoodService(QObject *parent = 0);

    ~LinkDoodService();

private:
    CSystemPackageManager *m_pPackageManager;
    AuthControler* m_pAuth;
    QString m_sInstallPath;
};

#endif // LINKDOODSERVICE_H
