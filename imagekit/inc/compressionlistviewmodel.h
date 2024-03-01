/*
 * @Author: weick
 * @Date: 2023-12-10 23:06:34
 * @Last Modified by: weick
 * @Last Modified time: 2023-12-13 00:00:16
 */

#pragma once
#include "models.h"
#include <QAbstractListModel>

class CompressionListViewModel : public QAbstractListModel {
    Q_OBJECT
public:
    explicit CompressionListViewModel(QObject *parent = 0);
    void changeModels(const QList<Models::CompressionData> &datas);
    void changeData(int row, const Models::CompressionData &data);
    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;

protected:
    QList<Models::CompressionData> m_Datas;
};
