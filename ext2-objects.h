#include <stdint.h>

typedef struct ext2_superblock {
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
  uint32_t s_researved[204];
} ext2_superblock_t;



typedef struct ext2_group_desc {
	uint32_t bg_block_bitmap; //Block number of block bitmap
	uint32_t bg_inode_bitmap; //Block number of inode bitmap
	uint32_t bg_inode_table; //Block number of first inode table block
	uint16_t bg_free_blocks_count; //Number of free blocks in group
	uint16_t bg_free_inodes_count; //Number of free inodes in group
	uint16_t bg_used_dirs_count; //Number of directories in group
	uint16_t bg_pad; // allight to word
	uint32_t bg_reserved[3]; //Nulls to pad out to 24bytes
} ext2_group_desc_t;

typedef struct ext2_inode {
	uint16_t i_mode; //File type and access rights
	uint16_t i_uid; //owner identifier
	uint32_t i_size; //file length in bytes
	uint32_t i_atime; //Time of last access
	uint32_t i_ctime; //time that inode last changed
	uint32_t i_mtime; //Time that file content last changed
	uint32_t i_dtime; //Time of file deletion
	uint16_t i_gid; //Group identifier
	uint16_t i_links_count; //Hard links counter
	uint32_t i_blocks;//Number of data blocks of that file
	uint32_t i_flags; //File flags
	//union osd1; //OS Specific Flags
	uint32_t osd1; //OS Specific Flags TODO: replace with union
	uint32_t i_direct_blocks[12]; //First 12 block numbers
	uint32_t i_single_block; //block number of single indirect block
	uint32_t i_double_block; //block number of double indirect block
	uint32_t i_triple_block; //block number of triple indirect block
	uint32_t i_generation; //Generation number
	uint32_t i_file_acl; // File ACL (>= v1)
	uint32_t i_dir_acl; // Dir ACL (>= 1)
	uint32_t i_faddr;
	//TODO:: replace with union to handle HURD/MASIX
	struct linux_osd2 {
		unsigned char osd1_frag; //Fragment number
		unsigned char osd1_frag_size; //Fragment size
		char researved_1[2]; //Fragment size
		unsigned short osd1_upper_user_id; //High 16 bits of 32-bit user id
		unsigned short osd1_upper_group_id; //High 16 bits of 32-bt group id
		char researved_2[4]; //Fragment size
	} ext2_inode_t;
};




