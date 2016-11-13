#ifndef CONTACTLABEL_HPP
#define CONTACTLABEL_HPP

#include <QStyledItemDelegate>

class ContactLabel : public QStyledItemDelegate
{
	Q_OBJECT

    public:
	enum datarole {nameRole = Qt::UserRole + 100,statusRole = Qt::UserRole+101};

	ContactLabel();
	~ContactLabel();

	void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
	QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index ) const;

    private:
};

#endif // CONTACTLABEL_HPP
