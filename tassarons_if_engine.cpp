/*
 * Tassaron's Interactive Fiction Engine
 * Written by Brianna Rainey (tassaron)
 * Created 2018-04-01
 */
#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include "tassarons_if_engine.h"

using std::cout;
using std::cin;
using std::endl;
using std::string;

/* word class */
word::word() { _alt_text.push_back(""); }
word::word(string foo) : word() { _text = foo; }
string word::text() { return _text; }
void word::set_text(string new_text) { _text.assign(new_text); }
std::vector<string> word::alt_text() { return _alt_text; }
string word::alt_text(int i) { return _alt_text[i]; }
int word::add_alt_text(string new_text) {
    if (_alt_text.size() == 1 && _alt_text[0].compare("") == 0) {
        // replace empty string with initial alt text
        _alt_text[0].assign(new_text);
    } else {
        _alt_text.push_back(new_text);
    }
    return _alt_text.size();
}
bool word::compare(word other_word) {
    if (other_word.code == code) {
        if (other_word.text() == text()) { return true; }
        for (int i = 0; i < _alt_text.size(); i++) {
            if (other_word.text().compare(_alt_text[i]) == 0) {
                return true;
            }
        }
    }
    return false;
}
bool word::compare(string str) {
    if (str.compare(text()) == 0) { return true; }
    for (int i = 0; i < _alt_text.size(); i++) {
        if (str.compare(_alt_text[i]) == 0) {
            return true;
        }
    }
    return false;
}
bool word::is_dir(word *dirs) {
    if ((compare(dirs[NORTH]) == true) ||
            (compare(dirs[SOUTH]) == true) ||
            (compare(dirs[EAST]) == true) ||
            (compare(dirs[WEST]) == true) ) {
        return true;
    }
    return false;
}

/* noun class */
string noun::description() { return _description; }
void noun::set_description(string new_text) { _description.assign(new_text);}
int noun::location() { return _location; }
bool noun::move_to(int roomId) {
    _location = roomId;
    if (_ilocation == NONE) {
        _ilocation = roomId;
    }
    return true;
}

/* room class */
string room::description() { return _description; }
void room::set_description(string new_text) { _description.assign(new_text);}
int room::automatically_move_the_player_to_this_room_after_the_description() {
    return _automatically_move_the_player_to_this_room_after_the_description;
}
void room::set_value_of_property_named_automatically_move_the_player_to_this_room_after_the_description(int new_room) {
    _automatically_move_the_player_to_this_room_after_the_description = new_room;
    exits[0] = new_room;
}

/* functions */
void press_key() {
    // Function taken from https://stackoverflow.com/a/1450007/8141870

    //the struct termios stores all kinds of flags which can manipulate the I/O Interface
    //I have an old one to save the old settings and a new
    static struct termios oldt, newt;
    cout << endl;

    //tcgetattr gets the parameters of the current terminal
    //STDIN_FILENO will tell tcgetattr that it should write the settings
    // of stdin to oldt
    tcgetattr( STDIN_FILENO, &oldt);
    //now the settings will be copied
    newt = oldt;

    //two of the c_lflag will be turned off
    //ECHO which is responsible for displaying the input of the user in the terminal
    //ICANON is the essential one! Normally this takes care that one line at a time will be processed
    //that means it will return if it sees a "\n" or an EOF or an EOL
    newt.c_lflag &= ~(ICANON | ECHO );

    //Those new settings will be set to STDIN
    //TCSANOW tells tcsetattr to change attributes immediately.
    tcsetattr( STDIN_FILENO, TCSANOW, &newt);

    //now the char wil be requested
    getchar();

    //the old settings will be written back to STDIN
    tcsetattr( STDIN_FILENO, TCSANOW, &oldt);

}

