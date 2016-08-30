/*
* This file is part of file-manager
*
* Copyright (C) 2014 Beijing Yuan Xin Technology Co.,Ltd. All rights reserved.
*
* Authors:
*       Zhenbin Cai <caizhenbin@syberos.com>
*
* This software, including documentation, is protected by copyright controlled
* by Beijing Yuan Xin Technology Co.,Ltd. All rights are reserved.
*/

/*
* This file is part of file-manager
*
* Copyright (C) 2014 Beijing Yuan Xin Technology Co.,Ltd. All rights reserved.
*
* Authors:
*       Zhenbin Cai <caizhenbin@syberos.com>
*
* This software, including documentation, is protected by copyright controlled
* by Beijing Yuan Xin Technology Co.,Ltd. All rights are reserved.
*/

#include <QProcess>
#include <QFileInfo>
#include "ctxteditor.h"

CTxtEditor::CTxtEditor(QObject *parent) :
    QAbstractListModel(parent), m_path(""), paginater(0)
{
}

CTxtEditor::~CTxtEditor()
{
    if(paginater && paginater->isRunning()) {
        paginater->stop();
        paginater->wait();
    }
}

void CTxtEditor::asyncPaging()
{
    pages.clear();
    pages << 0;

    if(paginater && paginater->isRunning()) {
        paginater->stop();
        paginater->wait();
    }
    paginater = new AsyncPaginater(m_path, codec, this);
    connect(paginater, SIGNAL(pagesChanged(int,qint64)),
            this, SLOT(setPages(int,qint64)));
    //connect(paginater, &AsyncPaginater::finished, paginater, &QObject::deleteLater);
    paginater->start();
}

void CTxtEditor::setPages(int page, qint64 positon)
{
    qDebug() << "set pages:" << page << positon;
    if(page < pages.count())
        pages.replace(page, positon);
    else if(page == pages.count()) {
        pages.append(positon);
        emit pageCountChanged();
    }
    else {
        qDebug() << "paging error:" << page << positon;
        return;
    }
}

void CTxtEditor::paging()
{
    pages.clear();
    pages << 0;
    QFile file(m_path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream in(&file);
    in.setCodec(codec.toLocal8Bit().data());
    while (!in.atEnd()) {
        in.read(CONTENT_LENGTH_PER_PAGE);
        pages << in.pos();
        qDebug() << pages.size() << pages.last() << file.pos();
    }
    file.close();

    //emit pagingFinished();
    qDebug() << "--------- page num:" << pages.count();
}

void CTxtEditor::setPath(QString path)
{
    m_path = path;

    QProcess process;
    process.start("/usr/bin/enca -L zh_CN " + m_path);
    process.waitForFinished(-1);
    QString stdout = process.readAllStandardOutput();
    QStringList re = stdout.split("\n").at(0).split(";");
    if(re.count() > 1) {
        codec = re.at(1).simplified();
    } else {
        codec = "UTF-8";
    }

    asyncPaging();

    emit pathChanged();

    qDebug() << "---------------- codec:" << m_path << codec;
}

void CTxtEditor::save(int page, QString content)
{
    QFile file(m_path);
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text))
        return;

    QTextStream in(&file);
    in.setCodec(codec.toLocal8Bit().data());
    in.seek(0);
    QString before = in.read(page * CONTENT_LENGTH_PER_PAGE);

    QString after = "";
    if(page < pages.count()-1) {
        qint64 pos = pages.at(page+1);
        in.seek(pos);
        after = in.read((pages.count() - page) * CONTENT_LENGTH_PER_PAGE);
    }
    file.resize(0);
    in << before << content << after;
    file.close();

    //paging();
    asyncPaging();

    qDebug() << "save done";
}

QString CTxtEditor::getContent(int page) const
{
    qDebug() << "--get page content:" << page << m_path;
    if(page < 0 || page >= pages.count()) {
        qDebug() << Q_FUNC_INFO << "wrong page number." << page << pages.count();
        return "";
    }
    if(m_path.isEmpty()) {
        qDebug() << Q_FUNC_INFO << "file path is emputy.";
        return "";
    }

    QFile file(m_path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << Q_FUNC_INFO << "can't open file." << m_path;
        return "";
    }

    qint64 pos = 0;
    if(!pages.isEmpty())
        pos = pages.at(page);

    QTextStream in(&file);
    in.setCodec(codec.toLocal8Bit().data());
    in.seek(pos);
    QString re = in.read(CONTENT_LENGTH_PER_PAGE);

//    if(!in.atEnd() &&  (pages.count() - page) > 1) {
//        pages.append(in.pos());
//        emit pageCountChanged();
//    }

    file.close();
    qDebug() << "--get content:" << pos;
    return re;
}

QHash<int, QByteArray> CTxtEditor::roleNames() const
{
    static QHash<int, QByteArray> roles;

    if (roles.isEmpty()) {
        roles[ContentRole] = "contentText";
    }

    return roles;
}

int CTxtEditor::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return pages.count();
}

QVariant CTxtEditor::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() >= pages.count())
        return QVariant();

    switch (role) {
    case ContentRole:
        return getContent(index.row());
    default:
        break;
    }

    return QVariant();
}

Qt::ItemFlags CTxtEditor::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::ItemIsEnabled;

    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}

bool CTxtEditor::setData(const QModelIndex &index,
                        const QVariant &value, int role)
{
    if(!index.isValid())
        return false;

    if (role == ContentRole) { //Qt::EditRole) {
        save(index.row(), value.toString());

        return true;
    }

    return false;
}
