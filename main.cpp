#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cstdint>


//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//  .d8888b.                                                                 
// d88P  Y88b                                                                
// Y88b.                                                                     
//  "Y888b.   888  888 88888b.d88b.  88888b.d88b.   8888b.  888d888 888  888 
//     "Y88b. 888  888 888 "888 "88b 888 "888 "88b     "88b 888P"   888  888 
//       "888 888  888 888  888  888 888  888  888 .d888888 888     888  888 
// Y88b  d88P Y88b 888 888  888  888 888  888  888 888  888 888     Y88b 888 
//  "Y8888P"   "Y88888 888  888  888 888  888  888 "Y888888 888      "Y88888 
//                                                                       888 
//                                                                  Y8b d88P 
//                                                                   "Y88P"  
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// 8888888b.                            888 888             
// 888   Y88b                           888 888             
// 888    888                           888 888             
// 888   d88P .d88b.  .d8888b  888  888 888 888888 .d8888b  
// 8888888P" d8P  Y8b 88K      888  888 888 888    88K      
// 888 T88b  88888888 "Y8888b. 888  888 888 888    "Y8888b. 
// 888  T88b Y8b.          X88 Y88b 888 888 Y88b.       X88 
// 888   T88b "Y8888   88888P'  "Y88888 888  "Y888  88888P' 
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

// System #1: 3.5 GHz Quad-Core Intel Core i5 running macOS Big Sur
// Average for median-filter V1: 1899.8 ms
// Average for median-filter V2: 1085.4 ms, 1.8x vs V1
// Average for median-filter V3: 1067.1 ms, 1.8x vs V1
// Average for median-filter V4:  470.9 ms, 4.0x vs V1
// Average for median-filter V5:  235.3 ms, 8.1x vs V1

// System #2: 

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//  .d88888b.           d8b          888           888     888 888    d8b 888 
// d88P" "Y88b          Y8P          888           888     888 888    Y8P 888 
// 888     888                       888           888     888 888        888 
// 888     888 888  888 888  .d8888b 888  888      888     888 888888 888 888 
// 888     888 888  888 888 d88P"    888 .88P      888     888 888    888 888 
// 888 Y8b 888 888  888 888 888      888888K       888     888 888    888 888 
// Y88b.Y8b88P Y88b 888 888 Y88b.    888 "88b      Y88b. .d88P Y88b.  888 888 
//  "Y888888"   "Y88888 888  "Y8888P 888  888       "Y88888P"   "Y888 888 888 
//        Y8b                                                                 
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

// Utility functions for quicksort and quickselect
// adapted from code found at https://www.geeksforgeeks.org/quick-sort/
// and https://www.geeksforgeeks.org/median-of-an-unsorted-array-in-liner-time-on/

// A utility function to swap two elements 
void swap(uint8_t *a, uint8_t *b) 
{ 
    int t = *a; 
    *a = *b; 
    *b = t; 
}

int min(const int a, const int b)
{
    return (b < a) ? b : a;
}

int max(const int a, const int b)
{
    return (b > a) ? b : a;
}


// This function takes last element as pivot, places the pivot element at its correct position in sorted 
// array, and places all smaller (smaller than pivot) to left of pivot and all greater elements to right 
// of pivot
int partition(uint8_t *arr, int low, int high) 
{ 
    int pivot = arr[high]; // pivot 
    int i = (low - 1); // Index of smaller element and indicates the right position of pivot found so far
  
    for (int j = low; j < high; j++) 
    { 
        // If current element is smaller than the pivot 
        if (arr[j] < pivot) 
        { 
            i++; // increment index of smaller element 
            swap(&arr[i], &arr[j]); 
        } 
    } 
    swap(&arr[i + 1], &arr[high]); 
    return (i + 1); 
}

// Picks a random pivot element between l and r and partitions arr[l..r]
// around the randomly picked element using partition()
int randomPartition(uint8_t *arr, int low, int high)
{
    int n = high - low + 1;
    int pivot = rand() % n;
    swap(&arr[low + pivot], &arr[high]);
    return partition(arr, low, high);
}

