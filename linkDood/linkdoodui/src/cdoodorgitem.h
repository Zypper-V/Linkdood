#ifndef CDOODORGITEM_H
#define CDOODORGITEM_H

#include <QObject>

class CDoodOrgItem : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString id READ id WRITE setId NOTIFY idChanged)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString select READ select WRITE setSelect NOTIFY selectChanged)

public:
    explicit CDoodOrgItem(QObject *parent = 0);

    QString id() const;
    QString setId(const QString &data);

    QString select() const;
    QString setName(const QString &data);

    QString name() const;
    QString setSelect(const QString &data);

signals:
    void idChanged();
    void nameChanged();
    void selectChanged();

private:
    QString mId;
    QString mName;
    QString mSelect;
};

#endif // CDOODORGITEM_H
