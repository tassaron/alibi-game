/*
 * Tassaron's Interactive Fiction Engine
 * Written by Brianna Rainey (tassaron)
 * Created 2018-04-01
 */
using std::string;

const int NONE = -1;
const int TOTAL_ROOMS = 5;
const int TOTAL_DIRS = 4;
const int TOTAL_VERBS = 10;
const int TOTAL_NOUNS = 4;
enum Directions { NORTH, SOUTH, EAST, WEST };
enum Verbs {
    QUIT, LOOK, INV, GO, HELP, OPEN, CLOSE, GET, DROP, WHERE
};
enum Nouns {
    PIE, BAKERY_FRONT_DOOR, KNIFE, FLOUR
};
enum Rooms {
    POCKET, ENTRYPOINT,
    BAKERY_FRONT, BAKERY_BACK,
    OUTSIDE_0
};

class word {
    protected:
        string _text = "";
        string _alt_text = "";

    public:
        int code = NONE;
        bool is_noun = false;

        word();
        word(string foo);

        //properties
        string text();
        void set_text(string new_text);
        string alt_text();
        void set_alt_text(string new_text);

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
        bool can_open = false;
        bool is_open = false;
        bool no_article = false;
        bool hidden = false;

        //properties
        string description();
        void set_description(string new_text);
        int location();
        bool moveTo(int roomId);
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