// Utility function to find median
void MedianUtil(uint8_t *arr, int low, int high, int k, int& a, int& b)
{
     // if low < high
    if (low <= high)
    {
         // Find the partition index
        int partitionIndex = randomPartition(arr, low, high);
 
        // If partition index = k, then we found the median of odd number element in arr[]
        if (partitionIndex == k)
        {
            b = arr[partitionIndex];
            if (a != -1)
                return;
        }
        // If index = k - 1, then we get a & b as middle element of arr[]
        else if (partitionIndex == k - 1)
        {
            a = arr[partitionIndex];
            if (b != -1)
                return;
        }
        // If partitionIndex >= k then find the index in first half of the arr[]
        if (partitionIndex >= k)
            return MedianUtil(arr, low, partitionIndex-1, k, a, b);
        // If partitionIndex <= k then find the index in second half of the arr[]
        else
            return MedianUtil(arr, partitionIndex + 1, high, k, a, b);
    }
     return;
}

// The main function that implements QuickSort 
// arr[] --> Array to be sorted, 
// low --> Starting index, 
// high --> Ending index 
void quickSort(uint8_t *arr, int low, int high) 
{ 
    if (low < high) 
    { 
        /* pi is partitioning index, arr[p] is now 
        at right place */
        int pi = partition(arr, low, high); 
  
        // Separately sort elements before 
        // partition and after partition 
        quickSort(arr, low, pi - 1); 
        quickSort(arr, pi + 1, high); 
    } 
} 


//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------
// 888888b.             .d888  .d888                      888     888 888    d8b 888 
// 888  "88b           d88P"  d88P"                       888     888 888    Y8P 888 
// 888  .88P           888    888                         888     888 888        888 
// 8888888K.  888  888 888888 888888 .d88b.  888d888      888     888 888888 888 888 
// 888  "Y88b 888  888 888    888   d8P  Y8b 888P"        888     888 888    888 888 
// 888    888 888  888 888    888   88888888 888          888     888 888    888 888 
// 888   d88P Y88b 888 888    888   Y8b.     888          Y88b. .d88P Y88b.  888 888 
// 8888888P"   "Y88888 888    888    "Y8888  888           "Y88888P"   "Y888 888 888 
//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------                                                                

void printBuffer(const uint8_t *buffer, int width, int height=1)
{
    for(int y = 0; y < height; ++y)
    {
        for(int x = 0; x < width;  ++x)
        {
            printf("%4i, ", buffer[x + y*width]);
        }
        printf("\n");
    }
    printf("\n");
}

void printKernel(const uint8_t *buffer, int len)
{
    for(int x = 0; x < len;  ++x)
        printf("%4i, ", buffer[x]);
    printf("\n\n");
}

bool compareBuffers(const uint8_t *buf1, const uint8_t *buf2, int width, int height)
{
    for(int y = 0; y < height; ++y)
    for(int x = 0; x < width;  ++x)
    {
        if(buf1[x + y*width] != buf2[x + y*width])
            return false;
    }
    return true;
}

//----------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------
// 888b     d888               888 d8b                        8888888888 d8b 888 888                             
// 8888b   d8888               888 Y8P                        888        Y8P 888 888                             
// 88888b.d88888               888                            888            888 888                             
// 888Y88888P888  .d88b.   .d88888 888  8888b.  88888b.       8888888    888 888 888888 .d88b.  888d888 .d8888b  
// 888 Y888P 888 d8P  Y8b d88" 888 888     "88b 888 "88b      888        888 888 888   d8P  Y8b 888P"   88K      
// 888  Y8P  888 88888888 888  888 888 .d888888 888  888      888        888 888 888   88888888 888     "Y8888b. 
// 888   "   888 Y8b.     Y88b 888 888 888  888 888  888      888        888 888 Y88b. Y8b.     888          X88 
// 888       888  "Y8888   "Y88888 888 "Y888888 888  888      888        888 888  "Y888 "Y8888  888      88888P' 
//----------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------



#define TRUE  1
#define FALSE 0

