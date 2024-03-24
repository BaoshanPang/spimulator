// Permission is hereby granted for anyone to do anything that they
// want with this material—you may freely reprint it, redistribute it,
// amend it or do whatever you like with it provided that
// you include an acknowledgement of the original authorship and copyright in
// the form of a link to this page. In doing so
// you must accept that you do so strictly on your own
// liability and that you accept any consequences with no liability whatsoever
// remaining with the original authors. If you find the material useful
// and happen to encounter one of the authors, it is unlikely
// that they will refuse offers to buy them a drink. You
// may therefore like to consider this material ‘drinkware’. (Offer void where
// prohibited by law, in which case fawning and flattery may be substituted.)

// https://publications.gbdirect.co.uk//c_book/copyright.html

// Copyright (c) 2021-2023 William Emerison Six
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//

/* Purpose */
// Read from std in until EOF (Ctrl-D on Linux)
// Print out number of command and periods

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

#include "operatingsystemfunctions.h"

/*
struct main_stack_frame {
  int32_t comma_count;
  int32_t stop_count;
  char this_char;
  int32_t return_code;
};
*/

#define MAIN_STACK_FRAME_OFFSET_TO_COMMA_COUNT 0
#define MAIN_STACK_FRAME_OFFSET_TO_STOP_COUNT \
  (MAIN_STACK_FRAME_OFFSET_TO_COMMA_COUNT + SIZE_OF_INT32_T)
#define MAIN_STACK_FRAME_OFFSET_TO_THIS_CHAR \
  (MAIN_STACK_FRAME_OFFSET_TO_STOP_COUNT + SIZE_OF_INT32_T)
#define MAIN_STACK_FRAME_OFFSET_TO_RETURN_VALUE \
  (MAIN_STACK_FRAME_OFFSET_TO_THIS_CHAR + SIZE_OF_INT32_T)
#define SIZE_OF_MAIN_STACK_FRAME \
  (MAIN_STACK_FRAME_OFFSET_TO_RETURN_VALUE + SIZE_OF_INT32_T)

