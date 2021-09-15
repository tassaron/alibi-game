/*
 * Tassaron's Interactive Fiction Engine
 * Written by Brianna Rainey (tassaron)
 * Created 2018-04-01
 */
#include <vector>
#include "game_defs.h"

using std::string;

const int NONE = -1;

class word {
    protected:
        string _text = "";
        std::vector<string> _alt_text;

    public:
        int code = NONE;
        bool is_noun = false;

        word();
        word(string foo);

        //properties
        string text();
        void set_text(string new_text);
        std::vector<string> alt_text();
        string alt_text(int);
        int add_alt_text(string new_text);

        bool compare(word other_word);

        bool compare(string other_word);

        bool is_dir(word *dirs);
};

class noun: public word {
    protected:
        string _description = "";
        int _location = NONE;  // current location
        int _ilocation = NONE; // initial location

    public:
        bool is_noun = true;
        bool can_get = false;
        bool can_eat = false;
        bool can_open = false;
        bool is_open = false;
        bool no_article = false;
        bool hidden = false;

        //properties
        string description();
        void set_description(string new_text);
        int location();
        bool move_to(int roomId);
};

class room {
    protected:
        string _description = "";
        int _automatically_move_the_player_to_this_room_after_the_description = NONE;

    public:
        int exits[4] = { NONE, NONE, NONE, NONE };
        int doors[4] = { NONE, NONE, NONE, NONE };
        bool visited = false;

        string description();
        void set_description(string new_text);
        int automatically_move_the_player_to_this_room_after_the_description();
        void set_value_of_property_named_automatically_move_the_player_to_this_room_after_the_description(int new_room);
};

void press_key();

void tokenize_command(string Cmd, string &wd1, string &wd2);

word parse_token(string token, word *dirs, word *verbs, noun *nouns);

void print_article(int current_noun, noun *nouns);

void print_nouns(int current_room, noun *nouns);

void action_show_inv(noun *nouns);
void action_show_help(word *verbs);
void action_where(int current_room, room *rooms, word *dirs);
void action_look_at(int current_room, room *rooms, noun *nouns, word word_1 = word());
int action_go(int current_room, room *rooms, noun *nouns, word dir);
bool action_close(word word_1, int current_room, room *rooms, noun *nouns);
bool action_open(word word_1, int current_room, room *rooms, noun *nouns);
bool action_get(word word_1, int current_room, room *rooms, noun *nouns);
bool action_drop(word word_1, int current_room, room *rooms, noun *nouns);
bool action_cut();
bool action_clean();
bool action_watch();
bool action_run();
bool action_walk();
bool action_wait();
bool action_eat();
bool action_search();
bool action_jump();
bool action_stab();
