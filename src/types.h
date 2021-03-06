/** 
 * \file types.h
 * \brief nfdump file structure types
 *
 * \author J.R.Versteegh <j.r.versteegh@orca-st.com>
 *
 * \copyright (C) 2017 SURFnet. All rights reserved.
 * \license This software may be modified and distributed under the 
 * terms of the BSD license. See the LICENSE file for details.
 */

#ifndef _TYPES_H
#define _TYPES_H

#include <stdint.h>
#include <sys/types.h>

#ifdef __cplusplus
extern "C" {
#endif

// ** Defines and types from nffile.h
#define IDENTLEN	128
#define IDENTNONE	"none"

typedef struct file_header_s {
	uint16_t	magic;				// magic to recognize nfdump file type and endian type
#define MAGIC 0xA50C

	uint16_t	version;			// version of binary file layout, incl. magic
#define LAYOUT_VERSION_1	1
#define LAYOUT_VERSION_2	2

	uint32_t	flags;				
#define FLAG_NOT_COMPRESSED	 0x0		// records are not compressed
#define FLAG_LZO_COMPRESSED	 0x1		// records are LZO compressed
#define FLAG_ANONYMIZED 	 0x2		// flow data are anonimized 
#define FLAG_CATALOG		 0x4		// has a file catalog record after stat record
#define FLAG_BZ2_COMPRESSED  0x8		// records are BZ2 compressed
// New flags introduced
#define FLAG_LZ4_COMPRESSED  0x10
#define FLAG_LZMA_COMPRESSED 0x20
	uint32_t	NumBlocks;			// number of data blocks in file
	char		ident[IDENTLEN];	// string identifier for this file
} file_header_t;

typedef struct stat_record_s {
	// overall stat
	uint64_t	numflows;
	uint64_t	numbytes;
	uint64_t	numpackets;
	// flow stat
	uint64_t	numflows_tcp;
	uint64_t	numflows_udp;
	uint64_t	numflows_icmp;
	uint64_t	numflows_other;
	// bytes stat
	uint64_t	numbytes_tcp;
	uint64_t	numbytes_udp;
	uint64_t	numbytes_icmp;
	uint64_t	numbytes_other;
	// packet stat
	uint64_t	numpackets_tcp;
	uint64_t	numpackets_udp;
	uint64_t	numpackets_icmp;
	uint64_t	numpackets_other;
	// time window
	uint32_t	first_seen;
	uint32_t	last_seen;
	uint16_t	msec_first;
	uint16_t	msec_last;
	// other
	uint32_t	sequence_failure;
} stat_record_t;

typedef struct data_block_header_s {
	uint32_t	NumRecords;		// number of data records in data block
	uint32_t	size;			// size of this block in bytes without this header
	uint16_t	id;				// Block ID == DATA_BLOCK_TYPE_2
#define DATA_BLOCK_TYPE_1       1
#define DATA_BLOCK_TYPE_2       2
#define Large_BLOCK_Type        3
#define CATALOG_BLOCK           4
	uint16_t	flags;			// 0 - compatibility
								// 1 - block uncompressed
								// 2 - block compressed
} data_block_header_t;

typedef struct L_record_header_s {
    uint32_t    type;
#define CommonRecordV0Type      1
#define ExtensionMapType        2
#define PortHistogramType       3
#define BppHistogramType        4
// TC code - phased out
#define ExporterRecordType      5
#define SamplerRecordype        6
// replaces TC Types
#define ExporterInfoRecordType  7
#define ExporterStatRecordType  8
#define SamplerInfoRecordype    9
// new extended Common Record as intermediate solution to overcome 255 exporters
// requires moderate changes till 1.7
#define CommonRecordType       10

    uint32_t    size;
} L_record_header_t;

// *** end of nffile.h defines and types

typedef enum {
  compressed_none, 
  compressed_lzo,
  compressed_bz2,
  compressed_lz4,
  compressed_lzma,
  compressed_term // terminator: leave as last element
} compression_t;


#ifdef __cplusplus
}  // extern "C"
#endif

#endif

