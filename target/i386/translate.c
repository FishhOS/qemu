// target/i386/translate.c 
#include "hw/misc/instruction_logger.h"

static void log_x86_instruction(DisasContext *s, target_ulong pc, 
                               const char *mnemonic, const char *ops)
{
    char timestamp[32];
    int64_t now = qemu_clock_get_ns(QEMU_CLOCK_VIRTUAL);
    snprintf(timestamp, sizeof(timestamp), "[%08lld] ", now / 1000000);
    
    log_instruction("%s0x%08llX: %-8s %s", 
                   timestamp, (long long)pc, mnemonic, ops);
}

static void gen_CLI(DisasContext *s, int ot)
{
    log_x86_instruction(s, s->pc, "cli", "");
}

static void gen_STI(DisasContext *s, int ot)
{
    log_x86_instruction(s, s->pc, "sti", "");
}

static void gen_HLT(DisasContext *s, int ot)
{
    log_x86_instruction(s, s->pc, "hlt", "");
}

static void gen_IN(DisasContext *s, int ot)
{
    log_x86_instruction(s, s->pc, "in", "");
}

static void gen_OUT(DisasContext *s, int ot)
{
    log_x86_instruction(s, s->pc, "out", "");
}