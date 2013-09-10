/* 
 * File:   string_subsearch.h
 * Author: vard
 *
 * Created on September 7, 2013, 9:16 PM
 */

#ifndef SUBSTRING_SEARCH_H
#define	SUBSTRING_SEARCH_H
#pragma once

#include <cstdint>
#include <string>
#include <vector>

namespace substring_search {

    class AbstractSubstringSearch {
    public:
        virtual int32_t search(const std::string& pattern, const std::string& text) = 0;
        virtual ~AbstractSubstringSearch();
    };

    class BruteForceSearch : public AbstractSubstringSearch {
    public:
        virtual int32_t search(const std::string& pattern, const std::string& text);
    };

    class KMPSubstringSearch : public AbstractSubstringSearch{
    private:
        std::vector<std::vector<uint32_t> > dfa_;
        void dfaConstruct(const std::string& pat);
    public:
        virtual int32_t search(const std::string& pattern, const std::string& text);
    };

    class BoyerMooreSubstringSearch : public AbstractSubstringSearch{
    private:
        std::vector<int32_t> right_;
    public:
        virtual int32_t search(const std::string& pattern, const std::string& text);
    };

}

#endif	/* SUBSTRING_SEARCH_H */

