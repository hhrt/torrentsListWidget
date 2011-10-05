#include<QtGui>
#include "torrentWidget.h"

int TorrentWidget::selectedCount = 0;

TorrentWidget::TorrentWidget(QWidget *parent): QFrame(parent) {

  id = TorrentWidgetCount;
  TorrentWidgetCount++;

  defaultPalette = palette();

  nameLabel = new QLabel("<b>"+QString::number(getId())+"</b>", this); //id instead name
  speedCaptionLabel = new QLabel("<b>Speed: </b>", this);
  speedLabel = new QLabel("", this);
  progressBar = new QProgressBar(this);
  progressBar->setMinimum(0);
  progressBar->setMaximum(100);
  progressBar->setValue(55);
  pauseButton = new QPushButton(this);
  pauseButton->setIcon(QIcon("./images/media-playback-stop.png"));
  pauseButton->setFixedSize(28,28);
  pauseButton->setFlat(true);
  connect(pauseButton, SIGNAL(clicked()), this, SLOT(pauseButtonClicked()));
  seedCaptionLabel = new QLabel("<b>Seeds: </b>", this);
  seedLabel = new QLabel("", this);
  seedCaptionLabel->setBuddy(seedLabel);
  leechCaptionLabel = new QLabel("<b>Leechs: </b>", this);
  leechLabel = new QLabel("", this);
  leechCaptionLabel->setBuddy(leechLabel);
  timeLeftCaptionLabel = new QLabel("<b>Time left: </b>", this);
  timeLeftLabel = new QLabel("", this);
  timeLeftCaptionLabel->setBuddy(timeLeftLabel);

  QVBoxLayout *mainLayout = new QVBoxLayout();
  QHBoxLayout *topLayout = new QHBoxLayout();
  QHBoxLayout *midLayout = new QHBoxLayout();
  QHBoxLayout *bottLayout = new QHBoxLayout();

  topLayout->addWidget(nameLabel);
  topLayout->addWidget(speedCaptionLabel);
  topLayout->addWidget(speedLabel);
  topLayout->addWidget(timeLeftCaptionLabel);
  topLayout->addWidget(timeLeftLabel);

  midLayout->addWidget(progressBar);
  midLayout->addWidget(pauseButton);

  bottLayout->addStretch(1);
  bottLayout->addWidget(seedCaptionLabel);
  bottLayout->addWidget(seedLabel);
  bottLayout->addWidget(leechCaptionLabel);
  bottLayout->addWidget(leechLabel);

  mainLayout->addLayout(topLayout);
  mainLayout->addLayout(midLayout);
  mainLayout->addLayout(bottLayout);

  setLayout(mainLayout);

  Paused = false;
  Selected = false;

  setFrameStyle(QFrame::Box);

  setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);
  setAutoFillBackground(true);
  setBackgroundRole(QPalette::Window);

  shiftPressed = false;
  controlPressed = false;
};

TorrentWidget::~TorrentWidget() {
  //qDebug() << "Destroing " << id << ".";
};

void TorrentWidget::setName(QString name) {
  nameLabel->setText(name);
};

void TorrentWidget::setSpeed(QString speed) {
  speedLabel->setText("<i>" + speed + "</i>");
};

void TorrentWidget::setTimeLeft(QString timeLeft) {
  timeLeftLabel->setText("<i>" + timeLeft + "</i>");
};

void TorrentWidget::setProgress(unsigned short int progress) {
  if(progress>100)
    progress = 100;
  progressBar->setValue(progress);
};

void TorrentWidget::setSeed(unsigned int seed) {
  seedLabel->setText(QString("<i>") + QString::number(seed) + "</i>");
};

void TorrentWidget::setLeech(unsigned int leech) {
  leechLabel->setText(QString("<i>") + QString::number(leech) + "</i>");
};

void TorrentWidget::setPaused(bool p) {
  Paused = p;
  pauseIconChange();
  if(Paused)
    emit paused(id);
  else
    emit runned(id);
};

void TorrentWidget::pauseIconChange() {
  if(Paused)
    pauseButton->setIcon(QIcon("./images/media-playback-start.png"));
  else
    pauseButton->setIcon(QIcon("./images/media-playback-stop.png"));
};

void TorrentWidget::pauseButtonClicked() {
  Paused = !Paused;
  setPaused(Paused);
};

void TorrentWidget::select() {
  //qDebug() << "Selected.";
  Selected = true;
  QPalette p;
  QColor c(palette().color(QPalette::Window));
  c.setBlue(c.blue()-(c.blue()/3));
  c.setGreen(c.green()-(c.green()/3));
  c.setRed(c.red()-(c.red()/3));
  /*c.setBlue(255);
  c.setGreen(200);
  c.setRed(200);*/
  p.setColor(QPalette::Window, c);
  setPalette(p);
  selectedCount++;
  qDebug() << "selectedCount:" << selectedCount;
  emit select(this);
};

void TorrentWidget::unselect() {
  //qDebug() << "Unselected.";
  Selected = false;
  setPalette(defaultPalette);
  if(selectedCount>0) selectedCount--;
  else qDebug() << "!!!!!selectedCount < 0!!!!!";
  qDebug() << "selectedCount:" << selectedCount;
  emit deselect(this);
};

void TorrentWidget::mousePressEvent(QMouseEvent *event){

/*  if(Selected)
    unselect();
  else
    select();
  repaint();
*/
  emit selected(this);
};

void TorrentWidget::focusInEvent(QFocusEvent *event) {
  qDebug() << getId() << "focus in.";
  emit focusIn(this);
};

void TorrentWidget::focusOutEvent(QFocusEvent *event) {
  qDebug() << getId() << "focus out.";
  emit focusOut(this);
};

void TorrentWidget::keyPressEvent(QKeyEvent *event) {
  switch(event->key()) {
    case Qt::Key_Shift:
    shiftPressed = true;
    break;
    case Qt::Key_Control:
    controlPressed = true;
  };
  emit keyPressed(this, event);
};

void TorrentWidget::keyReleaseEvent(QKeyEvent *event) {
  switch(event->key()) {
    case Qt::Key_Shift:
    shiftPressed = false;
    break;
    case Qt::Key_Control:
    controlPressed = false;
  };
  emit keyReleased(this, event);
};

QSize TorrentWidget::minimumSizeHint() const{
  qDebug() << "MinimumSize: " << sizeHint().width() << "x" << sizeHint().height();
  return sizeHint();
};

int TorrentWidget::getId() {
  return id;
};

bool TorrentWidget::isSelected() {
  return Selected;
};

/*
void TorrentWidget::paintBorder() {
  QPainter painter(this);
  painter.setWindow(geometry());
  painter.setRenderHint(QPainter::Antialiasing);
  painter.setPen(QPen(QBrush(Qt::black), 0.75, Qt::DotLine));
  QRect border(2, 2, geometry().width()-4, geometry().height()-4);
  painter.drawRect(border);
};

void TorrentWidget::paintEvent(QPaintEvent *event) {
  if(Selected)
    paintBorder();
};*/
