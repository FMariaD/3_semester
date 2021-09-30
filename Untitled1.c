��� ��� ���������� �������

// ���������� ������� ����������� �� ������������� ����� ��� SegmentState

    std::ofstream fout;
    fout.open("Segment(max).txt");
    for (int test_max = 110; test_max <= 1010; test_max += 20)
    {
            ProbabilityTest pt(10, 0, test_max, 1000000);
            fout << pt(s) << ";" << test_max << std::endl;
    }
    fout.close();

    // ���������� ������� ����������� �� ���������� ��������� ��� SegmentState

    fout.open("Segment(count).txt");
    for (int test_count = 0; test_count <= 1000000; test_count += 1000)
    {
            ProbabilityTest pt(10, 0, 100, test_count);
            fout << pt(s) << ";" << test_count << std::endl;
    }
    fout.close();

    // ���������� ������� ����������� �� ���������� ��������� ��� DiscreteState

    fout.open("Discrete(count).txt");
    for (int test_count = 0; test_count <= 1000000; test_count += 1000)
    {
            ProbabilityTest pt(10, 0, 100, test_count);
            fout << pt(d) << ";" << test_count << std::endl;
    }
    fout.close();

    // ���������� ������� ����������� �� ������������� ����� ��� DiscreteState

    fout.open("Discrete(max).txt");
    for (int test_max = 110; test_max <= 1010; test_max += 20)
    {
            ProbabilityTest pt(10, 0, test_max, 1000000);
            fout << pt(d) << ";" << test_max << std::endl;
    }
    fout.close();
