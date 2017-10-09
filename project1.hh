///////////////////////////////////////////////////////////////////////////////
// project1.hh
//
// The three algorithms specified in the project 1 requirements
// document, plus helper functions.
//
///////////////////////////////////////////////////////////////////////////////

#pragma once

#include <algorithm>
#include <cassert>
#include <fstream>
#include <string>
#include <vector>


// Convenient typedef for a vector of strings.
typedef std::vector<std::string> string_vector;





// Declaration of self made helper functions
char find_mode(const std::vector<char>& chars_found, const std::vector<int>& times_found);
void add_to_counts(char character,
                        std::vector<char>& chars_found, std::vector<int>& times_found);




// Load words from the file at the given path. The words vector is
// cleared, and then each word from the file is added to the
// vector. Returns true on success or false on I/O error.
bool load_words(string_vector& words, const std::string& path) {
  using namespace std;

  // vector is cleared
  words.clear();


  // Open file for reading
  ifstream readFile;
  readFile.open(path.c_str());

  //check for I/O error
  if (readFile.fail() ){
    readFile.clear();
    return false;
  }

  // occupy vector
  while(true)
  {
      string w;
      readFile >> w;
      if(!readFile)
      {
          readFile.clear();
          break;
      }
      words.push_back(w);
  }

  readFile.close();

  return true;
}

// Return true if string2 is a mirrored copy of string1, or false
// otherwise. In other words, return true if string1 is the reverse of
// string2. Return false when both strings are equal; by this rule,
// "aaa" is not a mirror of "aaa" even though they are technically the
// reverse of each other. Likewise "" is not a mirror of "". This
// function should be in-place, meaning that it only examines string1
// and string2 and never creates another string object.
bool is_mirrored(const std::string& string1, const std::string& string2) {

  // string can't be mirrors if they are not the same length.
  int str1Length = string1.length();
  int str2Length = string2.length();


  // "" is handled because it can't have a mirror that isn't itself
  // therefore if fails to not be equal to itself or is a different
  // size than the other string. No specific test is necessary.

  if( string1 != string2 && str1Length == str2Length ){

    for( int i = 0; i < string1.length(); i++){

        if( string1[i] == string2[str2Length - i - 1]){
            continue;
        }
        else{
            return false;
        }
    }
    return true;
  }

  return false;
}

// Return true if alleged_substring can be found as a substring of
// alleged_superstring. For example, "cat" is a substring of
// "catamaran"; "tama" is also a substring of "catamaran". This
// function should be in-place, meaning that it only examines string1
// and string2 and never creates another string object.
bool is_substring(const std::string& alleged_substring,
		  const std::string& alleged_superstring) {

  int sub_length = alleged_substring.length();
  int super_length = alleged_superstring.length();

  if (alleged_substring == ""){
    return true;
  }


  if(sub_length == super_length)
  {
      return false;
  }

  // if you go through all chars in the alleged substring
  // and they are all found in alleged super string
  // then the alleged substring is a substring
  int sequential_chars_from_sub_in_super = 0;
  for( int i = 0; i < super_length; i++){

        for( int j = 0; j < sub_length && (super_length - i) >= sub_length; j++){

            if (alleged_substring[j] != alleged_superstring[i+j]){
                break;
            }
            sequential_chars_from_sub_in_super = j+1;
        }
        if ( sequential_chars_from_sub_in_super == sub_length){
            return true;
        }
  }

  return false;
}

// Return the character that occurs the most times in the given vector
// of strings. The vector must contain at least one character, so that
// the mode is defined. In the event of a tie (i.e. two characters
// have the same count), this function returns the tied character with
// the lesser ASCII code (i.e. the tied character that comes first in
// conventional alphabetical order).
char character_mode(const string_vector& strings) {
  // TODO: implement this function, then delete this comment
  std::vector<char> chars_in_strings;
  std::vector<int> times_chars_occur;


  for( int i = 0; i < strings.size(); i++)
  {
    for( int j = 0; j < strings[i].length(); j++)
    {
        add_to_counts(strings[i][j], chars_in_strings, times_chars_occur);
    }

  }
  char mode_char = find_mode(chars_in_strings, times_chars_occur);

  return mode_char;
}






