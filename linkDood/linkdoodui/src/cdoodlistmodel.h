/*
* This file is part of CDoodListModel
*
* Copyright (C) 2014 Beijing Yuan Xin Technology Co.,Ltd. All rights reserved.
*
* Authors:
*       zhangpeng <zhangpeng@syberos.com>
*
* This software, including documentation, is protected by copyright controlled
* by Beijing Yuan Xin Technology Co.,Ltd. All rights are reserved.
*/

#ifndef CDOODLISTMODEL_H
#define CDOODLISTMODEL_H

#include <QAbstractListModel>

class CDoodListModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(int itemCount READ itemCount NOTIFY itemCountChanged)

    //! modify
    QHash<int, QByteArray> _roleNames;

public:
    explicit CDoodListModel(QObject *parent = 0, QList<QObject*> *list = new QList<QObject*>());
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int itemCount() const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    Q_INVOKABLE void reset();
    Q_INVOKABLE void move(int oldRow, int newRow);

    void insertItem(int index, QObject *item);
    void addItem(QObject *item);
    void addItemBegin(QObject *item);
    void removeItem(QObject *item);
    QObject* itemOfIndex(int index);

    Q_INVOKABLE void removeItem(int index);
    Q_INVOKABLE QObject* get(int index);
    int indexOf(QObject *obj) const;

    //! modify
    QObject * takeItemAt(int index);
    //! --

    template<typename T>
    QList<T*> *getList();
    QList<QObject*> *getList();

    template<typename T>
    void setList(QList<T*> *list);
    void setList(QList<QObject*> *list);

    //! modify
    virtual QHash<int, QByteArray>	roleNames() const;
    //! --

    QList<QObject*> *_list;

private slots:
    void removeDestroyedItem();

signals:
    void itemAdded(QObject *item);
    void itemCountChanged();
};

template<typename T>
QList<T*> *CDoodListModel::getList()
{
    return reinterpret_cast<QList<T *> *>(_list);
}

template<typename T>
void CDoodListModel::setList(QList<T*> *list)
{
    setList(reinterpret_cast<QList<QObject *> *>(list));
}

#endif // CDOODLISTMODEL_H
