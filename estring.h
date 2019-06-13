#ifndef ESTRING_H
#define ESTRING_H

#include "esymbol.h"
#include <QMessageBox>
#include <QVector>
#include <QString>
#include<cstdlib>
#include<ctime>
#include<cmath>

class EString
{
private:
    QVector<ESymbol*> m_symbols;

public:
    // Default constructor
    EString();
    // Constructor. Converts characters in text to ESymbols and
    // uses them to populate m_symbols
    EString(QString text);

    // Returns the ESymbol* at the given index in m_symbols
    ESymbol* get_eSymbol(int index);

    // Appends sym to end of m_symbols
    void add_symbol(ESymbol* sym);
    // Copies letter to new ESymbol, then appends pointer to that ESymbol to m_symbols
    void add_symbol(QString letter);

    // Converts text to a series of ESymbols stored in m_symbols
    void to_symbols(QString text);
    // Changes format of text so it can be converted to ESymbols
    QString format(QString text);
    // Sets the colors of each symbol in m_symbols
    void set_colors();

    // Checks whether input can be converted to ESymbols
    bool can_convert(QString input);

    // Returns index of the first ESymbol* in m_symbols of the given color
    int first_of_color(int color);
    // Searches from the given index to the end of m_symbols for the first ESymbol*
    // with the given color
    int first_of_color_after(int color, int index);
    // Searches from the end of m_symbols for an ESymbol* of the given color
    int last_of_color(int color);

    // Gets last item in vector of the given color and moves it to end of vector
    void set_last_item(int color);

    // Mixes the ESymbols* in m_symbols together
    void scramble();
    // Moves ESymbols* to their original position in m_symbols
    void unscramble();
    void copy_color_to(QVector<ESymbol*> &vect, int color);
    void mix_colors_evenly();
    void make_uneven();
    int random_color(int color=0);
    void swap_items(int first, int second);
    int next_color(int color);

    // @param iteration Increments each time function recurses, so that
    // function can prevent endless recursion
    void swap_random_index(int iteration=0);
    void move_to_end(int index);

    // Returns a QString interpretation of m_symbols
    QString as_text();

    // Debugging function
    QString color_listing();

    // Scramble the ESymbols in the range from begin to range1_end with the ESymbols
    // in the range from range2_begin and end
//    void merge_ranges(int begin, int range2_begin, int end);

    // Copies last element of the given vector to the given index of m_symbols,
    // and then removes that element from the first vector
//    void add_last_to(QVector<ESymbol*> &vect, int index);

    // Increments count if num is even; else, decrements count.
    // Returns 1 if count is less than -1.
    // Returns -1 if count is greater than 1.
    // Returns zero if count is -1, zero, or 1.
//    int prevent_pattern(int &count, int size_diff);
};

#endif // ESTRING_H
