//
// Created by selen on 30/05/2021.
//

#ifndef A10_911_BRINZA_ALINA_ELENA_1_PICTUREDELEGATE_H
#define A10_911_BRINZA_ALINA_ELENA_1_PICTUREDELEGATE_H

#include <QStyledItemDelegate>
#include <QPainter>

class PictureDelegate: public QStyledItemDelegate {
public:
    PictureDelegate(QWidget* parent = 0);

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};
#endif //A10_911_BRINZA_ALINA_ELENA_1_PICTUREDELEGATE_H
