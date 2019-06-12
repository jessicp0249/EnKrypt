#include "esymbol.h"

ESymbol::ESymbol()
{
    m_color=0;
}

ESymbol::ESymbol(QString letter)
{
    m_letter=letter;
    m_color=0;
}

QString ESymbol::get_letter()
{
    return m_letter;
}

QString ESymbol::get_mod()
{
    return m_mod;
}

int ESymbol::get_color()
{
    return m_color;
}

void ESymbol::set_letter(QString letter)
{
    m_letter=letter;
}

void ESymbol::append_letter(QString letter)
{
    m_letter+=letter;
}

void ESymbol::double_letter()
{
    append_letter(m_letter.at(0));
}

void ESymbol::set_mod(QString mod)
{
    m_mod=mod;
}

void ESymbol::add_mod(QString mod)
{
    m_mod+=mod;
}

void ESymbol::set_color(int color)
{
    assert(color>0);
    m_color=color;
}

QString ESymbol::as_text()
{
    return m_letter+m_mod;
}

bool ESymbol::is_upper()
{
    return !m_letter.isEmpty() && m_letter.begin()->isUpper();
}

bool ESymbol::is_punctuated()
{
    return !m_mod.isEmpty();
}

bool ESymbol::is_double()
{
    return m_letter.size()>1;
}
