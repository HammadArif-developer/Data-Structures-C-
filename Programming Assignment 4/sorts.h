#ifndef __SORTS_H
#define __SORTS_H

#include <iostream>
#include <vector>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <ctime>

using namespace std;

vector<long> InsertionSort(vector<long> nums);
vector<long> MergeSort(vector<long> nums);
vector<long> QuickSortArray(vector<long> nums);
vector<long> QuickSortList(vector<long> nums);
vector<long> HeapSort(vector<long> nums);
vector<long> QueenOfAllSorts(vector<long> nums);

#endif