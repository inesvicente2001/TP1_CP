#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include "../include/k_means.h"

#define N 10000000
#define K 4

void init_vector(struct point point[N]) {

    size_t i;

    srand(10);

    for(i = 0; i < N; i++) {
        point[i].x = (float) rand() / (float) RAND_MAX;
        point[i].y = (float) rand() / (float) RAND_MAX;
        point[i].cluster = 0;
    }

}

void init_k_clusters(struct point point[N], struct cluster cluster[K]) {

    size_t i;

    for(i = 0; i < K; i++) {
        cluster[i].x = point[i].x;
        cluster[i].y = point[i].y;
    }
}

bool atribute_sample(struct point point[N], struct cluster cluster[K]) {
    
    size_t i;
    short int j;
    float pointix, clusterjx, pointiy, clusterjy;

    float clx[K], cly[K], clN[K];
    float minor_dist, dist;
    short int minor_cluster;
    bool end = true;

    for (i = 0 ; i < K ; i++) {
        clN[i] = 0;
        clx[i] = 0;
        cly[i] = 0;
    }

    for (i = 0; i < N; i++) {

        pointix = point[i].x;
        pointiy = point[i].y;
        clusterjx = cluster[0].x;
        clusterjy = cluster[0].y;
        minor_dist = (pointix - clusterjx) * (pointix - clusterjx) + (pointiy - clusterjy) * (pointiy - clusterjy);
        minor_cluster = 0;
        for (j = 1; j < K; j++) {
            clusterjx = cluster[j].x;
            clusterjy = cluster[j].y;
            dist = (pointix - clusterjx) * (pointix - clusterjx) + (pointiy - clusterjy) * (pointiy - clusterjy);
            if(dist < minor_dist){
                minor_dist = dist;
                minor_cluster = j;
            }
        }
        clN[minor_cluster]++;
        clx[minor_cluster] += pointix;
        cly[minor_cluster] += pointiy;

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
    size_t i;

    struct point * point = malloc(sizeof(struct point) * N);
    struct cluster * cluster = malloc(sizeof(struct cluster) * K);

    init_vector(point);

    //coloca os valores x e y dos primeiros K pontos na estrutura dos cluster
    init_k_clusters(point, cluster);

    bool end = 0; //flag que indica se já convergiu
    size_t hh = 0; //número de iterações

    while (!end) {
        hh++;
        end = atribute_sample(point, cluster);
    }

    for (i = 0; i < K; i++) {
        printf("Center: (%.3f, %.3f) : Size: e\n", cluster[i].x, cluster[i].y);
        printf("%d\n", hh);
    }

    return 0;

}