#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QTimer>
#include <QGraphicsDropShadowEffect>


#define MEM_START 0x80000000
#define INVENTORY_START 0x804578CC

#define REFRESH_RATE 30

#define ITEM_DIM 80

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , ph(new PrimeHook)
{
    ui->setupUi(this);

    //ui->gridLayout->SetFixedSize(ITEM_DIM * 6, ITEM_DIM * 4);

    setGridImage(0,0, ":/mp/resources/Missile_launcher.png");
    setGridImage(0,1, ":/mp/resources/etank.png");
    setGridImage(0,2, ":/mp/resources/Wave_beam.png");
    setGridImage(0,3, ":/mp/resources/Ice_beam.png");
    setGridImage(0,4, ":/mp/resources/Plasma_beam.png");
    setGridImage(0,5, ":/mp/resources/XRay_Visor.png");

    setGridImage(1,0, ":/mp/resources/Morph_Ball.png");
    setGridImage(1,1, ":/mp/resources/bombs.png");
    setGridImage(1,2, ":/mp/resources/Boost_Ball.png");
    setGridImage(1,3, ":/mp/resources/Spider_Ball.png");
    setGridImage(1,4, ":/mp/resources/Power_Bomb.png");
    setGridImage(1,5, ":/mp/resources/Thermal_Visor.png");

    setGridImage(2,0, ":/mp/resources/Super_Missile.png");
    setGridImage(2,1, ":/mp/resources/Wavebuster.png");
    setGridImage(2,2, ":/mp/resources/Ice_Spreader.png");
    setGridImage(2,3, ":/mp/resources/Flamethrower.png");
    setGridImage(2,4, ":/mp/resources/Space_Jump_Boots.png");
    setGridImage(2,5, ":/mp/resources/XRay_Visor.png");

    setGridImage(3,0, ":/mp/resources/Varia_Suit.png");
    setGridImage(3,1, ":/mp/resources/Gravity_Suit.png");
    setGridImage(3,2, ":/mp/resources/Phazon_Suit.png");
    setGridImage(3,3, ":/mp/resources/Charge_Beam.png");
    setGridImage(3,4, ":/mp/resources/grapple_beam.png");
    setGridImage(3,5, ":/mp/resources/chozo_artifact.png");

    QLabel *art_text = new QLabel();
    art_text->setObjectName("art_label");
    art_text->setText("0");
    art_text->setStyleSheet("color:yellow; font-weight:bold; font-size:24pt; padding-left:12px");
    ui->artifact_layout->addWidget(art_text,0,0, Qt::AlignCenter);

    QLabel *missile_text = new QLabel();
    missile_text->setObjectName("missile_label");
    missile_text->setText("255");
    missile_text->setStyleSheet("font-size:16pt; padding-left:12px");
    ui->missile_layout->addWidget(missile_text,0,0,Qt::AlignHCenter | Qt::AlignBottom);

    QLabel *etank_text = new QLabel();
    etank_text->setObjectName("etank_label");
    etank_text->setText("14");
    etank_text->setStyleSheet("font-size:16pt; padding-left:12px");
    ui->etank_layout->addWidget(etank_text,0,0,Qt::AlignHCenter | Qt::AlignBottom);

    QLabel *pb_text = new QLabel();
    pb_text->setObjectName("pb_label");
    pb_text->setText("8");
    pb_text->setStyleSheet("font-size:16pt; padding-left:12px");
    ui->pb_layout->addWidget(pb_text,0,0,Qt::AlignHCenter | Qt::AlignBottom);

    QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect(this);
    effect->setOffset(0,0);
    effect->setBlurRadius(8.0);
    effect->setColor(Qt::black);

    QGraphicsDropShadowEffect *effect2 = new QGraphicsDropShadowEffect(this);
    effect2->setOffset(0,0);
    effect2->setBlurRadius(8.0);
    effect2->setColor(Qt::black);

    QGraphicsDropShadowEffect *effect3 = new QGraphicsDropShadowEffect(this);
    effect3->setOffset(0,0);
    effect3->setBlurRadius(8.0);
    effect3->setColor(Qt::black);

    QGraphicsDropShadowEffect *effect4 = new QGraphicsDropShadowEffect(this);
    effect4->setOffset(0,0);
    effect4->setBlurRadius(8.0);
    effect4->setColor(Qt::black);

    missile_text->setGraphicsEffect(effect);
    etank_text->setGraphicsEffect(effect2);
    pb_text->setGraphicsEffect(effect3);
    art_text->setGraphicsEffect(effect4);

    ui->retry_button->hide();

    connect(ui->retry_button, SIGNAL(clicked()), this, SLOT(onRetryClicked()));

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update_data()));
    timer->start(1000 / REFRESH_RATE);


}

void MainWindow::setGridImage(int i, int j, QString res){
    QLabel *item = MainWindow::findChild<QLabel *>("item_" + QString::number(i) + QString::number(j));
    QPixmap image(res);

    item->setFixedSize(ITEM_DIM, ITEM_DIM);
    int w = ITEM_DIM;
    int h = ITEM_DIM;
    item->setPixmap(image.scaled(w,h, Qt::KeepAspectRatio));
    item->setEnabled(false);

}

void MainWindow::onRetryClicked(){
    bool attempt = ph->attemptHook();
    if(attempt){
        ui->dolphin_status->setText("Dolphin status: Connected");
        ui->retry_button->hide();
    }
}

void MainWindow::update_data(){
    if(!ph->checkHook()){
        ui->dolphin_status->setText("Dolphin status: Disconnected");
        ui->retry_button->show();
    }
    else{
        ui->IGT_label->setText("IGT: " + QString::fromStdString(ph->get_IGT_value()));
        std::vector<std::vector<int>> items = ph->item_values();
        for(unsigned i = 0; i < items.size(); i++){
            for(unsigned j = 0; j < items[i].size(); j++){
                QLabel *item_label = MainWindow::findChild<QLabel *>("item_" + QString::number(i) + QString::number(j));
                item_label->setEnabled(items[i][j]);
            }
        }
        int art_count = ph->artifact_count();
        ui->item_35->setEnabled(art_count);
        QLabel *art_text = MainWindow::findChild<QLabel *>("art_label");
        art_text->setText(QString::number(art_count));

        QLabel *missile_text = MainWindow::findChild<QLabel *>("missile_label");
        QLabel *etank_text = MainWindow::findChild<QLabel *>("etank_label");
        QLabel *pb_text = MainWindow::findChild<QLabel *>("pb_label");

        missile_text->setText(QString::number(items[0][0]));
        etank_text->setText(QString::number(items[0][1]));
        pb_text->setText(QString::number(items[1][4]));
    }
}


MainWindow::~MainWindow()
{
    delete ui;
    delete ph;
}



