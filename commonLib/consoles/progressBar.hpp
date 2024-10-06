#pragma once

class ProgressBar {
public: 
    ProgressBar(int range);
    void progress(int index);
private:
    int _range;
    double _progressUnitSize;
    double _thre;
};