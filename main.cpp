/*
 * "Alibi", a piece of interactive fiction
 * Written by Brianna Rainey (tassaron)
 * Created 2018-04-01
 */
#include <iostream>
#include <string>
#include <cstring>
#include "tassarons_if_engine.h"

using std::cout;
using std::cin;
using std::endl;
using std::string;

void create_rooms(room *rooms) {
    // PRESENT-DAY SCENES
    rooms[ENTRYPOINT].set_description(
        "They've accused me of a crime. Time to explain what I was "
        "doing during the event... If they don't buy my story, I may "
        "spend the rest of my life in jail."
    );
    rooms[ENTRYPOINT].set_value_of_property_named_automatically_move_the_player_to_this_room_after_the_description(BAKERY_FRONT);

    // PAST TENSE SCENES
    // IN A BAKERY
    rooms[BAKERY_FRONT].set_description(
        "I was in the front of the bakery, where all the delicious "
        "pies were."
    );
    rooms[BAKERY_FRONT].exits[SOUTH] = BAKERY_BACK;
    rooms[BAKERY_FRONT].exits[NORTH] = OUTSIDE_0;
    rooms[BAKERY_FRONT].doors[NORTH] = BAKERY_FRONT_DOOR;

    rooms[BAKERY_BACK].set_description(
        "I was in the back of the bakery, home to flour and flour accessories."
    );
    rooms[BAKERY_BACK].exits[NORTH] = BAKERY_FRONT;

    // OUTSIDE WORLD
    rooms[OUTSIDE_0].set_description(
        "Outside the bakery (a place from which one can locate more bakeries)."
    );
    rooms[OUTSIDE_0].exits[SOUTH] = BAKERY_FRONT;
}

void create_nouns(noun *nouns) {
    nouns[PIE].set_text("pie"); nouns[PIE].code = PIE;
    nouns[PIE].set_description("It looked like a delicious pie");
    nouns[PIE].moveTo(BAKERY_FRONT);
    nouns[PIE].can_get = true;

    nouns[BAKERY_FRONT_DOOR].set_text("bakery front door");
    nouns[BAKERY_FRONT_DOOR].set_alt_text("door");
    nouns[BAKERY_FRONT_DOOR].code = BAKERY_FRONT_DOOR;
    nouns[BAKERY_FRONT_DOOR].set_description("A sturdy front door");
    nouns[BAKERY_FRONT_DOOR].moveTo(BAKERY_FRONT);
    nouns[BAKERY_FRONT_DOOR].can_open = true;
    nouns[BAKERY_FRONT_DOOR].hidden = true;

    nouns[KNIFE].set_text("pie knife");
    nouns[KNIFE].set_alt_text("knife");
    nouns[KNIFE].code = KNIFE;
    nouns[KNIFE].set_description("A knife for cutting pies");
    nouns[KNIFE].moveTo(BAKERY_FRONT);
    nouns[KNIFE].can_get = true;

    nouns[FLOUR].set_text("bag of flour");
    nouns[FLOUR].code = FLOUR;
    nouns[FLOUR].set_description(
        "There was nothing special about that bag of flour");
    nouns[FLOUR].moveTo(BAKERY_BACK);
    nouns[FLOUR].can_get = true;
}

void create_verbs(word *verbs) {
    verbs[QUIT].set_text("quit"); verbs[QUIT].code = QUIT;
    verbs[GET].set_text("get"); verbs[GET].code = GET;
    verbs[DROP].set_text("drop"); verbs[DROP].code = DROP;
    verbs[OPEN].set_text("open"); verbs[OPEN].code = OPEN;
    verbs[CLOSE].set_text("close"); verbs[CLOSE].code = CLOSE;
    verbs[HELP].set_text("help"); verbs[HELP].code = HELP;
    verbs[GO].set_text("go"); verbs[GO].code = GO;
    verbs[INV].set_text("inv"); verbs[INV].set_alt_text("i"); verbs[INV].code = INV;
    verbs[LOOK].set_text("look"); verbs[LOOK].code = LOOK;
    verbs[WHERE].set_text("where"); verbs[WHERE].code = WHERE;
}

