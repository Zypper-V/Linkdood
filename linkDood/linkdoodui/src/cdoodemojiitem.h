#ifndef CDOODEMOJIITEM_H
#define CDOODEMOJIITEM_H

#include <QObject>

class CDoodEmojiItem : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString path READ path WRITE setPath NOTIFY pathChanged)
    Q_PROPERTY(QString explain READ explain WRITE setExplain NOTIFY explainChanged)

public:
    explicit CDoodEmojiItem(QObject *parent = 0);

    QString name() const;
    QString setName(const QString &data);

    QString path() const;
    QString setPath(const QString &data);

    QString explain() const;
    QString setExplain(const QString &data);
signals:
      void nameChanged();
      void pathChanged();
      void explainChanged();

public slots:
private:
    QString mName;             //名字
    QString mPath;             //路径
    QString mExplain;          //解释
};

#endif // CDOODEMOJIITEM_H
