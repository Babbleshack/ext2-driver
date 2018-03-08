#include <stdint.h>

struct ext2_superblock {
  uint32_t s_inode_count; //Total number of Inodes
  uint32_t s_block_count; //Filesystem size in blocks
  uint32_t s_r_block_count; //number of researved blocks
  uint32_t s_free_block_count; //Free block count
  uint32_t s_free_inode_count; //Free inode count
  uint32_t s_first_data_block; //Number of first 'Superblock'
  uint32_t s_log_block_size; //Block Size (log)
  int32_t s_log_frag_size; //Fragment size (log)o
  uint32_t s_blocks_per_group; //Number of blocks per group
  uint32_t s_frags_per_group; //Number of fragments per group
  uint32_t s_inodes_per_group; //Number of inodes per group
  uint32_t s_mtime; //time of last mount operation
  uint32_t s_wtime; //time of last write operation
  uint16_t s_mnt_count; //Mount operation counter
  uint16_t s_max_mnt_count; //Max number of mounts before check
  uint16_t s_magic; //Ext2 signarture
  uint16_t s_state; //Status flag ( 1 - clean, 2 - errors)
  uint16_t s_errors; /* behaviour when error occurs (1 - continute, 2 - remount
                        fs RO, 3 - Kernel Panic!) */
  uint16_t s_minor_req_level; // minor revision level
  uint32_t s_lastcheck; //time of last check 
  uint32_t s_checkinterval; // time between checks
  uint32_t s_creator_os; /* 0 - Linux , 1 - GNU HURD, 2 - MASIX, 3 - FreeBSD, 4
                            - other(DARWIN, OpenBSD, NetBSD, etc) */
  uint32_t  s_rev_level; //revision level
  uint32_t s_def_resuid; //Default UUID for reserved blocks
  uint32_t s_def_resgid; //Default GID for researved blocks

  //Extended
  uint32_t s_first_inode; // number of first unresearved inode ( '/' dir)
  uint16_t s_inode_size; //size of inode
  uint32_t s_block_group_nr; //block group number of this superblock.
  uint32_t s_feature_compat; //Compatible features bitmap
  uint32_t s_feature_incompat; //Incomaptible features bitmap
  uint32_t s_feature_ro_compat; //Read only compatible features. 

  uint8_t s_uuid[16]; //128-bit filesystem identifier

  char s_volume_name[16]; //volume name
  char s_last_mounted[64]; //pathname of last mount

  uint32_t s_algorithm_usage_bitmap; // used for compression

  uint8_t s_prealloc_blocks; //number of blocks to preallocate
  uint8_t s_prealloc_dir_blocks; //number of blocks to preallocate for directories. 
  uint16_t s_padding1; //allignment to word
  uint32_t s_researved[204] = {0};
};
