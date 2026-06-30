#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QProcess>
#include <QTimer>
#include <QElapsedTimer>
#include "raylib.h"
#include "Inverted_gravity.h"

int Main_Menu(int argc, char *argv[]){    
    
    QApplication app(argc, argv);
    
    QWidget main_menu;
    main_menu.resize(width, height);
    main_menu.setStyleSheet("background-image: url(Background.png);");

    QLabel title("Inverted Gravity!", &main_menu);
    title.setGeometry(17*width/72, 9*height/100, 1000, 200);
    QFont font = title.font();
    font.setBold(true);
    font.setUnderline(true);
    font.setPointSize(50);
    title.setFont(font);
    title.setStyleSheet("Color: red;");
    title.setAlignment(Qt::AlignCenter);

    QPushButton start_game("Start", &main_menu);
    start_game.setGeometry(17*width/36, 3*height/10, 120, 60);
    start_game.setStyleSheet("background-color: yellow; color: blue; font-size: 25px; padding: 10px;");

    QPushButton info("Info", &main_menu);
    info.setGeometry(17*width/36, 2*height/5, 120, 60);
    info.setStyleSheet("background-color: yellow; color: blue; font-size: 25px; padding: 10px;");

    QPushButton quit_game("Quit", &main_menu);
    quit_game.setGeometry(17*width/36, height/2, 120, 60);
    quit_game.setStyleSheet("background-color: yellow; color: blue; font-size: 25px; padding: 10px;");

    QLabel infotext(&main_menu);
    infotext.setText("Welcome to Inverted Gravity! You are exploring a new galaxy and have to collect stars for research! Collect enough stars to advance through the ten levels! Unfortunately you cannot jump, so you have to manipulate gravity to your advantage! But beware, stray too far and it might be the last thing you do! Left/Right arrow keys to move, space bar to invert gravity!");
    infotext.setGeometry(17*width/45, 5*height/8, 500, 300);
    infotext.setStyleSheet("color: white; font-size: 25px;");
    infotext.setAlignment(Qt::AlignCenter);
    infotext.setWordWrap(true);
    infotext.hide();

    QObject::connect(&info, &QPushButton::clicked, [&]() {
        infotext.setVisible(!infotext.isVisible());
    });

    QObject::connect(&quit_game, &QPushButton::clicked, []() {
        QCoreApplication::quit();
    });

    QObject::connect(&start_game, &QPushButton::clicked, [&main_menu]() {
        // Reset global game state
        level = 1;
        stars = 0;
        player_x = player_sprite_size;
        player_y = player_sprite_size;
        gravity = 3.0f;
        game_won = false;

        // Reset collected flags
        star_1_level_2_collected = false;
        star_2_level_2_collected = false;
        star_3_level_2_collected = false;
        star_1_level_3_collected = false;
        star_2_level_3_collected = false;
        star_3_level_3_collected = false;
        star_4_level_3_collected = false;
        star_1_level_5_collected = false;

        // Reset moving star angles
        s1l2 = s2l2 = s3l2 = 0.0f;
        s1l3 = s2l3 = s3l3 = s4l3 = 0.0f;
        s1l5 = 0.0f;

        // Restore original levels
        levels = original_levels;

        main_menu.hide();
        run_game();
        main_menu.show();
    });

    main_menu.show();
    main_menu.setWindowTitle(QApplication::translate("toplevel", "Inverted Gravity!"));
    
    return app.exec();
}
