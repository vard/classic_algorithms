#include "union_find.h"
#include <iomanip>


namespace union_find{

    QuickFindUF::QuickFindUF(boost::uint32_t itemsCount)
        :id(new uint32_t[itemsCount]),
        count(itemsCount){
            for(uint32_t i = 0; i < count; ++i){
                id[i] = i;
            }
    }

    bool QuickFindUF::connected(boost::uint32_t p, boost::uint32_t q){
        return id[q] == id[q];
    }

    void QuickFindUF::unionItems(boost::uint32_t p, boost::uint32_t q){
        uint32_t pid = id[p];
        uint32_t qid = id[q];

        for(uint32_t i = 0; i < count; ++i){
            if(id[i] == pid)
                id[i] = qid;
        }
    }

    std::ostream& operator<<(std::ostream& outStream, const QuickFindUF& rhs ){
        outStream << setw(2);
        for(uint32_t i = 0; i < rhs.count; ++i){
            outStream << i << " ";
        }
        outStream << std::endl;
        outStream << setw(2);
        for(uint32_t i = 0; i < rhs.count; ++i){
            outStream << rhs.id[i] << " ";
        }
        return outStream;
    }

    QuickUnionUF::QuickUnionUF(boost::uint32_t itemsCount)
        :count(itemsCount),
        id(new uint32_t[count]){
            for(uint32_t i = 0; i < count; i++)
                id[i] = i;
    }

    uint32_t QuickUnionUF::root(uint32_t index){
        uint32_t i = index;
        while(id[i] != i)
            i = id[i];
        return i;
    }

    bool QuickUnionUF::connected(boost::uint32_t p, boost::uint32_t q){
        return root(p)==root(q);
    }

    void QuickUnionUF::unionItems(boost::uint32_t p, boost::uint32_t q){
        uint32_t rootP = root(p);
        uint32_t rootQ = root(q);
        id[rootQ] = rootP;
    }

    std::ostream& operator<<(std::ostream& outStream, const QuickUnionUF& rhs ){
        outStream << setw(2);
        for(uint32_t i = 0; i < rhs.count; ++i){
            outStream << i << " ";
        }
        outStream << std::endl;
        outStream << setw(2);
        for(uint32_t i = 0; i < rhs.count; ++i){
            outStream << rhs.id[i] << " ";
        }
        return outStream;
    }

}