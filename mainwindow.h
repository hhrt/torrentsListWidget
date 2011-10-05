#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QItemDelegate>
#include "torrentsListWidget.h"

class TorrentWidget;
class QPushButton;
class QListWidgetItem;

class MainWindow : public QMainWindow {
  Q_OBJECT
  public:
  MainWindow();

  private:
  QPushButton *addButton;
  QPushButton *someButton;
  TorrentsListWidget *torrentsListWidget;

  public slots:
  void addButtonClicked();
  void someButtonClicked();
};

#endif