#define DEBUG FALSE

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// 888     888  .d8888b.  
// 888     888 d88P  Y88b 
// 888     888 888    888 
// Y88b   d88P 888    888 
//  Y88b d88P  888    888 
//   Y88o88P   888    888 
//    Y888P    Y88b  d88P 
//     Y8P      "Y8888P"  
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// V0 - the version from the coding interview
// Obviously time was constrained for the implementation of this, and after
// the fact I began to realize some of the problems with it. Some minor, others
// more significant.
// Minor issues - lack of const safety
// Memory issue - didn't clean up dynamically allocated array at the end of the
//   function
// Structural issue - I was too focused on created an array of index offsets,
//   I think because I have found this helpful in the past. This needlessly
//   deferred fetching the actual kernel values to compute the median from and
//   complicated later functions. Ultimately it would've been better to 
//   immediately populate the kernel, then sort the values, and then
//   compute the median.
// Anyway, most of these issues became obvious on reimplementation, and now
// constitute V1 of the median filter implementation.

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// 888     888  d888   
// 888     888 d8888   
// 888     888   888   
// Y88b   d88P   888   
//  Y88b d88P    888   
//   Y88o88P     888   
//    Y888P      888   
//     Y8P     8888888 
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// V1, intended as the version from the coding interview, but I couldn't help but make improvements

uint8_t computeMedian(const uint8_t *kernel_values, int cnt)
{
    int halfCnt = cnt >> 1;
    uint8_t medianVal;
    if(cnt % 2 == 0) // if cnt is even
    {
        uint8_t val1 = kernel_values[halfCnt-1];
        uint8_t val2 = kernel_values[halfCnt];
        medianVal = (val1 + val2) >> 1;
    }
    else             // if cnt is odd
    {
        medianVal = kernel_values[halfCnt];
    }
    return medianVal;
}


