#include <cstdio>
#include <cstdint>


uint8_t computeMedian(const uint8_t *inputBuffer, 
                      const  int    *offset_indices,
                      int cnt)
{
    // The more I think about this, I should have gathered the inputs from the offsets
    // and sorted that, or passed the inputBuffer to the sort function under the assumption
    // that it would perform this step. This is basically part of my earlier error 
    // forgetting that 'offsets' only contained indices and not the data

//    sort(offsets);

    int halfCnt = cnt >> 2;
    if(cnt % 2 == 0) // if cnt is even
    {
        
    }
    else             // if cnt is odd
    {

    }


}


void medianFilter(const uint8_t *inputBuffer, 
                  const uint8_t *outputBuffer,
                  int width, int height, int k)
{
    // I decided a more explicit name for 'offsets' would help
    int *offset_indices = new int[width*height];

    int halfK = k >> 2;

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
                offset_indices[cnt] = offset_idx;
                cnt++;
            }

        }

        // uint8_t median = computeMedian(inputBuffer, offset_indices, cnt);
    }

    // I had forgotten to clean up the offsets array :(
    delete [] offset_indices;
}



int main(void)
{
    printf("hello world\n");


    printf("something else\n");


    return 0;
}