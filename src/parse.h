/**
 * parse.h
 *
 * 		Code for parsing the universe file
 */

#ifndef PARSE_H_
#define PARSE_H_

#include <string.h>
#include "universe.h"
#include "gui.h"

extern char* universe_fname; //name of the universe file
extern double SCALE;
extern int SPEEDUP;
extern double dt;

 /*
  * Parses the universe from a file containing the initial state
  *
  * Lightweight CSV parser, character-by-character. Assumes the input is valid.
  * Will probably crash or cause undefined behavior if input is invalid.
  */
 int parse_universe(universe* universe, char* fname);

 /*
  * Parses the color passed as a string containing the color in hex form
  *
  * Color is defined as a 6-charecter string of hex digits in RGB formatted.
  * For example, FF0000 is RED and 00FFFF is cyan.
  * A pointer to a array of unsigned char (8 bits) is passed. It will alwas contain
  *   three items: red, green, and blue.
  *
  *  Returns null pointer if error occurs.
  */
 unsigned char* parse_color(char* item);

 /*
  * Returns the numerical value of a hexidecial charecter.
  *
  * Returns -1 if the charecter is not hexidecial.
  */
 unsigned char hex_value(char charecter);

/*
 * Parses the arguments passed on the command line
 *
 * Possible args:
 *     --scale SCALE
 *         sets the scale to SCALE (should be a double)
 *     --speedup SPEEDUP
 *         sets the speedup to SPEEDUP (should be an integer)
 *     --dt DT
 *         sets the timestep to DT (in seconds)
 *         lower means more accuracy; higher means faster simulation
 *         defualt is 1 second
 */
void parse_args(int argc, char** argv);

#endif /*PARSE_H_*/
