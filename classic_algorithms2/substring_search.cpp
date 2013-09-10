#include <algorithm>
#include "substring_search.h"

using namespace std;

namespace substring_search{
    
    AbstractSubstringSearch::~AbstractSubstringSearch(){

    }

    int32_t BruteForceSearch::search(const std::string& pattern, const std::string& text){
        uint32_t txtLen = text.size();
        uint32_t patLen = pattern.size();
        for(uint32_t i = 0; i<= txtLen - patLen; ++i){
            uint32_t j;
            for(j = 0; j < patLen; ++j){
                if(text.at(j+i)!=pattern.at(j)){
                    break;
                }

            }
            if(j == patLen)
                return i;
        }
        return -1;
    }
    
    int32_t KMPSubstringSearch::search(const std::string &pattern, const std::string &text){
        dfaConstruct(pattern);
        uint32_t textLen = text.size();
        uint32_t patSize = pattern.size();

        uint32_t i, j;
        for(i = 0, j = 0; i < textLen && j < patSize; ++i){
            j = dfa_[text.at(i)][j];
        }
        if(j == patSize)
            return i-patSize;
        else
            return -1;
    }

    void KMPSubstringSearch::dfaConstruct(const std::string& pat){
        uint32_t alphabetSize = 256;
        uint32_t patLen = pat.size();
        dfa_.clear();
        dfa_.resize(alphabetSize);
        for(std::vector<vector<uint32_t> >::iterator it = dfa_.begin(); it != dfa_.end(); ++it){
            it->resize(patLen);
        }

        dfa_[pat.at(0)][0] = 1;

        for(uint32_t xState = 0, j = 1; j < patLen; ++j){
            for(uint32_t c = 0; c < alphabetSize; ++c){  // copy mismatches
                dfa_[c][j] = dfa_[c][xState];
            }

            dfa_[pat.at(j)][j] = j+1;
            xState = dfa_[pat.at(j)][xState];
        }
    }

    int32_t BoyerMooreSubstringSearch::search(const std::string& pattern, const std::string& text){
        right_.clear();
        uint32_t alphabetSize = 256;
        uint32_t patLen = pattern.size();
        right_.resize(alphabetSize);

        for(std::vector<int32_t>::iterator it = right_.begin(); it != right_.end(); ++it){
            *it = -1;
        }

        for(uint32_t c = 0; c < patLen; ++c){
            right_[pattern.at(c)] = c;
        }

        uint32_t textLen = text.size();
        uint32_t skip = 0;

        for(uint32_t i = 0; i < textLen - patLen; i+=skip){
            skip = 0;

            for(int32_t j = patLen -1 ; j >= 0; --j){
                if(pattern.at(j)!=text.at(i+j))
                    skip = std::max(1, right_[text.at(i+j)]);
            }
            if(skip==0)
                return i;
        }

        return -1;


    }
}
