#include "estring.h"

EString::EString()
{
}

EString::EString(QString text)
{
    // If text can be converted to ESymbols...
    if(can_convert(text))
    {
        // Format, convert, and use to fill m_symbols
        to_symbols(format(text));
        set_colors();	// Assign colors to each ESymbol in m_symbols
        scramble();		// Scramble vector m_symbols
    }
}

ESymbol *EString::get_eSymbol(int index)
{
    // Make sure index exists in m_symbols
    return m_symbols[index];
}

void EString::add_symbol(ESymbol *sym)
{
    m_symbols.push_back(sym);
}

void EString::add_symbol(QString letter)
{
    ESymbol* sym=new ESymbol(letter);
    add_symbol(sym);
}

void EString::to_symbols(QString text)
{

    QChar current=text.at(0);
    // Make first character in text the first ESymbol in m_symbols
    add_symbol(current);
    int max=text.size();    // Get length of given string

    for(int i=1; i<max; i++)
    {
        current=text.at(i);
        if(!current.isLetter() && !current.isNumber())
            m_symbols.last()->add_mod(current);
        else if(current==text.at(i-1).toLower())
            m_symbols.last()->double_letter();
        else
        {
            add_symbol(current);
        }
    }
}

QString EString::format(QString text)
{
    // Make all characters in text lowercase
    text=text.toLower();
    // Capitalize first character
    QString result=text.at(0).toUpper();
    int max=text.size();    // Get length of given string

    for(int i=1; i<max; i++)
    {
        // If current character is first letter in a word, capitalize it
        if(text.at(i).isLetter() && text.at(i-1).isSpace())
            result+=text.at(i).toUpper();	// Add character to result
        // If current character is NOT white space, add to result
        else if(!text.at(i).isSpace())
            result+=text.at(i);
    }
    return result;
}

void EString::set_colors()
{
    int max=m_symbols.size();    // Length of m_symbols
    int color=1;	// Current color
    // Number of ESymbols to be assigned per color
    int interval=max/COLOR_COUNT;
    // Interval must be at least one
    if(interval<1) interval=1;
    // If items in m_symbols don't divide evenly among colors,
    // increase interval to distribute remainder
    if(max%COLOR_COUNT>0) interval++;

    // Assign each color to about the same number of ESymbols
    for(int i=0; i<max; i++)
    {
        // Assign current color to current item in m_symbols
        m_symbols[i]->set_color(color);
        // If current color has been assigned to enough ESymbols,
        // and last color has not been reached, change current color
        if((i+1)%interval==0 && color<COLOR_COUNT)
        {
            color++;
            // If remainder items have been distributed, decrease interval.
            // (This operation will occur at most ONCE per function call.)
            if(color==(max%interval))
                interval--;
        }
    }
QMessageBox::information(nullptr,"",color_listing());
}

bool EString::can_convert(QString input)
{
    // If formatted input is not empty, input can be converted
    if(format(input).size()>0) return true;
    else return false;
}

int EString::first_of_color(int color)
{
    // Search from beginning of m_symbols for ESymbol of the given color
    return first_of_color_after(color,0);
}

int EString::first_of_color_after(int color, int index)
{
#if 0
    int match=-1;	// Default signals that no match was found

    // Go through every ESymbol* in m_symbols
    int i=index;
    while(i<m_symbols.size() && match==-1)
    {
        // If current symbol is the right color...
        if(m_symbols[i]->get_color()==color)
            match=i;	// Assign current index to variable index
        i++;
    }
    return match;
#endif

    for(int i=index; i<m_symbols.size(); i++)
    {
        if(m_symbols[i]->get_color()==color)
            return i;
    }
    return -1;
}

int EString::last_of_color(int color)
{
    for(int i=m_symbols.size()-1; i>=0; i--)
    {
        if(m_symbols[i]->get_color()==color)
            return i;
    }
    return -1;
}

void EString::set_last_item(int color)
{
    int index=last_of_color(color);
    move_to_end(index);
}