int main(int argc, char *argv[]) {
  // the frame pointer is the current stack frame, aka, where the local
  // variables are
  frame_pointer = frame_pointer - SIZE_OF_MAIN_STACK_FRAME;

  /*
  struct main_stack_frame main_stack_frame =
    {
      .comma_count = 0,
      .stop_count = 0,
      .this_char = 0,
      .return_code = EXIT_SUCCESS
    };
  */

  // set comma count
  {
    int32_t comma_count_in_instruction = 0;
    xmemcpy(/*dest*/ frame_pointer + MAIN_STACK_FRAME_OFFSET_TO_COMMA_COUNT,
            /*src*/ &comma_count_in_instruction,
            /*numberOfBytes*/ SIZE_OF_INT32_T);
  }
  // set stop count
  {
    int32_t stop_count_in_instruction = 0;
    xmemcpy(/*dest*/ frame_pointer + MAIN_STACK_FRAME_OFFSET_TO_STOP_COUNT,
            /*src*/ &stop_count_in_instruction,
            /*numberOfBytes*/ SIZE_OF_INT32_T);
  }
  // set this_char
  {
    int32_t this_char_in_instruction = 0;
    xmemcpy(/*dest*/ frame_pointer + MAIN_STACK_FRAME_OFFSET_TO_THIS_CHAR,
            /*src*/ &this_char_in_instruction,
            /*numberOfBytes*/ SIZE_OF_INT32_T);
  }
  // set return_code
  {
    int32_t return_code_in_instruction = EXIT_SUCCESS;
    xmemcpy(/*dest*/ frame_pointer + MAIN_STACK_FRAME_OFFSET_TO_RETURN_VALUE,
            /*src*/ &return_code_in_instruction,
            /*numberOfBytes*/ SIZE_OF_INT32_T);
  }

  {
    char readCharacter = read_char();
    xmemcpy(/*dest*/ frame_pointer + MAIN_STACK_FRAME_OFFSET_TO_THIS_CHAR,
            /*src*/ &readCharacter,
            /*numberOfBytes*/ SIZE_OF_INT32_T);
  }
loopBegin : {
  char this_char_in_register;
  xmemcpy(/*dest*/ &this_char_in_register,
          /*src*/ frame_pointer + MAIN_STACK_FRAME_OFFSET_TO_THIS_CHAR,
          /*numberOfBytes*/ SIZE_OF_INT32_T);
  if (this_char_in_register == EOF) goto loopEnd;
}
  {
    char this_char_in_register;
    xmemcpy(/*dest*/ &this_char_in_register,
            /*src*/ frame_pointer + MAIN_STACK_FRAME_OFFSET_TO_THIS_CHAR,
            /*numberOfBytes*/ SIZE_OF_INT32_T);
    if (this_char_in_register != '.') goto notAPeriod;
  }
  {
    char stop_count_in_register;
    xmemcpy(/*dest*/ &stop_count_in_register,
            /*src*/ frame_pointer + MAIN_STACK_FRAME_OFFSET_TO_STOP_COUNT,
            /*numberOfBytes*/ SIZE_OF_INT32_T);

    stop_count_in_register = stop_count_in_register + 1;

    xmemcpy(/*dest*/ frame_pointer + MAIN_STACK_FRAME_OFFSET_TO_STOP_COUNT,
            /*src*/ &stop_count_in_register,
            /*numberOfBytes*/ SIZE_OF_INT32_T);
  }
notAPeriod : {
  char this_char_in_register;
  xmemcpy(/*dest*/ &this_char_in_register,
          /*src*/ frame_pointer + MAIN_STACK_FRAME_OFFSET_TO_THIS_CHAR,
          /*numberOfBytes*/ SIZE_OF_INT32_T);

  if (this_char_in_register != ',') goto notAComma;
}
  {
    char comma_count_in_register;
    xmemcpy(/*dest*/ &comma_count_in_register,
            /*src*/ frame_pointer + MAIN_STACK_FRAME_OFFSET_TO_COMMA_COUNT,
            /*numberOfBytes*/ SIZE_OF_INT32_T);

    comma_count_in_register = comma_count_in_register + 1;

    xmemcpy(/*dest*/ frame_pointer + MAIN_STACK_FRAME_OFFSET_TO_COMMA_COUNT,
            /*src*/ &comma_count_in_register,
            /*numberOfBytes*/ SIZE_OF_INT32_T);
  }
notAComma : {
  char readCharacter = read_char();
  xmemcpy(/*dest*/ frame_pointer + MAIN_STACK_FRAME_OFFSET_TO_THIS_CHAR,
          /*src*/ &readCharacter,
          /*numberOfBytes*/ SIZE_OF_INT32_T);
  goto loopBegin;
}

loopEnd : {
  char comma_count_in_register;
  xmemcpy(/*dest*/ &comma_count_in_register,
          /*src*/ frame_pointer + MAIN_STACK_FRAME_OFFSET_TO_COMMA_COUNT,
          /*numberOfBytes*/ SIZE_OF_INT32_T);
  print_int(comma_count_in_register);
}
  print_string(" commas, ");
  {
    char stop_count_in_register;
    xmemcpy(/*dest*/ &stop_count_in_register,
            /*src*/ frame_pointer + MAIN_STACK_FRAME_OFFSET_TO_STOP_COUNT,
            /*numberOfBytes*/ SIZE_OF_INT32_T);
    print_int(stop_count_in_register);
  }
  print_string(" stops\n");
  {
    char return_code_in_register;
    xmemcpy(/*dest*/ &return_code_in_register,
            /*src*/ frame_pointer + MAIN_STACK_FRAME_OFFSET_TO_RETURN_VALUE,
            /*numberOfBytes*/ SIZE_OF_INT32_T);
    frame_pointer = frame_pointer + SIZE_OF_MAIN_STACK_FRAME;
    return return_code_in_register;
  }
}
