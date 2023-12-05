#include <stdlib.h>
#include <stdio.h>
#include "os_mem.h"

typedef struct super_duper_stack{
    super_duper_stack *parent;
    super_duper_stack *child;
    mem_handle_t *mmt;
} super_duper_stack;

super_duper_stack *__m = NULL;
long long int __stksz = 0;
long long int __ocpdsz = 0;

int create(int size, int num_pages);
int get_free_space();
int get_max_block_size();
mem_handle_t alloc(int block_size);
int free(mem_handle_t h);
int destroy();
void print_blocks();

int check_stack(super_duper_stack *block);
int init_stack(int size, int num_pages);
mem_handle_t alloc_block(int block_size);
int free_block(mem_handle_t h);
int rm_stack();

void print_blocks(){
    if(!check_stack(__m)) return;
    while(__m->parent != NULL) __m = __m->parent;
    // printf("\n");
    while(__m->child != NULL){
        __m = __m->child;
        printf("%d %d\n", __m->mmt->addr, __m->mmt->size);
    }
}

void setup_memory_manager(memory_manager_t *mm){
    mm->create = create;
    mm->alloc = alloc;
    mm->free = free;
    mm->destroy = destroy;
    mm->get_free_space = get_free_space;
    mm->get_max_block_size = get_free_space;
    mm->print_blocks = print_blocks;
}

int rm_stack(){
    while(__m->child != NULL) __m = __m->child;
    while(__m->parent != NULL){
        __m = __m->parent;
        free_block(mem_handle_t(__m->child->mmt->addr, __m->child->mmt->size));
    }
    free(__m->mmt);
    free(__m);
    __m = NULL;
    __ocpdsz = 0;
    __stksz = 0;
    return 1;
    // while(__m->child != NULL) __m = __m->child;
    // while(__m->parent != NULL){
    //     __m = __m->parent;
    //     free_block(mem_handle_t(1, 1));
    // }
    // free(__m->mmt);
    // // __m->mmt = NULL;
    // free(__m);
    // __m = NULL;
    // __ocpdsz = 0;
    // __stksz = 0;
    // return 1;
}

int free_block(mem_handle_t h){
    while(__m->child != NULL) __m = __m->child;
    super_duper_stack *rm_block = __m;
    if(rm_block == NULL || rm_block->mmt == NULL) return 0;
    __ocpdsz -= rm_block->mmt->size;
    if(__m->parent) __m = __m->parent;
    free(rm_block->mmt);
    free(rm_block);
    __m->child = NULL;
    return 1;
    // int is_exist = 0;
    // while(__m->parent != NULL) __m = __m->parent;
    // while(__m->child != NULL){
    //     if(__m->mmt->addr == h.addr && __m->mmt->size == h.size){
    //         is_exist = 1;
    //         break;
    //     }
    //     __m = __m->child;
    // }
    // if(!is_exist) return 0;
    // super_duper_stack *free_block = __m;
    // free_block->parent->child = free_block->child;
}

mem_handle_t alloc_block(int block_size){
    if(block_size <= 0 || block_size > __stksz || __ocpdsz + block_size > __stksz) return mem_handle_t(0,0);
    while(__m->child != NULL) __m = __m->child;
    
    super_duper_stack *new_block = (super_duper_stack*)malloc(sizeof(super_duper_stack));
    new_block->parent = __m;
    __m->child = new_block;
    new_block->child = NULL;
    
    new_block->mmt = (mem_handle_t*)malloc(sizeof(mem_handle_t));
    if(!__m->parent){
        new_block->mmt->addr = 0;
        new_block->mmt->size = block_size;
        // printf("allocated < %d | %d >\n", new_block->mmt->addr, new_block->mmt->size);
    }
    else{
        new_block->mmt->addr = __m->mmt->size + __m->mmt->addr;
        new_block->mmt->size = block_size;
        // printf("allocated < %d | %d >\n", new_block->mmt->addr, new_block->mmt->size);
    }
    __ocpdsz += new_block->mmt->size;
    return mem_handle_t(new_block->mmt->addr, new_block->mmt->size);
}

int init_stack(int size, int num_pages){
    if(size <= 0) return 0;
    __m = (super_duper_stack*)malloc(sizeof(super_duper_stack));
    if(!__m) exit(0);
    __m->child = NULL;
    __m->parent = NULL;
    __m->mmt = NULL;
    __stksz = size;
    return 1;
}


int create(int size, int num_pages) { return check_stack(__m) == 0 ? init_stack(size, num_pages) : 0; }
mem_handle_t alloc(int block_size) { return check_stack(__m) == 0 ? mem_handle_t(0,0) : alloc_block(block_size); }
int free(mem_handle_t h){ return check_stack(__m) == 0 ? 0 : free_block(h); }
int destroy(){ return check_stack(__m) == 0 ? 0 : rm_stack(); }

int get_free_space(){ return __stksz - __ocpdsz; }
int check_stack(super_duper_stack *block) { return block == NULL ? 0 : 1; }