#include "parse.h"


int parse_universe(universe* universe, char* fname)
 {
     char const* const file_name = fname;
     FILE* file = fopen(file_name, "r"); //Open the file for reading
     char line[256]; //buffer to store lines

     int body_num = 0;

     if (file != NULL)
     {
         //to store state variables
         char* name;
         double pos[3] = { 0, 0, 0 };
         double vel[3] = { 0, 0, 0 };
         double mass = 0;

         //while there's a new line
         while (fgets(line, sizeof(line), file))
         {
             if (feof(file) || strlen(line) == 0)
             {
                 //finished reading file, escape
                 break;
             }

             //if the line is not a comment
             if(line[0] != '#')
             {

                 int item_num = 0;
                 int item_start = 0; //starting index of current item
                 int item_end;

                 //scan the line for all 8 items of information (Name, pos_1, pos_2, pos_3, vel_1, vel_2, vel_3, mass)
                 while (item_num < 8)
                 {
                     int curr_char = item_start;

                     //find next comma/line end
                     while (line[curr_char] != ',' && line[curr_char] != '\n')
                     {
                         curr_char++;
                     }

                     item_end = curr_char;
                     char* item = malloc((item_end - item_start + 1) * sizeof(char)); //allocate space for current item
                     curr_char = item_start;

                     //copy the current item value to item
                     while (curr_char < item_end)
                     {
                         item[curr_char - item_start] = line[curr_char];
                         curr_char++;
                     }
                     item[item_end - item_start] = '\0'; //null terminator

                     //we now have the item in a string called `item` and need to use it
                     if (item_num == 0)
                     {
                         //the name
                         name = strdup(item);
                     }
                     if (item_num > 0 && item_num < 4)
                     {
                         //the position
                         pos[item_num - 1] = strtod(item, 0);
                     }
                     if (item_num > 3 && item_num < 7)
                     {
                         //the velocity
                         vel[item_num - 4] = strtod(item, 0);
                     }
                     if (item_num == 7)
                     {
                         //the mass
                         mass = strtod(item, 0);
                     }

                     //move onto next item

                     //if we're already at the end of the line, and we haven't found enough items
                     if(line[curr_char] == '\n' && item_num < 7)
                     {
                         free(item);
                         fclose(file);
                         return -1;
                     }
                     item_num++;
                     item_start = item_end + 1; //next item starts right after this one ends
                     free(item);
                 }

                 //if we found the name, pos, and mass but there is another item, then that item is the optional color
                 if(item_num == 8 && line[item_end] == ',')
                 {
                     item_start = item_end + 1;
                     int curr_char = item_start;
                     while(line[curr_char] != '\n')
                     {
                         curr_char++;
                     }
                     item_end = curr_char;
                     char* item = malloc((item_end - item_start + 1) * sizeof(char));
                     curr_char = item_start;
                     while(curr_char < item_end)
                     {
                         item[curr_char - item_start] = line[curr_char];
                         curr_char++;
                     }
                     if(item_end - item_start != 6)
                     {
                         return -1; //file is malformed as color must be 6 charecters long
                     }
                     unsigned char* the_color = parse_color(item);
                     free(item);
                     if(the_color != 0)
                     {
                         planet* my_planet;
                         my_planet = new_planet_color(name, pos, vel, mass, (unsigned char[3]) {the_color[0], the_color[1], the_color[2]});
                         add_planet(universe, my_planet);
                         body_num++;
                         free(name);
                         free(the_color);
                    }
                    else
                    {
                        free(name);
                        return -1; //file is malformed as the color was not a valid hexidecial string
                    }
                 }
                 else
                 {
                     //create a new planet with the value from the file, and add to universe
                     planet* my_planet;
                     my_planet = new_planet(name, pos, vel, mass);
                     add_planet(universe, my_planet);
                     body_num++;
                     free(name);
                 }
             }
         }
         //close the file
         fclose(file);
     }
     else
     {
         return -2;
     }
     return 0;
 }

 unsigned char* parse_color(char* item)
 {
     unsigned char* color = malloc(3 * sizeof(unsigned char));

     for(int i = 0; i < 3; i++)
     {
         unsigned char curr_color = 0;
         //first digit
         unsigned char c = hex_value(item[2*i]);
         if(c != -1)
         {
             curr_color += c;
         }
         else
         {
             return 0;
         }
         //second digit
         c = hex_value(item[2*i + 1]);
         if(c != -1)
         {
             curr_color += c * 16;
         }
         else
         {
             return 0;
         }
         //final color
         color[i] = curr_color;
     }

     return color;
 }

 unsigned char hex_value(char charecter)
 {
     if(charecter >= '0' && charecter <= '9')
     {
         return charecter - '0';
     }
     else
     {
         switch (charecter) {
             case 'A':
                return 10;
                break;
             case 'B':
                return 11;
                break;
             case 'C':
                return 12;
                break;
             case 'D':
                return 13;
                break;
             case 'E':
                return 14;
                break;
             case 'F':
                return 15;
                break;
             default:
                return -1;
                break;
         }
     }
 }

void parse_args(int argc, char** argv)
{
    for(int a = 1; a < argc; )
    {
        if(strcmp(argv[a], "--scale") == 0)
        {
            SCALE = strtod(argv[a+1],0);
            a += 2;
        }
        if(strcmp(argv[a], "--speedup") == 0)
        {
            SPEEDUP = (int) strtol(argv[a+1],0,10);
            a += 2;
        }
        else
        {
            universe_fname = strdup(argv[a]);
            printf("Found file %s\n", universe_fname);
            a++;
        }

    }

    return;
}