void medianFilterV1(const uint8_t *inputBuffer, uint8_t *outputBuffer, int width, int height, int k)
{
    // Kernel values
    uint8_t *kernel_values = new uint8_t[width*height];

    int halfK = k >> 1;     // this works fine as a replacement for the divide by 2 and floor

    for(int x = 0; x < width;  x++)
    for(int y = 0; y < height; y++)
    {
        int cnt = 0;
        for(int kx = -halfK; kx <= halfK; kx++)
        for(int ky = -halfK; ky <= halfK; ky++)
        {
            int ox = x + kx;
            int oy = y + ky;

            if( !(ox < 0 || ox >= width || oy < 0 || oy >= height) )
            {
                int offset_idx = ox + oy * width;
                // offset_indices[cnt] = offset_idx;
                kernel_values[cnt] = inputBuffer[offset_idx];
                cnt++;
            }
        }

        // It became quickly clear that pulling the sort out of computeMedian made more sense
        quickSort(kernel_values, 0, cnt-1);

        uint8_t median = computeMedian(kernel_values, cnt);

        int idx = x + y * width;
        outputBuffer[idx] = median;
    }

    // I had forgotten to clean up the offsets array :(
    delete [] kernel_values;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// 888     888  d888        d888   
// 888     888 d8888       d8888   
// 888     888   888         888   
// Y88b   d88P   888         888   
//  Y88b d88P    888         888   
//   Y88o88P     888         888   
//    Y888P      888   d8b   888   
//     Y8P     8888888 Y8P 8888888 
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------


void medianFilterV1_1(const uint8_t *inputBuffer, uint8_t *outputBuffer, int width, int height, int k)
{
    // Kernel values
    uint8_t *kernel_values = new uint8_t[width*height];

    int halfK = k >> 1;     // this works fine as a replacement for the divide by 2 and floor

    for(int x = 0; x < width;  x++)
    for(int y = 0; y < height; y++)
    {
        int cnt = 0;
        for(int ox = max(x - halfK, 0); ox <= min(x + halfK, width  - 1); ox++)
        for(int oy = max(y - halfK, 0); oy <= min(y + halfK, height - 1); oy++)
        {
            int offset_idx = ox + oy * width;
            kernel_values[cnt] = inputBuffer[offset_idx];
            cnt++;
        }
        
        // It became quickly clear that pulling the sort out of computeMedian made more sense
        quickSort(kernel_values, 0, cnt-1);

        // Pass the sorted kernel values to the median function
        uint8_t median = computeMedian(kernel_values, cnt);

        int idx = x + y * width;
        outputBuffer[idx] = median;
    }

    // I had forgotten to clean up the offsets array :(
    // delete [] offset_indices;
    delete [] kernel_values;
}


//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// 888     888  .d8888b.   
// 888     888 d88P  Y88b 
// 888     888        888 
// Y88b   d88P      .d88P 
//  Y88b d88P   .od888P"  
//   Y88o88P   d88P"      
//    Y888P    888"       
//     Y8P     888888888  
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// V2 - Algorithmic Optimization
// replaces the quicksort with a quickselect algorithm for finding the 
// median which runs in O(n) vs O(nlogn) for quicksort

uint8_t selectMedian(uint8_t *kernel_values, int cnt)
{
    uint8_t medianVal;
    
    int a = -1, b = -1;
    if(cnt % 2 == 0)    // even
    {
        MedianUtil(kernel_values, 0, cnt - 1, cnt >> 1, a, b);
        medianVal = (a + b) >> 1;
    }
    else                // odd
    {
        MedianUtil(kernel_values, 0, cnt - 1, cnt >> 1, a, b);
        medianVal = b;
    }
    return medianVal;
}

void medianFilterV2(const uint8_t *inputBuffer, uint8_t *outputBuffer, int width, int height, int k)
{
    // Kernel values
    uint8_t *kernel_values = new uint8_t[width*height];

    int halfK = k >> 1;     // this works fine as a replacement for the divide by 2 and floor

    for(int x = 0; x < width;  x++)
    for(int y = 0; y < height; y++)
    {
        int cnt = 0;
        for(int ox = max(x - halfK, 0); ox <= min(x + halfK, width  - 1); ox++)
        for(int oy = max(y - halfK, 0); oy <= min(y + halfK, height - 1); oy++)
        {
            int offset_idx = ox + oy * width;
            kernel_values[cnt] = inputBuffer[offset_idx];
            cnt++;
        }

        uint8_t median = selectMedian(kernel_values, cnt);

        int idx = x + y * width;
        outputBuffer[idx] = median;
    }

    // I had forgotten to clean up the offsets array :(
    delete [] kernel_values;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// 888     888  .d8888b.  
// 888     888 d88P  Y88b 
// 888     888      .d88P 
// Y88b   d88P     8888"  
//  Y88b d88P       "Y8b. 
//   Y88o88P   888    888 
//    Y888P    Y88b  d88P 
//     Y8P      "Y8888P"  
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// V3 - cache efficiency
// swap loop order to ensure we iterate through sequential array entries
// surprisingly little perf upligt, entire possible a whole row fits in cache
// on this machine

void medianFilterV3(const uint8_t *inputBuffer, uint8_t *outputBuffer, int width, int height, int k)
{
    // Kernel values
    uint8_t *kernel_values = new uint8_t[width*height];

    int halfK = k >> 1;     // this works fine as a replacement for the divide by 2 and floor

    for(int y = 0; y < height; ++y)
    for(int x = 0; x < width;  ++x)
    {
        int cnt = 0;
        for(int ox = max(x - halfK, 0); ox <= min(x + halfK, width  - 1); ox++)
        for(int oy = max(y - halfK, 0); oy <= min(y + halfK, height - 1); oy++)
        {
            int offset_idx = ox + oy * width;
            kernel_values[cnt] = inputBuffer[offset_idx];
            ++cnt;
        }

        uint8_t median;

        int a, b;
        if(cnt % 2 == 0)    // even
        {
            MedianUtil(kernel_values, 0, cnt - 1, cnt / 2, a, b);
            median = (a + b) / 2;
        }
        else                // odd
        {
            MedianUtil(kernel_values, 0, cnt - 1, cnt / 2, a, b);
            median = b;
        }

        int idx = x + y * width;
        outputBuffer[idx] = median;
    }

    // I had forgotten to clean up the offsets array :(
    delete [] kernel_values;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// 888     888     d8888  
// 888     888    d8P888  
// 888     888   d8P 888  
// Y88b   d88P  d8P  888  
//  Y88b d88P  d88   888  
//   Y88o88P   8888888888 
//    Y888P          888  
//     Y8P           888  
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// V4 - Bucketization of values
//

static unsigned int buckets[256];

// count the median value from the buckets
uint8_t countMedian(unsigned int *buckets, int cnt)
{
    uint8_t median;
    int halfCnt = cnt >> 1;

    if(cnt % 2 == 0)   // even
    {
        int i, sum, prevBucket = 0, currBucket = 0;
        for(i = 0, sum = 0; i < 256 && sum <= halfCnt; i++)
        {
            if(buckets[i] > 0)
            {
                prevBucket = currBucket;
                currBucket = i;
                sum += buckets[i];
            }
        }
        median = (prevBucket + currBucket) >> 1;
    }
    else    // odd
    {
        int i, sum;
        for(i = 0, sum = 0; i < 256 && sum <= halfCnt; i++)
        {
            sum += buckets[i];
            median = i;
        }
    }
    return median;
}

void medianFilterV4(const uint8_t *inputBuffer, uint8_t *outputBuffer, int width, int height, int k)
{
    int halfK = k >> 1;

    for(int y = 0; y < height; ++y)
    for(int x = 0; x < width;  ++x)
    {
        int cnt = 0;
        memset(&buckets, 0, 256);
        for(int ox = max(x - halfK, 0); ox <= min(x + halfK, width  - 1); ox++)
        for(int oy = max(y - halfK, 0); oy <= min(y + halfK, height - 1); oy++)
        {
            int offset_idx = ox + oy * width;
            buckets[inputBuffer[offset_idx]]++;
            ++cnt;
        }

        uint8_t median = countMedian(&buckets[0], cnt);

        int idx = x + y * width;
        outputBuffer[idx] = median;
    }
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// 888     888 888888888  
// 888     888 888        
// 888     888 888        
// Y88b   d88P 8888888b.  
//  Y88b d88P       "Y88b 
//   Y88o88P          888 
//    Y888P    Y88b  d88P 
//     Y8P      "Y8888P"  
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// V5 - Efficiency Optimization
// Idea same as V4, but track the last column of kernel elements and the 
// buckets they fall into, as we move across a row decrement those buckets,
// and increment only the new row.

void medianFilterV5(const uint8_t *inputBuffer, uint8_t *outputBuffer, int width, int height, int k)
{
    int halfK = k >> 1;     // this works fine as a replacement for the divide by 2 and floor

    // int *wave = new int[k];
    uint8_t *wave = new uint8_t[k];
    int waveCnt = 0;

    for(int y = 0; y < height; ++y)
    {
        int cnt = 0;
        for(int x = 0; x < width;  ++x)
        {
            // fully populate buckets on each new row
            if(x == 0)  
            {
                waveCnt = 0;
                memset(&buckets, 0, 256);
                for(int oy = max(y - halfK, 0); oy <= min(y + halfK, height - 1); oy++)
                for(int ox = max(x - halfK, 0); ox <= min(x + halfK, width  - 1); ox++)
                {
                    int offset_idx = ox + oy * width;
                    buckets[inputBuffer[offset_idx]]++;
                    ++cnt;
                }
            }
            else
            {
                if(x >= halfK-1)
                {   
                    // decrement all buckets in the wave
                    for(int i = 0; i < waveCnt; i++)
                    {
                        uint8_t bucketIdx = wave[i];
                        buckets[bucketIdx]--;
                        cnt--;
                    }

                    // Store the buckets to decrement
                    waveCnt = 0;
                    for(int oy = max(y - halfK, 0); oy <= min(y + halfK, height - 1); oy++)
                    {
                        int ox = x - (halfK);
                        int offset_idx = ox + oy * width;               
                        wave[waveCnt] = inputBuffer[offset_idx];
                        waveCnt++;
                    }
                }

                // Add the new column to the buckets
                for(int oy = max(y - halfK, 0); oy <= min(y + halfK, height - 1); oy++)
                {
                    int ox = x + halfK;
                    int offset_idx = ox + oy * width;
                    buckets[inputBuffer[offset_idx]]++;
                    ++cnt;
                }            
            }

            uint8_t median = countMedian(&buckets[0], cnt);
    
            int idx = x + y * width;
            outputBuffer[idx] = median;
        }
    }

    delete [] wave;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// 888     888 888888888          
// 888     888 888                
// 888     888 888                
// Y88b   d88P 8888888b.    888   
//  Y88b d88P       "Y88b 8888888 
//   Y88o88P          888   888   
//    Y888P    Y88b  d88P         
//     Y8P      "Y8888P"          
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------                                           
// V5+ Ideas
// V6 Idea - Broadcast to Buckets
// The idea for this one is to have an array of buckets, and as we iterate over
// the pixels broadcast their value into the correct array of buckets,
// effectively having a bucket-per-pixels. Though practically we would limit
// the number of "buckets" and recycyle them as we move through the pixels.
// Probably need better naming for this idea, because calling them buckets,
// which themselves have buckets is already confusing.
//
// Other Ideas/Optimization
// Vectorization - this is always an option
//   ISPC - would be fun to try an ISPC implementation of this
// Single loops - a lot of the double-for loops could be reduced to single 
//   loops, which would save a lot of indexing math, though I am unconvinced
//   this will yield a significant performance improvement, and would 
//   negatively impact the readability of the code.
//   
                                                 

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// 88888888888 d8b               d8b                   
//     888     Y8P               Y8P                   
//     888                                             
//     888     888 88888b.d88b.  888 88888b.   .d88b.  
//     888     888 888 "888 "88b 888 888 "88b d88P"88b 
//     888     888 888  888  888 888 888  888 888  888 
//     888     888 888  888  888 888 888  888 Y88b 888 
//     888     888 888  888  888 888 888  888  "Y88888 
//                                                 888 
//                                            Y8b d88P 
//                                             "Y88P"  
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

#include <chrono>
#include <iostream>
typedef std::chrono::high_resolution_clock Clock;

float timeFunction(void (*medianFilter)(const uint8_t *, uint8_t *, int, int, int), 
                   uint8_t *inBuf, uint8_t *outBuf, int width, int height, int k,
                   int testIterations = 1)
{
    uint64_t sum = 0;
    for(int i = 0; i < testIterations; i++)
    {
        auto t1 = Clock::now();
        medianFilter(inBuf, outBuf, width, height, k);
        auto t2 = Clock::now();
        uint64_t delta = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
        // std::cout << i << " " << delta << std::endl;
        sum += delta;
    }
    return (float)sum / (float)testIterations;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//                        d8b          
//                        Y8P          
                                    
// 88888b.d88b.   8888b.  888 88888b.  
// 888 "888 "88b     "88b 888 888 "88b 
// 888  888  888 .d888888 888 888  888 
// 888  888  888 888  888 888 888  888 
// 888  888  888 "Y888888 888 888  888 
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------


int main(void)
{
    printf("Testing and timing median filter implementations\n");

#if 1
    int width  = 1024;
    int height = 1024;
    int k = 7;
#else
    int width  = 4;
    int height = 4;
    int k = 3;
    static uint8_t minBuffer[16] = { 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    static uint8_t outBuf1[16];
    static uint8_t outBuf2[16];

    medianFilterV5(&minBuffer[0], &outBuf1[0], width, height, k);
    medianFilterV4(&minBuffer[0], &outBuf2[0], width, height, k);

    printBuffer(outBuf1, width, height);


    if(compareBuffers(outBuf1, outBuf2, width, height))
        printf("They're the same!!!\n");
    else
        printf("BUFFERS DO NOT MATCH\n");


#endif

    uint8_t *inputBuffer = new uint8_t[width*height];
    uint8_t *outputBuf1  = new uint8_t[width*height];
    uint8_t *outputBuf2  = new uint8_t[width*height];

    for(int y = 0; y < height; y++)
    for(int x = 0; x < width;  x++)
    {        
        int val = width*height - (x + y*width);
        inputBuffer[x + y*width] = val;
    }

    // printBuffer(inputBuffer, width, height);



    // medianFilterV1(inputBuffer, outputBuf1, width, height, k);

    // // printBuffer(outputBuf1, width, height);

    // medianFilterV2(inputBuffer, outputBuf2, width, height, k);

    // // printBuffer(outputBuf2, width, height);

    // if(compareBuffers(outputBuf1, outputBuf2, width, height))
    //     printf("They're the same!!!\n");
    // else
    //     printf("BUFFERS DO NOT MATCH\n");


    void (*medianFilterV[6])(const uint8_t *inputBuffer, uint8_t *outputBuffer, int width, int height, int k);
    medianFilterV[1] = medianFilterV1;
    medianFilterV[2] = medianFilterV2;
    medianFilterV[3] = medianFilterV3;
    medianFilterV[4] = medianFilterV4;
    medianFilterV[5] = medianFilterV5;

    int testIterations = 10;
    float avgV1 = timeFunction(medianFilterV[1], inputBuffer, outputBuf1, width, height, k, testIterations);
    printf("Average for median-filter V%i: %6.1f ms\n", 1, avgV1);
    for(int V = 2; V < 6; V++)
    {
        float avg = timeFunction(medianFilterV[V], inputBuffer, outputBuf1, width, height, k, testIterations);
        printf("Average for median-filter V%i: %6.1f ms, %2.1fx vs V1\n", V, avg, avgV1/avg);
    }

    return 0;
}