// Takes non-empty vectors of chars and associated vector integers
// detailing how many times the chars have been seen. Then gives the
// char with the greatest associated integer value (mode) and lowest
// ASCII value.
char find_mode(const std::vector<char>& chars_found,const std::vector<int>& times_found)
{
    int v_length = chars_found.size();
    char char_found_most = chars_found[0];
    int most_times_char_found = times_found[0];

    for( int i = 1; i < v_length; i++)
    {
        if( times_found[i] == most_times_char_found){
            if( chars_found[i] < char_found_most){
                char_found_most = chars_found[i];
            }
        }
        else if( times_found[i] > most_times_char_found){
            char_found_most = chars_found[i];
            most_times_char_found = times_found[i];
        }
    }

    return char_found_most;
}

void add_to_counts(char character,
                        std::vector<char>& chars_found, std::vector<int>& times_found)
{
    for( int i = 0; i < chars_found.size(); i++)
    {
        if( character == chars_found[i] ){
            times_found[i] += 1;
            return;
        }
    }
    chars_found.push_back(character);
    times_found.push_back(1);
}










// Return a longest string in the strings vector whose mirror is also
// in the vector. Strings are mirrors of each other in the same sense
// as described above for the is_mirrored(...) function. Either of the
// two mirrored strings may be returned; for example, if the vector
// contains both "cat" and "tac", this function is allowed to return
// either "cat" or "tac". If the vector contains no mirrored strings,
// returns an empty string.
std::string longest_mirrored_string(const string_vector& strings) {
  // TODO: implement this function, then delete this comment

  // find strings with mirrors (ms)
  string_vector string_with_mirror;

  for( int i = 0; i < strings.size() - 1 ; i++){
    for( int j = i; j < strings.size(); j++){
        if( is_mirrored(strings[i], strings[j]) ){
            string_with_mirror.push_back(strings[i]);
        }
    }
  }

  // no mirrored strings
  if( string_with_mirror.size() == 0 ){
    return "";
  }

  // find the longest ms
  int index_lms = 0;
  int maximum = string_with_mirror[0].length();

  for ( int i = 1; i < string_with_mirror.size(); i++){
      if( string_with_mirror[i].length() > maximum ){
        index_lms = i;
        maximum = string_with_mirror[i].length();
      }
  }

  return string_with_mirror[index_lms];
}

// Return a vector of length exactly three, containing the longest
// substring trio from the string vector. A substring trio is three
// non-empty, distinct, strings a, b, and c such that a is a substring
// of b, b is a substring of c. This function returns the substring
// trio with the longest total length of a, b, and c. If the input
// vector does not contain a substring trio, return a vector
// containing exactly three empty strings.
string_vector longest_substring_trio(const string_vector& strings) {
  // TODO: implement this function, then delete this comment

  int trio_Size = 3;
  std::vector<int> max_trio;
  int mt_sum = 0;

  std::vector<int> a_trio;
  int at_sum = 0;


  for( int i = 0; i < strings.size(); i++){

     for( int j = 0; j < strings.size(); j++){
        if( is_substring(strings[j], strings[i])  && j != i ){

            for( int k = 0; k < strings.size(); k++){
                if( is_substring(strings[k], strings[j]) &&  k!= j && k != i){
                    a_trio.push_back(i);
                    a_trio.push_back(j);
                    a_trio.push_back(k);
                    at_sum = strings[ a_trio[0] ].length()
                                + strings[ a_trio[1] ].length()
                                + strings[ a_trio[2] ].length();

                    if ( !max_trio.empty() ){
                        if( at_sum > mt_sum){
                            max_trio = a_trio;
                            mt_sum = at_sum;
                        }
                    }
                    else{
                        max_trio = a_trio;
                        mt_sum = at_sum;
                    }
                    a_trio.clear();
                }
            }
        }
     }
  }


  string_vector longest_trio;

  if ( mt_sum == 0 ){
      for( int i = 0; i < trio_Size; i++){
        longest_trio.push_back("");
      }
  }
  else{
      for( int i = 0; i < trio_Size; i++){
        longest_trio.push_back(strings[ max_trio[i] ] );
      }
  }

  return longest_trio;
}