void create_dirs(word *dirs) {
    dirs[NORTH].set_text("north"); dirs[NORTH].set_alt_text("n");
    dirs[NORTH].code = NORTH;
    dirs[SOUTH].set_text("south"); dirs[SOUTH].set_alt_text("s");
    dirs[SOUTH].code = SOUTH;
    dirs[WEST].set_text("west"); dirs[WEST].set_alt_text("w");
    dirs[WEST].code = WEST;
    dirs[EAST].set_text("east"); dirs[EAST].set_alt_text("e");
    dirs[EAST].code = EAST;
}

int play(int argc, char *argv[]) {
    room rooms[TOTAL_ROOMS];
    word verbs[TOTAL_VERBS];
    word dirs[TOTAL_DIRS];
    noun nouns[TOTAL_NOUNS];
    bool gamestate_debug = false;
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--debug") == 0) {
            gamestate_debug = true;
        }
    }

    create_rooms(rooms);
    create_dirs(dirs);
    create_verbs(verbs);
    create_nouns(nouns);

    // Start playing the game
    int current_room = ENTRYPOINT;
    string command;
    string token_0;
    string token_1;
    word word_0 = word();
    word word_1 = word();
    bool help_msg_shown = false;

    action_look_at(current_room, rooms, nouns);
    rooms[current_room].visited = true;

    while(word_0.compare(verbs[QUIT]) == false) {
        if (rooms[current_room].automatically_move_the_player_to_this_room_after_the_description() != NONE) {
            press_key();
            current_room = action_go(current_room, rooms, nouns, verbs[NORTH]);
            continue;
        }
        if ( ! help_msg_shown) {
            cout << "Enter \"help\" for a list of verbs" << endl;
            help_msg_shown = true;
        }
        command.clear();
        token_0.clear();
        token_1.clear();
        cout << "[What did I do next?] ";
        getline(cin, command);
        tokenize_command(command, token_0, token_1);
        word_0 = parse_token(token_0, dirs, verbs, nouns);
        word_1 = parse_token(token_1, dirs, verbs, nouns);

        if (gamestate_debug) {
            cout << "### word0: " << word_0.text() << " | word1: ";
            if (word_1.is_noun) {
                cout << nouns[word_1.code].text();
            } else {
                cout << word_1.text();
            }
            cout << " ###" << endl;
        }

        cout << endl;
        if (word_0.is_noun) {
            cout << "What should I do with " << nouns[word_0.code].text()
                 << "?" << endl;
        // LOOK
        } else if (word_0.compare(verbs[LOOK])) {
            action_look_at(current_room, rooms, nouns, word_1);
        // GO
        } else if ((word_0.compare(verbs[GO])) &&
                  (word_1.is_dir(dirs))) {
            current_room = action_go(current_room, rooms, nouns, word_1);
        // NORTH/SOUTH/EAST/WEST IMPLICIT GO
        } else if (word_0.is_dir(dirs)) {
            current_room = action_go(current_room, rooms, nouns, word_0);
        // OPEN
        } else if (word_0.compare(verbs[OPEN])) {
            action_open(word_1, current_room, rooms, nouns);
        // CLOSE
        } else if (word_0.compare(verbs[CLOSE])) {
            action_close(word_1, current_room, rooms, nouns);
        // GET
        } else if (word_0.compare(verbs[GET])) {
            action_get(word_1, current_room, rooms, nouns);
        // DROP
        } else if (word_0.compare(verbs[DROP])) {
            action_drop(word_1, current_room, rooms, nouns);
        // WHERE
        } else if (word_0.compare(verbs[WHERE])) {
            action_where(current_room, rooms, dirs);
        // INV
        } else if (word_0.compare(verbs[INV])) {
            action_show_inv(nouns);
        // HELP
        } else if (word_0.compare(verbs[HELP])) {
            action_show_help(verbs);
        }
    }
    return 0;
}

int main(int argc, char *argv[]) {
    return play(argc, argv);
}
