/* 
 * File:   main.cpp
 * Author: LUPO Kévin - LAMOUROUX Vincent - KEMPF Anthony 
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#define MAX_SERVICES 100 //Limite du nombre de services

#include <QMainWindow>
#include <QTableWidget>
#include <QCheckBox>
#include <string>
 

 class QAction;
 class QActionGroup;
 class QLabel;
 class QMenu;
 class QPushButton;
 
  struct Service{
      QString _protocol;
      QString _service;
      QString _port;
      QString _receiver;
      bool _activated;
 };

 /*
  * Class permettant la création de l'interface graphique de l'éditeur de fichers
  * de services mandatés
  **/
 class MainWindow : public QMainWindow
 {
     Q_OBJECT

 public:
     MainWindow();

 private slots:
     void newFile();//Reinitialise le fichier de service
     void save();//Sauve la configuration actuelle
     void about();//Noms des étudiants ayant réalisés le projet
     void check();//Vérifie si la checkbox a été tické
     void addLine();//Ajoute une ligne au fichier de configuration
     void removeLine();//Enlève laderniere ligne
     void startProxy();//Lance le proxy
     void restartProxy();//Redémarre le proxy pour prendre en compte les modifications


 private:
     void createActions();
     void createMenus();

     QMenu *fileMenu;//Menu
     QMenu *helpMenu;//Menu d'aide
     QPushButton *add;//Bouton ajouter
     QPushButton *remove;//Bouton Bouton retirer
     QPushButton *start;//Bouton démarrer
     QPushButton *restart;//Bouton redémarrer
    
     
      //Les différentes actions liées lors de l'éxécution
     QAction *newAct;
     QAction *saveAct;
     QAction *exitAct;
     QAction *aboutAct;
     QAction *checked;
     
     //La table permettant l'affichage du fichier et son édition
     QTableWidget *table;
     //Les différentes checkbox 
     QCheckBox *checkBox[MAX_SERVICES];
     //Tableau de de services, dans le cas ou le fichier n'est pas vide 
     Service _servicesArray[MAX_SERVICES];
     
 };

 #endif