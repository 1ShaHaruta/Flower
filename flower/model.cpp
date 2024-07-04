#include "model.h"

Model::Model(QObject *parent): QAbstractListModel(parent), db(new QSqlDatabase(QSqlDatabase::addDatabase("QSQLITE")))
{
    db->setDatabaseName("/home/ilya/Рабочий стол/Flower/DB/My_db.db");

}

QVariant Model::headerData(int section, Qt::Orientation orientation, int role) const
{
    // FIXME: Implement me!
}

void Model::getName(const QString& str_db, const QString &str_ac){
    database_name=str_db;
    account_name=str_ac;
}

int Model::rowCount(const QModelIndex &parent) const
{

    if (parent.isValid())
        return 0;
    QSqlQuery query(*db);
    db->open();
    QString command1="SELECT max(Number) FROM "+ database_name;
    query.exec(command1);
     QSqlRecord rec= query.record();
    query.next();
    db->close();
    return query.value(rec.indexOf("Number")) .toInt();


}

QVariant Model::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
    QSqlQuery query(*db);
    db->open();
    QString command1="SELECT * FROM "+ database_name+" WHERE Number=="+ QString::number(index.row());
    query.exec(command1);
     QSqlRecord rec= query.record();
    query.next();
    db->close();
    QString result=query.value(rec.indexOf("Name")) .toString()+query.value(rec.indexOf("Sort")) .toString()+query.value(rec.indexOf("Cost")) .toString();

    return result;
}

bool Model::insertRows(int row, int count, const QModelIndex &parent)
{
    beginInsertRows(parent, row, row + count - 1);
    // FIXME: Implement me!
    endInsertRows();
}

bool Model::removeRows(int row, int count, const QModelIndex &parent)
{
    beginRemoveRows(parent, row, row + count - 1);
    // FIXME: Implement me!
    endRemoveRows();
}
