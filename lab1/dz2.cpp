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
    SegmentState const *sg;
    DiscreteState const *ds;

public:
    SegmPlusDisc(SegmentState *sg, DiscreteState *ds): sg(sg), ds(ds) { }
    bool contains(int s) const {
        return (sg->contains(s) || ds->contains(s));
    }
};

// непрерывные состояния с пропуском

class SegmMinusDisc: public States {
private:
    SegmentState const *sg;
    DiscreteState const *ds;

public:
    SegmMinusDisc(SegmentState *sg, DiscreteState *ds): sg(sg), ds(ds) { }
    bool contains(int s) const {
        return sg->contains(s) && !(ds->contains(s));
    }
};

// непрерывные состояния с пропуском и дополнением

class SegmBothDisc: public States {
private:
    SegmPlusDisc const *spd;
    SegmMinusDisc const *smd;

public:
    SegmBothDisc(SegmPlusDisc *spd, SegmMinusDisc *smd): spd(spd), smd(smd) { }
    bool contains(int s) const {
        return spd->contains(s) || smd->contains(s);
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
    ProbabilityTest pt(10,0,100,100000);
    std::cout << pt(d) << std::endl;
    std::cout << pt(s) << std::endl;
    std::cout << pt(ss) << std::endl;

    // построение графика вероятности от максимального числа для SegmentState

    std::ofstream fout;
    fout.open("Segment(max).txt");
    for (int test_max = 110; test_max <= 1010; test_max += 20)
    {
            ProbabilityTest pt(10, 0, test_max, 1000000);
            fout << pt(s) << ";" << test_max << std::endl;
    }
    fout.close();

    // построение графика вероятности от количества испытаний для SegmentState

    fout.open("Segment(count).txt");
    for (int test_count = 0; test_count <= 1000000; test_count += 1000)
    {
            ProbabilityTest pt(10, 0, 100, test_count);
            fout << pt(s) << ";" << test_count << std::endl;
    }
    fout.close();

    // построение графика вероятности от количества испытаний для DiscreteState

    fout.open("Discrete(count).txt");
    for (int test_count = 0; test_count <= 1000000; test_count += 1000)
    {
            ProbabilityTest pt(10, 0, 100, test_count);
            fout << pt(d) << ";" << test_count << std::endl;
    }
    fout.close();

    // построение графика вероятности от максимального числа для DiscreteState

    fout.open("Discrete(max).txt");
    for (int test_max = 110; test_max <= 1010; test_max += 20)
    {
            ProbabilityTest pt(10, 0, test_max, 1000000);
            fout << pt(d) << ";" << test_max << std::endl;
    }
    fout.close();

    return 0;
}
