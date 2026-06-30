#include "Inverted_gravity.h"
#include "Main_Menu.h"

int main(int argc, char *argv[]) {
    Make_Levels();   // initialize levels once
    return Main_Menu(argc, argv);
}
