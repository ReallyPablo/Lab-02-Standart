#include "cpu.hpp"
#include "alu.hpp"
#include <iostream>

DecodedInstruction decode(Byte op) {
    DecodedInstruction inst;
    inst.group = (op >> 4) & 0x0F; 
    inst.index = op & 0x0F;        
    return inst;
}

void dump_regs(const CPU& cpu) {
    std::cout << "PC:" << cpu.pc
              << " A:" << (int)cpu.a
              << " B:" << (int)cpu.b
              << " Z:" << cpu.f.z
              << " N:" << cpu.f.n
              << " C:" << cpu.f.c << '\n';
}

void step(CPU& cpu) {
    Byte op = mem_get(*cpu.mem, cpu.pc);
    DecodedInstruction inst = decode(op); 

    Byte group = inst.group;

    if (group == 0x0) {
        switch (op) {
        case OP_HALT:
            cpu.halted = true;
            cpu.pc += 1;
            break;
        case OP_NOP:
            cpu.pc += 1;
            break;
        default:
            cpu.pc += 1;
            break;
        }
    } else if (group == 0x1) {
        switch (op) {
        case OP_ADD: cpu.a = alu_add(cpu.a, cpu.b, cpu.f); break;
        case OP_SUB: cpu.a = alu_sub(cpu.a, cpu.b, cpu.f); break;
        case OP_AND: cpu.a = alu_and(cpu.a, cpu.b, cpu.f); break;
        case OP_OR:  cpu.a = alu_or(cpu.a, cpu.b, cpu.f);  break;
        case OP_XOR: cpu.a = alu_xor(cpu.a, cpu.b, cpu.f); break;
        case OP_NOT: cpu.a = alu_not(cpu.a, cpu.f);        break;
        case OP_SHL: cpu.a = alu_shl(cpu.a, cpu.f);        break;
        case OP_SHR: cpu.a = alu_shr(cpu.a, cpu.f);        break;
        case OP_INC: cpu.a = alu_inc(cpu.a, cpu.f);        break;
        case OP_DEC: cpu.a = alu_dec(cpu.a, cpu.f);        break;
        default: break;
        }
        cpu.pc += 1;
    } else {
        cpu.pc += 1;
    }
}