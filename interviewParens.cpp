/*
 * Access Parentheses Removal Program
 *
 * During a phone interview this friday, the interviewer asked me this question
 * which I feel like I kinda botched.
 *
 * So, I kept working on it for about 40 minutes fter the interview
 * (mostly typing it all in again, since hackerrank wouldn't let me copy it,
 * and commenting it)
 * to make sure my solution worked and that I'm not an idiot.  Also to clarify
 * further what I said in the interview.
 *
 * @author James Winters
 * @date   17 Fri 2017
 */

#include <iostream>

/*
 * removeParens
 *
 * @param  : input : std::string : the string to be "cleaned"
 *                                 (i.e. removed of access parens)
 * @retval : std::string : a copy of n with access parens removed
 *
 * removes as many parentheses as possible from a string,
 * while maintaining pairs (an open and a close paren, in order)
 *
 * e.g.
 *
 *  "()()" -> "()()"
 *  "((()" -> "()"
 *  "(guten()(tag)" -> "(guten)(tag)" or "(guten()tag)"
 *  ")(" -> ""
 *
 * the basic idea is that we go through the string trying to find
 * pairs of parens until we find them all, then remove all parens that
 * aren't part of a pair
 */
std::string removeParens(std::string input)
{
  /*
   * Pair
   * a struct to store information for a single pair
   *
   * open  : int : the index of the opening paren
   * close : int : the index of the closing paren
   * isOpen : bool : whether or not the struct is open
   *                 (open paren was found but not the closer)
   */
  struct Pair
  {
    int open;
    int close;
    bool isOpen;

    Pair()
    {
      reset();
    }

    void reset()
    {
      open = -1;
      close = -1;
      isOpen = false;
    }
  } pair;

  // stores whether or not we made a pair this passthrough
  bool hasMadeANewPair = false;
  // stores, for each character in the input, whether or not it
  // will be included in the final output
  bool isIncluded[input.size()];

  for(int i=0; i<input.size(); i++)
  {
    // any character that isn't ( or ) is included
    isIncluded[i] = !(input[i] == '(' || input[i] == ')');
  }

  // find an add a paren-pair
  do
  {
    // each time we loop reset the variables
    hasMadeANewPair = false;
    pair.reset();

    // loop through the input
    for(int i=0; i<input.size(); i++)
    {
      if( !isIncluded[i] )  // ignore characters that are already included
      {
        // if we find an open paren and we haven't made a new pair yet ...
        if(input[i] == '(' && !pair.isOpen)
        {
          // ... make a new pair that opens at i
          pair.open = i;
          pair.isOpen = true;
          hasMadeANewPair = true;
        }

        // if we find a close paren and we have made a new pair ...
        if(input[i] == ')' && pair.isOpen)
        {
          // ... close the pair, and break out of the for loop
          pair.close = i;
          pair.isOpen = false;
          break;
        }
      }
    }

    // if we succesfully made and closed a pair, add those characters to isIncluded
    if(hasMadeANewPair && !pair.isOpen)
    {
      isIncluded[pair.open]  = true;
      isIncluded[pair.close] = true;
    }
  }
  while(hasMadeANewPair && !pair.isOpen);
  // keep going until we fail to make a new pair (no open paren)
  // or the pair fails to close (no close paren)

  std::string retval = "";

  // loop through the input and append any included characters to retval
  for(int i=0; i<input.size(); i++)
  {
    if(isIncluded[i])
    {
      // append 1 copy of the current character
      retval.append(1,input[i]);
    }
  }

  return retval;
}

/*
 * main
 *
 * main just reads a string from cin, and prints it back, along with it's
 * "cleaned" version
 */
int main(int argc, char** argv)
{
  // display a prompt
  std::cout << "enter a string to remove parens from" << std::endl << "> ";
  // declare a string and get a word from cin
  std::string input;
  std::cin >> input;

  // print the input and output of removeParens(input)
  std::cout << " input: \"" << input << "\"" << std::endl;
  std::cout << "output: \"" << removeParens(input) << "\"" << std::endl;

  return 0;
}
