#ifndef EFIBLOCKIO_HPP
#define EFIBLOCKIO_HPP

#include "defs/undefix.hpp"
#include "types/untypes.hpp"

struct EFI_BLOCK_IO_MEDIA{
    UINT32 MediaId;

    BOOLEAN RemovableMedia;
    BOOLEAN MediaPresent;

    BOOLEAN LogicalPartition;

    BOOLEAN ReadOnly;
    BOOLEAN WriteCaching;

    UINT32 BlockSize;
    UINT32 IoAlign;

    EFI_LBA LastBlock;
    EFI_LBA LowestAlignedLba;

    UINT32 LogicalBlocksPerPhysicalBlock;
    UINT32 OptimalTransferLengthGranularity;
};

struct EFI_BLOCK_IO_PROTOCOL;

typedef EFI_STATUS (EFIAPI *EFI_BLOCK_RESET)(IN EFI_BLOCK_IO_PROTOCOL* _this, IN BOOLEAN extendedVerification);
typedef EFI_STATUS (EFIAPI *EFI_BLOCK_READ)(IN EFI_BLOCK_IO_PROTOCOL* _this, IN UINT32 mediaId, IN EFI_LBA lba, IN UINTN bufferSize, OUT void* buffer);
typedef EFI_STATUS (EFIAPI *EFI_BLOCK_WRITE)(IN EFI_BLOCK_IO_PROTOCOL* _this, IN UINT32 mediaId, IN EFI_LBA lba, IN UINTN bufferSize, IN void* buffer);
typedef EFI_STATUS (EFIAPI *EFI_BLOCK_FLUSH)(IN EFI_BLOCK_IO_PROTOCOL* _this);

struct EFI_BLOCK_IO_PROTOCOL{
    UINT64 Revision;

    EFI_BLOCK_IO_MEDIA* Media;

    EFI_BLOCK_RESET Reset;
    EFI_BLOCK_READ ReadBlocks;
    EFI_BLOCK_WRITE WriteBlocks;
    EFI_BLOCK_FLUSH FlushBlocks;
};

constexpr EFI_GUID EFI_BLOCK_IO_PROTOCOL_GUID = {0x964e5b21, 0x6459, 0x11d2, {0x8e, 0x39, 0x0, 0xa0, 0xc9, 0x69, 0x72, 0x3b}};

#define BLOCK_IO_PROTOCOL EFI_BLOCK_IO_PROTOCOL_GUID
 
#define EFI_BLOCK_IO_PROTOCOL_REVISION 0x00010000
 
#define EFI_BLOCK_IO_PROTOCOL_REVISION2 0x00020001
 
#define EFI_BLOCK_IO_PROTOCOL_REVISION3 0x0002001F
 
#define EFI_BLOCK_IO_INTERFACE_REVISION EFI_BLOCK_IO_PROTOCOL_REVISION

#endif // EFIBLOCKIO_HPP
