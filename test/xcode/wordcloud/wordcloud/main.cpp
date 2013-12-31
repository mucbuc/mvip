#include <cassert>
#include <string>
#include <map>
#include <sstream>
#include <istream>
#include <vector>
#include <iostream>
#include <iterator>
#include <sstream>

using namespace std;

struct WordInfo {
    WordInfo(const string &w, int c) : word(w), count(c) {}
    bool operator<(const WordInfo &info) const {
        //TODO: Fill in if necessary
        return false;
    }
    
    string word;
    int count;
};

class WordWizard {
public:
    WordWizard(string input) : doc(input) {
    }
    
    //Return a list of the words in the document with the number of times they occur.
    //The list should be sorted by most to least used words.
    vector<WordInfo> wordCloud() {
        vector<WordInfo> cloud;
        
        //TODO: Fill in
        
        return cloud;
    }
    
    static void test_split() {
        vector< string > r( split( "hello luke" ) );
        
        assert( r.size() == 3 );
        assert( r[0] == "hello" );
        assert( r[1] == "luke" );
    
        std::cout << "test_split passed" << std::endl;
    }
    
protected:
    //Split the given input into a vector of words using whitespace as the delimeter.
    static vector<string> split(const string &input) {
        //TODO: Fill in
        
        std::stringstream s( input );
        vector<string> result;
        while (s) {
            string t;
            s >> t;
            result.push_back( t );
        }
        
        return result;
    }
    
    string doc;
};


int main(int argc, char *argv[])
{
    WordWizard::test_split();
    
    
    WordWizard wizard("This is a word cloud test.\r\nThe word cloud test will sort and count the words of the test.\r\nSo cloud it up.");
    vector<WordInfo> cloud = wizard.wordCloud();
    for(vector<WordInfo>::iterator itr = cloud.begin(); itr != cloud.end(); itr++) {
        WordInfo info = *itr;
        cout << "[" << info.word << "] --> " << info.count << endl;
    }
    return 0;
}
