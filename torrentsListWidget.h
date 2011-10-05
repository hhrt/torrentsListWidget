#ifndef TORRENTSLISTWIDGET_H
#define TORRENTSLISTWIDGET_H

#include "torrentWidget.h"
#include <QListWidget>

class QListWidgetItem;

class TorrentsListWidget : public QListWidget {
  Q_OBJECT
  public:
  TorrentsListWidget(QWidget *parent);

  void keyPressEvent(QKeyEvent *event);
  void keyReleaseEvent(QKeyEvent *event);
  void mousePressEvent(QMouseEvent *event);

  void addItem(TorrentWidget *item);
  void removeItems(QList<TorrentWidget *> &items);

  QList<TorrentWidget *> getSelectedItems();

  private:
  QMap<TorrentWidget *, QListWidgetItem *> torrentWidgetItems;
  QList<TorrentWidget *> selectedItems;
  bool shiftKeyPressed;
  bool controlKeyPressed;

  void changeSelection(TorrentWidget *item);
  void clearSelection(TorrentWidget *item);
  void selectItem(TorrentWidget *item);
  void unselectItem(TorrentWidget *item);
  void selectRange(int a, int b);

  private slots:
  void torrentWidgetKeyPressed(TorrentWidget *item, QKeyEvent *event);
  void torrentWidgetKeyReleased(TorrentWidget *item, QKeyEvent *event);
  void torrentWidgetMousePressed(TorrentWidget *item);
};


#endif