void tokenize_command(string Cmd, string &wd1, string &wd2) {
    /* Original function from:
     * http://cplussplussatplay.blogspot.ca/2012/11/text-adventure-games-c-part-1.html
     */
    string sub_str;
    std::vector<string> words;
    char search = ' ';
    size_t i, j;

    // Split command into vector
    for(i = 0; i < Cmd.size(); i++) {
        if(Cmd.at(i) != search) {
            sub_str.insert(sub_str.end(), Cmd.at(i));
        }
        if(i == Cmd.size() - 1) {
            words.push_back(sub_str);
            sub_str.clear();
        }
        if(Cmd.at(i) == search) {
            words.push_back(sub_str);
            sub_str.clear();
        }
    }
    // Clear out any blanks. Work backwards through the vectors here
    // as a cheat not to invalidate the iterator
    for(i = words.size() - 1; i > 0; i--) {
        if(words.at(i) == "") {
            words.erase(words.begin() + i);
        }
    }
    // Make words lowercase (where the functions from cctype are used)
    for(i = 0; i < words.size(); i++) {
        for(j = 0; j < words.at(i).size(); j++) {
            if(isupper(words.at(i).at(j))) {
                words.at(i).at(j) = tolower(words.at(i).at(j));
            }
        }
    }

    if (words.empty()) {
        cout << "What? " << endl;
    } else if(words.size() == 1) {
        wd1 = words.at(0);
    } else if(words.size() == 2) {
        wd1 = words.at(0);
        wd2 = words.at(1);
    } else if(words.size() > 2) {
        wd1 = words.at(0);
        wd2 = words.at(1);
        // concatenate each string past wd2 into wd2
        for (size_t i = 2; i != words.size(); i++) {
            wd2 = wd2 + search + words.at(i);
        }
    }
}

word parse_token(string token, word *dirs, word *verbs, noun *nouns) {
    if (token != "") {
        for (int i = 0; i < TOTAL_DIRS; i++) {
            if ( dirs[i].compare(token) ) {
                return dirs[i];
            }
        }
        for (int i = 0; i < TOTAL_VERBS; i++) {
            if ( verbs[i].compare(token) ) {
                return verbs[i];
            }
        }
        for (int i = 0; i < TOTAL_NOUNS; i++) {
            if ( nouns[i].compare(token) ) {
                word noun_word;
                noun_word.code = i;
                noun_word.is_noun = true;
                return noun_word;
            }
        }
    }

    word new_word (token);
    return new_word;
}

void print_article(int current_noun, noun *nouns) {
    if ( ! nouns[current_noun].no_article ) {
        char let = nouns[current_noun].text()[0];
        if (let == 'a' || let == 'e' || let == 'i' || let == 'o' || let == 'u') {
            cout << " an ";
        }
        cout << " a ";
    }
}

void print_nouns(int current_room, noun *nouns) {
    bool has_nouns = false;
    bool more_than_two = false;
    int next_noun_to_print = -1;

    for (int i = 0; i < TOTAL_NOUNS; i++) {
        if (nouns[i].location() == current_room && nouns[i].hidden == false) {
            if (has_nouns == false) {
                if (current_room != POCKET) {
                    cout << " I saw";
                }
                has_nouns = true;
                print_article(i, nouns);
                cout << nouns[i].text();
            } else {
                if (next_noun_to_print != -1) {
                    // print noun found last time
                    // this is necessary to detect when to add the 'and'
                    more_than_two = true;
                    cout << ",";
                    print_article(next_noun_to_print, nouns);
                    cout << nouns[next_noun_to_print].text();
                }
                next_noun_to_print = i;
            }
        }
    }
    if (next_noun_to_print != -1) {
        if (more_than_two) {
            cout << ",";
        }
        cout << " and"; print_article(next_noun_to_print, nouns);
        cout << nouns[next_noun_to_print].text();
    }
    if (has_nouns) { cout << "."; }
}

void action_show_inv(noun *nouns) {
    cout << "Items on hand: ";
    print_nouns(POCKET, nouns);
    cout << endl;
}

void action_show_help(word *verbs) {
    cout << "Available verbs: ";
    for (int i = 0; i < TOTAL_VERBS; i++) {
        cout << verbs[i].text();
        if (i < (TOTAL_VERBS - 1)) {
            cout << ", ";
        } else {
            cout << endl;
        }
    }
}

void action_where(int current_room, room *rooms, word *dirs) {
    cout << "Available exits:";
    for (int i = 0; i < TOTAL_DIRS; i++) {
        if (rooms[current_room].exits[i] != NONE) {
            cout << " " << dirs[i].text();
        }
    }
    cout << endl;
}

void action_look_at(
        int current_room, room *rooms, noun *nouns, word word_1) {
    if (word_1.is_noun) {
        // looking at a noun
        cout << nouns[word_1.code].description() << endl;
    } else if (word_1.text() == "") {
        // looking at the room
        cout << rooms[current_room].description();
        print_nouns(current_room, nouns);
        cout << endl;
    } else if (word_1.text() == "me") {
        cout << "As good-looking as ever." << endl;
    } else {
        cout << "I don't see any \"" << word_1.text() << "\"" << endl;
    }
}

