//******** copyright © 2025 jishnu periya, jonathon bell. all rights reserved.
//*
//*
//*  version : $header:$
//*
//*
//*  purpose : implements the main entry point to the test runner.
//*
//*
//*  see also: https://github.com/doctest/doctest/blob/master/doc/markdown/main.md
//*            for more on the doctest main entry point.
//*                                                                     0-0
//*                                                                   (| v |)
//**********************************************************************w*w***

#include <set>										     // for std::set
#include <algorithm>								     // for std::set_intersection, std::set_union
#include <vector>									     // for std::vector
#include <doctest/doctest.h>                             // for doctest
#include "harmony.hpp"								     // for harmony::note
#include "note_set.hpp"                                  // for harmony::note_set
//****************************************************************************

using namespace harmony;


TEST_CASE("basic operations")
{

   /* using notes_t = std::set<note>;*/
    using notes_t = harmony::note_set;

    std::vector<note> notes = { note("C"), note("E") , note("G") };
    notes_t c_major(notes.begin(), notes.end());

    SUBCASE("insert") {
        c_major.insert(note("B"));
        CHECK(c_major.contains(note("B")));
    }

    SUBCASE("erase") {
        c_major.insert(note("B"));
        c_major.erase(note("B"));
        CHECK(!c_major.contains(note("B")));
    }

    SUBCASE("contains and find") {
        CHECK(c_major.contains(note("C")));
        CHECK(c_major.find(note("C")) != c_major.end());
        CHECK(!c_major.contains(note("A")));
    }

    SUBCASE("iteration") {
        std::vector<std::string> collected;
        for (auto& n : c_major) {
            collected.push_back(n.name());
        }

        CHECK(collected.size() == 3);
        CHECK(collected[0] == "C");
        CHECK(collected[1] == "E");
        CHECK(collected[2] == "G");
    }
}

TEST_CASE("set algorithms on notes_t") {
    using notes_t = std::set<note>;

    notes_t c_major = { note("C"), note("E"), note("G") };
    notes_t minor = { note("A"), note("C"), note("E") };

    SUBCASE("intersection") {
        notes_t inter;
        std::set_intersection(
            c_major.begin(), c_major.end(),
            minor.begin(), minor.end(),
            std::inserter(inter, inter.begin())
        );

        CHECK(inter.size() == 2);
        CHECK(inter.contains(note("C")));
        CHECK(inter.contains(note("E")));
    }

    SUBCASE("union") {
        notes_t uni;
        std::set_union(
            c_major.begin(), c_major.end(),
            minor.begin(), minor.end(),
            std::inserter(uni, uni.begin())
        );

        CHECK(uni.size() == 4);
        CHECK(uni.contains(note("A")));
        CHECK(uni.contains(note("C")));
        CHECK(uni.contains(note("E")));
        CHECK(uni.contains(note("G")));
    }
}
