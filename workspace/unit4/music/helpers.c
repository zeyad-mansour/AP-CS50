// Helper functions for music

#include <cs50.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "helpers.h"

// Converts a fraction formatted as X/Y to eighths
int duration(string fraction)
{
    //TODO
    int num = fraction[0] - '0';
    int den = fraction[2] - '0';
    return num * (8 / den);

}
// Calculates frequency (in Hz) of a note
int frequency(string note)
{
    //TODO
    int oct = note[strlen(note) - 1] - '0';

    double frequency = 0.0;
    if (note[0] == 'A')
    {
        frequency = 440;
    }
    else if (note[0] == 'B')
    {
        frequency = 440.0 * (pow(2.0, (2.0 / 12.0)));
    }
    else if (note[0] == 'C')
    {
        frequency = 440.0 / (pow(2.0, (9.0 / 12.0)));
    }
    else if (note[0] == 'D')
    {
        frequency = 440.0 / (pow(2.0, (7.0 / 12.0)));
    }
    else if (note[0] == 'E')
    {
        frequency = 440.0 / (pow(2.0, (5.0 / 12.0)));
    }
    else if (note[0] == 'F')
    {
        frequency = 440.0 / (pow(2.0, (4.0 / 12.0)));
    }
    else if (note[0] == 'G')
    {
        frequency = 440.0 / (pow(2.0, (2.0 / 12.0)));
    }


    if (oct > 4) //oct is octave
    {
        for (int i = 0; i < oct - 4; i++)
        {
            frequency *= 2.0;
        }
    }
    else if (oct < 4)
    {
        for (int i = 0; i < 4 - oct; i++)
        {
            frequency /= 2.0;
        }
    }

    if (note[1] == 'b')
    {
        frequency /= (pow(2.0, (1.0 / 12.0)));
    }
    else if (note[1] == '#')
    {
        frequency *= (pow(2.0, (1.0 / 12.0)));
    }

    return round(frequency);

}

// Determines whether a string represents a rest
bool is_rest(string s)
{
    //TODO
	if (s[0] == '\0')
    {
        return true;
    }
    else
    {
        return false;
    }
}