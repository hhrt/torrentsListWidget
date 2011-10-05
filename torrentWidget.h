#ifndef TORRENTWIDGET_H
#define TORRENTWIDGET_H

#include <QFrame>

static int TorrentWidgetCount = 0;

class QLabel;
class QProgressBar;
class QSize;
class QPushButton;
class QPalette;

class TorrentWidget: public QFrame {

Q_OBJECT

  public:
  TorrentWidget(QWidget *parent = 0);
  ~TorrentWidget();
  int id;
  void setName(QString name);
  void setSpeed(QString speed);
  void setTimeLeft(QString timeLeft);
  void setProgress(unsigned short int progress);
  void setSeed(unsigned int seed);
  void setLeech(unsigned int leech);
  void setPaused(bool p);
  void pauseIconChange();
  void select();
  void unselect();
  void mousePressEvent(QMouseEvent *event);
  void keyPressEvent(QKeyEvent *event);
  void keyReleaseEvent(QKeyEvent *event);
  void focusInEvent(QFocusEvent *event);
  void focusOutEvent(QFocusEvent *event);
  QSize minimumSizeHint() const;
  int getId();
  bool isSelected();

  private:
  static int selectedCount;
  QLabel *nameLabel;
  QLabel *speedCaptionLabel;
  QLabel *speedLabel;
  QLabel *timeLeftCaptionLabel;
  QLabel *timeLeftLabel;
  QProgressBar *progressBar;
  QPushButton *pauseButton;
  QLabel *seedCaptionLabel;
  QLabel *seedLabel;
  QLabel *leechCaptionLabel;
  QLabel *leechLabel;
  bool Paused;
  bool Selected;
  bool shiftPressed;
  bool controlPressed;
  QPalette defaultPalette;
//  void paintBorder();
//  void paintEvent(QPaintEvent *event);

  private slots:
  void pauseButtonClicked();

  signals:
  void paused(int id);
  void runned(int id);
  void select(TorrentWidget *selfPointer);
  void deselect(TorrentWidget *selfPointer);
  void focusIn(TorrentWidget *selfPointer);
  void focusOut(TorrentWidget *selfPointer);
  void keyPressed(TorrentWidget *selfPointer, QKeyEvent *event);
  void keyReleased(TorrentWidget *selfPointer, QKeyEvent *event);
  void mousePressed(TorrentWidget *selfPointer);
  void selected(TorrentWidget *item);

};

#endif
