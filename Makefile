LD = lld-link

TARGET = $(OUTDIR)/BOOTX64.EFI
OUTDIR = efi/EFI/BOOT

LDFLAGS = /subsystem:efi_application /entry:_start

OBJS := $(shell find build/CMakeFiles -type f -name '*.o')

all: $(TARGET)

$(OUTDIR):
	mkdir -p $(OUTDIR)

$(TARGET): $(OUTDIR) $(OBJS)
	$(LD) $(OBJS) $(LDFLAGS) /out:$(TARGET)

clean:
	rm -f $(TARGET)