int action_go(int current_room, room *rooms, noun *nouns, word dir) {
    if (rooms[current_room].exits[dir.code] != NONE) {
        if ( (rooms[current_room].doors[dir.code] == NONE) ||
                ( (rooms[current_room].doors[dir.code] != NONE) &&
                  (nouns[rooms[current_room].doors[dir.code]].is_open == true))) {
            int new_room = rooms[current_room].exits[dir.code];
            if (rooms[new_room].visited == false) {
                action_look_at(new_room, rooms, nouns);
                rooms[new_room].visited = true;
            }
            return new_room;
        } else if (rooms[current_room].doors[dir.code] != NONE) {
            cout << "My way is blocked by "
                 << nouns[rooms[current_room].doors[dir.code]].text() << endl;
        }
    }
    return current_room;
}

bool action_close(word word_1, int current_room, room *rooms, noun *nouns) {
    if (word_1.is_noun && nouns[word_1.code].can_open) {
        if (nouns[word_1.code].is_open) {
            nouns[word_1.code].is_open = false;
            cout << "Closed the " << nouns[word_1.code].text() << endl;
            return true;
        } else {
            string name = nouns[word_1.code].text();
            name[0] = toupper(name[0]);
            cout << name << " is already closed!" << endl;
        }
    } else if (word_1.is_noun && nouns[word_1.code].can_open == false) {
        cout << "How could I close a " << nouns[word_1.code].text()
             << "?" << endl;
    } else if (word_1.text() != "") {
        cout << "Not sure what \"" << word_1.text() << "\" is" << endl;
    }
    return false;
}

bool action_open(word word_1, int current_room, room *rooms, noun *nouns) {
    if (word_1.is_noun && nouns[word_1.code].can_open) {
        if (nouns[word_1.code].is_open) {
            string name = nouns[word_1.code].text();
            name[0] = toupper(name[0]);
            cout << name << " is already open!" << endl;
        } else {
            nouns[word_1.code].is_open = true;
            cout << "Opened the " << nouns[word_1.code].text() << endl;
            return true;
        }
    } else if (word_1.is_noun && nouns[word_1.code].can_open == false) {
        cout << "How could I open a " << nouns[word_1.code].text()
             << "?" << endl;
    } else if (word_1.text() != "") {
        cout << "Not sure what \"" << word_1.text() << "\" is" << endl;
    }
    return false;
}

bool action_get(word word_1, int current_room, room *rooms, noun *nouns) {
    if (word_1.is_noun && nouns[word_1.code].can_get &&
            nouns[word_1.code].location() != POCKET) {
        cout << "Got " << nouns[word_1.code].text() << endl;
        nouns[word_1.code].move_to(POCKET);
        return true;
    } else if (word_1.is_noun && nouns[word_1.code].can_get == false) {
        cout << "I can't pick up " << nouns[word_1.code].text() << endl;
    } else if (word_1.is_noun == false) {
        cout << "I don't see any \"" << word_1.text() << "\"" << endl;
    } else {
        cout << "Already gotten" << endl;
    }
    return false;
}

bool action_drop(word word_1, int current_room, room *rooms, noun *nouns) {
    if (word_1.is_noun && nouns[word_1.code].can_get &&
            nouns[word_1.code].location() == POCKET) {
        cout << "Dropped " << nouns[word_1.code].text() << endl;
        nouns[word_1.code].move_to(current_room);
        return true;
    } else if (word_1.is_noun && nouns[word_1.code].can_get == false) {
        cout << "I can't pick that up in the first place" << endl;
    } else if (word_1.is_noun == false) {
        cout << "I don't see any \"" << word_1.text() << "\"" << endl;
    } else {
        cout << "Already dropped" << endl;
    }
    return false;
}

bool action_cut(){ return true; }
bool action_clean(){ return true; }
bool action_watch(){ return true; }
bool action_run(){ return true; }
bool action_walk(){ return true; }
bool action_wait(){ return true; }
bool action_eat(){ return true; }
bool action_search(){ return true; }
bool action_jump(){ return true; }
bool action_stab(){ return true; }
