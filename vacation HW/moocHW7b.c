#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
// #define ONLINE_JUDGE

/*
 struct for product items
 */
typedef struct _Product {
    char name[51];
    float price;
    float review;
    int  num_reviews;
} Product;

int compare(const void *a, const void *b)
{
    Product *ia, *ib;
    ia = *(Product **)a;
    ib = *(Product **)b;
    /* your code here */
    if(ia->review>ib->review) return -1;
    else if(ia->review<ib->review) return 1;
    else{
        if(ia->price>ib->price) return 1;
        else return -1;
    }
}

int compare_name(const void *a, const void *b)
{
    /* your code here */
    Product *ia, *ib;
    ia = *(Product **)a;
    ib = *(Product **)b;
    
    char a_brand_name[51];
    char b_brand_name[51];
    
    int i=0;
    while(ia->name[i]!=' ')
    {
        a_brand_name[i] = ia->name[i];
        i++;
    }
    a_brand_name[i]='\0';
    
    i=0;
    while(ib->name[i]!=' ')
    {
        b_brand_name[i] = ib->name[i];
        i++;
    }
    b_brand_name[i]='\0';
    
    if(!strcmp(a_brand_name, b_brand_name))
        return compare(a, b);
    else return strcmp(a_brand_name, b_brand_name);
}

void show_product(Product *item)
{
    printf("%s, ", item->name);
    printf("$%.2f, ", item->price);
    printf("%.1f\n", item->review);
}

int main(void)
{
    Product **items;
    int i, j;
    int ndata, nqueries;
    Product **filtered;
    float lower, upper;
    int num;
 /*
#ifndef ONLINE_JUDGE
    freopen("testcase2", "r", stdin);
    //freopen("out1", "w", stdout);
#endif
  */
    
    scanf("%d", &ndata);
    while (getchar() !='\n');
    
    items = (Product**) malloc(sizeof(Product*) * ndata);
    
    for (i=0; i<ndata; i++) {
        items[i] = (Product*) malloc(sizeof(Product));
        fgets(items[i]->name, 31, stdin);
        items[i]->name[strlen(items[i]->name)-1] = '\0';
        scanf("%f", &items[i]->price);
        scanf("%f", &items[i]->review);
        scanf("%d", &items[i]->num_reviews);
        while (getchar() !='\n');
    }
    
    scanf("%d", &nqueries);
    while (getchar() !='\n');
    
    qsort(items, ndata, sizeof(Product *), compare_name);
    
    filtered = (Product**) malloc(sizeof(Product*) * ndata);
    for (i=0; i<nqueries; i++) {
        scanf("%f%f", &lower, &upper);
        printf("%.2f<=price<=%.2f\n", lower, upper);
        
        /* your code here*/
        for(j=0;j<ndata;j++)
        {
            if( items[j]->price<=upper && items[j]->price>=lower)
            {
                show_product(items[j]);
            }
        }
    }
    
    for (i=0; i<ndata; i++) {
        free(items[i]);
    }
    free(items);
    free(filtered);
    return 0;
}

