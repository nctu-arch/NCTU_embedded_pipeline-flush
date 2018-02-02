#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <arm_neon.h>

//#define NUMBER_OF_INPUTS 4
//#define SIZE 16
#define SIZE 1000000

long neon_iteration;

float32_t mul(float *source,float *weight);

static long diff_in_us(struct timespec t1, struct timespec t2){
    struct timespec diff;
    if (t2.tv_nsec-t1.tv_nsec < 0) {
        diff.tv_sec  = t2.tv_sec - t1.tv_sec - 1;
        diff.tv_nsec = t2.tv_nsec - t1.tv_nsec + 1000000000;
    } else {
        diff.tv_sec  = t2.tv_sec - t1.tv_sec;
        diff.tv_nsec = t2.tv_nsec - t1.tv_nsec;
    }   
    return (diff.tv_sec * 1000000.0 + diff.tv_nsec / 1000.0);
}


int main(int argc, char *argv[]){

    struct timespec start,end;
    float source[SIZE] ;
    float weight[SIZE] ;
    FILE *fptr;
    srand(time(NULL));
    for(int i = 0;i<SIZE;i++){
    //    source[i] = ((float32_t)rand() /(float32_t)(RAND_MAX) ) * 100.0;
    //    weight[i] = ((float32_t)rand() /(float32_t)(RAND_MAX) ) * 100.0;
        source[i] = (float32_t)(rand()%100)+1;
        weight[i] = (float32_t)(rand()%100)+1;
    }
    clock_gettime(CLOCK_REALTIME,&start);
    printf("output:  %f\n",mul(source,weight));
    clock_gettime(CLOCK_REALTIME,&end);
    printf("spend:  %ld us\n",diff_in_us(start,end));
    return 0;
}

float32_t mul(float *source,float *weights){
    float32x4_t in1_128,in2_128,sum1,sum2,prod;
    float32_t result[4];
    float32_t output = 0.0;
    int i;
    for (i=0; i<SIZE; i+=4)
    {
        in1_128 = vld1q_f32(&source[i]);
        in2_128 = vld1q_f32(&weights[i]);
        prod = vmulq_f32(in1_128, in2_128);
#ifdef FLUSH
        sum1 = vaddq_f32(prod, vrev64q_f32(prod));
        sum2 = vaddq_f32(sum1, vcombine_f32(vget_high_f32(sum1), vget_low_f32(sum1)));
        vst1q_f32((float32_t *)result , sum2);
        output += result[0];
#endif
    }
    //printf("loop times: %d\n",i);
#ifdef NON_FLUSH
    sum1 = vaddq_f32(prod, vrev64q_f32(prod));
    sum2 = vaddq_f32(sum1, vcombine_f32(vget_high_f32(sum1), vget_low_f32(sum1)));
    vst1q_f32((float32_t *)result , sum2);
    output = result[0];
#endif

    return output;
}