void EString::scramble()
{
    if(m_symbols.size()<COLOR_COUNT) return;

    mix_colors_evenly();
    set_last_item(COLOR_COUNT);
    make_uneven();
}

// Unfinished function (not tested for bugs)
void EString::unscramble()
{
    // Create new vector the same size as m_symbols
    QVector<ESymbol*> sorted(m_symbols.size());

    // Copy items of each color to sorted
    for(int i=1; i<=COLOR_COUNT; i++)
        copy_color_to(sorted,i);

    // Copy sorted vector to m_symbols
    m_symbols=sorted;
}

void EString::copy_color_to(QVector<ESymbol *> &vect, int color)
{
QMessageBox::information(nullptr,"","Copying color "+QString::number(color));
    ESymbol* filler=new ESymbol;
    int index=0;
     // Add each red ESymbol* from m_symbols to sorted
    while(index>=0)
    {
        index=first_of_color(color);
        vect.push_back(m_symbols[index]);
        m_symbols[index]=filler;
    }

    delete filler;
}

void EString::mix_colors_evenly()
{
    int max = m_symbols.size();
    // Pointer to blank ESymbol
    ESymbol* filler=new ESymbol;
    // Temporary vector to contain rearranged items from m_symbols
    QVector<ESymbol*> temp(max);

    int index=-1;
    for(int i=0; i<max; i++)
    {
        // Iterate through colors based on position in temp
        int color=(i%COLOR_COUNT)+1;
        // Position of first item in m_symbols of the given color
        index=first_of_color(color);
        while(index<0)
        {
            index=first_of_color(color);
            color=next_color(color);
        }
        // Copy item from m_symbols to temp at current position
        temp[i]=m_symbols[index];
        // Replace item in m_symbols with blank filler item,
        // so that first_of_color() doesn't return its index again
        m_symbols[index]=filler;
    }
    m_symbols=temp;		// Copy temp to m_symbols
    delete filler;	// Reclaim memory from temporary filler item
}

void EString::make_uneven()
{
    // Based on vector size, get number of times to swap a random pair of items
    int swap_count=m_symbols.size()/(COLOR_COUNT+1);

    // Swap random items that many times
    for(int i=0; i< swap_count; i++)
        swap_random_index();
}

int EString::random_color(int color)
{
    int new_color=(rand()%COLOR_COUNT)+1;	// Generate random color number

    // If new color is same as old color, this is the color's second use
    if(new_color==color)
        new_color*=(-1);	// Make new color negative to indicate second use
    // If new color matches negative color, this color has been used twice in a row
    else if(new_color==(-color))
        new_color=random_color(color);	// Do over until a different color is assigned

    return new_color;
}

void EString::swap_items(int first, int second)
{
    // Exit function if first and second indexes are the same
    if(first==second) return;

    ESymbol* temp=m_symbols[first];
    m_symbols[first]=m_symbols[second];
    m_symbols[second]=temp;
}

int EString::next_color(int color)
{
    if(color==COLOR_COUNT) color=0;
    color++;
    return color;
}

void EString::swap_random_index(int iteration)
{
    // Exit function if it recurses more than the given number of times
    if(iteration>m_symbols.size()) return;

    srand(time(nullptr));	// Initialize random number generator
    // Get random index that is not the first or last item in vector
    int index=rand()%(m_symbols.size()-2)+1;

    // If index is directly after the first item, move forward one
    if((index-1) == 0)index++;

    // If this item is the same color as the one before it, redo this function
    if(m_symbols[index]->get_color() == m_symbols[index-1]->get_color())
        swap_random_index(iteration+1);
    // Switch item at index with the one before it
    else swap_items(index, index-1);
}

void EString::move_to_end(int index)
{
    // Index of last item in m_symbols
    int max=m_symbols.size()-1;
    for(int i=index; i<max; i++)
        swap_items(i, i+1);
}

