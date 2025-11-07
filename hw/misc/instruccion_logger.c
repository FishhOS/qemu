// hw/misc/instruction_logger.c
#include "qemu/osdep.h"
#include "hw/hw.h"
#include "hw/sysbus.h"
#include "qemu/timer.h"
#include "sysemu/sysemu.h"

#define TYPE_INSTRUCTION_LOGGER "instruction-logger"
#define INSTRUCTION_LOGGER(obj) \
    OBJECT_CHECK(InstructionLogger, (obj), TYPE_INSTRUCTION_LOGGER)

typedef struct {
    SysBusDevice parent_obj;
    MemoryRegion iomem;

    char log_buffer[4096][128];
    uint32_t log_head;
    uint32_t log_tail;
    uint32_t log_count;
    
    QemuMutex lock;
} InstructionLogger;

static void instruction_logger_dump(InstructionLogger *s)
{
    printf("\n=== INSTRUCTION LOG ===\n");
    for (uint32_t i = 0; i < s->log_count; i++) {
        uint32_t idx = (s->log_tail + i) % 4096;
        printf("%s\n", s->log_buffer[idx]);
    }
    printf("=== END LOG ===\n");
}

static void handle_monitor_dump(Monitor *mon, const QDict *qdict)
{
    InstructionLogger *s =;
    instruction_logger_dump(s);
}

static void log_instruction(const char *fmt, ...)
{
    InstructionLogger *s = ;
    va_list args;
    
    qemu_mutex_lock(&s->lock);
    
    va_start(args, fmt);
    vsnprintf(s->log_buffer[s->log_head], sizeof(s->log_buffer[0]), fmt, args);
    va_end(args);
    
    s->log_head = (s->log_head + 1) % 4096;
    if (s->log_count < 4096) s->log_count++;
    else s->log_tail = (s->log_tail + 1) % 4096;
    
    qemu_mutex_unlock(&s->lock);
}