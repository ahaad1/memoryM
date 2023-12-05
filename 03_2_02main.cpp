#include <stdlib.h>
#include <stdio.h>
#include "03_2_02task.cpp"
// #include "os_mem.h"

#include <iostream>
using namespace std;

int main(){
    memory_manager_t mm;
    setup_memory_manager(&mm);
    
    /* Common memory manager test 1 */
    cout << (mm.create(1000, 2) == 1); /* expected: 1 */
    cout << (mm.destroy() == 1); /* expected: 1 */
    cout << (mm.destroy()== 0); /* expected: 0 */
    cout << (mm.create(1000, 1) == 1); /* expected: 1 */
    cout << (mm.create(1000, 3 )== 0); /* expected: 0 */
    cout << (mm.destroy() == 1) << endl; /* expected: 1 */

    cout << (mm.create(160,1) == 1); /* expected: 1 */
    cout << (mm.create(160,1) == 0); /* expected: 0 */
    cout << (mm.alloc(32) == mem_handle_t(0,32)); /* expected: mem_handle_t(0,32) */
    cout << (mm.alloc(32) == mem_handle_t(32,32)); /* expected: mem_handle_t(32,32) */
    cout << (mm.alloc(32) == mem_handle_t(64,32)); /* expected: mem_handle_t(64,32) */
    cout << (mm.alloc(32) == mem_handle_t(96,32)); /* expected: mem_handle_t(96,32) */
    cout << (mm.alloc(32) == mem_handle_t(128,32)); /* expected: mem_handle_t(128,32) */
    cout << (mm.free(mem_handle_t(128,32)) == 1); /* expected: 1 */
    cout << (mm.free(mem_handle_t(96,32)) == 1); /* expected: 1 */
    cout << (mm.free(mem_handle_t(64,32)) == 1); /* expected: 1 */
    cout << (mm.alloc(32) == mem_handle_t(64,32)); /* expected: mem_handle_t(64,32) */
    cout << (mm.alloc(32) == mem_handle_t(96,32)); /* expected: mem_handle_t(96,32) */
    cout << (mm.get_max_block_size() == 32); /* expected: 32 */
    cout << (mm.get_free_space() == 32); /* expected: 32 */
    cout << (mm.destroy() == 1) << endl; /* expected: 1 */

    cout << (mm.create(1000,1) == 1); /* expected: 1 */
    cout << (mm.create(1000,1) == 0); /* expected: 0 */
    cout << (mm.alloc(1) == mem_handle_t(0,1)); /* expected: mem_handle_t(0,1) */
    cout << (mm.alloc(2) == mem_handle_t(1,2)); /* expected: mem_handle_t(1,2) */
    cout << (mm.alloc(3) == mem_handle_t(3,3)); /* expected: mem_handle_t(3,3) */
    cout << (mm.alloc(4) == mem_handle_t(6,4)); /* expected: mem_handle_t(6,4) */
    cout << (mm.alloc(100) == mem_handle_t(10,100)); /* expected: mem_handle_t(10,100) */
    cout << (mm.free(mem_handle_t(0,1)) == 1); /* expected: 1 */
    cout << (mm.free(mem_handle_t(0,1)) == 1); /* expected: 1 */
    cout << (mm.free(mem_handle_t(0,1)) == 1); /* expected: 1 */
    cout << (mm.alloc(100) == mem_handle_t(3,100)); /* expected: mem_handle_t(3,100) */
    cout << (mm.alloc(100) == mem_handle_t(103,100)); /* expected: mem_handle_t(103,100) */
    cout << (mm.get_max_block_size() == 797); /* expected: 797 */
    cout << (mm.get_free_space() == 797); /* expected: 797 */
    cout << (mm.free(mem_handle_t(0,1)) == 1); /* expected: 1 */
    cout << (mm.free(mem_handle_t(0,1)) == 1); /* expected: 1 */
    cout << (mm.free(mem_handle_t(0,1)) == 1); /* expected: 1 */
    cout << (mm.free(mem_handle_t(0,1)) == 1); /* expected: 1 */
    cout << (mm.free(mem_handle_t(0,1)) == 0); /* expected: 0 */
    cout << (mm.free(mem_handle_t(0,1)) == 0); /* expected: 0 */
    cout << (mm.alloc(20) == mem_handle_t(0,20)); /* expected: mem_handle_t(0,20) */
    cout << (mm.alloc(1) == mem_handle_t(20,1)); /* expected: mem_handle_t(20,1) */
    cout << (mm.get_max_block_size() == 979); /* expected: 979 */
    cout << (mm.get_free_space() == 979); /* expected: 979 */
    cout << (mm.free(mem_handle_t(0,1)) == 1); /* expected: 1 */
    cout << (mm.free(mem_handle_t(0,1)) == 1); /* expected: 1 */
    cout << (mm.free(mem_handle_t(0,1)) == 0); /* expected: 0 */
    cout << (mm.get_max_block_size() == 1000); /* expected: 1000 */
    cout << (mm.get_free_space() == 1000); /* expected: 1000 */
    cout << (mm.destroy() == 1) << endl; /* expected: 1 */

    cout << (mm.create(150,1) == 1); /* expected: 1 */
    cout << (mm.alloc(1) == mem_handle_t(0,1)); /* expected: mem_handle_t(0,1) */
    cout << (mm.alloc(2) == mem_handle_t(1,2)); /* expected: mem_handle_t(1,2) */
    cout << (mm.alloc(3) == mem_handle_t(3,3)); /* expected: mem_handle_t(3,3) */
    mm.print_blocks(); 
    cout << (mm.alloc(100) == mem_handle_t(6,100)); /* expected: mem_handle_t(6,100) */
    cout << (mm.alloc(100) == mem_handle_t(0,0)); /* expected: mem_handle_t(0,0) */
    cout << (mm.free(mem_handle_t(0,1)) == 1); /* expected: 1 */
    cout << (mm.free(mem_handle_t(0,1)) == 1); /* expected: 1 */
    cout << (mm.free(mem_handle_t(0,1)) == 1); /* expected: 1 */
    cout << (mm.alloc(100) == mem_handle_t(1,100)); /* expected: mem_handle_t(1,100) */
    cout << (mm.alloc(10) == mem_handle_t(101,10)); /* expected: mem_handle_t(101,10) */
    cout << (mm.alloc(20) == mem_handle_t(111,20)); /* expected: mem_handle_t(111,20) */
    cout << (mm.alloc(20) == mem_handle_t(0,0)); /* expected: mem_handle_t(0,0) */
    cout << (mm.get_max_block_size() == 19); /* expected: 19 */
    cout << (mm.get_free_space() == 19); /* expected: 19 */
    cout << (mm.free(mem_handle_t(0,1)) == 1); /* expected: 1 */
    cout << (mm.free(mem_handle_t(0,1)) == 1); /* expected: 1 */
    cout << (mm.free(mem_handle_t(0,1)) == 1); /* expected: 1 */
    cout << (mm.free(mem_handle_t(0,1)) == 1); /* expected: 1 */
    cout << (mm.free(mem_handle_t(0,1)) == 0); /* expected: 0 */
    cout << (mm.free(mem_handle_t(0,1)) == 0); /* expected: 0 */
    cout << (mm.alloc(1) == mem_handle_t(0,1)); /* expected: mem_handle_t(0,1) */
    cout << (mm.alloc(1) == mem_handle_t(1,1)); /* expected: mem_handle_t(1,1) */
    cout << (mm.get_max_block_size() == 148); /* expected: 148 */
    cout << (mm.get_free_space() == 148); /* expected: 148 */
    mm.print_blocks();
    cout << (mm.free(mem_handle_t(0,1)) == 1); /* expected: 1 */
    cout << (mm.free(mem_handle_t(0,1)) == 1); /* expected: 1 */
    cout << (mm.free(mem_handle_t(0,1)) == 0); /* expected: 0 */
    cout << (mm.get_max_block_size() == 150); /* expected: 150 */
    cout << (mm.get_free_space() == 150); /* expected: 150 */
    mm.print_blocks();
    cout << (mm.destroy() == 1) << endl; /* expected: 1 */

    mm.create(1000, 1);
    mm.alloc(10);
    mm.alloc(10);
    mm.alloc(10);
    mm.alloc(10);
    mm.destroy();
    return 0;
}