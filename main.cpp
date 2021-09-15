/*
 * "Alibi", a piece of interactive fiction
 * Written by Brianna Rainey (tassaron)
 * Created 2018-04-01
 */
#include <iostream>
#include <string>
#include <cstring>
#include "tassarons_if_engine.h"
//#include "game_defs.h"

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
    rooms[BAKERY_BACK].exits[SOUTH] = BAKERY_BEHIND;

    rooms[BAKERY_BEHIND].exits[NORTH] = BAKERY_BACK;
    rooms[BAKERY_BEHIND].exits[EAST] = OUTSIDE_0;

    // OUTSIDE WORLD
    rooms[OUTSIDE_0].set_description(
        "Outside the bakery (a place from which one can locate more bakeries)."
    );
    rooms[OUTSIDE_0].exits[NORTH] = LAUNDROMAT;
    rooms[OUTSIDE_0].exits[SOUTH] = BAKERY_FRONT;

    rooms[LAUNDROMAT].exits[SOUTH] = OUTSIDE_0;
/*
    rooms[TERRIBLE_END];
    rooms[BAD_END];
    rooms[NEUTRAL_END];
    rooms[GOOD_END];
    rooms[BEST_END];*/
}

void create_nouns(noun *nouns) {
    nouns[RASP_PIE].set_text("raspberry pie"); nouns[RASP_PIE].code = RASP_PIE;
    nouns[RASP_PIE].set_description(
        "It was a delicious and conveniently-red raspberry pie.");
    nouns[RASP_PIE].move_to(BAKERY_FRONT);
    nouns[RASP_PIE].can_get = true;

    nouns[BLUE_PIE].set_text("blueberry pie"); nouns[BLUE_PIE].code = BLUE_PIE;
    nouns[BLUE_PIE].set_description(
        "It was a delicious yet useless blueberry pie.");
    nouns[BLUE_PIE].move_to(BAKERY_FRONT);
    nouns[BLUE_PIE].can_get = true;

    nouns[BAKERY_FRONT_DOOR].set_text("bakery front door");
    nouns[BAKERY_FRONT_DOOR].add_alt_text("door");
    nouns[BAKERY_FRONT_DOOR].add_alt_text("front door");
    nouns[BAKERY_FRONT_DOOR].code = BAKERY_FRONT_DOOR;
    nouns[BAKERY_FRONT_DOOR].set_description("A sturdy front door");
    nouns[BAKERY_FRONT_DOOR].move_to(BAKERY_FRONT);
    nouns[BAKERY_FRONT_DOOR].can_open = true;
    nouns[BAKERY_FRONT_DOOR].hidden = true;

    nouns[BAKERY_BACK_DOOR].set_text("bakery back door");
    nouns[BAKERY_BACK_DOOR].add_alt_text("door");
    nouns[BAKERY_BACK_DOOR].add_alt_text("back door");
    nouns[BAKERY_BACK_DOOR].code = BAKERY_BACK_DOOR;
    nouns[BAKERY_BACK_DOOR].set_description("A sturdy back door");
    nouns[BAKERY_BACK_DOOR].move_to(BAKERY_BACK);
    nouns[BAKERY_BACK_DOOR].can_open = true;
    nouns[BAKERY_BACK_DOOR].hidden = true;
    nouns[KNIFE].set_text("pie knife");
    nouns[KNIFE].add_alt_text("knife");
    nouns[KNIFE].code = KNIFE;
    nouns[KNIFE].set_description("A knife for cutting pies");
    nouns[KNIFE].move_to(BAKERY_FRONT);
    nouns[KNIFE].can_get = true;

    nouns[FLOUR].set_text("bag of flour");
    nouns[FLOUR].add_alt_text("flour");
    nouns[FLOUR].add_alt_text("bag");
    nouns[FLOUR].code = FLOUR;
    nouns[FLOUR].set_description(
        "There was nothing special about that bag of flour");
    nouns[FLOUR].move_to(BAKERY_BACK);
    nouns[FLOUR].can_get = true;

    nouns[DUMPSTER].set_text("dumpster");
    nouns[DUMPSTER].code = DUMPSTER;
    nouns[DUMPSTER].set_description(
        "A standard black dumpster with the top open");
    nouns[DUMPSTER].move_to(BAKERY_BEHIND);

    nouns[POISON].set_text("poison"); nouns[POISON].code = POISON;
    nouns[POISON].set_description(
        "A vial with skull on it. Probably poison. Could be pirate juice");
    nouns[POISON].can_eat = true; nouns[POISON].can_get = true;
    nouns[POISON].hidden = true;
    nouns[POISON].move_to(BAKERY_BEHIND);

    nouns[FENCE].set_text("fence"); nouns[FENCE].code = FENCE;
    nouns[FENCE].set_description("A tall ass-fence");
    nouns[FENCE].hidden = true; nouns[FENCE].move_to(BAKERY_BEHIND);

    nouns[SECURITY_CAM].set_text("security camera");
    nouns[SECURITY_CAM].code = SECURITY_CAM; nouns[SECURITY_CAM].hidden = true;
    nouns[SECURITY_CAM].set_description(
        "A sinister device capable of great deception");
    nouns[SECURITY_CAM].move_to(OUTSIDE_0);

    nouns[CAR].set_text("car"); nouns[CAR].code = CAR;
    nouns[CAR].set_description("");
    nouns[CAR].hidden = true; nouns[CAR].move_to(OUTSIDE_0);

    nouns[ASPHALT].set_text("asphalt"); nouns[ASPHALT].code = ASPHALT;
    nouns[ASPHALT].set_description("");
    nouns[ASPHALT].hidden = true; nouns[ASPHALT].move_to(OUTSIDE_0);

    nouns[MOON].set_text("moon"); nouns[MOON].code = MOON;
    nouns[MOON].set_description("");
    nouns[MOON].hidden = true; nouns[MOON].move_to(OUTSIDE_0);

    nouns[WASH_MACHINE].set_text("washing machine");
    nouns[WASH_MACHINE].code = WASH_MACHINE;
    nouns[WASH_MACHINE].set_description("");
    nouns[WASH_MACHINE].move_to(LAUNDROMAT);

    nouns[DRYER].set_text("dryer"); nouns[DRYER].code = DRYER;
    nouns[DRYER].move_to(LAUNDROMAT);
    nouns[DRYER].set_description("");

    nouns[LAUNDROMAT_DOOR].set_text("laundromat door");
    nouns[LAUNDROMAT_DOOR].code = LAUNDROMAT_DOOR;
    nouns[LAUNDROMAT_DOOR].set_description("");
    nouns[LAUNDROMAT_DOOR].move_to(LAUNDROMAT);
    nouns[LAUNDROMAT_DOOR].hidden = true;
    nouns[LAUNDROMAT_DOOR].can_open = true;
}

