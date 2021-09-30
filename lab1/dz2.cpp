#include <iostream>
#include <set>
#include <random>
#include <fstream>

//общий класс

class States {
public:
    States() = default;

    virtual bool contains(int s) const {
        return true;
    }

};

class DiscreteState: public States {
private:
    int const state;

public:
    DiscreteState(int state): state(state) { }

    bool contains(int s) const {
        return s == state;
    }
};

class SegmentState: public States {
private:
    int const beg, end;

public:
    SegmentState(): beg(0), end(-1) { }
    SegmentState(int beg, int end): beg(beg), end(end) { }

    bool contains(int s) const {
        return s >= beg && s <= end;
    }
};

class SetState: public States {
private:
    std::set<int> const states;

public:
    SetState(): states() { }
    SetState(std::set<int> const &src): states(src) { }

    bool contains(int s) const {
        return states.count(s) > 0;
    }
};

// непрерывные состояния с дополнением

class SegmPlusDisc: public States {
private:
    States const *s1, *s2;

public:
    SegmPlusDisc(States *s1, States *s2): s1(s1), s2(s2) { }
    bool contains(int s) const {
        return (s1->contains(s) || s2->contains(s));
    }
};

// непрерывные состояния с пропуском

class SegmMinusDisc: public States {
private:
    States const *s1, *s2;

public:
    SegmMinusDisc(States *s1, States *s2): s1(s1), s2(s2) { }
    bool contains(int s) const {
        return s1->contains(s) && !(s2->contains(s));
    }
};

class ProbabilityTest {
private:
    unsigned seed;
    int test_min, test_max;
    unsigned test_count;

public:
    ProbabilityTest(unsigned seed, int test_min, int test_max, unsigned test_count): seed(seed), test_min(test_min),test_max(test_max), test_count(test_count) { }

    float operator()(States const &s) const {
        std::default_random_engine rng(seed);
        std::uniform_int_distribution<int> dstr(test_min,test_max);
        unsigned good = 0;
        for (unsigned cnt = 0; cnt != test_count; ++cnt)
            if (s.contains(dstr(rng))) ++good;

        return static_cast<float>(good)/static_cast<float>(test_count);
    }
};

int main(int argc, const char * argv[]) {
    DiscreteState d(100);
    SegmentState s(0,10);
    SetState ss({1, 3, 5, 7, 23, 48, 57, 60, 90, 99});
    ProbabilityTest pt(10,1,10,100000);

    DiscreteState ds1(10);
    SegmentState ss1(1, 3);
    SegmentState ss2(8, 10);

    std::cout << pt(ds1) << std::endl;
    std::cout << pt(ss1) << std::endl;
    std::cout << pt(ss2) << std::endl;

    SegmPlusDisc splus(&ss2, &ss1);
    SegmMinusDisc sminus(&ss2, &ds1);

    std::cout << pt(splus) << std::endl;
    std::cout << pt(sminus) << std::endl;

    return 0;
}
