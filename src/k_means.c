#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include "../include/k_means.h"

#define N 10000000
#define K 4

void init_vector(struct point point[N]) {

    int i;

    srand(10);

    for(i = 0; i < N; i++) {
        point[i].x = (float) rand() / (float) RAND_MAX;
        point[i].y = (float) rand() / (float) RAND_MAX;
        point[i].cluster = 0;
    }

}

void init_k_clusters(struct point point[N], struct cluster cluster[K]) {

    int i;

    for(i = 0; i < K; i++) {
        cluster[i].x = point[i].x;
        cluster[i].y = point[i].y;
    }
}

bool atribute_sample(float * clN, struct point point[N], struct cluster cluster[K]) {
    
    int i, j;

    float clx[K], cly[K];
    float minor_dist, dist;
    int minor_cluster;
    bool bool_dist;
    bool end = true;

    for (i = 0 ; i < K ; i++) {
        clN[i] = 0;
        clx[i] = 0;
        cly[i] = 0;
    }

    for (i = 0; i < N; i++) {

        minor_dist = sqrtf(powf(point[i].x - cluster[0].x, 2) + powf(point[i].y - cluster[0].y, 2));
        minor_cluster = 0;
        for (j = 1; j < K; j++) {
            dist = sqrtf(powf(point[i].x - cluster[j].x, 2) + powf(point[i].y - cluster[j].y, 2));
            bool_dist = dist < minor_dist;
            minor_dist = bool_dist ? dist : minor_dist;
            minor_cluster = bool_dist ? j : minor_cluster;
        }
        clN[minor_cluster]++;
        clx[minor_cluster] += point[i].x;
        cly[minor_cluster] += point[i].y;

        if (point[i].cluster != minor_cluster) {
            end = false;
            point[i].cluster = minor_cluster;
        }
    }

    for (i = 0 ; i < K ; i++) {
        cluster[i].x = clx[i] / clN[i];
        cluster[i].y = cly[i] / clN[i];
    }

    return end;
}

int main() {
    int i;

    struct point * point = malloc(sizeof(struct point) * N);
    struct cluster * cluster = malloc(sizeof(struct cluster) * K);

    float * clN = malloc(sizeof(int) * K);

    init_vector(point);

    init_k_clusters(point, cluster);

    bool end = 0;
    int hh=0;

    while (!end) {
        hh++;
        end = atribute_sample(clN, point, cluster);
    }

    for (i = 0; i < K; i++) {
        printf("Center: (%.3f, %.3f) : Size: %.0f\n", cluster[i].x, cluster[i].y, clN[i]);
    }

    return 0;

}