#include "ext2-objects.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <math.h>

#define SUPERBLOCK_ADDR 1024
#define SUPERBLOCK_SIZE 1024 //replace with sizeof(ext2_superblock_t);

void readSuperBlock(FILE *ext2fd, ext2_superblock_t* sblock) {
    memset(sblock, 0, sizeof(ext2_superblock_t));
    if( (fseek(ext2fd, SUPERBLOCK_ADDR, SEEK_SET)) < 0) {
        printf("Error fseek");   
    }
    //reading the superblock like this will work only for linux; this is
    //because the OS type defines the size of the osd1/2 flags union. 
    //FIXME: handle other os types
    //
    //TODO: gdb output weirdness, check out s_volume_name 
    //(gdb) p *sblock
    //$1 = {s_inode_count = 5136, s_block_count = 20480, s_r_block_count =
    //    1024, s_free_block_count = 19622, s_free_inode_count = 5005,
    //s_first_data_block = 1, s_log_block_size = 0, s_log_frag_size = 0, s_blocks_per_group = 8192, s_frags_per_group = 8192,
    //s_inodes_per_group = 1712, s_mtime = 0, s_wtime = 1415188180, s_mnt_count = 1, s_max_mnt_count = 65535, s_magic = 61267,
    //s_state = 0, s_errors = 1, s_minor_req_level = 0, s_lastcheck = 1415188180, s_checkinterval = 0, s_creator_os = 0,
    //s_rev_level = 1, s_def_resuid = 0, s_def_resgid = 0, s_first_inode = 11, s_inode_size = 128, s_block_group_nr = 0,
    //s_feature_compat = 56, s_feature_incompat = 2, s_feature_ro_compat = 3,
    //s_uuid = "K\301\207\275\377\bA\251\263\230\270:\207\226z", s_volume_name = "\272SCC211 OS Modul",
    //s_last_mounted = "e", '\000' <repeats 62 times>, s_algorithm_usage_bitmap = 0, s_prealloc_blocks = 0 '\000',
    //s_prealloc_dir_blocks = 0 '\000', s_padding1 = 79, s_researved = {0, 0, 0, 0, 0, 0, 0, 2920503927, 2739053623, 3734030763,
    //2135131877, 1, 12, 0, 1415188180, 0 <repeats 21 times>, 1, 0 <repeats 167 times>}}
    fread(sblock, sizeof(ext2_superblock_t), 1, ext2fd);

}

void readBlockGroupDescriptor(FILE *ext2fd, ext2_group_desc_t *bgDescription) {
    long addr = (SUPERBLOCK_ADDR + SUPERBLOCK_SIZE);
    if( (fseek(ext2fd, addr, SEEK_SET)) < 0) {
        printf("Error fseek");   
    }
    memset(bgDescription, 0, sizeof(ext2_group_desc_t));
    fread(bgDescription, sizeof(ext2_group_desc_t), 1, ext2fd);
}

int assertBlocksPerGroup(ext2_superblock_t *superblock) {
    double blocksViaBlocksPerGroup = (double)superblock->s_block_count / superblock->s_blocks_per_group;
    double blocksViaInodesPerGroup = (double)superblock->s_inode_count / superblock->s_inodes_per_group;
    int r1 = round(blocksViaBlocksPerGroup);
    int r2 = round(blocksViaInodesPerGroup);
    return (r1 == r2);
}

int validateMagicNumber(ext2_superblock_t *superblock) {
    return(superblock->s_magic == 0xef53);
}

int main() {
    FILE *ext2fd = fopen("./ext2fs", "rw");
    ext2_superblock_t *superblock = malloc(sizeof(ext2_superblock_t)); 
    readSuperBlock(ext2fd, superblock);
    printf("%lu\n", sizeof(*superblock));
    printf("volume name: %s\n", superblock->s_volume_name);
    printf("last mount path: %s\n", superblock->s_last_mounted);

    if(!assertBlocksPerGroup(superblock)) {
        printf("Blocks per group error\n");
    }
    if(!validateMagicNumber(superblock)) {
        printf("magic number error\n");
    }

    uint32_t blockSize = (1024 << superblock->s_log_block_size); 

    printf("block size: %u\n", blockSize);

    ext2_group_desc_t *groupDescriptor = malloc(sizeof(ext2_group_desc_t));
    readBlockGroupDescriptor(ext2fd, groupDescriptor);

    printf("free blocks in group %u\n", groupDescriptor->bg_free_blocks_count);



    
    free(superblock);
    fclose(ext2fd);
    return(0);
}