QString EString::as_text()
{
    QString text="";	// Create empty string
    int max=m_symbols.size();	// Get size of m_symbols

    // Append contents of each ESymbol* in m_symbols to text
    for(int i=0; i<max; i++)
        text+=m_symbols[i]->as_text();

    return text;
}

QString EString::color_listing()
{
    QString output="";
    int max=m_symbols.size();	// Get size of m_symbols
    for(int i=0; i<max; i++)
    {
        if(m_symbols[i]->get_color()==1)
            output+="Y";
        else if(m_symbols[i]->get_color()==2)
            output+="B";
        else if(m_symbols[i]->get_color()==3)
            output+="R";
    }
    return output;
}

#if 0
// Rejected version of function
void EString::scramble()
{
    // Blank ESymbol* to replace items in m_symbols that have already been copied
    ESymbol* filler=new ESymbol;

    // Copy m_symbols to temporary vector
    QVector<ESymbol*> temp=m_symbols;

    srand(time(nullptr));	// Initialize random number generator
    int color=0;
    m_symbols[0]=filler;

    // Excluding the first item, traverse the contents of temp
    for(int i=1; i<m_symbols.size(); i++)
    {
        color=random_color(color);	// Get random color
        // Get index of first item in m_symbols with the current color
        int sym=first_of_color(abs(color));
        if(sym<=0) i--;
        else
        {
            temp[i]=m_symbols[sym]; // Copy item from m_symbols to temp at index i
            m_symbols[sym]=filler;	// Replace item in m_symbols with filler
        }
    }
    m_symbols=temp;	// Copy temp to m_symbols
    delete filler;	// Reclaim memory used by filler item

    // Index of first blue ESymbol in m_symbols
    int blue_begin=first_of_color(BLUE);
    // Index of last blue ESymbol in m_symbols
    int blue_end=first_of_color(RED)-1;

    // Merge Yellow and Blue portions of vector,
    // but keep first item the same
    merge_ranges(1, blue_begin-1, blue_end);

    // Merge scrambled portion of vector with Red portion,
    // but keep first and last items the same
    merge_ranges(1,blue_end+1,m_symbols.size()-2);
}

// Unfinished function - need debugging
void EString::merge_ranges(int begin, int range2_begin, int end)
{
    QVector<ESymbol*> range1;
    for(int i=begin; i<range2_begin; i++)
        range1.push_back(m_symbols[i]);

    QVector<ESymbol*> range2;
    for(int i=range2_begin; i<=end; i++)
        range2.push_back(m_symbols[i]);

    // Size difference between the two ranges
    int size_diff=range1.size()-range2.size();
    int count=0;	// Increments for even numbers, decrements for odd numbers

    for(int i=end; i>=begin; i--)
    {
        // Generate random number
        int randnum=prevent_pattern(count, size_diff);

QMessageBox::information(nullptr,"","randnum:"+QString::number(randnum));

        // If range1 is empty or randnum is odd...
        if((randnum%2!=0 && !range2.isEmpty()) || range1.isEmpty())
            add_last_to(range2,i);
        // If range2 is empty or randnum is even...
        else if((randnum%2==0 && !range1.isEmpty()) || range2.isEmpty())
            add_last_to(range1,i);
    }

QMessageBox::information(nullptr,"",as_text());
}

void EString::add_last_to(QVector<ESymbol *> &vect, int index)
{
    m_symbols[index]=vect.last();	// Copy last item in vect to m_symbols
    vect.pop_back();	// Remove last item in vector
}

int EString::prevent_pattern(int &count, int size_diff)
{
    // if abs value of size_diff > COLOR_COUNT
    // make sure distribution is even

    srand(time(nullptr));	// Initialize random number generator
    int num=rand();		// Generate random number

    if(num%2==0 && count==1)
    {
        num++;
        count--;
    }
    else if(num%2==0) count++;
    else if(count==-1)
    {
        num++;
        count++;
    }
    else count--;

    return num;
}
#endif
