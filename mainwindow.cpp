#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //escena
    this->setGeometry(400,50,1200,1030);
    this->setMinimumSize(width(),height());
    this->setMaximumSize(width(),height());
    scene = new QGraphicsScene();
    scene->setBackgroundBrush(QPixmap(":/imagenes/space.png").scaled(1000,1000));
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setFixedSize(1000,1000);
    ui->graphicsView->setSceneRect(0,0,1000,1000);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //escena entrada de datos
    scene2 = new QGraphicsScene();
    ui->graphicsView_2->setScene(scene2);
    ui->graphicsView_2->setFixedSize(900,300);
    ui->graphicsView_2->setSceneRect(0,0,800,300);
    ui->graphicsView_2->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView_2->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView_2->setVisible(false);
    Invisible();
    //Sol
    Sun();
    //timer
    timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(mover()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::CreatePlanet()
{
    if(!planetName(":/imagenes/planet2.png")){
        planets.push_back(new Planet(":/imagenes/planet2.png"));
    }
    else if(!planetName(":/imagenes/planet3.png")){
        planets.push_back(new Planet(":/imagenes/planet3.png"));
    }
    else if(!planetName(":/imagenes/planet4.png")){
        planets.push_back(new Planet(":/imagenes/planet4.png"));
    }
    else if(!planetName(":/imagenes/planet5.png")){
        planets.push_back(new Planet(":/imagenes/planet5.png"));
    }
    else if(!planetName(":/imagenes/planet6.png")){
        planets.push_back(new Planet(":/imagenes/planet6.png"));
    }
}

bool MainWindow::planetName(QString name)
{
    for(Planet *i: planets){
        if(i->getName() == name) return true;
    }
    return false;
}

void MainWindow::Sun()
{
    planets.push_back(new Planet(":/imagenes/sol.png"));
    planets[0]->setMasa(70000/10);
    planets[0]->setRadio(200/10);
    planets[0]->setVelx(0);
    planets[0]->setVely(0);
    planets[0]->Tamanio();
    planets[0]->setPosx(500-planets[0]->getRadio());
    planets[0]->setPosy(500-planets[0]->getRadio());
    scene->addItem(planets[0]);
    planets[0]->setPos(planets[0]->getPosx(),planets[0]->getPosy());
}

void MainWindow::mover()
{
    //Aceleracion();
    qDebug() << "Entro en mover";
    time += 0.1;
    qDebug() << time;
    for(short pos=1;pos<planets.size();pos++){
        qDebug() << "Entro en el for";
        planets[pos]->setVelx(planets[pos]->getVelx()+(planets[pos]->getAc_x()*time));
        planets[pos]->setVely(planets[pos]->getVely()+(planets[pos]->getAc_y()*time));
        planets[pos]->setPosx(planets[pos]->getPosx()+(planets[pos]->getVelx()*time));
        planets[pos]->setPosy(planets[pos]->getPosy()+(planets[pos]->getVely()*time));
        qDebug() << planets[pos]->getVelx();
        qDebug() << planets[pos]->getVely();
        qDebug() << "Posx: " << planets[pos]->getPosx();
        qDebug() << "Posy: " << planets[pos]->getPosy();
        planets[pos]->setPos(planets[pos]->getPosx(),planets[pos]->getPosy());
    }
}

void MainWindow::Aceleracion()
{
    double acx=0,acy=0,dist=0;
    for(short pos=1;pos<planets.size();pos++){
        for(short pos2=0;pos2<planets.size();pos2++){
            if(pos!=pos2){
                dist = pow(planets[pos2]->getPosx()-planets[pos]->getPosx(),2);
                dist += pow(planets[pos2]->getPosy()-planets[pos]->getPosy(),2);
                dist = sqrt(dist);
                acx+=(planets[pos2]->getMasa()/pow(dist,3))*(planets[pos2]->getPosx()-planets[pos]->getPosx());
                acy+=(planets[pos2]->getMasa()/pow(dist,3))*(planets[pos2]->getPosy()-planets[pos]->getPosy());
            }
            qDebug() << "Distancia " << dist;
            dist = 0;
        }
        planets[pos]->setAc_x(acx);
        planets[pos]->setAc_y(acy);
        qDebug() << "ac x " << acx;
        qDebug() << "ac y " << acy;
        acx=0,acy=0;
    }
}

void MainWindow::on_add_clicked()
{
    ui->graphicsView_2->setVisible(true);
    Visible();
}
void MainWindow::on_save_clicked()
{
    if(planets.size()==6){
        QMessageBox::critical(this,"Error","No se pueden agregar más de 6 planetas.");
        ui->graphicsView_2->setVisible(false);
        Invisible();
        return;
    }
    //agregar planeta
    short pos;
    CreatePlanet();
    pos = planets.size()-1;
    planets[pos]->setMasa(ui->masa->value());
    planets[pos]->setRadio(ui->radio->value()/10);
    planets[pos]->setVelx(ui->velx->value()/10);
    planets[pos]->setVely(ui->vely->value()/10);
    planets[pos]->Tamanio();
    planets[pos]->setPosx(500+(ui->posx->value()/10)-planets[pos]->getRadio());
    planets[pos]->setPosy(500+(ui->posy->value()/10)-planets[pos]->getRadio());
    scene->addItem(planets[pos]);
    planets[pos]->setPos(planets[pos]->getPosx(),planets[pos]->getPosy());
    //cerrar scena
    ui->graphicsView_2->setVisible(false);
    Invisible();
    //aceleracion planetas
    Aceleracion();
}

void MainWindow::on_pushButton_3_clicked()
{
    ui->graphicsView_2->setVisible(false);
    Invisible();
}

void MainWindow::Visible()
{
    //label
    ui->label->setVisible(true);
    ui->label_2->setVisible(true);
    ui->label_3->setVisible(true);
    ui->label_4->setVisible(true);
    ui->label_5->setVisible(true);
    ui->label_6->setVisible(true);
    //spin box
    ui->posx->setVisible(true);
    ui->posy->setVisible(true);
    ui->masa->setVisible(true);
    ui->radio->setVisible(true);
    ui->velx->setVisible(true);
    ui->vely->setVisible(true);
    //button
    ui->splitter_2->setVisible(true);
}

void MainWindow::Invisible()
{
    //label
    ui->label->setVisible(false);
    ui->label_2->setVisible(false);
    ui->label_3->setVisible(false);
    ui->label_4->setVisible(false);
    ui->label_5->setVisible(false);
    ui->label_6->setVisible(false);
    //spin box
    ui->posx->setVisible(false);
    ui->posy->setVisible(false);
    ui->masa->setVisible(false);
    ui->radio->setVisible(false);
    ui->velx->setVisible(false);
    ui->vely->setVisible(false);
    //button
    ui->splitter_2->setVisible(false);
}
void MainWindow::on_play_clicked()
{
    qDebug() << "Entro en play";
    timer->start(500);
}

void MainWindow::on_stop_clicked()
{
    timer->stop();
}
