#include <iostream>
#include <string>

/* 
Regular Expression:  a regular expression is a specific pattern that provides concise and flexible means 
	to "match" strings of text, such as particular characters, words, or patterns of characters. - wikipedia
*/

#include <regex>
using namespace std;

int main() {
   string str;
   while (true) {
      cin >> str;
	//   regex e("abc.", regex_constants::icase);   // .   Any character except newline
	//   regex e("abc?");               // ?       Zero or 1 preceding character
	//   regex e("abc*");               // *       Zero or more preceding character
	//   regex e("abc+");               // +       One of more preceding character
	//   regex e("ab[cd]*");            // [...]   Any character inside the square brackets
	//   regex e("ab[^cd]*");           // [^...]   Any character not inside the square brackets
	//   regex e("ab[cd]{3,5}");
	//   regex e("abc|de[\\]fg]");         // |       Or
	//   regex  e("(abc)de+\\1");       // \1      First group
	//   regex  e("(ab)c(de+)\\2\\1");
	//   regex e("[[:w:]]+@[[:w:]]+\\.com"); // [[:w:]] word character: digit, number, or underscore
	  regex e("[[:w:]]+@[[:w:]]+\\.com"); 

	//   regex e("abc.$");                 // $   End of the string
	//   regex e("^abc.+");                 // ^   begin of the string
	  

	  bool match = regex_match(str, e);
	//   bool match = regex_search(str, e);

	  cout << (match? "Matched" : "Not matched") << endl << endl;
   }
}





/*

Regular Expression Grammars:

   ECMAScript
   basic
   extended
   awk
   grep 
   egrep

 */

