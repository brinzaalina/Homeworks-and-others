//
// Created by selen on 30/05/2021.
//

#include <QEventLoop>
#include "picturedelegate.h"

PictureDelegate::PictureDelegate(QWidget *parent): QStyledItemDelegate{parent} {

}

void PictureDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const {
    QString dog = index.model()->data(index, Qt::EditRole).toString();
    if (index.column() != 4) {
        QStyledItemDelegate::paint(painter, option, index);
        return;
    }
    if (dog.contains("Husky")) {
        QPixmap pixmap("../husky.jpeg");
        painter->drawPixmap(option.rect, pixmap);
    } else if (dog.contains("Samoyed")) {
        QPixmap pixmap("../samoyed.jpeg");
        painter->drawPixmap(option.rect, pixmap);
    } else if (dog.contains("Akita Inu")) {
        QPixmap pixmap("../akita-inu.png");
        painter->drawPixmap(option.rect, pixmap);
    } else if (dog.contains("German Shepherd")) {
        QPixmap pixmap("../ciobanesc-german.jpeg");
        painter->drawPixmap(option.rect, pixmap);
    } else if (dog.contains("Golden Retriever")) {
        QPixmap pixmap("../golden-retriever.jpeg");
        painter->drawPixmap(option.rect, pixmap);
    } else if (dog.contains("Poodle")) {
        QPixmap pixmap("../pudel-standard-caniche.png");
        painter->drawPixmap(option.rect, pixmap);
    } else if (dog.contains("Corgi")) {
        QPixmap pixmap("../welsh-corgi-pembroke.jpeg");
        painter->drawPixmap(option.rect, pixmap);
    } else {
        QPixmap pixmap("../dog.jpg");
        painter->drawPixmap(option.rect, pixmap);
    }
}

QSize PictureDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const {
    if (index.column() == 1)
        return {32, 64};
    return QStyledItemDelegate::sizeHint(option, index);
}
