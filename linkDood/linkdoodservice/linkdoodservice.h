#ifndef LINKDOODSERVICE_H
#define LINKDOODSERVICE_H

#include <QObject>
#include "authcontroler.h"

class LinkDoodService : public QObject
{
    Q_OBJECT

public:
    void static createService();

    static LinkDoodService* instance();

public:
    static LinkDoodService* m_pInstance;

private:
    LinkDoodService(QObject *parent = 0);
        static AuthControler* m_auth;


    ~LinkDoodService();
};

#endif // LINKDOODSERVICE_H
