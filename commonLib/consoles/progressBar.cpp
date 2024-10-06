#include "progressBar.hpp"

#include<iostream>
using std::cout;
using std::endl;
using std::flush;

ProgressBar::ProgressBar(int range) {
    int barLength = 20;
    this->_range = range;
    this->_thre = 0;
    
        this->_progressUnitSize = (double)range / barLength;

    cout << R"(0%      50%       100%)" << endl;
    cout << R"(+--------+---------+)" << endl;
}

void ProgressBar::progress(int index) {
    if(_thre <= index) {
        cout << "#" << flush;
        _thre += _progressUnitSize;
    }
    if(index + 1 == _range) {
        cout << endl;
    }
}