void create_verbs(word *verbs) {
    verbs[QUIT].set_text("quit"); verbs[QUIT].code = QUIT;
    verbs[GET].set_text("get"); verbs[GET].code = GET; verbs[GET].add_alt_text("take");
    verbs[DROP].set_text("drop"); verbs[DROP].code = DROP;
    verbs[OPEN].set_text("open"); verbs[OPEN].code = OPEN;
    verbs[CLOSE].set_text("close"); verbs[CLOSE].code = CLOSE;
    verbs[HELP].set_text("help"); verbs[HELP].code = HELP;
    verbs[GO].set_text("go"); verbs[GO].code = GO;
    verbs[INV].set_text("inv"); verbs[INV].add_alt_text("i");
    verbs[INV].add_alt_text("inventory"); verbs[INV].code = INV;
    verbs[LOOK].set_text("look"); verbs[LOOK].code = LOOK;
    verbs[WHERE].set_text("where"); verbs[WHERE].code = WHERE;

    verbs[CUT].set_text("cut"); verbs[CUT].code = CUT;
    verbs[CUT].add_alt_text("slice");
    verbs[CLEAN].set_text("clean"); verbs[CLEAN].code = CLEAN;
    verbs[CLEAN].add_alt_text("wash"); verbs[CLEAN].add_alt_text("rinse");
    verbs[WATCH].set_text("watch"); verbs[WATCH].code = WATCH;
    verbs[RUN].set_text("run"); verbs[RUN].code = RUN;
    verbs[WALK].set_text("walk"); verbs[WALK].code = WALK;
    verbs[WAIT].set_text("wait"); verbs[WAIT].code = WAIT;
    verbs[EAT].set_text("eat"); verbs[EAT].code = EAT;
    verbs[EAT].add_alt_text("drink");
    verbs[SEARCH].set_text("search"); verbs[SEARCH].code = SEARCH;
    verbs[JUMP].set_text("jump"); verbs[JUMP].code = JUMP;
    verbs[STAB].set_text("stab"); verbs[STAB].code = STAB;
    verbs[STAB].add_alt_text("kill");
}

