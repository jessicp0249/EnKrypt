#ifndef ESYMBOL_H
#define ESYMBOL_H

#include<QString>
#include<QChar>

const int YELLOW=1;
const int BLUE=2;
const int RED=3;
const int COLOR_COUNT=3;

class ESymbol
{
private:
    QString m_letter;
    QString m_mod;
    int m_color;

public:
    explicit ESymbol();
    ESymbol(QString letter);

    // Accessor for m_letter
    QString get_letter();
    // Accessor for m_mod
    QString get_mod();
    // Accessor for m_color
    int get_color();

    // Overwrites m_letter with the given string
    void set_letter(QString letter);
    // Adds the given string to the end of m_letter
    void append_letter(QString letter);
    // Duplicates the first character in m_letter and appends it to m_letter
    void double_letter();
    // Overwrites m_mod with the given string
    void set_mod(QString mod);
    // Adds the given string to the end of m_mod
    void add_mod(QString mod);
    // Assigns the given int to m_color
    void set_color(int color);
    // Returns data in the ESymbol as a QString
    QString as_text();

    // Determines whether m_letter is an uppercase letter
    bool is_upper();
    // Determines whether ESymbol has punctuation attached
    bool is_punctuated();
    // Determines whether m_letter in more than one character long
    bool is_double();
};

#endif // ESYMBOL_H
