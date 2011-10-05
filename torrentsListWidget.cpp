#include "torrentsListWidget.h"
#include <QtGui>

//constructor
TorrentsListWidget::TorrentsListWidget(QWidget *parent) : QListWidget(parent) {
  selectedItems.clear();
  torrentWidgetItems.clear();
  shiftKeyPressed = false;
  controlKeyPressed = false;
};


//methods
void TorrentsListWidget::addItem(TorrentWidget *item) {
  QListWidget::addItem("");
  this->item(count()-1)->setSizeHint(item->sizeHint());
  this->setItemWidget(this->item(count()-1), item);
  torrentWidgetItems.insert(item, this->item(count()-1));
  
  connect(item, SIGNAL(keyReleased(TorrentWidget *, QKeyEvent *)), 
          this, SLOT(torrentWidgetKeyReleased(TorrentWidget *, QKeyEvent *)));
  connect(item, SIGNAL(keyPressed(TorrentWidget *, QKeyEvent *)), 
          this, SLOT(torrentWidgetKeyPressed(TorrentWidget *, QKeyEvent *)));
  connect(item, SIGNAL(selected(TorrentWidget *)), 
          this, SLOT(torrentWidgetMousePressed(TorrentWidget *)));
  
};

void TorrentsListWidget::removeItems(QList<TorrentWidget *> &items) {
  int i;
  for(i=0;i<items.count();i++) {
    qDebug() << "Removing item:" << items.at(i)->getId();
    this->removeItemWidget(torrentWidgetItems.value(items.at(i)));
    this->takeItem(row(torrentWidgetItems.value(items.at(i))));
    if(selectedItems.contains(items.at(i))) unselectItem(items.at(i));
    torrentWidgetItems.remove(items.at(i));
    delete items.at(i);
  }
};

void TorrentsListWidget::clearSelection(TorrentWidget *item = 0) {
    int i;
    TorrentWidget *tw;
    for(i=0;i<this->count();i++) {
      tw = qobject_cast<TorrentWidget *>(this->itemWidget(this->item(i)));
      if(tw != item) unselectItem(tw);
    }
};

void TorrentsListWidget::changeSelection(TorrentWidget *item) {
  if(shiftKeyPressed && !controlKeyPressed) {
    selectRange(row(torrentWidgetItems.value(item)),row(torrentWidgetItems.value(selectedItems.last())));
    return;
  }
  if(!controlKeyPressed) clearSelection(item);

  if(item->isSelected()) {
    if(controlKeyPressed || shiftKeyPressed) unselectItem(item);
  }
  else selectItem(item);
};

void TorrentsListWidget::selectItem(TorrentWidget *item) {
  if(!selectedItems.contains(item)) {
    selectedItems << item;
    item->select();
  }
};

void TorrentsListWidget::unselectItem(TorrentWidget *item) {
  item->unselect();
  selectedItems.removeAll(item);
};


void TorrentsListWidget::selectRange(int a, int b) {
  if(a > b) qSwap(a, b);
  int i;
  for(i=a;i<=b;i++) selectItem(qobject_cast<TorrentWidget *>(itemWidget(this->item(i))));
};

//events
void TorrentsListWidget::keyPressEvent(QKeyEvent *event) {
  qDebug() << "keyPressed" << "key code:" << event->key(); 
  switch(event->key()) {
    case Qt::Key_Control:
    controlKeyPressed = true;
    break;
    case Qt::Key_Shift:
    shiftKeyPressed = true;
    break;
  }
};

void TorrentsListWidget::keyReleaseEvent(QKeyEvent *event) {
  qDebug() << "keyReleased" << "key code:" << event->key();
  switch(event->key()) {
    case Qt::Key_Control:
    controlKeyPressed = false;
    break;
    case Qt::Key_Shift:
    shiftKeyPressed = false;
    break;
  }
};

//slots
void TorrentsListWidget::torrentWidgetKeyPressed(TorrentWidget *item, QKeyEvent *event) {
  switch(event->key()) {
    case Qt::Key_Control:
    case Qt::Key_Shift:
    keyPressEvent(event);
    break;
  }
};

void TorrentsListWidget::torrentWidgetKeyReleased(TorrentWidget *item, QKeyEvent *event) {
  switch(event->key()) {
    case Qt::Key_Control:
    case Qt::Key_Shift:
    keyReleaseEvent(event);
    break;
  }
};

void TorrentsListWidget::torrentWidgetMousePressed(TorrentWidget *item) {
  changeSelection(item);
};

void TorrentsListWidget::mousePressEvent(QMouseEvent *event) {
  clearSelection();
};

QList<TorrentWidget *> TorrentsListWidget::getSelectedItems() {
  return selectedItems;
};
