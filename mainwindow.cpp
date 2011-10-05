#include <QtGui>
#include "mainwindow.h"
#include "torrentWidget.h"

MainWindow::MainWindow() {
  addButton = new QPushButton("add", this);
  someButton = new QPushButton("delete", this);
  connect(addButton, SIGNAL(clicked()), this, SLOT(addButtonClicked()));
  connect(someButton, SIGNAL(clicked()), this, SLOT(someButtonClicked()));
  torrentsListWidget = new TorrentsListWidget(this);

  QVBoxLayout *layout = new QVBoxLayout();
  layout->addWidget(addButton);
  layout->addWidget(someButton);
  layout->addWidget(torrentsListWidget);

  QWidget *mw = new QWidget(this);
  mw->setLayout(layout);

  setCentralWidget(mw);

  resize(QApplication::desktop()->screenGeometry().width()*0.7, QApplication::desktop()->screenGeometry().height()*0.7);
};

void MainWindow::addButtonClicked() {
  TorrentWidget *item = new TorrentWidget();
  item->setFocusPolicy(Qt::StrongFocus);
  torrentsListWidget->addItem(item);
};

void MainWindow::someButtonClicked() {
/*  qDebug() << "Selected items:";
  int i;
  for(i=0;i<torrentsListWidget->getSelectedItems().count();i++)
    qDebug() << torrentsListWidget->getSelectedItems().at(i)->getId(); */
  QList<TorrentWidget *> tl = torrentsListWidget->getSelectedItems();
  torrentsListWidget->removeItems(tl);
};