void create_dirs(word *dirs) {
    dirs[NORTH].set_text("north"); dirs[NORTH].add_alt_text("n");
    dirs[NORTH].code = NORTH;
    dirs[SOUTH].set_text("south"); dirs[SOUTH].add_alt_text("s");
    dirs[SOUTH].code = SOUTH;
    dirs[WEST].set_text("west"); dirs[WEST].add_alt_text("w");
    dirs[WEST].code = WEST;
    dirs[EAST].set_text("east"); dirs[EAST].add_alt_text("e");
    dirs[EAST].code = EAST;
}

void print_cmdline_help() {
    string s = "            ";
    cout << "usage: alibi-game [--help] [--debug]" << endl << endl;
    cout << "optional arguments:" << endl;
    cout << "  -h, --help" << s << "show this help message and exit" << endl;
    cout << "  --debug" << s << "show ugly debug information during the game" << endl;
}

int play(int argc, char *argv[]) {
    // parse cmdline args
    bool gamestate_debug = false;
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--debug") == 0) {
            gamestate_debug = true;
        } else if ( strcmp(argv[i], "--help") == 0 ||
                    strcmp(argv[i], "-h") == 0 ) {
            print_cmdline_help();
            return 0;
        }
    }

    // now start creating the game
    room rooms[TOTAL_ROOMS];
    word verbs[TOTAL_VERBS];
    word dirs[TOTAL_DIRS];
    noun nouns[TOTAL_NOUNS];
    create_rooms(rooms);
    create_verbs(verbs);
    create_dirs(dirs);
    create_nouns(nouns);

    int current_room = ENTRYPOINT;
    // current_time is the current hour in gametime (aka 6pm, 7pm, or 8pm)
    int current_time = 6;
    int time_ticker = -1;
    string command;
    string token_0;
    string token_1;
    word word_0 = word();
    word word_1 = word();
    bool help_msg_shown = false;

    action_look_at(current_room, rooms, nouns);
    rooms[current_room].visited = true;

    while(word_0.compare(verbs[QUIT]) == false) {
        if (time_ticker == 14) {
            // increase gametime by 1 hour every 15 turns
            current_time++;
            time_ticker = 0;
        } else {
            time_ticker++;
        }
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
        // HELP
        } else if (word_0.compare(verbs[HELP])) {
            action_show_help(verbs);
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
        // CUT
        } else if (word_0.compare(verbs[CUT])) {
            action_cut();
        // CLEAN
        } else if (word_0.compare(verbs[CLEAN])) {
            action_clean();
        // WATCH
        } else if (word_0.compare(verbs[WATCH])) {
            action_watch();
        // RUN
        } else if (word_0.compare(verbs[RUN])) {
            action_run();
        // WALK
        } else if (word_0.compare(verbs[WALK])) {
            action_walk();
        // WAIT
        } else if (word_0.compare(verbs[WAIT])) {
            action_wait();
        // EAT
        } else if (word_0.compare(verbs[EAT])) {
            action_eat();
        // SEARCH
        } else if (word_0.compare(verbs[SEARCH])) {
            action_search();
        // JUMP
        } else if (word_0.compare(verbs[JUMP])) {
            action_jump();
        // STAB
        } else if (word_0.compare(verbs[STAB])) {
            action_stab();
        // QUIT
        } else if (word_0.compare(verbs[QUIT])) {
            cout << "My life abruptly ended" << endl;
        } else if (word_0.text() != "") {
            cout << "I don't know what \"" << word_0.text() << "\" means" << endl;
        }
    }
    return 0;
}

int main(int argc, char *argv[]) {
    return play(argc, argv);
}
