#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cstdint>

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
     // if low < r
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


// V0 the version from the coding interview


//----------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------
// V1, intended as the version from the coding interview, but I couldn't help but make improvements
//
//----------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------

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
        

        printKernel(kernel_values, cnt);

        // It became quickly clear that pulling the sort out of computeMedian made more sense
        quickSort(kernel_values, 0, cnt-1);


        uint8_t median = computeMedian(kernel_values, cnt);

        printf("median: %i\n", median);
        printKernel(kernel_values, cnt);


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


void medianFilterV2(const uint8_t *inputBuffer, uint8_t *outputBuffer, int width, int height, int k)
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
                kernel_values[cnt] = inputBuffer[offset_idx];
                cnt++;
            }
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

        printf("median: %i    cnt: %i\n", median, cnt);
        quickSort(kernel_values, 0, cnt-1);
        printKernel(kernel_values, cnt);

        int intMedian = (int)median;

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
// V2 replaces the quicksort with a quickselect algorithm for finding the 
// median which runs in O(n) vs O(nlogn) for quicksort

void medianFilterV3(const uint8_t *inputBuffer, uint8_t *outputBuffer, int width, int height, int k)
{
    // Kernel values
    uint8_t *kernel_values = new uint8_t[width*height];

    int halfK = k >> 1;     // this works fine as a replacement for the divide by 2 and floor

    for(int y = 0; y < height; ++y)
    for(int x = 0; x < width;  ++x)
    {
        int cnt = 0;
        for(int ky = -halfK; ky <= halfK; ++ky)
        for(int kx = -halfK; kx <= halfK; ++kx)
        {
            int ox = x + kx;
            int oy = y + ky;

            if( !(ox < 0 || ox >= width || oy < 0 || oy >= height) )
            {
                int offset_idx = ox + oy * width;
                kernel_values[cnt] = inputBuffer[offset_idx];
                ++cnt;
            }
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

void medianFilterV4(const uint8_t *inputBuffer, uint8_t *outputBuffer, int width, int height, int k)
{
    int halfK = k >> 1;     // this works fine as a replacement for the divide by 2 and floor

    for(int y = 0; y < height; ++y)
    for(int x = 0; x < width;  ++x)
    {
        int cnt = 0;
        memset(&buckets, 0, 256);
        for(int ky = -halfK; ky <= halfK; ++ky)
        for(int kx = -halfK; kx <= halfK; ++kx)
        {
            int ox = x + kx;
            int oy = y + ky;

            if( !(ox < 0 || ox >= width || oy < 0 || oy >= height) )
            {
                int offset_idx = ox + oy * width;
                buckets[inputBuffer[offset_idx]]++;
                ++cnt;
            }
        }

        int median;
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
                // if(sum >= halfCnt)
                //     break;
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


void medianFilterV5(const uint8_t *inputBuffer, uint8_t *outputBuffer, int width, int height, int k)
{
    int halfK = k >> 1;     // this works fine as a replacement for the divide by 2 and floor

    for(int y = 0; y < height; ++y)
    for(int x = 0; x < width;  ++x)
    {
        int cnt = 0;
        memset(&buckets, 0, 256);
        for(int ky = -halfK; ky <= halfK; ++ky)
        for(int kx = -halfK; kx <= halfK; ++kx)
        {
            int ox = x + kx;
            int oy = y + ky;

            if( !(ox < 0 || ox >= width || oy < 0 || oy >= height) )
            {
                int offset_idx = ox + oy * width;
                buckets[inputBuffer[offset_idx]]++;
                ++cnt;
            }
        }

        int median;
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

        int idx = x + y * width;
        outputBuffer[idx] = median;
    }
}

#include <chrono>
#include <iostream>
typedef std::chrono::high_resolution_clock Clock;

int main(void)
{
    printf("hello world\n");
    printf("something else\n");

    int width  = 8;
    int height = 8;
    int k = 7;

    uint8_t *inputBuffer = new uint8_t[width*height];
    uint8_t *outputBuf1  = new uint8_t[width*height];
    uint8_t *outputBuf2  = new uint8_t[width*height];

    for(int y = 0; y < height; y++)
    for(int x = 0; x < width;  x++)
    {        

        int val = width*height - (x + y*width);
     //   printf("%i \n", width*height - (x + y*width));

        inputBuffer[x + y*width] = val;

        // printf("%i \n", inputBuffer[x + y*width]);
    }

    printBuffer(inputBuffer, width, height);

    int testIterations = 5;

    medianFilterV1(inputBuffer, outputBuf1, width, height, k);

    printBuffer(outputBuf1, width, height);

    medianFilterV4(inputBuffer, outputBuf2, width, height, k);

    printBuffer(outputBuf2, width, height);

    if(compareBuffers(outputBuf1, outputBuf2, width, height))
        printf("They're the same!!!\n");
    else
        printf("BUFFERS DO NOT MATCH\n");


    uint64_t sum = 0;
    for(int i = 0; i < testIterations; i++)
    {
        auto t1 = Clock::now();
        medianFilterV1(inputBuffer, outputBuf1, width, height, k);
        auto t2 = Clock::now();

        uint64_t delta = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();

        std::cout << i << " " << delta << std::endl;

        sum += delta;
    }

    std::cout << "average: " << (float)sum / (float)testIterations << " milliseconds" << std::endl;

    return 0;
}