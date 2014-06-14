#include <iostream>
#include <thread>
using namespace std;
#define LENGTH 100000
#define CORES 8
void merge(long *orig, int left, int mid, int right, long *modif)
{
    int l = left;
    int r = mid;
    for (int i = left; i < right; i++)
        if (l < mid && (r >= right || orig[l] <= orig[r]))
            modif[i] = orig[l++];
        else
            modif[i] = orig[r++];
	for (int i = left; i < right; i++)
		orig[i] = modif[i];
}
void split(long *orig, int left, int right, long *modif)
{
    if (right - left < 2)return;
    split(orig, left, (left + right) / 2,modif);
    split(orig, (left + right) / 2, right,modif);
    merge(orig, left, (left + right) / 2, right,modif);
}
void merge_sort(long *in, int length)
{
    long temp[LENGTH];
    thread threads[CORES];
    for (int i = 0; i < CORES; i++)
        threads[i]=thread(&split,in,i*LENGTH/CORES,(i+1)*LENGTH/CORES,temp);
    for (int i = 0; i < CORES; i++)
        threads[i].join();
    for (int i = CORES/2; i > 0; i = i >> 1)
        for (int j = 0; j < i; j++){
            int left = (j)*LENGTH / i;
            int right = (j + 1)*LENGTH / i;
            merge(in, left, (left + right) / 2, right, temp);
        }
}
int main(int argc, char *argv[])
{
    long array[LENGTH];
    for (int i = 0; i < LENGTH; i++)
		array[i] = LENGTH - i;
    merge_sort(array, LENGTH);
    //for (int i = 0; i < LENGTH; i++)
		//cout << array[i] << endl;
	return 0;
}